import { Injectable } from '@nestjs/common';
import { PassportStrategy } from '@nestjs/passport';
import { Strategy } from 'passport-42';
import { AuthService } from '../auth.service';
import { AuthLogin42Dto } from '../dtos/auth42.dto';

@Injectable()
export class FortyTwoStrategy extends PassportStrategy(Strategy) {
  constructor(private readonly authService: AuthService) {
    super({
      clientID: process.env.FORTYTWO_ID,
      clientSecret: process.env.FORTYTWO_SECRET,
      callbackURL: "http://"+process.env.HOST+":3000/auth/42/callback",
	  profileFields: {
		'id': function (obj) { return String(obj.id); },
		'name': 'login',
		'email': 'email',
		'avatarLink': function (obj) { return String(obj.image.link); }
	  }
    });
  }

  async validate(accessToken: string, refreshToken: string, profile: AuthLogin42Dto){
		return await this.authService.findOrCreate(profile);
  }
}

