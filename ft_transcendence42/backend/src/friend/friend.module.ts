import { Module } from '@nestjs/common';
import { FriendController } from './friend.controller';
import { FriendService } from './friend.service';
import { TypeOrmModule } from '@nestjs/typeorm';
import { User } from 'src/user/user.entity';
import { Friend } from 'src/friend/friend.entity';
import { UserModule } from 'src/user/user.module';
import { ChatModule } from 'src/chat/chat.module';

@Module({
	imports: [TypeOrmModule.forFeature([User, Friend]), UserModule, ChatModule],
	controllers: [FriendController],
	providers: [FriendService],
	exports: [FriendService]
})
export class FriendModule {}
