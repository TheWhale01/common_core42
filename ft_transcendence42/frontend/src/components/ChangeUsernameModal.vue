<template>
	<div class="modal-overlay" @click="closeModal">
		<div class="modal-username" @click.stop>
			<SlidingTitle text="Changer de Pseudo"/>
			<div class="username-items">
				<div class="form__group">
					<input type="text" maxlength="15" v-model="username" class="input_username" id="name" placeholder="Nouveau Pseudo"/>
					<label for="name" class="input_label">Nouveau Pseudo</label>
				</div>
				<BlueButton text="Confirmer" icon="fa-solid fa-pen" @click="changeUsername" />
			</div>
		</div>
	</div>
</template>

<script lang="ts">

import SlidingTitle from './SlidingTitle.vue';
import BlueButton from './BlueButton.vue';

export default{
	components: {
		SlidingTitle,
		BlueButton
	},
	data: () => ({
		username: "",
	}),
	methods: {
		closeModal(){
			this.$emit('close-modal');
			this.username = "";
		},

		handleResponse(res: Response){
			if (res.status != 201)
				this.$emit('already-exist');
			else {
				this.$emit('updated');
				this.closeModal();
			}
		},

		changeUsername(){
			if (!this.username)
				return;
			if (!this.username.match(/^(?=.{1,15}$)[\p{L}\p{N}_]+$/u)) {
				this.$emit('bad-format');
				return;
			}
			fetch("http://" + import.meta.env.VITE_HOST + ":3000/user/setname",
			{
				method: 'POST',
				credentials: 'include',
				headers: {
					'Content-Type': 'application/json'
				},
				body: JSON.stringify({
					username: this.username,
				})
			})
			.then(res => this.handleResponse(res));
		}
	},
}
</script>

<style scoped>

.modal-overlay {
	position: fixed;
	top: 0;
	bottom: 0;
	left: 0;
	right: 0;
	display: flex;
	justify-content: center;
	background-color: #242424d0;
	transition: opacity 0.3s ease;
	transition: all 0.3s ease;
	z-index: 2;
}
.modal-username {
	text-align: center;
	background-color: white;
	height: 30%;
	width: 40%;
	margin-top: auto;
	margin-bottom: auto;
	padding: 60px 0;
	border-radius: 20px;
	display: flex;
	flex-direction: column;
	align-items: center;
	justify-content: center;
	min-width: 270px;
	max-width: 600px;
}

.username-items{
	display: flex;
	flex-direction: column;
	justify-content: center;
	row-gap: 30px;
	height: 70%;
}
.input_label {
  font-family: 'Poppins', sans-serif;
  font-size: 0.8rem;
  display: block;
  transition: all 0.3s;
  transform: translateY(0rem);
}

.input_username {
	font-family: 'Poppins', sans-serif;
	color: #333;
	font-size: clamp(0.75rem, 0.3654rem + 1.2308vw, 1.25rem);
	border-radius: 10px;
	background-color: rgb(255, 255, 255);
	display: block;
	transition: all 0.3s;
}

.input_username:placeholder-shown + .input_label {
  opacity: 0;
  visibility: hidden;
  -webkit-transform: translateY(-4rem);
  transform: translateY(-4rem);
}


</style>