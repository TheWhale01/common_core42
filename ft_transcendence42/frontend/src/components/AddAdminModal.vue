<script lang="ts">
import { SocketService } from '@/services/SocketService';
import { useNotification } from '@kyvg/vue3-notification';
import ChannelOptionModal from './ChannelOptionModal.vue';


export default {
	data() {
		return ({
			channelId: -1 as number,
		});
	},

	components: {
		ChannelOptionModal
	},

	props: {
		show: Boolean,
		channelId: Number,
	},

	methods: {
		async addAdmin(username: string) {
			if (!username.length || !username.match(/^(?=.{1,15}$)[\p{L}\p{N}_]+$/u)){
				const notif = useNotification();
				notif.notify({
					title: 'Erreur',
					text: "Veuillez entrer un nom d'utilisateur valide !",
					type: 'error',
					group: 'notif-center',
				});
				return;
			}
			const user_resp = await fetch('http://' + import.meta.env.VITE_HOST + ':3000/user/' + username, { credentials: 'include' });
			if (!user_resp['ok'] || username == '') {
				this.$emit('close');
				return;
			}
			try {
				let user;
				try { user = await user_resp.json(); }
				catch { throw new Error("Cet utilisateur n'existe pas !");}
				const userInChannelResponse = await fetch('http://' + import.meta.env.VITE_HOST + ':3000/chat/' + this.$props.channelId + '/isUserInChannel/' + user['id'], { credentials: 'include' });
				const userInChannel = await userInChannelResponse.json();
				if (!userInChannel)
					throw new Error("Cet utilisateur n'est pas dans le channel !");
				const response = await fetch('http://' + import.meta.env.VITE_HOST + ':3000/chat/' + this.$props.channelId + '/addAdmin/' + user['id'], { credentials: 'include', method: 'POST' });
				const response_json = await response.json();
				const notif = useNotification();
				if (response_json['ok']) {
					const data = {
						channelId: this.$props.channelId,
						new_owner_id: user['id'],
					}
					SocketService.getInstance.emit('changeAdmin', data);
					SocketService.getInstance.emit('setAdmin', user['id'], data.channelId);
					this.$emit('close');
					notif.notify({
						title: "Modération",
						text: 'Admin ajouté !',
						type: 'success',
						group: 'notif-center',
					});
				}
				else {
					notif.notify({
						title: 'Erreur',
						text: response_json["message"],
						type: 'error',
						group: 'notif-center',
					});
				}
			}
			catch (error: any) {
				const notif = useNotification();
				notif.notify({
					title: 'Erreur',
					text: error.message,
					type: 'error',
					group: 'notif-center',
				});
			}
		}
	},
};

</script>

<template>
	<Transition name="slide-fade" mode="out-in">
		<div v-if="show" class="modal_overlay" @click="$emit('close')">
			<ChannelOptionModal @click.stop title="Ajouter un admin" placeholder="Nom d'utilisateur" @callback="addAdmin" ></ChannelOptionModal>
		</div>
	</Transition>
</template>

<style scoped>
.modal_overlay {
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

.modal {
	display: flex;
	flex-direction: column;
	align-items: end;
	width: 75%;
	height: 70%;
	max-width: 500px;
	background-color: #DBEFFC;
	border-radius: 20px;
}

.modal button {
	display: flex;
	background-color: #DBEFFC;
	height: 6%;
	width: 6%;
	align-items: center;
	justify-content: center;
	border: none;
	font-size: 1.3em;
	border-radius: 20px;
}

.modal button:hover {
	background-color: rgb(182, 227, 238);
}

.form {
	display: flex;
	border-radius: 20px;
	width: 100%;
	height: 80%;
	flex-direction: column;
	align-items: center;
	padding-top: 5%;
}

.field {
	display: flex;
	flex-direction: column;
	width: 70%;
	height: 70%;
	gap: 12%;
	align-items: center;
	padding-top: 2%;
}

.entry {
	display: flex;
	border-radius: 20px;
	width: 100%;
	height: 30%;
	outline: none;
	border: none;
	text-align: center;
	font-size: larger;
}

.choice {
	display: flex;
	justify-content: center;
	align-items: center;
	width: 100%;
	height: 25%;
}

.choice button {
	display: flex;
	width: 25%;
	height: 80%;
	background-color: #036280;
	;
	border: 1px solid #000000;
	border-radius: 20px;
}

</style>