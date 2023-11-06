<script lang="ts">
import { defineComponent } from 'vue';
import ProfilCell from './ProfilCell.vue';
import BlockListCell from './BlockListCell.vue';
import type { Channel } from '@/interfaces/channel.interface';
import type { Message } from '@/interfaces/message.interface';
import type { friendTab } from '@/interfaces/friendTab.interface';

export default defineComponent({
	components: {
		ProfilCell,
		BlockListCell
	},
	props: ['updateTimestamp', 'socket', 'friendTimestamp'],
	data() {
		return {
			friends: [] as friendTab[],
			blockList: [] as number[],
			sender: -1 as number,
			block: false as boolean,
			print: 0 as number,
			dataLoaded: false,
			selectedFriend: {} as friendTab,
		};
	},

	computed:{
		getFriendRequest(){
			let number = 0;
			for (let friend of this.friends) {
				if (friend.request !== this.sender && friend.status === 'pending' && !this.blockList.includes(friend.id))
					number++;
			}
			return (number);
		},

		emptyMessage(){
			return (this.print === 1 ? "Vous n'avez pas de demande d'amis !" : "Vous n'avez pas encore ajouté d'amis !");
		}
	},

	async mounted() {
		this.sender = (await (await fetch('http://' + import.meta.env.VITE_HOST + ':3000/user/me', { credentials: 'include' })).json())['id'];
		await this.fetchBlockList();
		await this.fetchFriends();
		this.dataLoaded = true;
	},

	methods: {
		async fetchFriends() {
			const response = await fetch("http://" + import.meta.env.VITE_HOST + ":3000/friend/" + this.sender + "/list", { credentials: 'include' });
			const friends = await response.json();
			this.friends = friends;
			for (let friend of friends) {
				const owner: number = (await (await fetch('http://' + import.meta.env.VITE_HOST + ':3000/chat/' + friend['channel']['id'] + '/owner', {credentials: 'include'})).json())['id'];
				const messages: Message[] = await this.getChannelMessages(friend['channel']['id']);
				const admins: number[] = friend['channel']['admins'];
				const channel: Channel = {
					id: friend['channel']['id'],
					name: friend['channel']['name'],
					owner: owner,
					messages: messages,
					protected: friend['channel']['protected'],
					isPrivate: friend['channel']['isPrivate'],
					admins: admins,
				}
				friend['channel'] = channel;
			}
		},

		async fetchBlockList() {
			const response = await fetch("http://" + import.meta.env.VITE_HOST + ":3000/user/" + this.sender + "/block/blocklist", { credentials: 'include' });
			this.blockList = await response.json();
		},

		async getChannelMessages(channelId: number): Promise<Message[]> {
			const message_response = await fetch('http://' + import.meta.env.VITE_HOST + ':3000/message/' + channelId + '/list', { credentials: 'include' });
			let messages = [] as Message[];
			try {
				const messages_json = await message_response.json();
				for (let i = 0; i < messages_json.length; i++) {
					messages.push({
						channelId: channelId,
						text: messages_json[i].message_text,
						sender: messages_json[i].sender_id,
						sender_name: messages_json[i].sender_name,
						sender_img: messages_json[i].sender_avatarLink,
					});
				}
				return (messages);
			}
			catch {
				return ([] as Message[]);
			}
		},

		showChannelForwarder(channelId: number): void {
			this.$emit('showPrivateMessage', channelId);
		},

		selectFriend(friend: friendTab): void {
			this.selectedFriend = friend;
		},

		getSelectedFriendClass(friend: friendTab): string {
			return (friend === this.selectedFriend ? 'selected' : '');
		}
	},

	watch: {
		friendTimestamp: {
			async handler(){
				await this.fetchFriends();
				await this.fetchBlockList();
			}
		},
		updateTimestamp: {
			handler() {
				this.print = 0;
			},
		},
	},
});

</script>

<template>
	<div class="friend_list_container">
		<transition name="fade2" mode="out-in">
			<div class="friend_buttons_container">
				<button v-bind:class="{ 'focused': print === 1 }" class="tri" @click="print = 1;">Demandes</button>
				<button v-bind:class="{ 'focused': print === 2 }" class="tri" @click="print = 2;">Bloqués</button>
				<div v-if="getFriendRequest"  class="notifDemande">
					<strong>{{ getFriendRequest }}</strong>
				</div>
			</div>
		</transition>
		<transition name="fade2" mode="out-in">
			<div v-if="dataLoaded && !print" class="list_friend">
				<div v-if="!friends.length || !(friends.length - getFriendRequest - blockList.length)" class="empty_blocked">
					 <span>{{ emptyMessage }}</span>
				</div>
				<ProfilCell v-else v-for="friend in friends" :friend="friend" :myId=sender :blockList=blockList
						:print=print @showChannel="showChannelForwarder"></ProfilCell>
			</div>
			<div v-else-if="dataLoaded && print === 1" class="list_friend">
				<div v-if="!friends.length" class="empty_blocked">
					 <span>{{ emptyMessage }}</span>
				</div>
				<ProfilCell v-else-if="getFriendRequest" v-for="friend in friends" :friend="friend" :myId=sender :blockList=blockList
						:print=print @showChannel="showChannelForwarder"></ProfilCell>
				<div v-else class="empty_blocked">
					Vous n'avez pas de demandes d'amis !
				</div>
			</div>
			<div v-else-if="print === 2" class="list_friend">
				<BlockListCell v-if="blockList.length > 0" v-for="block in blockList" :block=block :myId=sender></BlockListCell>
				<div v-else class="empty_blocked">
					Vous n'avez bloqué aucun utilisateur !
				</div>
			</div>
		</transition>
	</div>
</template>

<style>

.list_friend {
	display: flex;
	align-items: center;
	flex-direction: column;
	width: 100%;
	height: 94%;
}

.friend_list_container{
	height: 100%;
}

.empty_friends{
	height: 100%;
	text-align: center;	
}

.friend_buttons_container{
	display: flex;
	flex-direction: row;
	gap: 10px;
	justify-content: center;
	height: 6%;
}

.tri {
	color: white;
	background-color: #046280;
	width: 45%;
	overflow: hidden;
	border-radius: 20px;
	border: none;
	cursor: pointer;
	font-family: 'Poppins', sans-serif;
	font-weight: bold;
	font-size: clamp(0.5rem, 0.4118rem + 0.4706vw, 0.75rem);
}

.tri:hover {
}

.tri:focus {
	background-color: #032f3d;
}

.notifDemande {
	position: absolute;
	background: red;
	border-radius: 50px;
	width: 20px;
	font-size: 0.6em;
	text-align: center;
	margin-right: 20px;
	margin-bottom: 20px;
	color: white;
}

.empty_blocked {
	text-align: center;
	margin-top: 10px;
}

.selected {
	background-color: #F0F8FF;
}

.focused {
	background-color: #032f3d;
}

</style>