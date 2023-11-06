import { Body, Controller, Get, Param, Patch, Post, Query, Req, Res, UseGuards, } from '@nestjs/common';
import { Response, Request } from 'express';
import { UserService } from './user.service';
import { JwtAuthGuard } from '../auth/guards/jwt-auth.guard'
import { ChatService } from 'src/chat/chat.service';

@Controller('user')
export class UserController {
	constructor(
		private readonly userService: UserService,
		private readonly chatService: ChatService
	) { }

	@Get()
	async getUsers() {
		return (await this.userService.getAllUsers());
	}

	@Get('/me')
	@UseGuards(JwtAuthGuard)
	async me(@Req() req: Request) {
		if (!req["user"]["user"]) {
			return ({ error: true });
		}
		const id = req["user"]["user"]["id"];
		const user = await this.userService.getById(id);
		return (this.userService.getPartialUser(user));
	}

	@Get('/leaderboard')
	async getLeaderboardData() {
		return await this.userService.getLeaderBoard();
	}

	@Get(":name")
	async getUserByName(@Param('name') name: string) {
		const user = await this.userService.getByName(name)
		if (!user)
			return (null);
		return (this.userService.getPartialUser(user));
	}

	@Post('/setname')
	@UseGuards(JwtAuthGuard)
	async setUsername(@Req() req, @Body() body, @Res() res: Response) {
		if (! await this.userService.updateUsername(req["user"]["user"]["email"], body["username"]))
			res.statusCode = 403;
		else
			res.statusCode = 201;
		res.send();
	}

	@Get("/id/:id")
	async getUserById(@Param('id') id: number) {
		const user = await this.userService.getById(id);
		return (this.userService.getPartialUser(user));
	}

	@Post('/:userId/channels/:channelId/add')
	async addUserToChannel(@Param('userId') userId: number, @Param('channelId') channelId: number, @Body('password') password: string) {
		try {
			const channel = await this.chatService.getById(channelId);
			if (channel?.isPrivate)
				throw new Error("Vous ne pouvez pas faire d'operations dans un channel privé.");
			await this.userService.addUserToChannel(userId, channelId, password);
		}
		catch (e) {
			return {
				ok: false,
				message: e.message,
			};
		}
		return {
			ok: true,
			message: 'user added',
		};
	}

	@Post('/:userId/channels/:channelId/remove')
	async removeUserFromChannel(@Param('userId') userId: number, @Param('channelId') channelId: number) {
		const channel = await this.chatService.getById(channelId);
		if (channel?.isPrivate)
			return ({
				ok: false,
				message: "Vous ne pouvez pas faire d'operations dans un channel privé.",
			});
		await this.userService.removeUserFromChannel(userId, channelId);
		return ({
			ok: true,
			message: 'User successfully removed from channel',
		});
	}

	@Post('/:userId/channels/:channelId/kick')
	async kickUserFromChannel(@Param('userId') userId: number, @Param('channelId') channelId: number) {
		try {
			const channel = await this.chatService.getById(channelId);
			if (channel?.isPrivate)
				throw new Error("Vous ne pouvez pas faire d'operations dans un channel privé.");
			await this.userService.kickUserFromChannel(userId, channelId);
		}
		catch (e) {
			return {
				ok: false,
				message: e.message,
			}
		}
		return {
			ok: true,
			message: 'Utilisateur exclu !',
		}
	}

	@Post('/:userId/channels/:channelId/ban')
	async banUserFromChannel(@Param('userId') userId: number, @Param('channelId') channelId: number) {
		try {
			const channel = await this.chatService.getById(channelId);
			if (channel?.isPrivate)
				throw new Error("Vous ne pouvez pas faire d'operations dans un channel privé.");
			await this.userService.banUserFromChannel(userId, channelId);
		}
		catch (e) {
			return {
				ok: false,
				message: e.message,
			}
		}
		return {
			ok: true,
			message: 'Utilisateur banni !',
		}
	}

	@Post('/:userId/channels/:channelId/unban')
	async UnbanUserFromChannel(@Param('userId') userId: number, @Param('channelId') channelId: number) {
		await this.userService.UnbanUserFromChannel(userId, channelId);
	}

	@Get('/:userId/joinedChannels')
	async getJoinedChannels(@Param('userId') userId: number) {
		if (isNaN(userId))
			return ([]);
		return (await this.userService.getJoinedChannels(userId));
	}

	@Post('/block/blocked')
	async blockUser(@Body('userId') userId: number, @Body('blockId') blockId: number) {
		if (isNaN(userId) || isNaN(blockId))
			return;
		return (await this.userService.blockUser(userId, blockId));
	}

	@Get('/:userId/block/blocklist')
	async getBlockList(@Param('userId') userId: number) {
		if (isNaN(userId))
			return ([]);
		return (await this.userService.getBlockList(userId));
	}

	@Patch('/block/unblock')
	async unblockUser(@Body('userId') userId: number, @Body('unblockId') unblockId: number) {
		if (isNaN(userId))
			return;
		return (await this.userService.unblockUser(userId, unblockId));
	}

	@Post('/isBlocked')
	async isUserBlocked(@Body('userId') userId: number, @Body('blockId') blockId: number) {
		if (isNaN(userId))
			return (false);
		return ((await this.userService.getBlockList(userId)).includes(blockId));
	}
}
