<script lang="ts">

import { defineComponent } from 'vue';
import BlueButton from "./BlueButton.vue";
import SlidingTitle from "./SlidingTitle.vue";
import { useNotification } from '@kyvg/vue3-notification';

export default defineComponent ({
	data() {
		return ({
			channel_name: '' as string,
			channel_password: '' as string,
		});
	},

	components: {
		BlueButton,
		SlidingTitle,
	},

	props: {
		show: Boolean,
	},

	methods: {
		async addChannel() {
			if (!this.channel_name.length || !this.channel_name.match(/^(?=.{1,15}$)[\p{L}\p{N}_]+$/u)){
				const notif = useNotification();
				notif.notify({
						title: 'Erreur',
						text: "Veuillez entrer un nom valide !",
						type: 'error',
						group: 'notif-center',
					});
				return ;
			}
			if (Array.from(this.channel_name)[0] === '#')
				this.channel_name.split('#').join('');
			const me = await (await fetch('http://' + import.meta.env.VITE_HOST + ':3000/user/me', {credentials: 'include'})).json();
			const response_json = await (await fetch('http://' + import.meta.env.VITE_HOST + ':3000/chat/create', {
				credentials: 'include',
				method: 'POST',
				headers: {
					'Content-Type': 'application/json'
				},
				body: JSON.stringify({
					name: this.channel_name,
					password: this.channel_password,
					creator: me,
				}),
			})).json();
			if (response_json['channel'] !== null)
				this.$emit('newChannel', response_json['channel'], this.channel_password);
			else {
				let response = await fetch('http://' + import.meta.env.VITE_HOST + ':3000/chat/' + encodeURIComponent(this.channel_name), { credentials: 'include' });
				let channel = await (response.json());
				this.$emit('newChannel', channel, this.channel_password);
			}
			this.$emit('close');
			this.channel_name = '';
			this.channel_password = '';
		}
	},
});

</script>

<template>
	<Transition name="slide-fade" mode="out-in">
	<div v-if="show" class="modal_overlay_channel" @click="$emit('close')">
		<div class="modal_channel" @click.stop>
			<SlidingTitle text="Rejoindre un channel"/>
			<div class="field_channel">
				<input v-model="channel_name" class="entry_channel" type="text" maxlength="15" placeholder="Nom du channel"/>
				<input class="entry_channel" type="password" placeholder="Mot de passe (optionnel)" v-model="channel_password"/>
				<BlueButton text="Confirmer" icon="" @click="addChannel()" />
			</div>
		</div>
	</div>
	</Transition>
</template>

<style scoped>

.entry_channel {
	display: flex;
	border-radius: 20px;
	height: 30%;
	width: 100%;
	outline: none;
	text-align: center;
	font-size: larger;
}

.field_channel {
	display: flex;
	flex-direction: column;
	margin-top: 20px;
	width: 50%;
	height: 50%;
	justify-content: space-between;
	align-items: center;
	gap: 30px;

	font-size: clamp(0.75rem, 0.3654rem + 1.2308vw, 1.25rem);
}
.field_channel button {
	font-size: larger;
	height: 30%;
	width: 70%;
	text-align: center;
	border-radius: 20px;
	font-size: clamp(1.2rem, 0.3654rem + 1.2308vw, 1.25rem);
}

.modal_overlay_channel {
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
}

.modal_channel {
	display: flex;
	flex-direction: column;
	height: 55%;
	width: 75%;
	max-width: 600px;
	background-color: white;
	border-radius: 20px;
	justify-content: center;
	align-items: center;
}

</style>