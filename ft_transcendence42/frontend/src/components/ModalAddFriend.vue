<script lang="ts">

import { useNotification } from "@kyvg/vue3-notification";
import { SocketService } from "@/services/SocketService";
import BlueButton from "./BlueButton.vue";
import SlidingTitle from "./SlidingTitle.vue";

export default {
	components: {
		BlueButton,
		SlidingTitle,
	},
	props: {
		show: Boolean
	},
	data() {
		return {
			username: '' as string,
			sender: -1 as number,
			textNotif: '' as string,
		}
	},
	methods: {
		async addUser() {
			this.sender = (await (await fetch('http://' + import.meta.env.VITE_HOST + ':3000/user/me', { credentials: 'include' })).json())['id'];
			const response = await fetch('http://' + import.meta.env.VITE_HOST + ':3000/friend/add',{
				credentials: 'include',
				method: 'POST',
				headers: {
					'Content-Type': 'application/json'
				},
				body: JSON.stringify({
					username: this.username,
					sender: this.sender,
				})
			})
			if (response.status == 406) {
				this.addFriendNotif("Veuillez insérer un nom", "error");
				return ;
			}
			const ret = await (await response.blob()).text();
			if (ret.length == 0) {
				this.addFriendNotif("Demande d'ami envoyé", "success");
				this.$emit('close');
				SocketService.getInstance.emit('refreshFriendList', this.username);
				SocketService.getInstance.emit('addFriendNotif', this.username);
			}
			else
				this.addFriendNotif(ret, "error");
		},

		addFriendNotif (text: string, status: string) {
			const notification = useNotification()
			notification.notify({
				title: text,
				type: status,
				group: 'notif-center'
			});
		}
	}
}
</script>

<template>
	<Transition name="slide-fade" mode="out-in">
	<div v-if="show" class="modal_overlay_friend" @click="$emit('close')">
		<div class="modal_friend" @click.stop>
				<SlidingTitle text="Ajouter un ami"/>
				<div class="input_friend">
					<input class="entry_friend" type="text" placeholder="Pseudo" v-model="username">
					<BlueButton text="Ajouter" icon="" @click="addUser" />
				</div>
		</div>
	</div>
	</Transition>
</template>

<style scoped>

.input_friend {
	display: flex;
	width: 100%;
	height: 50%;
	justify-content: center;
	align-items: center;
	gap: 15px;
	font-size: clamp(0.75rem, 0.3654rem + 1.2308vw, 1.25rem);
}
.entry_friend {
	display: flex;
	border-radius: 20px;
	height: 50%;
	width: 40%;
	outline: none;
	text-align: center;
	font-size: larger;
}

.input_friend button {
	font-size: larger;
	height: 50%;
	text-align: center;
	border-radius: 20px;
}
.title_modal_friend {
	text-align: center;
	font-size: clamp(0.9375rem, 0.2163rem + 2.3077vw, 1.875rem);
}

.modal_overlay_friend {
	position: fixed;
	display: flex;
	z-index: 2;
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
	font-family: 'poppins';
	display: flex;
}

.modal_friend {
	display: flex;
	flex-direction: column;
	width: 75%;
	max-width: 500px;
	height: 30%;
	background-color: white;
	border-radius: 20px;
	justify-content: center;
	align-items: center;
}

</style>