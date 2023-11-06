import { Controller, Post, Body, Delete, Get, Query, Patch, Param } from '@nestjs/common';
import { FriendService } from './friend.service';
import { friendDto } from './dtos/friend.dto';

@Controller('friend')
export class FriendController {
	constructor(private friendService: FriendService) { }

	@Post('/add')
	async addFriend(@Body() friendDto: friendDto) {
		return await this.friendService.addFriend(friendDto.username, friendDto.sender);
	}

	@Patch('/accept')
	async acceptFriend(@Query('id1') id1: number, @Query('id2') id2: number) {
		return await this.friendService.acceptFriend(id1, id2);
	}

	@Delete('/delete')
	async deleteFriend(@Query('id1') id1: number, @Query('id2') id2: number) {
		return await this.friendService.deleteFriend(id1, id2);
	}

	@Get('/:id/list')
	async getFriend(@Param('id') id: number) {
		if (isNaN(id))
			return ([]);
		return await this.friendService.getFriend(id);
	}

	@Post('/isFriend')
	async isFriend(@Body() friendDto: friendDto) {
		return await this.friendService.isFriend(friendDto.username, friendDto.sender);
	}
}
