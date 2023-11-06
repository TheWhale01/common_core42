import {
	SubscribeMessage,
	WebSocketGateway,
	OnGatewayInit,
	WebSocketServer,
	OnGatewayConnection,
	OnGatewayDisconnect,
} from '@nestjs/websockets';
import { Logger } from '@nestjs/common';
import { Socket, Server } from 'socket.io';
import { ChatService } from './chat.service';
import { State } from 'src/user/user.entity';
import { FriendService } from 'src/friend/friend.service';
import { UserService } from 'src/user/user.service';

interface Mute {
	userId: number,
	time: number,
}

interface StateInfo {
	client_socket: Socket;
	state: State;
	displayUpdate: boolean;
}

interface InviteInfo {
	userId: number;
	mode: string;
}

@WebSocketGateway({
	cors: {
		origin: true,
	}
})
export class ChatGateway implements OnGatewayInit, OnGatewayConnection, OnGatewayDisconnect {
	constructor(
		private readonly chatService: ChatService,
		private readonly friendService: FriendService,
		private readonly userService: UserService,
	) { }
	@WebSocketServer() server: Server;
	private logger: Logger = new Logger('ChatGateway');
	private clients: Map<number, StateInfo> = new Map<number, StateInfo>;
	private invites: Map<number, InviteInfo> = new Map<number, InviteInfo>; // invited -> sender
	private muteds: Map<number, Mute[]> = new Map<number, Mute[]>;

	private searchMute(userId: number, muted_list: Mute[]): Mute {
		if (!muted_list)
			return (undefined);
		for (let muted of muted_list) {
			if (muted.userId === userId)
				return (muted);
		}
		return (undefined);
	}

	@SubscribeMessage('message')
	async handleMessage(client: Socket, payload: any) {
		let { channelId, text, sender } = payload;
		channelId = Number(channelId);
		text = String(text);
		sender = Number(sender);
		const users = await this.chatService.getUsersInChannel(channelId);
		if (!users)
			return (payload);
		const muted = this.muteds.get(channelId);
		const mute_instance = this.searchMute(sender, muted);
		if (!mute_instance) {
			for (let user of users) {
				if (!user.blockList.includes(sender))
					this.clients.get(user.id)?.client_socket.emit('message', payload);
			}
			await this.chatService.addMessageToChannel({ channelId, text, sender });
			this.logger.log(`message received: ${text}`);
		}
		return (payload);
	}

	@SubscribeMessage('mute')
	async handleMute(client: Socket, payload: any) {
		let { userId, channelId, time } = payload;
		userId = Number(userId);
		channelId = Number(channelId);
		time = Number(time);
		const target = this.clients.get(userId);
		const channel = await this.chatService.getById(channelId);
		const channelOwner = await this.chatService.getChannelOwner(channelId);
		const data = {
			started: true,
			channelName: channel.name,
			id: channelId,
			error: false,
			message: '',
		}
		if (time <= 0) {
			data.error = true;
			data.message = 'Entrez un nombre strictement positif.';
			target?.client_socket.emit('mute', data);
			return;
		}
		if (channel.isPrivate) {
			data.error = true;
			data.message = "Vous ne pouvez pas faire d'operations sur un channel privé.";
			target?.client_socket.emit('mute', data);
			return;
		}
		if (userId === channelOwner.id) {
			data.error = true;
			data.message = 'Vous ne pouvez pas mute le owner du channel.';
			target?.client_socket.emit('mute', data);
			return;
		}
		if (client.data.userId !== channelOwner.id) {
			data.error = true;
			data.message = 'Seul le owner du channel peut mute.';
			target?.client_socket.emit('mute', data);
			return;
		}
		let users = (await this.chatService.getUsersInChannel(channelId));
		const usersId = users.map((user) => user.id);
		if (!usersId.includes(userId)) {
			data.error = true;
			data.message = 'Cet utilisateur n\'est pas dans le channel !';
			client.emit('mute', data);
			return;
		}
		const mute_instance = {
			userId: userId,
			time: time * 1000,
		};
		if (!this.muteds.get(channelId)) {
			let array: Mute[] = [];
			array.push(mute_instance);
			this.muteds.set(channelId, array);
		}
		else {
			const arr = this.muteds.get(channelId);
			for (var el of arr) {
				if (el.userId === userId) {
					data.error = true;
					data.message = 'Cet utilisateur est déjà mute !';
					client.emit('mute', data);
					return;
				}
			}
			this.muteds.get(channelId).push(mute_instance);
		}
		let muted = this.muteds.get(channelId);
		target?.client_socket.emit('mute', data);
		setTimeout(() => {
			muted.splice(muted.indexOf(mute_instance), 1);
			data.started = false;
			target?.client_socket.emit('mute', data);
		}, mute_instance.time);
	}

	@SubscribeMessage('getMute')
	async handleGetMute(client: Socket, payload: number) {
		let response = [];
		const channels = await this.userService.getJoinedChannels(payload);
		for (let channel of channels) {
			const muted = this.muteds.get(channel.id);
			const mute_instance = this.searchMute(payload, muted);
			if (mute_instance)
				response.push(channel.id);
		}
		this.clients.get(payload).client_socket.emit('getMute', response);
	}

	@SubscribeMessage('getStatus')
	async handleGetStatus(client: Socket, payload: number) {
		const friends = await this.friendService.getFriendsFromUser(Number(payload));
		if (!friends)
			return;
		for (let friend of friends) {
			const user = this.clients.get(payload);
			if (!user)
				this.clients.get(friend)?.client_socket.emit('getStatus', { userId: payload, state: State.OFFLINE });
			else
				this.clients.get(friend)?.client_socket.emit('getStatus', { userId: payload, state: user.state });
		}
	}

	@SubscribeMessage('getClientStatus')
	getClientStatus(client: Socket, payload: number) {
		return (client.emit('getClientStatus', this.clients.get(payload).state));
	}

	@SubscribeMessage('setStatus')
	async setStatus(client: Socket, payload: any) {
		this.clients.set(payload[0], { client_socket: client, state: payload[1], displayUpdate: false });
		await this.handleGetStatus(client, payload[0]);
	}

	@SubscribeMessage('kick')
	handleKick(client: Socket, payload: any) {
		this.clients.get(Number(payload[1])).client_socket.emit('kick', payload);
		return (payload);
	}

	@SubscribeMessage('changeAdmin')
	handleChangeAdmin(client: Socket, payload: any) {
		this.server.emit('changeAdmin', payload);
		return (payload);
	}

	@SubscribeMessage('changeOwner')
	async changeOwner(client: Socket, payload: any) {
		await this.chatService.setOwner(payload.channel_id, payload.new_owner_id);
		this.server.emit('changeOwner', payload);
	}

	async afterInit(server: Server) {
		this.logger.log('Websocket server has started up !');
	}

	handleDisconnect(client: Socket) {
		this.logger.log(`Client disconnected: ${client.id}`);
		if (!this.clients.get(client.data.userId)) {
			client.disconnect();
			return;
		}

		this.clients.get(client.data.userId).displayUpdate = true;
		if (this.clients.get(client.data.userId)?.displayUpdate) {
			setTimeout(() => {
				if (this.clients.get(client.data.userId)?.displayUpdate) {
					this.handleGetStatus(client, client.data.userId);
					this.clients.delete(client.data.userId);
				}
			}, 1000);
		}
		client.disconnect();
	}

	async handleConnection(client: Socket, ...args: any[]) {
		client.data.userId = Number(client.handshake.query['userId']);
		if (!this.clients.get(client.data.userId))
			this.clients.set(client.data.userId, { client_socket: client, state: State.ONLINE, displayUpdate: false });
		else
			this.clients.get(client.data.userId).client_socket = client;
		client.data.canInvite = true;
		await this.handleGetStatus(client, client.data.userId);
		this.logger.log(`Client connected: ${client.id}`);
	}

	@SubscribeMessage('pongInvite')
	async sendPongInvite(client: Socket, payload: any) {
		if (this.invites.get(payload[1]) || this.invites.get(payload[0]) || !client.data.canInvite ||
			this.clients.get(payload[1]).state !== State.ONLINE)
			return;
		this.clients.get(payload[0])?.client_socket.emit('displayInvite', true, payload[2], payload[3]);
		this.clients.get(payload[1])?.client_socket.emit('displayInvite', false, payload[2], payload[3]);
		this.invites.set(payload[1], { userId: payload[0], mode: payload[3] });
		client.data.canInvite = false;
	}

	@SubscribeMessage('handlingInvite')
	async pongInviteHandler(client: Socket, payload: any) {
		const inviteInfo: InviteInfo = this.invites.get(client.data.userId);
		if (payload) {
			this.clients.get(inviteInfo.userId).client_socket.emit('joinGame',
				inviteInfo.userId, inviteInfo.mode);
			setTimeout(() => {
				this.clients.get(client.data.userId).client_socket.emit('joinGame',
					inviteInfo.userId, inviteInfo.mode);
			}, 25);
		}
		if (inviteInfo)
			this.clients.get(inviteInfo.userId).client_socket.emit('closeInvite');
		if (this.clients.get(client.data.userId))
			this.clients.get(client.data.userId).client_socket.emit('closeInvite');
		this.invites.delete(client.data.userId);
		client.data.canInvite = true;
	}

	@SubscribeMessage('refreshFriendList')
	async refreshFriendList(client: Socket, payload: string) {
		const target = await this.userService.getByName(payload);
		this.clients.get(target.id).client_socket.emit('updateFriendList');
	}

	@SubscribeMessage('refreshFriendListId')
	async refreshFriendListId(client: Socket, payload: number) {
		const target = await this.userService.getById(payload);
		this.clients.get(target?.id)?.client_socket.emit('updateFriendList');
	}

	@SubscribeMessage('hideChan')
	async hideChan(client: Socket, payload: string[]) {
		const target = await this.userService.getById(parseInt(payload[0]));
		this.clients.get(target?.id)?.client_socket.emit('hideChan', payload[1]);
	}

	@SubscribeMessage('addFriendNotif')
	async displayFriendNotif(client: Socket, payload: string) {
		const target = await this.userService.getByName(payload);
		if (!target.blockList.includes(client.data.userId))
			this.clients.get(target?.id)?.client_socket.emit('friendNotif');
	}

	@SubscribeMessage('setAdmin')
	async setAdmin(client: Socket, payload: any[]) {
		this.clients.get(payload[0]).client_socket.emit('upgradeAdmin', (await this.chatService.getById(payload[1])).name);
	}

	@SubscribeMessage('unsetAdmin')
	async unsetAdmin(client: Socket, payload: any[]) {
		this.clients.get(payload[0]).client_socket.emit('downgradeAdmin', (await this.chatService.getById(payload[1])).name);
	}
}