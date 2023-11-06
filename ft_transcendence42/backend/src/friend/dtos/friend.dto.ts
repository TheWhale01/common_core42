import { IsNotEmpty } from 'class-validator';

export class friendDto {
	@IsNotEmpty()
	username: string;
	sender: number;
}