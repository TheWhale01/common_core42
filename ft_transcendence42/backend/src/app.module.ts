import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { DatabaseModule } from './database/database.module';
import { UserModule } from './user/user.module';
import { AuthModule } from './auth/auth.module';
import { ServeStaticModule } from '@nestjs/serve-static';
import { join } from 'path';
import { AppService } from './app.service';
import { AvatarModule } from './avatar/avatar.module';
import { StatsController } from './stats/stats.controller';
import { StatsModule } from './stats/stats.module';
import { MatchController } from './match/match.controller';
import { MatchModule } from './match/match.module';
import { ChatModule } from './chat/chat.module';
import { PongModule } from './pong/pong.module';
import { FriendModule } from './friend/friend.module';

@Module({
  imports: [
		DatabaseModule,
		UserModule,
		AuthModule,
		ServeStaticModule.forRoot({rootPath: join(__dirname, '..', 'qrcode'), serveRoot: '/qrcode',}),
		AvatarModule,
		StatsModule,
		MatchModule,
		ChatModule,
		PongModule,
		FriendModule,
	],
  controllers: [AppController, StatsController, MatchController],
  providers: [AppService]
})
export class AppModule {}

