import { Module } from '@nestjs/common';
import { AuthService } from './auth.service';
import { AuthController } from './auth.controller';
import { UserModule } from 'src/user/user.module';
import { PassportModule } from '@nestjs/passport';
import { JwtModule } from '@nestjs/jwt';
import { ConfigModule, ConfigService } from '@nestjs/config';
import { FortyTwoStrategy } from './strategies/42.strategy';
import { JwtStrategy } from './strategies/jwt.strategy';
import { Auth2fStrategy } from './strategies/tfa.strategy';

@Module({
	imports: [
		UserModule,
		PassportModule,
		JwtModule.registerAsync({
		  imports: [ConfigModule],
		  useFactory: async () => ({
			secret: process.env.JWT_SECRET,
			signOptions: { expiresIn: "14400s" }
		  }),
		  inject: [ConfigService],
		}),
	  ],
  controllers: [AuthController],
  providers: [AuthService, JwtStrategy, FortyTwoStrategy, Auth2fStrategy],
  exports:[AuthService]
})
export class AuthModule {}
