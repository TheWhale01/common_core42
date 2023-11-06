import { Controller, Get, Req, UseGuards } from '@nestjs/common';
import { PongGame } from './pong.service';
import { JwtAuthGuard } from 'src/auth/guards/jwt-auth.guard';
import { User } from 'src/user/user.entity';
import { Room } from './interface/room.interface';
import { RoomService } from './room.service';

@Controller('pong')
export class PongController {
	constructor(private pongService: PongGame, private roomService: RoomService) { }

	@Get()
	async getAllRooms() {
		return await this.roomService.getRooms();
	}

	@Get('/status')
	@UseGuards(JwtAuthGuard)
	async getStatus(@Req() req) {
		const user: User = req["user"]["user"];
		if (!user)
			return;
		const statusObject = await this.roomService.hasDisconnect(user["email"]);
		const room: Room = await this.roomService.getRoomById(statusObject["roomId"]);
		if (room)
			return { disconnect: statusObject["status"], mode: room.mode, id: room.id };
		else
			return { disconnect: false, mode: -1 };
	}
}
