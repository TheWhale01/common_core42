import { Socket } from 'socket.io';
import { Racket } from './racket.interface';

export interface Player {
	socket: Socket;
	score: number;
	user: any;
	roomId: number;
	racket: Racket;
	nbPowerups: number;
}
