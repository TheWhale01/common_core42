import { IsEmail, IsNotEmpty, Length } from 'class-validator';

export class AuthLoginDto {
	constructor(body){
		this.email = body["email"];
		this.password = body["password"];
	}

	@IsEmail()
	@IsNotEmpty()
	email: string;

	@IsNotEmpty()
	password: string;
}

export class AuthRegisterDto {
	constructor(body){
		this.email = body["email"];
		this.password = body["password"];
		this.name = body["name"];
	}

	@IsEmail()
	@IsNotEmpty()
	email: string;

	@IsNotEmpty()
	password: string;

	@IsNotEmpty()
	@Length(3, 20)
	name: string;
}