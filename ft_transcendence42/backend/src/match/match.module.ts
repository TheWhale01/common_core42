import { Module } from '@nestjs/common';
import { MatchService } from './match.service';
import { MatchController } from './match.controller';
import { Match } from './match.entity';
import { TypeOrmModule } from '@nestjs/typeorm';
import { UserModule } from 'src/user/user.module';
import { StatsModule } from 'src/stats/stats.module';

@Module({
  providers: [MatchService],
  controllers: [MatchController],
  imports: [TypeOrmModule.forFeature([Match]), UserModule, StatsModule],
  exports: [MatchService]
})
export class MatchModule {}




