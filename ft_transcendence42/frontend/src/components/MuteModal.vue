<script lang="ts">
import { useNotification } from '@kyvg/vue3-notification';
import ChannelOptionModal from './ChannelOptionModal.vue';
import { SocketService } from '@/services/SocketService';

export default {
	components:{
		ChannelOptionModal
	},

	props: {
		show: Boolean,
		channelId: Number,
		username: String,
	},

	methods: {
		async MuteUser(time: string) {
			if (/^0*$/.test(time)){
				const notif = useNotification();
				notif.notify({
					title: 'Erreur',
					text: "Veuillez entrer un nombre strictement positif !",
					type: 'error',
					group: 'notif-center',
				});
				return;
			}
			const user_resp = await fetch('http://' + import.meta.env.VITE_HOST + ':3000/user/' + this.$props.username, {credentials: 'include'});
			if (!user_resp['ok'] || this.$props.username == '') {
				this.$emit('close');
				return ;
			}
			const user = (await user_resp.json())['id'];
			const data = {
				userId: user,
				channelId: this.$props.channelId,
				time: time,
			};
			SocketService.getInstance.emit('mute', data);
			this.$emit('close');
		}
	},
};

</script>

<template>
	<Transition name="slide-fade" mode="out-in">
		<div v-if="show" class="modal_overlay" @click="$emit('close')">
			<ChannelOptionModal @click.stop title="Mute un utilisateur" isDigit="true" placeholder="Temps en seconde" @callback="MuteUser" ></ChannelOptionModal>
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