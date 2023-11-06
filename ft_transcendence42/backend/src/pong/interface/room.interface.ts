import { Player } from "./player.interface";
import { Powerup } from "./powerup.interface";

export class Coords {
	x:	number;
	y:	number;
}

export class Ball {
	constructor(){
		this.position = {x: 300, y: 300};
		this.speed = 1;
		this.direction  = {x: 1, y: 1};
		this.lastHit = -1;
	}

	position:	Coords;
	direction:	Coords;
	speed:		number;
	radius:		number;
	lastHit: number;
}

export class Canvas {
	width: number;
	height: number;
}

export enum State {
	QUEUE = 0,
	INIT,
	COOLDOWN,
	PLAY,
	RESET,
	WAITING,
	ENDGAME,
	FINAL
}

export enum Mode {
	DEFAULT = 0,
	ARCADE,
	RANKED,
	DUEL_DEFAULT,
	DUEL_ARCADE,
}

export class Room {
	id: number;
	state: State;
	mode: Mode;
	players: Array<Player>;
	ball: Ball = undefined;
	time: number;
	timerInterval: NodeJS.Timeout;
	timerTimeout: NodeJS.Timeout;
	gameInterval: NodeJS.Timeout;
	canvas: Canvas;
	isFinished: boolean;
	isSavingData: boolean;
	powerups: Array<Powerup>;
}