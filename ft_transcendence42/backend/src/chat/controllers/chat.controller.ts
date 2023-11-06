import { Controller, Get, Post, Body, Param } from "@nestjs/common";
import { ChatService } from "../chat.service";
import { User } from "src/user/user.entity";

@Controller('chat')
export class ChatController {
	constructor(private readonly chatService: ChatService) {}

	@Get('/list')
	getChannels() {
		return (this.chatService.getAll());
	}

	@Get('/:name')
	async getByName(@Param('name') name: any) {
		let channel = null;
		if (!isNaN(name))
			channel = await this.chatService.getById(name);
		else {
			if (Array.from(name)[0] != '#')
				name = '#' + name;
			channel = await this.chatService.getByName(name);
		}
		return (channel);
	}

	@Post('/create')
	async create(@Body('name') name: string, @Body('password') password: string, @Body('creator') creator: User) {
		if (Array.from(name)[0] != '#')
			name = '#' + name;
		let channel;
		try {channel = await this.chatService.create(name, password, (password !== ''), creator);}
		catch {return (null);}
		return {
			message: 'channel created',
			channel
		};
	}

	@Post('/delete')
	async delete(@Body('name') name: string) {
		if (Array.from(name)[0] != '#')
			name = '#' + name;
		this.chatService.delete(name);
	}

	@Get('/:id/owner')
	async getOwner(@Param('id') id: number) {
		return (await this.chatService.getChannelOwner(id));
	}

	@Get('/:id/getUsers')
	async getUsersInChannel(@Param('id') id: number) {
		return (await this.chatService.getUsersInChannel(id));
	}

	@Post('/:id/addAdmin/:userId')
	async addAdmin(@Param('id') id: number, @Param('userId') userId: number) {
		try {await this.chatService.addAdminInChannel(id, userId);}
		catch (e) {
			return {
				ok: false,
				message: e.message,
			}
		}
		return {
			ok: true,
			message: 'New admin added',
		}
	}

	@Post('/:id/removeAdmin/:userId')
	async removeAdmin(@Param('id') id: number, @Param('userId') userId: number) {
		try {await this.chatService.removeAdminInChannel(id, userId)}
		catch (e) {
			return {
				ok: false,
				message: e.message,
			}
		}
		return {
			ok: true,
			message: 'admin removed from channel',
		}
	}

	@Post('/:channelId/:userId/removePassword')
	async removePassword(@Param('userId') userId: number, @Param('channelId') channelId: number) {
		try {await this.chatService.removePassword(userId, channelId);}
		catch (e) {
			return {
				ok: false,
				message: e.message,
			};
		}
		return {
			ok: true,
			message: 'Le mot de passe a été retiré !',
		};
	}

	@Get('/:channelId/getAdmins')
	async getAdmins(@Param('channelId') channelId: number) {
		return (await this.chatService.getAdmins(channelId));
	}

	@Post('/:channelId/:userId/changePassword')
	async changePassword(@Param('userId') userId: number, @Param('channelId') channelId: number, @Body('password') password: string) {
		try {await this.chatService.changePassword(userId, channelId, password);}
		catch (e) {
			return {
				ok: false,
				message: e.message,
			};
		}
		return {
			ok: true,
			message: 'Le mot de passe a été changé !',
		};
	}

	@Get('/:channelId/isUserInChannel/:userId')
	async isUserInChannel(@Param('channelId') channelId: number, @Param('userId') userId: number) {
		return (await this.chatService.isUserInChannel(channelId, userId));
	}

	@Get('/:channelId/isUserBan/:userId')
	async isUserBan(@Param('channelId') channelId: number, @Param('userId') userId: number) {
		return (await this.chatService.isUserBan(channelId, userId));
	}
}