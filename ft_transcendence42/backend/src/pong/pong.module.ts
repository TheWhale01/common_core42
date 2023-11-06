import { Module } from '@nestjs/common';
import { PongGame } from './pong.service';
import { PongGateway } from './pong.gateway';
import { AuthModule } from 'src/auth/auth.module';
import { PongController } from './pong.controller';
import { MatchModule } from 'src/match/match.module';
import { UserModule } from 'src/user/user.module';
import { RoomService } from './room.service';
import { GameService } from './game.service';
import { StatsService } from 'src/stats/stats.service';
import { StatsModule } from 'src/stats/stats.module';
import { TypeOrmModule } from '@nestjs/typeorm';
import { StatsDetail } from 'src/stats/stats.entity';

@Module({
	providers: [PongGateway, GameService, RoomService, StatsService, PongGame],
	imports: [TypeOrmModule.forFeature([StatsDetail]), AuthModule, StatsModule, MatchModule, UserModule,],
	controllers: [PongController],
})
export class PongModule { }