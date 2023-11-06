import { IsNotEmpty, IsNumber } from 'class-validator';

export class MatchDto {
	@IsNumber()
	player1Id: number

	@IsNumber()
	player2Id: number

	@IsNumber()
	scorePlayer1: number;

	@IsNumber()
	scorePlayer2: number;

	@IsNotEmpty()
	mode: string

	@IsNumber()
	leaverId: number = -1;
}
