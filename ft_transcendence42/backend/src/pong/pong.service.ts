import { Injectable } from '@nestjs/common';
import { Socket } from 'socket.io';
import { Ball, Mode, Room, State } from './interface/room.interface';
import { Racket } from './interface/racket.interface';
import { Effect, Powerup } from './interface/powerup.interface';

import { PongConstants } from './interface/constants.interface';
import { UserService } from 'src/user/user.service';

@Injectable()
export class PongGame {

	constructor(private readonly userService: UserService) { }

	randomPos() {
		const randomNumber = Math.random();
		const sign = Math.random() < 0.5 ? -1 : 1;
		return sign * (0.5 + randomNumber * 0.5);
	}

	resetBall(room: Room) {
		room.ball.radius = 10;
		room.ball.position.x = PongConstants.CANVAS_WIDTH / 2;
		room.ball.position.y = PongConstants.CANVAS_HEIGHT / 2;
		room.ball.direction.x = this.randomPos();
		room.ball.direction.y = (Math.random() - 0.5);
		room.ball.speed = PongConstants.MIN_BALL_SPEED;
		room.ball.lastHit = -1;
	}

	resetRacket(room: Room) {
		if (room.players[0]) {
			room.players[0].racket.pos.x = (PongConstants.RACKET_WIDTH);
			room.players[0].racket.pos.y = (PongConstants.CANVAS_HEIGHT / 2) - (PongConstants.RACKET_HEIGHT / 2);
			room.players[0].racket.size = PongConstants.RACKET_HEIGHT;
			room.players[0].racket.width = PongConstants.RACKET_WIDTH;
			if (room.players[0].racket.effectTimeout) {
				clearTimeout(room.players[0].racket.effectTimeout);
				room.players[0].racket.effectTimeout = null;
			}
		}
		if (room.players[1]) {
			room.players[1].racket.pos.x = (PongConstants.CANVAS_WIDTH - (PongConstants.RACKET_WIDTH * 2));
			room.players[1].racket.pos.y = (PongConstants.CANVAS_HEIGHT / 2) - (PongConstants.RACKET_HEIGHT / 2);
			room.players[1].racket.size = PongConstants.RACKET_HEIGHT;
			room.players[1].racket.width = PongConstants.RACKET_WIDTH;
			if (room.players[1].racket.effectTimeout) {
				clearTimeout(room.players[1].racket.effectTimeout);
				room.players[1].racket.effectTimeout = null;
			}
		}
	}

	racketHandling(racket: Racket, room: Room, dy: number) {
		if (this.hasRacketIntersect(room.ball, racket))
			return;
		const canMove: boolean = ((dy > 0 && racket.pos.y + racket.size < room.canvas.height - room.ball.radius) || (dy < 0 && racket.pos.y > room.ball.radius));
		racket.pos.y += dy * Number(canMove);
	}

	getRacketDirection(keyUp: boolean, keyDown: boolean): number {
		return (keyUp && !keyDown ? -1 : keyDown && !keyUp ? 1 : 0);
	}

	updateRacket(client: Socket, room: Room, keyUp: boolean, keyDown: boolean) {
		if (client === room.players[0].socket) {
			this.racketHandling(room.players[0].racket, room, this.getRacketDirection(keyUp, keyDown) * room.players[0].racket.speed);
		} else if (client === room.players[1].socket) {
			this.racketHandling(room.players[1].racket, room, this.getRacketDirection(keyUp, keyDown) * room.players[1].racket.speed);
		}
	}

	racketBallCollision(room: Room, racket: Racket, playerHit: number) {
		if (room.ball.lastHit === playerHit)
			return;
		room.ball.lastHit = playerHit;
		const offset = (room.ball.position.y + room.ball.radius - racket.pos.y) / (racket.size + room.ball.radius)
		const angle = (1 / 4) * Math.PI * (2 * offset - 1);
		room.ball.direction.x *= -1;
		room.ball.direction.y = Math.sin(angle);
		if (room.ball.speed != PongConstants.SPEED_BALL_POWERUP)
			room.ball.speed = Math.min(room.ball.speed += 0.5, PongConstants.MAX_BALL_SPEED);
		if (playerHit === 0) {
			room.ball.position.x = room.players[0].racket.pos.x + room.players[0].racket.width + room.ball.radius + 2;
		}
		else {
			room.ball.position.x = room.players[1].racket.pos.x - room.ball.radius - 2;
		}
	}

	hasRacketIntersect(ball: Ball, racket: Racket): boolean {
		const distX = Math.abs(ball.position.x - racket.pos.x - racket.width / 2);
		const distY = Math.abs(ball.position.y - racket.pos.y - racket.size / 2);
		if (distX > (racket.width / 2 + ball.radius))
			return (false);
		if (distY > (racket.size / 2 + ball.radius))
			return (false);
		if (distX <= (racket.width / 2))
			return (true);
		if (distY <= (racket.size / 2))
			return (true);
		const dx = distX - racket.width / 2;
		const dy = distY - racket.size / 2;
		return (dx * dx + dy * dy <= ball.radius * ball.radius);
	}

	hasPowerupIntersect(ball: Ball, powerup: Powerup): boolean {
		const distX = Math.abs(ball.position.x - powerup.pos.x - powerup.radius / 2);
		const distY = Math.abs(ball.position.y - powerup.pos.y - powerup.radius / 2);
		if (distX > (powerup.radius / 2 + ball.radius))
			return (false);
		if (distY > (powerup.radius / 2 + ball.radius))
			return (false);
		if (distX <= (powerup.radius / 2))
			return (true);
		if (distY <= (powerup.radius / 2))
			return (true);
		const dx = distX - powerup.radius / 2;
		const dy = distY - powerup.radius / 2;
		return (dx * dx + dy * dy <= ball.radius * ball.radius);
	}

	hasPowerup2Intersect(powerup1: Powerup, powerup2: Powerup): boolean {
		return powerup1.pos.x <= (powerup2.pos.x + powerup2.radius) && (powerup1.pos.x + powerup1.radius) >= powerup2.pos.x &&
			powerup1.pos.y <= (powerup2.pos.y + powerup2.radius) && (powerup1.pos.y + powerup1.radius) >= powerup2.pos.y;
	}

	updateBall(room: Room) {
		const next = {
			x: room.ball.direction.x * room.ball.speed + room.ball.radius,
			y: room.ball.direction.y * room.ball.speed + room.ball.radius,
		}
		if (room.ball.position.y + next.y >= room.canvas.height
			|| room.ball.position.y + next.y <= room.ball.radius * 2) {
			room.ball.direction.y *= -1;
		}

		if (this.hasRacketIntersect(room.ball, room.players[0].racket))
			this.racketBallCollision(room, room.players[0].racket, 0);

		else if (this.hasRacketIntersect(room.ball, room.players[1].racket))
			this.racketBallCollision(room, room.players[1].racket, 1);

		else {
			room.ball.position.x += room.ball.direction.x * room.ball.speed;
			room.ball.position.y += room.ball.direction.y * room.ball.speed;
		}
		let indexPlayer = -1;
		if (room.ball.position.x > room.canvas.width)
			indexPlayer = 0;
		else if (room.ball.position.x < room.ball.radius)
			indexPlayer = 1;

		if (indexPlayer != -1) {
			room.players[indexPlayer].score++;
			room.state = State.COOLDOWN;
			this.resetBall(room);
			this.resetRacket(room);
			return;
		}
	}

	activatePowerup(powerup: Powerup, room: Room) {
		powerup.activatedBy = Number(room.ball.direction.x < 0);
		let racket: Racket = room.players[powerup.activatedBy].racket;
		room.players[powerup.activatedBy].user.stats.totalPowerups += 1;
		this.userService.saveUser(room.players[powerup.activatedBy].user);
		switch (powerup.effect) {
			case Effect.BIG_PADDLE: {
				racket.pos.y -= PongConstants.BIG_PAD_VALUE;
				racket.size += PongConstants.BIG_PAD_VALUE * 2;
				racket.effectTimeout = setTimeout(() => {
					racket.size = PongConstants.RACKET_HEIGHT;
				}, PongConstants.BIG_PADDLE_DURATION)
			}
				break;
			case Effect.LIL_PADDLE: {
				racket = room.players[Number(!(powerup.activatedBy))].racket;
				racket.pos.y += PongConstants.LIL_PAD_VALUE;
				const oldSize = racket.size;
				racket.size -= PongConstants.LIL_PAD_VALUE * 2;
				if (racket.size <= 0)
					racket.size = oldSize;
				racket.effectTimeout = setTimeout(() => {
					racket.size = PongConstants.RACKET_HEIGHT;
				}, PongConstants.LIL_PADDLE_DURATION)
			}
				break;
			case Effect.SPEEDY_BALL: {
				room.ball.speed += 2;
				setTimeout(() => {
					if (room.ball.speed === PongConstants.SPEED_BALL_POWERUP)
						room.ball.speed -= 2;
				}, PongConstants.SPEEDY_BALL_DURATION)
			}
				break;
		}
	}

	powerupsHandling(room: Room) {
		for (let i = 0; i < room.powerups.length; i++) {
			if (this.hasPowerupIntersect(room.ball, room.powerups[i])) {
				this.activatePowerup(room.powerups[i], room);
				room.powerups.splice(i, 1);
			}
		}
	}

	updateGame(client: Socket, room: Room, updatePhysics: boolean = true) {
		client.emit('time', this.formatTime(room.time, room.mode))
		if (updatePhysics){
			this.updateBall(room);
			this.updateRacket(client, room, client.data.keyUp, client.data.keyDown);
			this.powerupsHandling(room);
		}
		const { ["effectTimeout"]: timeOut1, ...racket1 } = room.players[0].racket;
		const { ["effectTimeout"]: timeOut2, ...racket2 } = room.players[1].racket;

		client.emit("updateBall", room.ball);
		client.emit("updatePads", racket1, racket2);
		client.emit("updatePowerups", room.powerups);
		client.emit("updateGame");
	}

	async initGame(room: Room) {
		if (!room.ball) {
			room.ball = new Ball();
			this.resetBall(room);
		}

		room.players[0].score = 0;
		if (!room.players[0].racket)
			room.players[0].racket = new Racket()

		if (room.players[1]) {
			room.players[1].score = 0;
			if (!room.players[1].racket)
				room.players[1].racket = new Racket()
		}

		if (room.players[1] && room.players[1].racket)
			this.resetRacket(room);
		room.canvas.width = PongConstants.CANVAS_WIDTH;
		room.canvas.height = PongConstants.CANVAS_HEIGHT;
	}

	formatTime(total: number, mode: Mode): string {
		let time;
		if (mode !== Mode.RANKED)
			time = PongConstants.GAME_DURATION - total;
		else
			time = total;
		time = Math.max(time, 0);
		const minutes = Math.floor(time / 60);
		const seconds = time % 60;
		const formattedMinutes = String(minutes).padStart(2, "0");
		const formattedSeconds = String(seconds).padStart(2, "0");
		return `${formattedMinutes}:${formattedSeconds}`;
	}

	async startTimer(room: Room) {
		if (room.players.length != 2) {
			return;
		}
		room.timerInterval = setInterval(() => {
			room.time++;
			room.players[0].socket.emit('time', this.formatTime(room.time, room.mode));
			room.players[1].socket.emit('time', this.formatTime(room.time, room.mode));
		}, 1000);
		if (room.mode !== Mode.RANKED) {
			room.timerTimeout = setTimeout(() => {
				room.state = State.ENDGAME;
				room.players[0].socket.emit('time', this.formatTime(room.time + 1, room.mode));
				room.players[1].socket.emit('time', this.formatTime(room.time + 1, room.mode));
				clearInterval(room.timerInterval);
			}, (PongConstants.GAME_DURATION - room.time) * 1000);
		}
	}

	randInt(min: number, max: number): number {
		return Math.floor(Math.random() * (max - min + 1) + min)
	}

	isValidPowerupPos(powerup: Powerup, room: Room): Powerup {
		let iteration = 0;
		let hasCollide = true;
		while (hasCollide && iteration < 20) {
			iteration++;
			powerup.pos = {
				x: this.randInt(200, room.canvas.width - 200),
				y: this.randInt(100, room.canvas.height - 100)
			};
			hasCollide = false;
			for (let power of room.powerups) {
				hasCollide = hasCollide || this.hasPowerup2Intersect(power, powerup) || this.hasPowerupIntersect(room.ball, power);
			}
		}
		if (iteration === 20)
			powerup = undefined;
		return (powerup);
	}

	generatePowerup(room: Room): Powerup | undefined {
		const possibilities = [{ name: "Grande Raquette", effect: Effect.BIG_PADDLE },
		{ name: "Petite Raquette", effect: Effect.LIL_PADDLE },
		{ name: "Balle Rapide", effect: Effect.SPEEDY_BALL }];
		const choice = possibilities[this.randInt(0, 2)];
		const res: Powerup = {
			name: choice.name,
			effect: choice.effect,
			activatedBy: -1,
			pos: { x: -1, y: -1 },
			radius: 64,
		}
		return (this.isValidPowerupPos(res, room));
	}

	async powerupsInit(room: Room) {
		if (room.mode != Mode.ARCADE && room.mode != Mode.DUEL_ARCADE)
			return;
		const it = setInterval(() => {
			if (room.state === State.FINAL)
				clearInterval(it);
			if (room.time % 5 === 3) {
				const power = this.generatePowerup(room);
				if (power)
					room.powerups.push(power);
			}
		}, 1000)
	}

}