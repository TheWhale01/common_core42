<script lang="ts">

import BlueButton from './BlueButton.vue';
import Invite from './Invite.vue';
import router from '@/router';
import MuteModal from './MuteModal.vue';
import { SocketService } from '@/services/SocketService';
import { useNotification } from '@kyvg/vue3-notification';

export default {
	props: ["connected_user", "friendId", "username", "show", "selectedChannel"],

	components: {
		BlueButton,
		Invite,
		MuteModal,
	},

	data() {
		return {
			modalInvite: false as boolean,
			showMuteModal: false as boolean,
		}
	},

	computed: {
		displayButton(): boolean {
			if (this.selectedChannel.isPrivate)
				return (false);
			return (this.connected_user.id === this.selectedChannel.owner
				|| (this.userIsAdmin(this.connected_user.id)
				&& this.friendId !== this.selectedChannel.owner
				&& !this.userIsAdmin(this.friendId)));
		}
	},

	methods: {

		redirecToProfil(name: string) {
			router.push({ path: '/profile', query: { user: name } });
		},

		async deleteFriend() {
			const response = await fetch(`http://${import.meta.env.VITE_HOST}:3000/friend/delete?id1=${this.connected_user.id}&id2=${this.friendId}`, {
				credentials: 'include',
				method: 'DELETE',
				headers: {
					'Content-Type': 'application/json'
				},
			});
			SocketService.getInstance.emit('refreshFriendListId', this.connected_user.id);
			SocketService.getInstance.emit('refreshFriendListId', this.friendId);
			const text = await response.text();
			SocketService.getInstance.emit('hideChan', this.connected_user.id, text);
			SocketService.getInstance.emit('hideChan', this.friendId, text);
		},

		async blockUser() {
			const response = await fetch(`http://${import.meta.env.VITE_HOST}:3000/user/block/blocked`, {
				credentials: 'include',
				method: 'POST',
				headers: {
					'Content-Type': 'application/json'
				},
				body: JSON.stringify({
					userId: this.connected_user.id,
					blockId: this.friendId,
				}),
			});
		},

		async kickUser() {
			const user_resp = await fetch('http://' + import.meta.env.VITE_HOST + ':3000/user/' + this.$props.username, { credentials: 'include' });
			if (!user_resp['ok'] || this.$props.username == '') {
				this.$emit('close');
				return;
			}
			const user = await user_resp.json();
			const response = await fetch('http://' + import.meta.env.VITE_HOST + ':3000/user/' + user['id'] + '/channels/' + this.$props.selectedChannel.id + '/kick', { credentials: 'include', method: 'POST' });
			const response_json = await response.json();
			if (response_json['ok']) {
				SocketService.getInstance.emit('kick', this.$props.selectedChannel.id, user['id'], false);
				const notif = useNotification();
				notif.notify({
					title: 'Modération',
					text: response_json["message"],
					type: 'success',
					group: 'notif-center',
				});
				this.$emit('close');
			}
			else {
				const notif = useNotification();
				notif.notify({
					title: 'Erreur',
					text: response_json["message"],
					type: 'error',
					group: 'notif-center',
				});
			}
		},

		async banUser() {
			const user_resp = await fetch('http://' + import.meta.env.VITE_HOST + ':3000/user/' + this.$props.username, { credentials: 'include' });
			if (!user_resp['ok'] || this.$props.username == '') {
				this.$emit('close');
				return;
			}
			const user = await user_resp.json();
			const response = await fetch('http://' + import.meta.env.VITE_HOST + ':3000/user/' + user['id'] + '/channels/' + this.$props.selectedChannel.id + '/ban', { credentials: 'include', method: 'POST' });
			const response_json = await response.json();
			if (response_json['ok']) {
				SocketService.getInstance.emit('kick', this.$props.selectedChannel.id, user['id'], true);
				const notif = useNotification();
				notif.notify({
					title: 'Modération',
					text: response_json["message"],
					type: 'success',
					group: 'notif-center',
				});
				this.$emit('close');
			}
			else {
				const notif = useNotification();
				notif.notify({
					title: 'Erreur',
					text: response_json["message"],
					type: 'error',
					group: 'notif-center',
				});
			}
		},

		userIsAdmin(userId: number): boolean {
			for (let admin of this.selectedChannel.admins)
				if (admin === userId)
					return (true);
			return (false);
		},
	}
}

</script>

<template>
	<Transition name="slide-fade" mode="out-in">
		<div v-if="show" class="modal_overlay_chat" @click="$emit('close')">
			<div class="modal_chat" @click.stop>
				<div class="grid">
					<div :class="displayButton ? 'button_grid_column' : 'button_grid_row'">
						<BlueButton class="modal_chat_button" :text="'Profil de ' + username" @click="redirecToProfil(username); $emit('close')" />
						<BlueButton class="modal_chat_button" text="Inviter à jouer" @click="modalInvite = true" />
						<BlueButton class="modal_chat_button" text="Bloquer" @click="blockUser(); deleteFriend(); $emit('close')" />
						<BlueButton class="modal_chat_button" v-if="displayButton" text="Mettre en sourdine" @click="showMuteModal = true;" />
						<BlueButton class="modal_chat_button" v-if="displayButton" text="Exclure" @click="kickUser()" />
						<BlueButton class="modal_chat_button" v-if="displayButton" text="Bannir" @click="banUser()" />
					</div>
				</div>
			</div>
			<invite @click.stop :show="modalInvite" @close="modalInvite = false" @close-modals="modalInvite = false; $emit('close')" :myId="connected_user.id" :friendId="friendId"></invite>
		</div>
	</Transition>
	<Teleport to="body">
		<MuteModal :channelId="selectedChannel.id" :username="username" :show="showMuteModal" @close="showMuteModal = false;" />
	</Teleport>
</template>

<style scoped>
.modal_overlay_chat {
	position: fixed;
	display: flex;
	left: 0;
	top: 0;
	width: 100%;
	height: 100%;
	background-color: rgba(0, 0, 0, 0.5);
	align-items: center;
	justify-content: center;
	transition: opacity 0.4s ease;
	transition: all 0.4s ease;
	min-height: 600px;
	min-width: 500px;
	z-index: 3;
}

.grid {
	display: flex;
	justify-content: center;
	align-items: center;
	width: 100%;
}

.modal_chat {
	display: flex;
	flex-direction: center;
	justify-content: center;
	width: 40%;
	min-width: 400px;
	height: 50%;
	background-color: white;
	border-radius: 20px;
}

.button_grid_column {
	display: grid;
	grid-template-columns: repeat(2, 1fr);
	row-gap: 20%;
	column-gap: 10%;
	width: 80%;
	height: 60%;
}

.button_grid_row {
	display: grid;
	grid-template-rows: repeat(3, 1fr);
	row-gap: 20%;
	column-gap: 10%;
	width: 60%;
	max-width: 250px;
	height: 60%;
}

.modal_chat_button{
	font-size: clamp(0.75rem, 0.3654rem + 1.2308vw, 1.25rem);
}

</style>
