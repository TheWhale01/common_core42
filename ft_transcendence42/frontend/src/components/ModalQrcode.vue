<template>
	<div class="qrcode_modal_overlay" @click="closeModal">
		<div class="qrcode_modal" @click.stop>
			<SlidingTitle text="Double Authentification" class="qrcode_title"></SlidingTitle>
			<div class="instructions">
				Scannez le code avec l'application Google Authenticator sur mobile.
			</div>
			<img alt="qrcode" v-if="isDataLoaded" :src="getUrl()" class="qrcode">
			<div class="instructions">
				Entrez le code présent sur l'application.
			</div>
			<InputField v-on:keydown.enter.prevent class="qrcode_input" @complete="fecthCode"
				:is-invalid-code="isInvalidCode" @reset="isInvalidCode = false"></InputField>
			<button :class="!isActivated ? 'activate_button' : 'desactivate_button'" @click="sendCode">
				{{ isActivated ? "Désactiver" : "Activer" }}
			</button>
		</div>
	</div>
</template>

<script lang="ts">

import SlidingTitle from './SlidingTitle.vue';
import InputField from './InputField.vue';
import { useNotification } from '@kyvg/vue3-notification';
import { ref } from 'vue';

export default {
	data() {
		return ({
			isActivated: false,
			isDataLoaded: false,
			isInvalidCode: ref(false),
			code: "",
		})
	},
	methods: {
		closeModal() {
			this.$emit('close');
			this.isInvalidCode = false;
		},
		fecthCode(code: string) {
			this.code = code;
		},
		getUrl() {
			return ("http://" + import.meta.env.VITE_HOST + ":3000/auth/2fa/qrcode")
		},
		async sendCode() {
			this.isInvalidCode = false;
			const res = await fetch("http://" + import.meta.env.VITE_HOST + ":3000/auth/2fa/" + (this.isActivated ? "off" : "on"),
				{
					method: 'POST',
					credentials: 'include',
					headers: {
						'Content-Type': 'application/json'
					},
					body: JSON.stringify({
						code: this.code,
					})
				})
			const json = await res.json();
			const notification = useNotification()
			if (json["status"] === "Failure") {
				notification.notify({
					title: "Code incorrect !",
					type: 'error',
					group: 'notif-center'
				});
				this.isInvalidCode = true;
			}
			else {
				this.$emit('close');
				sessionStorage.setItem('tokens', json["token"]);
				let message: string = !this.isActivated ? "Double Authentification activée !" : "Double Authentification désactivée !"
				notification.notify({
					title: message,
					type: 'success',
					group: 'notif-center'
				});
				this.isActivated = !this.isActivated;
			}
		},
	},
	components: {
		SlidingTitle,
		InputField
	},
	async beforeMount() {
		const res = await fetch("http://" + import.meta.env.VITE_HOST + ":3000/auth/2fa/completeStatus", { method: "get", credentials: "include" });
		const infos = (await res.json());
		if (!infos["generated"]) {
			await fetch('http://' + import.meta.env.VITE_HOST + ':3000/auth/2fa/generate', { credentials: 'include', method: 'POST' });
		}
		this.isActivated = infos["activated"];
		this.isDataLoaded = true;
	},
}


</script>

<style>
.instructions {
	margin-left: 10px;
	margin-right: 10px;
	font-size: clamp(0.875rem, 0.25rem + 2vw, 1.375rem);
}

.qrcode_title {
	margin-top: 15px;
	margin-bottom: -15px;
}

.qrcode_modal_overlay {
	position: fixed;
	top: 0;
	bottom: 0;
	left: 0;
	right: 0;
	display: flex;
	justify-content: center;
	align-items: center;
	background-color: #242424d0;
	transition: opacity 0.3s ease;
	transition: all 0.3s ease;
	z-index: 2;
}

.qrcode_modal {
	font-family: 'poppins';
	text-align: center;
	display: flex;
	justify-content: space-evenly;
	align-items: center;
	flex-direction: column;
	background-color: white;
	border-radius: 20px;
	width: 55%;
	height: 50%;
	max-width: 500px;
	min-height: 500px;
	padding: 10px;
}

.qrcode {
	image-rendering: optimizeSpeed;
	image-rendering: -moz-crisp-edges;
	image-rendering: -o-crisp-edges;
	image-rendering: -webkit-optimize-contrast;
	image-rendering: pixelated;
	image-rendering: optimize-contrast;
	-ms-interpolation-mode: nearest-neighbor;
	aspect-ratio: 1;
	padding: 3px;
	border: 2px #515151 solid;
	border-radius: 25px;
}

.activate_button {
	background-color: green;

	font-family: 'poppins';
	border-radius: 250px;
	text-align: center;
	outline: none;
	font-size: clamp(0.875rem, 0.25rem + 2vw, 1.375rem);
	border: 2px #515151 solid;
	cursor: pointer;
	color: white;
}

.desactivate_button {
	background-color: red;
	font-family: 'poppins';
	border-radius: 250px;
	text-align: center;
	font-size: clamp(0.875rem, 0.25rem + 2vw, 1.375rem);
	outline: none;
	border: 2px #515151 solid;
	cursor: pointer;
	color: white;
}
</style>