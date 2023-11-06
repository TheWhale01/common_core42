import { Inject, Injectable, UseInterceptors } from "@nestjs/common";
import { Channel } from "./entities/channel.entity";
import { InjectRepository } from "@nestjs/typeorm";
import { Repository, getConnection } from "typeorm";
import { Message } from "./entities/message.entity";
import { User } from "src/user/user.entity";
import * as bcrypt from 'bcrypt';

@Injectable()
export class ChatService {
	constructor(
		@InjectRepository(Channel)
		private channelRepository: Repository<Channel>,
		@InjectRepository(Message)
		private messageRepository: Repository<Message>,
		@InjectRepository(User)
		private userRepository: Repository<User>,
	) { }

	getAll(): Promise<Channel[]> {
		return (this.channelRepository.find());
	}

	getById(id: number): Promise<Channel | null> {
		return (this.channelRepository.findOneBy({ id }));
	}

	getByName(name: string): Promise<Channel | null> {
		return (this.channelRepository.findOneBy({ name }));
	}

	async create(name: string, password: string, protect: boolean, creator: User, isPrivate: boolean = false): Promise<Channel | null> {
		if (name.match('/^\s*$/'))
			throw new Error('wrong name format.');
		if (await this.getByName(name) !== null)
			return (null);
		const channel = new Channel();
		channel.name = name;
		channel.password = (protect ? await bcrypt.hash(password, 8) : '');
		channel.protected = protect;
		channel.owner = creator
		channel.isPrivate = isPrivate;
		const createdChannel = await this.channelRepository.save(channel);
		return (createdChannel);
	}

	async delete(name: string) {
		let rm = await this.getByName(name);
		if (rm == null)
			return;
		this.channelRepository.delete({ id: rm.id });
	}

	async addMessageToChannel(msg: { channelId: number, text: string, sender: number }) {
		const { channelId, text, sender } = msg;
		const channel = await this.channelRepository.findOne({ where: { id: channelId } });
		if (!channel)
			return (null);
		let messages = await this.messageRepository.find({ where: { channel: channelId } });
		const senderUser = await this.userRepository.createQueryBuilder('user')
			.leftJoinAndSelect('user.channels', 'channels')
			.where('user.id = ' + sender)
			.andWhere('channels.id = ' + channelId)
			.getOne();
		if (!senderUser)
			return (null);
		const message = new Message();
		message.text = text;
		message.channel = channel.id;
		message.sender = senderUser.id;
		const savedMessage = await this.messageRepository.save(message);
		messages.push(savedMessage);
		const user = await this.userRepository.findOne({ where: { id: sender }, relations: ['stats'] });
		user.stats.totalMessages++;
		await this.userRepository.save(user);
		await this.channelRepository.save(channel);
		return (savedMessage);
	}

	async getChannelMessages(userId: number, channelId: number): Promise<Message[] | null> {
		const user = await this.userRepository.findOne({ where: { id: userId } });
		const channel = await this.channelRepository.findOne({ where: { id: channelId } });
		if (!user || !channel)
			return (null);
		let messages: Message[];
		if (user.blockList.length) {
			messages = await this.messageRepository.createQueryBuilder('message')
				.select(['message.id', 'message.sender', 'message.text'])
				.where(`message.channel = ${channel.id}`)
				.andWhere(`(message.sender NOT IN (:...blockList))`, { blockList: user.blockList })
				.orderBy('message.id', 'ASC')
				.getRawMany()
		}
		else {
			messages = await this.messageRepository.createQueryBuilder("message")
				.select(['message.id', 'message.sender', 'message.text'])
				.where(`message.channel = ${channel.id}`)
				.orderBy('message.id', 'ASC')
				.getRawMany();
		}
		return (messages);
	}

	async getChannelOwner(channelId: number): Promise<User | null> {
		const channel = await this.channelRepository.findOne({ where: { id: channelId }, relations: ['owner'] });
		if (!channel)
			return (null);
		return (channel.owner);
	}

	async getUsersInChannel(channelId: number): Promise<User[] | null> {
		const channel = await this.channelRepository.findOne({ where: { id: channelId } });
		if (!channel)
			return (null);
		const users = await this.userRepository.createQueryBuilder('user')
			.leftJoinAndSelect('user.channels', 'channel')
			.where('channel.id = ' + channel.id)
			.getMany();
		if (!users)
			return (null);
		return (users);
	}

	async addAdminInChannel(channelId: number, userId: number): Promise<Channel> {
		const channel = await this.channelRepository.findOne({ where: { id: channelId }, relations: ['owner'] });
		const user = await this.userRepository.findOne({ where: { id: userId } });

		if (!channel)
			throw new Error("Could not find channel.");
		if (!user)
			throw new Error("Could not find user.");
		if (user.id === channel.owner.id)
			throw new Error("Cet utilisateur est le propriétaire de ce channel !");
		if (channel.bannedUsers.includes(user.id))
			throw new Error("Cet utilisateur est banni de ce channel !");
		if (channel.admins.includes(user.id))
			throw new Error("Cet utilisateur est déjà admin de ce channel !");
		channel.admins.push(user.id);
		return (await this.channelRepository.save(channel));
	}

	async removeAdminInChannel(channelId: number, userId: number): Promise<Channel> {
		const channel = await this.channelRepository.findOne({ where: { id: channelId }, relations: ['owner'] });
		const user = await this.userRepository.findOne({ where: { id: userId } });

		if (!channel)
			throw new Error("Could not find channel.");
		if (!user)
			throw new Error("Could not find user.");
		if (!channel.admins.includes(user.id))
			throw new Error("Cet utilisateur n'est pas admin de ce channel !");
		for (let admin of channel.admins) {
			if (admin === user.id) {
				channel.admins.splice(channel.admins.indexOf(user.id), 1);
				return (await this.channelRepository.save(channel));
			}
		}
	}

	async removePassword(userId: number, channelId: number) {
		const user = await this.userRepository.findOne({ where: { id: userId } });
		const channel = await this.channelRepository.findOne({ where: { id: channelId }, relations: ['owner'] });

		if (!user)
			throw new Error('Could not find user.');
		if (!channel)
			throw new Error("Could not find channel.");
		if (!channel.protected)
			throw new Error("Channel is already not protected.");
		if (user.id !== channel.owner.id)
			throw new Error('User is not the owner of the channel');
		channel.protected = false;
		channel.password = '';
		return (await this.channelRepository.save(channel));
	}

	async changePassword(userId: number, channelId: number, password: string) {
		const user = await this.userRepository.findOne({ where: { id: userId } });
		const channel = await this.channelRepository.findOne({ where: { id: channelId }, relations: ['owner'] });

		if (!user)
			throw new Error('Could not find user.');
		if (!channel)
			throw new Error("Could not find channel.");
		if (user.id !== channel.owner.id)
			throw new Error('User is not the owner of the channel');
		channel.protected = true;
		channel.password = await bcrypt.hash(password, 8);
		return (await this.channelRepository.save(channel));
	}

	async getAdmins(channelId: number): Promise<number[]> {
		const channel = await this.channelRepository.findOne({ where: { id: channelId } });
		if (!channel)
			return (undefined);
		return (channel.admins);
	}

	async setOwner(channelId: number, userId: number): Promise<Channel> {
		const channel = await this.channelRepository.findOne({ where: { id: channelId }, relations: ['owner'] });
		const user = await this.userRepository.findOne({ where: { id: userId } });

		if (!channel || !user)
			return (undefined);
		channel.owner = user;
		if (channel.admins.includes(user.id)) {
			for (let admin of channel.admins) {
				if (admin === user.id) {
					channel.admins.splice(channel.admins.indexOf(user.id), 1);
					break;
				}
			}
		}
		return (await this.channelRepository.save(channel));
	}

	async isUserInChannel(channelId: number, userId: number): Promise<boolean> {
		const user = await this.userRepository.findOne({ where: { id: userId } });
		const channel = await this.channelRepository.findOne({ where: { id: channelId } });
		if (!user || !channel)
			return (false);
		const result = await this.userRepository.createQueryBuilder('user')
			.innerJoinAndSelect('user.channels', 'channel', `channel.id = ${channel.id}`)
			.where(`user.id = ${user.id}`)
			.getOne();
		return (!!result);
	}

	async getCountMessages(userId: number): Promise<number> {
		const user = await this.userRepository.findOne({ where: { id: userId }, relations: ['stats'] });
		if (!user)
			return (0);
		return (user.stats.totalMessages);
	}

	async isUserBan(channelId: number, userId: number): Promise<boolean> {
		const channel = await this.channelRepository.findOne({ where: { id: channelId } });
		for (let id of channel.bannedUsers) {
			if (id == userId)
				return (true);
		}
		return (false);
	}

	async getBanList(channelId: number): Promise<number[]> {
		const channel = await this.channelRepository.createQueryBuilder('channel')
			.leftJoinAndSelect('channel.bannedUsers', 'bannedUsers')
			.where('channel.id = :channelId', { channelId })
			.getOne();
		return (channel.bannedUsers);
	}
}
