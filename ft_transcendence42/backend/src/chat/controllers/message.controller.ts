import { Controller, Param, Get, Req } from "@nestjs/common";
import { ChatService } from "../chat.service";
import { Message } from "../entities/message.entity";
import { AuthService } from "src/auth/auth.service";

@Controller('message')
export class MessageController {
	constructor(
		private readonly chatService: ChatService,
		private readonly authService: AuthService,
	) {}

	@Get(":channelId/list")
	async getChannelMessages(@Param('channelId') channelId: number, @Req() request: Request): Promise<Message[] | null> {
		const user = await this.authService.getUserFromToken(request['cookies']['access_token']);
		return (await this.chatService.getChannelMessages(user.id, channelId));
	}

	@Get('/count')
	async getCountMessages(@Req() request: Request): Promise<number> {
		const user = await this.authService.getUserFromToken(request['cookies']['access_token']);
		if (!user)
			return (0);
		return (await this.chatService.getCountMessages(user.id));
	}
}