<template>
	<div class="play-modal-overlay" @click="$emit('close-modal')">
		<div class="modal" @click.stop>
			<div class="play-modal-title">Choix du mode de jeu</div>
			<div class="buttons-play-modal">
				<BlueButton class="button-play-modal" text="Classique" @click="goToPong('classic')"></BlueButton>
				<BlueButton class="button-play-modal" text="Classée" @click="goToPong('ranked')"></BlueButton>
				<BlueButton class="button-play-modal" text="Arcade" @click="goToPong('arcade')"></BlueButton>
			</div>
		</div>
	</div>
</template>

<script lang="ts">

import BlueButton from './BlueButton.vue';

export default{
	components: {
		BlueButton,
	},
	methods: {
		goToPong(mode: string){
			this.$router.push({ path: '/pong', query: { mode: mode }});
		}
	}
}

</script>

<style>

.play-modal-overlay {
	position: fixed;
	z-index: 1;
	top: 0;
	bottom: 0;
	left: 0;
	right: 0;
	display: flex;
	justify-content: center;
	background-color: #242424d0;
	transition: opacity 0.3s ease;
	transition: all 0.3s ease;
}

.modal {
	text-align: center;
	background-color: white;
	margin-top: auto;
	margin-bottom: auto;
	padding: 40px;
	border-radius: 20px;
	display: flex;
	flex-direction: column;
	align-items: center;
	justify-content: center;
}

.play-modal-title{
	display: flex;
	justify-content: center;
	align-items: center;
	font-family: 'poppins';
	margin-bottom: 20px;
	font-weight: bold;
	font-size: 1.4em;
}

.buttons-play-modal{
	display: flex;
	justify-content: center;
	align-items: center;
	flex-direction: column;
	gap: 30px;
	width: 100%;
}

.button-play-modal{
	width: 80%;
	height: 100%;
}

</style>