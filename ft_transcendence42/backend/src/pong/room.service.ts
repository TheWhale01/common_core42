import { Injectable } from "@nestjs/common";
import { Room, State } from "./interface/room.interface";
import { MatchService } from "src/match/match.service";
import { Mode } from 'src/pong/interface/room.interface';
import { Socket } from "socket.io";
import { Player } from "./interface/player.interface";
import { MatchDto } from "src/match/match.dto";
import { GameService } from "./game.service";
import { PongConstants } from "./interface/constants.interface";
import { StatsService } from "src/stats/stats.service";

@Injectable()
export class RoomService {

	private lastRoomId = 0;
	private roomsMap: Map<Mode, Room[]> = new Map();
	private disconnectedUsers: Map<number, string> = new Map();
	private checkedRooms: Set<Room> = new Set();

	constructor(private readonly matchService: MatchService,
		private readonly statsService: StatsService) {
		this.roomsMap.set(Mode.DEFAULT, []);
		this.roomsMap.set(Mode.ARCADE, []);
		this.roomsMap.set(Mode.RANKED, []);
		this.roomsMap.set(Mode.DUEL_DEFAULT, []);
		this.roomsMap.set(Mode.DUEL_ARCADE, []);
	}

	async checkRoomLoop(gameService: GameService) {
		const keysArray = Array.from(this.roomsMap.keys());
		for (var key of keysArray as Mode[]) {
			for (var room of this.roomsMap.get(key) as Room[]) {
				if (!this.checkedRooms.has(room)) {
					await gameService.checkRoom(room);
					this.checkedRooms.add(room);
				}
			}
		}
	}

	async extractRoom(rooms: Room[]) {
		const filteredRooms = rooms.map(room => {
			const { players, timerInterval, timerTimeout, gameInterval, ...rest } = room;
			const filteredPlayers = players.map(({ socket, ...player }) => player);
			return { ...rest, players: filteredPlayers };
		});
		return filteredRooms;
	}

	async hasDisconnect(email: string): Promise<Object> {
		let roomId: number = -1;
		for (let [key, value] of this.disconnectedUsers.entries()) {
			if (value === email) {
				roomId = key;
				break;
			}
		}
		return ({ status: roomId !== -1, roomId: roomId });
	}

	async getRooms() {
		let res = [];
		const keysArray = Array.from(this.roomsMap.keys());
		for (var key of keysArray) {
			res.push(await this.extractRoom(this.roomsMap.get(key)));
		}
		return (res);
	}

	async getRoomById(id: number) {
		for (let [key, value] of this.roomsMap) {
			const res = value.find(room => room.id === id);
			if (res)
				return (res);
		}
	}

	async createRoom(mode: Mode, id?: number): Promise<Room> {
		const room: Room = {
			id: this.lastRoomId++,
			state: State.QUEUE,
			mode: mode,
			players: [],
			ball: null,
			time: 0,
			canvas: { width: PongConstants.CANVAS_WIDTH, height: PongConstants.CANVAS_HEIGHT },
			timerInterval: null,
			timerTimeout: null,
			gameInterval: null,
			isFinished: false,
			powerups: [],
			isSavingData: false,
		};
		if (id)
			room.id = id;
		this.roomsMap.get(mode).push(room);
		return room;
	}

	async joinRoom(client: Socket, room: Room, player: Player): Promise<Room> {
		if (room.players.length < 2) {
			player.user.stats = await this.statsService.getUserStats(player.user.stats.id);
			room.players.push(player);
			client.data.room = room;
			if (room.players.length === 2) {
				if (room.state === State.QUEUE)
					room.state = State.INIT;
				player.roomId = room.id;
			}
			if (room.players.length === 1)
				client.emit("ids", player.user.id, "");
			return (room);
		}
		else {
			player.roomId = room.id;
			player.user.stats = await this.statsService.getUserStats(player.user.stats.id);
			client.data.room = room;
			client.emit("ids", room.players[0].user.id, room.players[1].user.id);
			return (room);
		}
	}

	async isSocketInsideRoom(room: Room, socketId: string): Promise<Boolean> {
		const playerNames: string[] = room.players.map((player) => player.socket.id);
		return (playerNames.includes(socketId));
	}

	async isEmailInGame(email: string): Promise<Boolean> {
		const keysArray = Array.from(this.roomsMap.keys());
		for (var key of keysArray) {
			for (var room of this.roomsMap.get(key)) {
				if (this.isEmailInsideRoom(room, email))
					return (true);
			}
		}
		return (false);
	}

	async isPlayerInsideRoom(room: Room, player: Player): Promise<Boolean> {
		const playerNames: string[] = room.players.map((player) => player.user.email);
		return (playerNames.includes(player.user.email) && room.players.length === 1);
	}

	async isEmailInsideRoom(room: Room, email: string): Promise<Boolean> {
		const playerNames: string[] = room.players.map((player) => player.user.email);
		return (playerNames.includes(email));
	}

	async duelHandling(client: Socket, player: Player, mode: Mode, id: number) {
		for (var room of this.roomsMap.get(mode) as Room[]) {
			if (room.id === id) {
				if (this.disconnectedUsers.get(room.id))
					this.disconnectedUsers.delete(room.id);
				return (this.joinRoom(client, room, player));
			}
		}
		const newRoom: Room = await this.createRoom(mode, id);
		player.roomId = newRoom.id;
		return (this.joinRoom(client, newRoom, player));
	}

	async searchRoom(client: Socket, player: Player, mode: Mode, id?: any): Promise<Room> {
		if (mode === Mode.DUEL_ARCADE || mode === Mode.DUEL_DEFAULT) {
			return (this.duelHandling(client, player, mode, id));
		}
		if (this.roomsMap.get(mode)) {
			for (var room of this.roomsMap.get(mode) as Room[]) {
				if ((room.id === player.roomId || room.state === State.QUEUE) && !await this.isPlayerInsideRoom(room, player)) {
					if (this.disconnectedUsers.get(room.id))
						this.disconnectedUsers.delete(room.id);
					return (this.joinRoom(client, room, player));
				}
			}
		}
		const newRoom: Room = await this.createRoom(mode);
		player.roomId = newRoom.id;
		return (this.joinRoom(client, newRoom, player));
	}

	async leaveRoomSocket(socketId: string, client: Socket) {
		const keysArray = Array.from(this.roomsMap.keys());
		for (var key of keysArray as Mode[]) {
			for (var room of this.roomsMap.get(key) as Room[]) {
				if (!await this.isSocketInsideRoom(room, socketId))
					continue;
				if (room.players.length === 2 && room.state !== State.ENDGAME) {
					room.state = State.WAITING;
					if (this.disconnectedUsers.get(room.id)) {
						room.state = State.ENDGAME;
					}
					else
						this.disconnectedUsers.set(room.id, client.data.user.email);
				}
				else if (room.players.length === 1) {
					room.state = State.FINAL;
				}
			}
		}
	}

	emitToPlayers(room: Room, event: string, ...args: any[]) {
		room.players[0].socket.emit(event, ...args);
		if (room.players[1])
			room.players[1].socket.emit(event, ...args);
	}

	async endGame(room: Room) {
		if (room.players.length != 2)
			return;
		if (room.timerInterval)
			clearInterval(room.timerInterval);
		const modes: string[] = ["Classique", "Arcade", "Classée", "Duel Classique", "Duel Arcade"];
		const matchDto: MatchDto = {
			player1Id: room.players[0].user["id"], player2Id: room.players[1].user["id"],
			scorePlayer1: room.players[0].score, scorePlayer2: room.players[1].score,
			mode: modes[room.mode], leaverId: -1
		}
		const leaverEmail: string = this.disconnectedUsers.get(room.id);
		if (leaverEmail && room.players[0].user["email"] === leaverEmail)
			matchDto.leaverId = matchDto.player1Id;
		else if (leaverEmail && room.players[1].user["email"] === leaverEmail)
			matchDto.leaverId = matchDto.player2Id;
		if (matchDto.leaverId !== -1) {
			this.emitToPlayers(room, 'userDisco', matchDto.leaverId);
		}
		room.state = State.FINAL;
		return (await this.matchService.createMatch(matchDto, room.mode === Mode.RANKED, room));
	}

	haveUserDisco(roomId: number): Boolean {
		return (this.disconnectedUsers.get(roomId) !== undefined);
	}


	finalGame(room: Room) {
		this.disconnectedUsers.delete(room.id);
		this.roomsMap.set(room.mode, this.roomsMap.get(room.mode).filter((el) => el !== room));
		this.emitToPlayers(room, 'text', "ENDGAME");
		this.checkedRooms.delete(room);
		room.isFinished = true;
	}

	getRoomFromSocket(client: Socket): Room {
		for (var room of this.checkedRooms) {
			const sockets = room.players.map((player) => { return player.socket; });
			if (sockets.includes(client))
				return room
		}
	}

}