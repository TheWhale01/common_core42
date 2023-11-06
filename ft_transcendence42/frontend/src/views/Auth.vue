<script setup>

import {ref} from "vue"
import inscription from "@/components/inscription.vue"
import { useNotification } from "@kyvg/vue3-notification";
import router from '../router'

const email = ref('')
const password = ref('')
const showModal = ref(false)

sessionStorage.removeItem('channelId');

async function login(){
	const res = await fetch("http://" + import.meta.env.VITE_HOST + ":3000/auth/login",
	{
		credentials: 'include',
		method: 'post',
		mode: "cors",
		headers: {
			'Content-Type': 'application/json'
		},
		body: JSON.stringify({
			email: email.value,
			password: password.value

		})
	})
	switch (res.status) {
		case 406:{
			const response = await res.json();
			const notification = useNotification()
			notification.notify({
				title: response["message"],
				type: 'error',
				group: 'notif-center'
			});
			break;
		}
		case 401:{
			const notification = useNotification()
			notification.notify({
				title: "Mauvais mot de passe !",
				type: 'error',
				group: 'notif-center'
			});
			break;
		}
		case 201:{
			router.push('/home');
			break;
		}
		case 207:{
			router.push({path:'/auth/2fa/verif'});
			break;
		}
	}
}

</script>

<template>

<div class="connection">
	<div class= "co-42">
		<img class="logo42" src="../assets/img/42.png" alt="logo 42">
		<button @click="$redirect('/auth/42/login')" type="button" class="btn42">Connexion</button>
	</div>
	<div class= "co-email">
		<span class="text">Authentification</span>
		<div class="form">
			<input class="field" type="email" id="email" placeholder="Email / Pseudo" v-model="email" />
			<input class="field" type="password" placeholder="Mot de passe" v-model="password" />
			<button @click="login">Connexion</button>
		</div>
		<div class="inscription">
			<button id="inscription-btn" @click="showModal = true">Inscription</button>
		</div>
		<Teleport to="body">
			<inscription :show="showModal" @close="showModal = false" />
		</Teleport>
	</div>
</div>

</template>

<style scoped>

.connection {
	min-height: 350px;

	height: 100vh;
	width: 100vw;
	display: flex;
	flex-direction: row;
	gap: 20px;
	justify-content: space-around;
	align-items: center;

}
.co-42 {
	width: 30%;
	aspect-ratio: 1;
	max-width: 300px;
	padding: 40px 30px;
	background-color: pink;
	background: #EBECF0;
	border-radius: 10px;
	box-shadow:  4px 4px 4px #474747,
             -4px -4px 4px #eaeaea;
}

.co-42 .logo42 {
	aspect-ratio: 1;
	width: 60%;

	display: block;
	margin-left: auto;
	margin-right: auto;
}

.co-email {
	display: flex;
	flex-direction: column;
	width: 35%;
	max-width: 500px;
	height: 400px;
	padding: 40px 30px;
	gap: 20px;
	background: #EBECF0;

	border-radius: 10px;
	box-shadow:  4px 4px 4px #474747,
             -4px -4px 4px #eaeaea;
}

.co-email .text {
	font-size: clamp(1.25rem, 0.4808rem + 2.4615vw, 2.25rem);
	font-weight: 600;
	display: flex;
	align-items: center;
	flex-direction: column;
	margin-bottom: 35px;
	color: #595959;
}

.btn42 {
	color: #595959;
	display: block;
	margin-top: 20px;
	margin-left: auto;
	margin-right: auto;
	--border-radius: 25px;
	--border-width: 6px;
	appearance: none;
	position: relative;
	padding: 1em 2em;
	border: 0;
	background: none;
	font-family: "Roboto", Arial, "Segoe UI", sans-serif;
	font-size: 18px;
	font-weight: 500;
	color: #fff;
	z-index: 2;
}

.btn42:hover {
	cursor: pointer;
}

.btn42::after {
	color: #595959;

	--m-i: linear-gradient(#000, #000);
	--m-o: content-box, padding-box;
	content: "";
	position: absolute;
	left: 0;
	top: 0;
	width: 100%;
	height: 100%;
	padding: var(--border-width);
	border-radius: var(--border-radius);
	background-image: conic-gradient(
			#488cfb,
			#29dbbc,
			#ddf505,
			#ff9f0e,
			#e440bb,
			#655adc,
			#488cfb
		);
	-webkit-mask-image: var(--m-i), var(--m-i);
	mask-image: var(--m-i), var(--m-i);
	-webkit-mask-origin: var(--m-o);
	mask-origin: var(--m-o);
	-webkit-mask-clip: var(--m-o);
	mask-composite: exclude;
	-webkit-mask-composite: destination-out;
	filter: hue-rotate(0);
	animation: rotate-hue linear 1s infinite;
	animation-play-state: paused;
}

.btn42,
.btn42:hover::after {
	color: #595959;

	animation-play-state: running;
}

@keyframes rotate-hue {
	to {
		filter: hue-rotate(1turn);
	}
}

.inscription {
	display: flex;
	direction: row;
	justify-content: center;
}

#inscription-btn {
	margin-top: 10px;
	width: 80%;
	max-width: 300px;
	height: 50px;
	font-size: 18px;
	line-height: 50px;
	font-weight: 600;
	background: #dde1e7;
	border-radius: 25px;
	border: none;
	outline: none;
	cursor: pointer;
	color: #595959;
	box-shadow:  4px 4px 4px #616161,
             -4px -4px 4px #eaeaea;
}

#inscription-btn:focus {
	color: #3498db;
	box-shadow:  4px 4px 4px #606060,
             -4px -4px 4px #c9c9c9;
}

.btn42::after {
	box-sizing: border-box;
}

.btn42:focus {
	color: black;
;

}

.form button {
	margin-top: 10px;
	width: 80%;
	max-width: 300px;
	height: 50px;
	font-size: 18px;
	line-height: 50px;
	font-weight: 600;
	background: #dde1e7;
	border-radius: 25px;
	border: none;
	outline: none;
	cursor: pointer;
	color: #595959;
	box-shadow:  4px 4px 4px #616161,
             -4px -4px 4px #eaeaea;
}
.form button:focus {
	color: #3498db;
	box-shadow:  4px 4px 4px #606060,
             -4px -4px 4px #c9c9c9;
}

.form {
	display: flex;
	flex-direction: column;
	align-items: center;
	justify-content: center;
	gap: 20px;
}

.field {
	font-size: clamp(1rem, 0.8077rem + 0.6154vw, 1.25rem);
	width: 80%;
	max-width: 350px;
	padding-left: 10px;
	padding-right: 10px;
	height: 50px;
	outline: none;
	border: none;
	background: #dde1e7;
	color: #595959;
	border-radius: 25px;
	box-shadow: inset 2px 2px 5px #BABECC,
				inset -5px -5px 10px #ffffff73;
}

.field:focus{
	box-shadow: inset 1px 1px 2px #BABECC,
				inset -1px -1px 2px #ffffff73;
}
.field button {
	margin: 15px 0;
	width: 100%;
	height: 50px;
	font-size: 18px;
	line-height: 50px;
	font-weight: 600;
	background: #dde1e7;
	border-radius: 25px;
	border: none;
	outline: none;
	cursor: pointer;
	color: #595959;
	box-shadow:  4px 4px 4px #616161,
             -4px -4px 4px #eaeaea;
}
.field button:focus {
	color: #3498db;
	box-shadow:  4px 4px 4px #606060,
             -4px -4px 4px #c9c9c9;
}

</style>

