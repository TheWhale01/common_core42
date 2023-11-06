<script setup lang="ts">
import { ref } from 'vue'
import router from '../router'
import { useNotification } from '@kyvg/vue3-notification';

const props = defineProps({show: Boolean})
const email = ref('')
const pseudo = ref('')
const password = ref('')

async function register(){
	const res = await fetch("http://" + import.meta.env.VITE_HOST + ":3000/auth/register",
	{
		credentials: 'include',
		mode: "cors",
		method: 'post',
		headers: {
			'Content-Type': 'application/json'
		},
		body: JSON.stringify({
			email: email.value,
			name: pseudo.value,
			password: password.value

		})
	});
	switch (res.status) {
		case 201:{
			router.push('/home');			
			break;
		}
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
		default:
			break;
	}
}

</script>

<template>
<Transition name="modal">
    <div v-if="show" class="modal-mask" @click="$emit('close')">
    	<div class="modal-container" @click.stop>
        	<div class="modal-body">
				<span class="text">Inscription</span>
					<div class="form">
						<div class="field">
							<input type="email" placeholder="Email" v-model="email" />
						</div>
						<div class="field">
							<input type="text" placeholder="Nom d'utilisateur" v-model="pseudo" />
						</div>
						<div class="field">
							<input type="password" placeholder="Mot de passe" v-model="password" />
						</div>
						<button @click="register">S'inscrire</button>
						</div>
        		</div>
    		</div>
    	</div>
	</Transition>
</template>``

<style scoped>
.modal-mask {
	position: fixed;
	z-index: 2;
	left: 0;
	top: 0;
	width: 100%;
	height: 100%;
	background-color: rgba(0, 0, 0, 0.5);
	display: flex;
	transition: opacity 0.3s ease;
}

.modal-container {
	margin: auto;
	background: #EBECF0;
	box-shadow: 0 2px 8px rgba(0, 0, 0, 0.33);

	width: 400px;
	height: auto;
	padding: 40px 30px;
	display: flex;
	flex-direction: column;

	border-radius: 10px;
	box-shadow:  4px 4px 4px #47474780,
             -4px -4px 4px #eaeaea80;
			 transition: all 0.3s ease;
}

.modal-body .text { 
	font-family: 'Poppins', sans-serif;

	font-size: 50px;
	font-weight: 600;
	display: flex;
	align-items: center;
	flex-direction: column;
	margin-bottom: 35px;
	color: #595959;
}

.modal-default-button {
	float: right;
}

.modal-enter-from {
	opacity: 0;
}

.modal-leave-to {
	opacity: 0;
}

.modal-enter-from .modal-container,
.modal-leave-to .modal-container {
	-webkit-transform: scale(1.5);
	transform: scale(1.5);
}

.form button {
	margin: 15px 0;
	width: 100%;
	height: 50px;
	font-size: 18px;
	line-height: 50px;
	font-weight: 600;
	border-radius: 25px;
	border: none;
	outline: none;
	cursor: pointer;
	color: #595959;
	box-shadow:  4px 4px 4px #616161,
             -4px -4px 4px #eaeaea;
	background: white;	
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
	align-self: center;
	align-content: center;
	gap: 20px;
}

.form .field input{ 
	padding-left: 25px;
	padding-right: 25px;
	height: 50px;
	width: 300px;
	outline: none;
	border: none;
	font-size: 18px;
	color: #595959;
	border-radius: 25px;
	box-shadow: inset 2px 2px 5px #BABECC,
				inset -5px -5px 10px #ffffff73;
}

.field input:focus{
	box-shadow: inset 1px 1px 2px #BABECC,
				inset -1px -1px 2px #ffffff73;
}

.field span {
	position: absolute;
	color: #595959;
	width: 50px;
	line-height: 50px;
}

.field label {
	position: absolute;
	top: 50%;
	transform: translateY(-50%);
	left: 25px;
	pointer-events: none;
	color: #666666;
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

