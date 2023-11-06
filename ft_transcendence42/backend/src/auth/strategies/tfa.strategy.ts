import { Injectable } from '@nestjs/common';
import { PassportStrategy } from '@nestjs/passport';
import { ExtractJwt, Strategy } from 'passport-jwt';
import { UserService } from 'src/user/user.service';
import { Request } from 'express';

@Injectable()
export class Auth2fStrategy extends PassportStrategy(Strategy, 'tfa') {
	constructor(private readonly userService: UserService) {
		super({
			jwtFromRequest: ExtractJwt.fromExtractors([
				(request: Request) => {
					const auth2f_token = request.cookies.auth2f_token;
					return (auth2f_token);
				},
			]),
			ignoreExpiration: false,
			secretOrKey: process.env.JWT_SECRET,
		});
	}

	async validate(payload: { username: string, email: string }): Promise<any> {
		const user = await this.userService.getByEmail(payload.email);
		return { user };
	}
}