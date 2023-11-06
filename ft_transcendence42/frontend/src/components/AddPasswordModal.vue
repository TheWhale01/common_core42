<script lang="ts">
import { defineComponent } from 'vue';
import { useNotification } from '@kyvg/vue3-notification';
import ChannelOptionModal from './ChannelOptionModal.vue';

export default defineComponent({
	props: ['show', 'channelId', 'sender',],

	components: {
		ChannelOptionModal
	},

	methods: {
		async addPassword(password: string) {
			if (!password.length || !password.match(/^(?=.{1,32}$)[\p{L}\p{N}_]+$/u)){
				const notif = useNotification();
				notif.notify({
					title: 'Erreur',
					text: "Veuillez entrer un mot de passe valide !",
					type: 'error',
					group: 'notif-center',
				});
				return;
			}
			const response = await fetch('http://' + import.meta.env.VITE_HOST + ':3000/chat/' + this.$props.channelId + "/" + this.$props.sender.id + '/changePassword', {
				credentials: 'include',
				method: 'POST',
				headers: {
					'Content-Type': 'application/json'
				},
				body: JSON.stringify({
					'password': password,
				}),
			});
			const response_json = await response.json();
			const notif = useNotification();
			if (!response_json['ok']) {
				notif.notify({
					title: 'Erreur',
					text: response_json['message'],
					type: 'error',
					group: 'notif-center',
				});
				return ;
			}
			else {
				notif.notify({
					text: response_json['message'],
					type: 'success',
					group: 'notif-center',
				});
				this.$emit('updateButton');
			}
			this.$emit('close');
		}
	},
});

</script>

<template>
	<Transition name="slide-fade" mode="out-in">
		<div v-if="show" class="modal_overlay" @click="$emit('close')">
			<ChannelOptionModal @click.stop title="Modifier le mot de passe"
				placeholder="Nouveau mot de passe"
				@callback="addPassword"
				isPassword="1" ></ChannelOptionModal>
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
	max-width: 500px;
	height: 70%;
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