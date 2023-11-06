<template>
	<div class="invite_modal_content">
		<div class="invite_text">
				<strong>{{ senderName }}</strong>
				vous invite à un duel 
				<strong>{{ mode === "duelClassic" ? " Classique" : "Arcade" }}</strong>
		</div>
		<div class="buttons_invite">
			<button @click="handleClick(true)" class="green_color">Accepter</button>
			<button @click="handleClick(false)" class="red_color">Refuser</button>
		</div>
		<div class="progress-container">
			<div class="progress-bar" id="myProgressBar"></div>
		</div>
	</div>
</template>

<script setup lang="ts">

import { SocketService } from '@/services/SocketService';

const props = defineProps(['senderName', 'mode']);
const emit = defineEmits(['close']);

function handleClick(value: boolean) {
	if (value)
		SocketService.getInstance.emit('handlingInvite', true);
	else
		SocketService.getInstance.emit('handlingInvite', false);
	emit('close');
}

</script>

<style>

.buttons_invite{
	display: flex;
	justify-content: center;
	align-items: center;
	gap: 20px;
}

.invite_text{
	display: flex;
	font-size: clamp(0.5rem, 0.3676rem + 0.7059vw, 0.875rem);
	flex-direction: row;
	justify-content: space-between;
	gap: 4px;
	align-items: center;
}

.invite_modal_content {
	text-align: center;
	height: 100%;
	width: 100%;
	padding: 40px;
}

.progress-container {
	margin-top: 5px;
    width: 100%;
    height: 10px;
    border-radius: 10px;
    overflow: hidden;
}

.progress-bar {
    width: 100%;
    height: 100%;
    border-radius: 10px;
    animation: decreaseWidth 5s linear;
}

@keyframes decreaseWidth {
    0% {
        width: 100%;
		background: green;
    }
    100% {
		background: red;
		width: 0;
    }
}

.red_color{
	background-color: red;
	font-family: 'poppins';
	border-radius: 250px;
	text-align: center;
	font-size: clamp(0.5rem, 0.4118rem + 0.4706vw, 0.75rem);
	outline: none;
	border: 2px #515151 solid;
	cursor: pointer;
	color: white;
	font-weight: bold;
}

.green_color{
	font-weight: bold;
	background-color: green;
	font-family: 'poppins';
	border-radius: 250px;
	text-align: center;
	font-size: clamp(0.5rem, 0.4118rem + 0.4706vw, 0.75rem);
	outline: none;
	border: 2px #515151 solid;
	cursor: pointer;
	color: white;
}

</style>