import { Injectable, NotAcceptableException, UnauthorizedException, Req, Res, BadRequestException } from '@nestjs/common';
import { JwtService } from '@nestjs/jwt';
import { UserService } from 'src/user/user.service';
import { AuthLoginDto } from './dtos/auth.dto';
import { User } from 'src/user/user.entity';
import { AuthLogin42Dto } from './dtos/auth42.dto';
import { authenticator } from 'otplib';
import { toDataURL } from 'qrcode';
import { Response } from 'express';
import { ValidationError, validate } from 'class-validator';

@Injectable()
export class AuthService {
	constructor(private usersService: UserService, private jwtService: JwtService) { }

	async getErrorMsg(errors: ValidationError[]): Promise<string> {
		let res: string = "";
		if (errors[0]["property"] === "email")
			res += "Adresse Email ";
		else if (errors[0]["property"] === "password")
			res += "Mot de passe ";
		return (res += "invalide !");
	}

	async getUserObject(authDto: AuthLoginDto, res: Response) {
		if (!authDto["email"].includes("@")) {
			try {
				const email: string = await this.usersService.getEmailByUsername(authDto["email"]);
				authDto["email"] = email;
			}
			catch (error) {
				throw new NotAcceptableException('Utilisateur Introuvable !');
			}
		}
		const errors: ValidationError[] = await validate(new AuthLoginDto(authDto));
		if (errors.length)
			throw new NotAcceptableException(await this.getErrorMsg(errors))
		const tokens: string = await this.login(authDto, res);
		const user: User = await this.usersService.getByEmail(authDto["email"]);
		return { tokens: tokens, user: user };
	}

	async login(authLoginDto: any, @Res() res: Response): Promise<string> {
		const user = await this.validateUser(authLoginDto, res);
		const payload = { username: user.name, email: user.email };
		const access_token = this.jwtService.sign(payload, { expiresIn: '15m' });
		return (access_token);
	}

	async validateUser(authLoginDto: AuthLoginDto, @Res({ passthrough: true }) res): Promise<User> {
		const { email, password } = authLoginDto;
		const user = await this.usersService.getByEmail(email);
		if (!user)
			throw new NotAcceptableException('Utilisateur Introuvable !');
		const validPass = await user.validatePassword(password)
		if (!validPass)
			throw new UnauthorizedException();
		return user;
	}

	async login42(@Req() req, @Res({ passthrough: true }) res, data: AuthLogin42Dto) {
		const user = await this.usersService.getByEmail(data.email);
		if (!user) {
			if (await this.usersService.getByName(data.name))
				throw new NotAcceptableException('User Already Exist !');
			const user = await this.usersService.createUser42(data);
			const payload = { username: user.name, email: user.email };
			res.redirect("http://" + process.env.HOST + ":" + process.env.FRONT_PORT + "/");
			return { access_token: this.jwtService.sign(payload, { expiresIn: '15m' }) };
		}
		if (user.auth2f === true) {
			const payload = { username: user.name, email: user.email };
			res.redirect("http://" + process.env.HOST + ":" + process.env.FRONT_PORT + "/verif");
			return { access_token: this.jwtService.sign(payload, { expiresIn: '15m' }) };
		}
		else {
			const payload = { username: user.name, email: user.email };
			res.redirect("http://" + process.env.HOST + ":" + process.env.FRONT_PORT + "/");
			return { access_token: this.jwtService.sign(payload, { expiresIn: '15m' }) };
		}
	}

	async generate2FASecret(user: User) {
		const secret = authenticator.generateSecret();
		const otpAuthUrl = authenticator.keyuri(user.email, "ft_transcendence", secret);
		await this.usersService.set2faSecret(secret, user.id);
		return { secret, otpAuthUrl: otpAuthUrl };
	}

	async generateQrCode(url: string) {
		return (toDataURL(url));
	}

	isValidCode(user: User, code: string): boolean {
		return (authenticator.verify({ token: code, secret: user.auth2fSecret }));
		// return (true);
	}

	async getTokenByUser(user: User): Promise<string> {
		if (!user)
			return ("");
		const payload = { id: user.id, email: user.email };
		const token: string = this.jwtService.sign(payload, { expiresIn: '15m' });
		return (token);
	}

	async findOrCreate(loginDto: AuthLogin42Dto): Promise<User> {
		try {
			const user = await this.usersService.getByEmail(loginDto.email);
			if (!user)
				return await this.usersService.createUser42(loginDto);
			return (user);
		}
		catch (error) {
			throw new NotAcceptableException('findOrCreate');
		}
	}

	async getUserFromToken(token: string): Promise<Partial<User> | undefined> {
		if (!token)
			return (undefined);
		const email: string = this.jwtService.decode(token)["email"];
		const user: User = await this.usersService.getByEmail(email);
		return (this.usersService.getPartialUser(user));
	}
}