<template>
	<body>

		<Head v-if="!$route.fullPath.includes('auth') && $route.fullPath.length !== 1" :updateTimestamp="timestampRef" @socketReady="socketReady">
		</Head>
		<transition name="fade" mode="out-in">
			<div v-if="displayModalInvite" class="invite_modal">
				<ModalInvite :sender-name="senderName" :mode="modeRef" @close="displayModalInvite = false"></ModalInvite>
			</div>
			<div v-else-if="displayModalSend" class="invite_modal">
				<div class="invite_modal_content">
					En attente ...
				</div>
			</div>
		</transition>
		<notifications position="top center" group="notif-center" max="2" />
		<FloatingSquares v-if="displayBackground"></FloatingSquares>
		<div v-else class="background"></div>


		<router-view v-slot="{ Component }" appear>
			<transition name="grow-in" mode="out-in">
				<Component v-if="$route.fullPath.includes('auth') || socketReadyRef" :key="$route.fullPath" :is="Component" @update="test" @socketReady="socketReady" @toggleBackground="displayBackground = !displayBackground"/>
			</transition>
		</router-view>
	</body>
</template>

<script setup lang="ts">

import { ref } from 'vue'
import Head from './components/Head.vue';
import { SocketService } from './services/SocketService';
import router from '@/router';

import FloatingSquares from './components/FloatingSquares.vue';
import ModalInvite from './components/ModalInvite.vue'; 


const timestampRef = ref()

const displayModalInvite = ref(false)
const displayModalSend = ref(false)
const senderName = ref("");
const modeRef = ref("");
const socketReadyRef = ref(false);
const displayBackground = ref(true);

let timeoutId: number = -1;

function socketReady() {
	socketReadyRef.value = true;
	SocketService.getInstance.on('displayInvite', (isSender: boolean, name: string, mode: string) => {
		senderName.value = name;
		const ref = isSender ? displayModalSend : displayModalInvite;
		ref.value = true;
		modeRef.value = mode;
		if (timeoutId !== -1)
			clearTimeout(timeoutId);
		timeoutId = setTimeout(() => {
			ref.value = false;
			SocketService.getInstance.emit('handlingInvite', false);
		}, 5000);
	})

	SocketService.getInstance.on('joinGame', (senderId: number, mode: string) => {
		router.push({ path: '/pong', query: { mode: mode, id: senderId } });
	});

	SocketService.getInstance.on('closeInvite', () => {
		displayModalSend.value = false;
	});
}
function test() {
	timestampRef.value = Date.now();
}



</script>

<style scoped lang="scss">
@import url('https://fonts.googleapis.com/css?family=Poppins:400,500,600,700&display=swap');

.anim-enter-from,
.anim-leave-to {
	opacity: 0;
}

.anim-enter-active,
.anim-leave-active {
	transition: opacity 0.3s ease-out;
}

* {
	margin: 0;
	padding: 0;
	box-sizing: border-box;
	font-family: 'Poppins', sans-serif;
}

body {
	margin: -8px;
	position: absolute;
	height: 100vh;
	width: 100vw;
	overflow: scroll;
}
.background{
    background: #92ccf0;
}

@-webkit-keyframes AnimationName {
	0% {
		background-position: 0% 52%
	}

	50% {
		background-position: 100% 49%
	}

	100% {
		background-position: 0% 52%
	}
}

@-moz-keyframes AnimationName {
	0% {
		background-position: 0% 52%
	}

	50% {
		background-position: 100% 49%
	}

	100% {
		background-position: 0% 52%
	}
}

@-o-keyframes AnimationName {
	0% {
		background-position: 0% 52%
	}

	50% {
		background-position: 100% 49%
	}

	100% {
		background-position: 0% 52%
	}
}

@keyframes AnimationName {
	0% {
		background-position: 0% 52%
	}

	50% {
		background-position: 100% 49%
	}

	100% {
		background-position: 0% 52%
	}
}


body::-webkit-scrollbar {
	display: none;
}

.grow-in-enter-from, .grow-in-leave-to {
	opacity: 0;
	transform: scale(0.3);
}

.grow-in-enter-active,
.grow-in-leave-active {
	transition: 0.2s ease-out;
}

.invite_modal {
	position: absolute;
  	left: 50%;
  	transform: translate(-50%, -50%);
	background: white;
	border: 2px #515151 solid;
	border-radius: 10px;
	padding: 5px;
	z-index: 5;
}

</style>

<style>
.fade-enter-from,
.fade-leave-to {
	opacity: 0;
}

.fade-enter-active,
.fade-leave-active {
	transition: opacity 0.3s ease-out;
}

.slide-enter-from,
.slide-leave-to {
	opacity: 0;
	transform: translateX(-100%);
}

.slide-enter-active,
.slide-leave-active {
	transition: 0.3s ease-out;
}

.slide-down-enter-from,
.slide-down-leave-to {
	opacity: 0;
	transform: translateY(300px);
}

.slide-down-enter-active,
.slide-down-leave-active {
	transition: 0.3s ease-out;
}




.grow-out-enter-from,
.grow-out-leave-to {
	opacity: 0;
	transform: scale(1.5);
}

.grow-out-enter-active,
.grow-out-leave-active {
	transition: 0.3s ease-out;
}
</style>