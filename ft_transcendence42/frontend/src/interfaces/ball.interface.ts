import { pos } from "@/interfaces/pos.interface.ts";

export interface ball{
	position: pos,
	speed: number,
	direction: pos,
	lastHit: number,
	radius: number
}