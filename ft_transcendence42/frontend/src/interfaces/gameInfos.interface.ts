import { ball } from "@/interfaces/ball.interface.ts";
import { paddle } from "@/interfaces/paddle.interface.ts";

export interface gameInfos{
	ball: ball,
	pad1: paddle,
	pad2: paddle,
	powerups: [],
}