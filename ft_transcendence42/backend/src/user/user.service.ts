import { Injectable, NotAcceptableException, ValidationError } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { User } from './user.entity';
import { AuthRegisterDto } from 'src/auth/dtos/auth.dto';
import { AuthLogin42Dto } from 'src/auth/dtos/auth42.dto';
import { StatsDetail } from 'src/stats/stats.entity';
import { validate } from 'class-validator';
import { Channel } from 'src/chat/entities/channel.entity';
import * as bcrypt from 'bcrypt';

@Injectable()
export class UserService {
	constructor(
		@InjectRepository(User)
		private usersRepository: Repository<User>,
		@InjectRepository(Channel)
		private channelRepository: Repository<Channel>,
	) { }

	async getErrorMsg(errors: ValidationError[]): Promise<string> {
		let res: string = "";
		if (errors[0]["property"] === "email")
			res += "Adresse Email ";
		else if (errors[0]["property"] === "password")
			res += "Mot de passe ";
		return (res += "invalide !");
	}

	getPartialUser(user: User): Partial<User> {
		return {
			id: user.id,
			email: user.email,
			name: user.name,
			avatarLink: user.avatarLink,
			stats: user.stats,
		}
	}

	getAllUsers(): Promise<string[]> {
		const names = this.usersRepository
			.createQueryBuilder('entity')
			.select('entity.name', 'name')
			.getRawMany();
		return names.then(names => names.map((res) => res.name))
	}

	async createUser(user: AuthRegisterDto): Promise<User> {
		const errors: ValidationError[] = await validate(user);
		if (errors.length)
			throw new NotAcceptableException(await this.getErrorMsg(errors));
		if (await this.getByEmail(user.email) != null)
			throw new NotAcceptableException('Email déjà utilisé !');
		if (await this.getByName(user.name) != null)
			throw new NotAcceptableException('Pseudo déjà utilisé !');
		const newUser = await this.usersRepository.create(user);
		newUser.stats = new StatsDetail();
		await this.usersRepository.save(newUser);
		this.updatePictureLink(user.email);
		return newUser;
	}

	async createUser42(data: AuthLogin42Dto): Promise<User> {
		let i: number = 1;
		while (await this.getByName(data.name) != null)
			data.name += i++;
		data.password = Math.random().toString(36).slice(-8);
		const user = await this.usersRepository.create(data);
		user.stats = new StatsDetail();
		await this.usersRepository.save(user);
		return user;
	}

	async getByEmail(email: string): Promise<User> {
		const retUser = await this.usersRepository.findOne({ where: { email: email } });
		return (retUser);
	}

	async getByName(name: string): Promise<User> {
		const retUser = await this.usersRepository.findOne({ where: { name: name } });
		return (retUser);
	}

	async getById(id: number): Promise<User> {
		const retUser = await this.usersRepository.findOne({ where: { id: id } });
		return (retUser);
	}

	async set2faSecret(secret: string, id: number) {
		const user = await this.getById(id);
		user.auth2fSecret = secret;
		await this.usersRepository.save(user);
	}

	async enable2fa(id: number) {
		const user = await this.getById(id);
		user.auth2f = true;
		this.usersRepository.save(user);
	}

	async disable2fa(id: number) {
		const user = await this.getById(id);
		user.auth2f = false;
		this.usersRepository.save(user);
	}

	async updatePictureLink(email: string, link: string = "http://" + process.env.HOST + ":3000/avatar/default.png") {
		const user = await this.getByEmail(email);
		user.avatarLink = link;
		await this.usersRepository.save(user);
	}

	async updateUsername(email: string, username: string) {
		const user = await this.getByEmail(email);
		if (await this.getByName(username) != null)
			return (false);
		user.name = username;
		await this.usersRepository.save(user);
		return (true);
	}

	async saveUser(user: Partial<User>) {
		await this.usersRepository.save(user);
	}

	async getEmailByUsername(username: string): Promise<string> {
		const user = (await this.usersRepository.findOne({ where: { name: username } }));
		if (!user)
			throw new NotAcceptableException('User not found');
		return (user.email);
	}

	async addUserToChannel(userId: number, channelId: number, password: string) {
		const user = await this.usersRepository.findOne({ where: { id: userId }, relations: ['channels'] });
		const channel = await this.channelRepository.findOne({ where: { id: channelId } });
		if (password === undefined)
			return;

		for (let banned of channel.bannedUsers) {
			if (banned == userId)
				throw new Error('Utilisateur banni.');
		}
		if (channel.protected && await bcrypt.compare(password, channel.password) === false)
			throw new Error('Mauvais mot de passe.');
		user.channels.push(channel);
		await this.usersRepository.save(user);
	}

	async removeUserFromChannel(userId: number, channelId: number) {
		const user = await this.usersRepository.findOne({ where: { id: userId }, relations: ['channels'] });
		const channel = await this.channelRepository.findOne({ where: { id: channelId }, relations: ['owner'] });
		user.channels = user.channels.filter((c) => c.id !== channel.id);
		let users = await this.usersRepository.createQueryBuilder('user')
			.leftJoinAndSelect('user.channels', 'channel')
			.where('channel.id = ' + channel.id)
			.getMany();
		const usersId: number[] = users.map((user) => user.id);
		let isInChan: boolean = false;
		for (let id of usersId) {
			if (id == userId) {
				isInChan = true;
				break;
			}
		}
		if (!isInChan)
			return;
		if (!(users.length - 1)) {
			await this.channelRepository.delete(channel.id);
			return (null);
		}
		if (user.id === channel.owner.id) {
			if (channel.admins.length) {
				let index = Math.floor(Math.random() * (channel.admins.length));
				channel.owner = await this.getById(channel.admins[index]);
			}
			else {
				let index = Math.floor(Math.random() * (users.length));
				while (users[index].id === user.id)
					index = Math.floor(Math.random() * (users.length));
				channel.owner = users[index];
			}
			await this.channelRepository.save(channel);
		}
		return (await this.usersRepository.save(user));
	}

	async kickUserFromChannel(userId: number, channelId: number) {
		const user = await this.usersRepository.findOne({ where: { id: userId } });
		const channel = await this.channelRepository.findOne({ where: { id: channelId }, relations: ['owner'] });
		const channel_users = await this.usersRepository.createQueryBuilder('user')
			.leftJoinAndSelect('user.channels', 'channel')
			.where('channel.id = ' + channel.id)
			.getMany();
		if (!user)
			return;
		if (user.id === channel.owner.id)
			throw new Error('You cannot kick the owner of the channel.');
		for (let channel_user of channel_users)
			if (channel_user.id === user.id)
				return (await this.removeUserFromChannel(user.id, channel.id));
		throw new Error("Cet utilisateur n'est pas dans le channel !");
	}

	async banUserFromChannel(userId: number, channelId: number) {
		const user = await this.usersRepository.findOne({ where: { id: userId } });
		const channel = await this.channelRepository.findOne({ where: { id: channelId }, relations: ['owner'] });
		if (!user || !channel)
			return;
		if (user.id === channel.owner.id)
			throw new Error('Vous ne pouvez pas bannir le propriétaire du channel !');
		for (let ban of channel.bannedUsers) {
			if (ban == user.id) {
				throw new Error('Cet utilisateur est déjà banni !');
			}
		}
		await this.removeUserFromChannel(userId, channelId);
		channel.bannedUsers.push(user.id);
		await this.channelRepository.save(channel);
	}

	async UnbanUserFromChannel(userId: number, channelId: number) {
		const user = await this.usersRepository.findOne({ where: { id: userId } });
		const channel = await this.channelRepository.findOne({ where: { id: channelId } });

		if (!user || !channel || channel.isPrivate)
			return;
		channel.bannedUsers = channel.bannedUsers.filter((toRemove) => toRemove !== user.id);
		await this.channelRepository.save(channel);
	}

	async getJoinedChannels(userId: number): Promise<Channel[] | null> {
		const user = await this.usersRepository.findOne({ where: { id: userId }, relations: ['channels'] });
		if (!user)
			return (null);
		return (user.channels);
	}

	async blockUser(userId: number, blockId: number) {
		const user = await this.usersRepository.findOne({ where: { id: userId } });
		if (!user.blockList.includes(blockId, 0)) {
			user.blockList.push(blockId);
			await this.usersRepository.save(user);
		}
	}

	async unblockUser(userId: number, unblockId: number) {
		const user = await this.usersRepository.findOne({ where: { id: userId } });
		if (user.blockList.includes(unblockId, 0)) {
			user.blockList = user.blockList.filter((elem) => elem != unblockId);
			await this.usersRepository.save(user);
		}
	}

	async getBlockList(userId: number) {
		if (!userId)
			return ([]);
		let user = await this.usersRepository.findOne({ where: { id: userId } });
		return (user.blockList);
	}

	async getLeaderBoard() {
		const users = (await this.usersRepository.find()).map((user) => this.getPartialUser(user));
		users.sort((a, b) => b.stats.mmr - a.stats.mmr);
		return (users);
	}
}
