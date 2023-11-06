import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { Friend } from './friend.entity';
import { UserService } from '../user/user.service';
import { Channel } from 'src/chat/entities/channel.entity';
import { ChatService } from 'src/chat/chat.service';
import * as bcrypt from 'bcrypt';
import { User } from 'src/user/user.entity';


export interface friendTab {
	id: number;
	status: string;
	username: string;
	request: number;
	channel: Channel;
}

@Injectable()
export class FriendService {

	constructor(
		@InjectRepository(Friend)
		private friendRepository: Repository<Friend>,
		private userService: UserService,
		private chatService: ChatService,
	) { }

	async addFriend(username: string, sender: number): Promise<string> {
		const friendToAdd = await this.userService.getByName(username);
		if (!friendToAdd)
			return ("Ce nom d'utilisateur n'existe pas !");
		if (friendToAdd.id === sender)
			return ("Vous ne pouvez pas vous ajouter en ami !");
		if (await this.getFriendId(friendToAdd.id, sender))
			return ("Cet utilisateur est déjà dans votre liste d'amis !");
		const user: User = await this.userService.getById(sender);
		if (user.blockList.includes(friendToAdd.id))
			return ("Vous ne pouvez pas ajouter un utilisateur bloqué !");
		const friend = new Friend();
		friend.UserId = sender;
		friend.FriendId = friendToAdd.id;
		friend.Status = 'pending';
		friend.channel = await this.chatService.create(await bcrypt.hash(`${friend.FriendId}_${friend.UserId}`, 8), '', false, friendToAdd, true);
		await this.friendRepository.save(friend);
		return ('');
	}

	async deleteFriend(id1: number, id2: number): Promise<string> {
		let friendship = await this.friendRepository.findOne({ where: { UserId: id1, FriendId: id2 } });
		if (!friendship)
			friendship = await this.friendRepository.findOne({ where: { UserId: id2, FriendId: id1 } });
		if (!friendship)
			return;
		await this.chatService.delete(friendship.channel.name);
		await this.friendRepository.delete({ UserId: id1, FriendId: id2 });
		await this.friendRepository.delete({ UserId: id2, FriendId: id1 });
		return (friendship.channel.name);
	}

	async acceptFriend(id1: number, id2: number): Promise<void> {
		const friendship = await this.friendRepository.findOne({
			where: [
				{ UserId: id1, FriendId: id2 },
				{ UserId: id2, FriendId: id1 },
			],
		});
		if (!friendship)
			return;
		friendship.Status = 'accepted';
		await this.userService.addUserToChannel(friendship.FriendId, friendship.channel.id, '');
		await this.userService.addUserToChannel(friendship.UserId, friendship.channel.id, '');
		await this.friendRepository.save(friendship);
	}

	async getFriendId(
		FriendToAdd: number,
		sender: number,
	): Promise<Friend | null> {
		return await this.friendRepository.findOne({
			where: [
				{ UserId: sender, FriendId: FriendToAdd },
				{ UserId: FriendToAdd, FriendId: sender },
			],
		});
	}

	async getFriendsFromUser(userId: number): Promise<number[]> {
		if (isNaN(userId))
			return ([]);
		const friendships = await this.friendRepository.find({
			where: [
				{ UserId: userId },
				{ FriendId: userId },
			],
		});
		const friends = [];
		for (let friendship of friendships) {
			if (friendship.UserId === userId)
				friends.push(friendship.FriendId);
			else
				friends.push(friendship.UserId);
		}
		return (friends);
	}

	async getFriend(id: number) {
		const friendships = await this.friendRepository.find({
			where: [
				{ UserId: id },
				{ FriendId: id },
			],
		});
		let friendId: number;
		const friends: friendTab[] = [];
		for (let friendship of friendships) {
			if (friendship.UserId == id)
				friendId = friendship.FriendId;
			else
				friendId = friendship.UserId;
			const friend: friendTab = {
				id: friendId,
				status: friendship.Status,
				username: (await this.userService.getById(friendId)).name,
				request: friendship.UserId,
				channel: friendship.channel,
			};
			friends.push(friend);
		}
		return friends;
	}

	async isFriend(username: string, requester: number): Promise<boolean> {
		const friends = await this.getFriend(requester);
		for (var friend of friends) {
			if (friend.username === username)
				return (true);
		}
		return (false);
	}
}