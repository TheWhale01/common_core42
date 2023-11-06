import { Injectable } from '@nestjs/common';
import { PassportStrategy } from '@nestjs/passport';
import { ExtractJwt, Strategy } from 'passport-jwt';
import { UserService } from 'src/user/user.service';
import { Request } from 'express';

@Injectable()
export class JwtStrategy extends PassportStrategy(Strategy, 'jwt') {
  constructor(private readonly userService: UserService) {
    super({
		jwtFromRequest: ExtractJwt.fromExtractors([
			(request: Request) => {
				const accessToken = request.cookies.access_token;
				return (accessToken);
			},
		]),
      ignoreExpiration: false,
      secretOrKey: process.env.JWT_SECRET,
    });
  }

  async validate(payload: {id: string, email: string}): Promise<any> {
	const user = await this.userService.getByEmail(payload.email);
	return {user};
  }
}