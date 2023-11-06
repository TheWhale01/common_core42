import { Module } from '@nestjs/common';
import { ChatGateway } from './chat.gateway';
import { TypeOrmModule } from '@nestjs/typeorm';
import { Channel } from './entities/channel.entity';
import { Message } from './entities/message.entity';
import { ChatController } from './controllers/chat.controller';
import { ChatService } from './chat.service';
import { MessageController } from './controllers/message.controller';
import { User } from 'src/user/user.entity';
import { UserService } from 'src/user/user.service';
import { FriendService } from 'src/friend/friend.service';
import { Friend } from 'src/friend/friend.entity';
import { AuthService } from 'src/auth/auth.service';
import { JwtService } from '@nestjs/jwt';

@Module({
  imports: [TypeOrmModule.forFeature([Channel, Message, User, Friend])],
  providers: [ChatGateway, ChatService, UserService, FriendService, AuthService, JwtService],
  controllers: [MessageController, ChatController],
  exports: [ChatService],
})
export class ChatModule {}
