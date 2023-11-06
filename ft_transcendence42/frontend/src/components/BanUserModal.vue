<script lang="ts">
import { SocketService } from '@/services/SocketService';
import ChannelOptionModal from './ChannelOptionModal.vue';
import { useNotification } from '@kyvg/vue3-notification';

export default {

	components:{
		ChannelOptionModal
	},

	data() {
		return ({
			username: '' as string,
			channelId: -1 as number,
		});
	},

	props: {
		show: Boolean,
		channelId: Number,
	},

	methods: {
		async banUser(username: string) {
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
			const notif = useNotification();
			if (username === SocketService.getUser.name){
				notif.notify({
					title: 'Erreur',
					text: "Vous ne pouvez pas vous auto-bannir !",
					type: 'error',
					group: 'notif-center',
				});
				return;
			}

			const user_resp = await fetch('http://' + import.meta.env.VITE_HOST + ':3000/user/' + username, {credentials: 'include'});

			if (!user_resp['ok'] || username == '') {
				this.$emit('close');
				return ;
			}
			try {
				const user = await user_resp.json();
				const response = await fetch('http://' + import.meta.env.VITE_HOST + ':3000/user/' + user['id'] + '/channels/' + this.$props.channelId + '/ban', {credentials: 'include', method: 'POST'});
				const response_json = await response.json();
				if (response_json['ok']){
					SocketService.getInstance.emit('kick', this.$props.channelId, user['id'], true);
					notif.notify({
						title: 'Modération',
						text: "Utilisateur banni !",
						type: 'success',
						group: 'notif-center',
					});
					this.$emit('close');
				}
				else {
					notif.notify({
						title: 'Erreur',
						text: response_json["message"],
						type: 'error',
						group: 'notif-center',
					});
				}
			} catch (error) {
				notif.notify({
					title: 'Erreur',
					text: "Cet utilisateur n'existe pas !",
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
			<ChannelOptionModal @click.stop title="Bannir un utilisateur" placeholder="Nom d'utilisateur" @callback="banUser" ></ChannelOptionModal>
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

</style>