import { Injectable, } from '@nestjs/common';
import { PongGame } from './pong.service';
import { RoomService } from './room.service';
import { Mode, Room, State } from './interface/room.interface';
import { Socket } from 'socket.io';
import { PongConstants } from './interface/constants.interface';
import { Powerup } from './interface/powerup.interface';


interface GameVar {
	needUpdate: boolean;
	countDown: number;
	cooldown: number;
};

@Injectable()
export class GameService {
	private infosMap: Map<number, GameVar> = new Map<number, GameVar>;

	constructor(private readonly pongGame: PongGame, private readonly roomService: RoomService) {
		setInterval(async () => {
			await this.roomService.checkRoomLoop(this);
		}, 200);
	};

	async checkRoom(room: Room) {
		if (room.isFinished)
			return;
		if (!this.infosMap.get(room.id) && room.players.length === 2) {
			this.infosMap.set(room.id, { needUpdate: false, countDown: 0, cooldown: 0 } as GameVar)
			await this.playGame(room);
		}
		let gameVars: GameVar = this.infosMap.get(room.id);
		switch (room.state) {
			case State.INIT: {
				this.roomService.emitToPlayers(room, 'time', this.pongGame.formatTime(room.time, room.mode));
				room.state = State.COOLDOWN;
			}
				break;
			case State.COOLDOWN: {
				room.powerups = [] as Powerup[];
				this.pongGame.updateGame(room.players[0].socket, room, false);
				this.pongGame.updateGame(room.players[1].socket, room, false);

				if (gameVars.needUpdate) {
					gameVars.needUpdate = false;
					this.pongGame.resetBall(room);
					this.pongGame.updateGame(room.players[0].socket, room, false);
					this.pongGame.updateGame(room.players[1].socket, room, false);
					this.roomService.emitToPlayers(room, "updateScore", room.players[0].score, room.players[1].score);
				}
				if (room.timerInterval) {
					clearInterval(room.timerInterval);
					clearTimeout(room.timerTimeout);
				}
				if (gameVars.cooldown < (1000 / PongConstants.GAME_TICK) * 2)
					gameVars.cooldown++;
				else {
					gameVars.cooldown = 0;
					room.state = State.PLAY;
					this.pongGame.startTimer(room);
					gameVars.needUpdate = true;
				}
			}
				break;
			case State.WAITING: {
				if (room.timerInterval) {
					clearInterval(room.timerInterval);
					clearTimeout(room.timerTimeout);
					room.timerInterval = null;
				}

				this.roomService.emitToPlayers(room, 'text', 'WAITING');
				gameVars.countDown++;
				if (!this.roomService.haveUserDisco(room.id)) {
					room.state = State.INIT;
					gameVars.countDown = 0;
				}
				if (gameVars.countDown > (1000 / PongConstants.GAME_TICK) * 5) {
					room.state = State.ENDGAME;
				}
			}
				break;

			case State.ENDGAME: {
				clearInterval(room.timerInterval);
				this.roomService.emitToPlayers(room, 'text', "ENDGAME");
				await this.roomService.endGame(room);
			}
				break;

			case State.FINAL: {
				this.infosMap.delete(room.id);
				this.roomService.finalGame(room);
			}
				break;

			case State.PLAY: {
				gameVars.countDown = 0;
				gameVars.cooldown = 0;
				this.pongGame.updateGame(room.players[0].socket, room);
				this.pongGame.updateGame(room.players[1].socket, room);
				if (room.mode === Mode.RANKED && (room.players[0].score === PongConstants.WIN_SCORE_VALUE || room.players[1].score === PongConstants.WIN_SCORE_VALUE)) {
					this.roomService.emitToPlayers(room, "updateScore", room.players[0].score, room.players[1].score);
					room.state = State.ENDGAME;
				}
			}
				break;

			case State.QUEUE: {
				this.roomService.emitToPlayers(room, 'text', "QUEUEING");
			}
				break;

			default:
				break;
		}
		if (!room.isFinished) {
			setTimeout(async () => {
				await this.checkRoom(room);
			}, PongConstants.GAME_TICK)
		}
	}

	async keyHandling(client: Socket) {
		var keyUp: boolean = false;
		var keyDown: boolean = false;
		client.on('arrowUpdate', (data) => {
			if (data === "arrowUp")
				keyUp = true;
			else if (data === "stopArrowUp")
				keyUp = false;
			if (data === "arrowDown")
				keyDown = true;
			else if (data === "stopArrowDown")
				keyDown = false;
			client.data.keyDown = keyDown;
			client.data.keyUp = keyUp;
		});
	}

	async playGame(room: Room) {
		await this.pongGame.initGame(room);
		await this.pongGame.startTimer(room);
		await this.pongGame.powerupsInit(room);
		this.roomService.emitToPlayers(room, "ids", room.players[0].user.id, room.players[1].user.id)
	}

}