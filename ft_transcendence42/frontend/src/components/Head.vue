<script lang="ts">
import router from '@/router';
import { SocketService } from '@/services/SocketService';
import { State } from '@/views/Home.vue';
import { useNotification } from '@kyvg/vue3-notification';
import { defineComponent } from 'vue';

export default defineComponent({

	data() {
		return {
			name: '' as string, avatar: '' as string,
		};
	},

	props: ["updateTimestamp"],

	methods: {
		async getInfos(){
			await SocketService.fetchUser();
			this.name = SocketService.getUser["name"];
			this.avatar = SocketService.getUser["avatarLink"];
			if (!SocketService.getStatus)
				await SocketService.setSocket('http://' + import.meta.env.VITE_HOST + ':3000/', { query: { userId: SocketService.getUser.id } });
			this.$emit('socketReady');
		},
		redirectToHome(){
			router.push('/home')
		},
	},

	watch: {
		async updateTimestamp() {
			await this.getInfos();
		}
	},

	async created() {
		await this.getInfos();
		SocketService.getInstance.on('friendNotif', () =>{
			const notif = useNotification();
			notif.notify({
				type: 'status',
				text: "Vous avez reçu une demande d'ami !",
				group: 'notif-center'
			});
		})
		const res = await fetch("http://" + import.meta.env.VITE_HOST + ":3000/auth/refresh", { credentials: 'include', method: 'POST' });
		sessionStorage.setItem('token', (await res.json())["token"]);
		setInterval(async () => {
			const res = await fetch("http://" + import.meta.env.VITE_HOST + ":3000/auth/refresh", { credentials: 'include', method: 'POST' });
			sessionStorage.setItem('token', (await res.json())["token"]);
		}, 1000 * 60 * 1);
	},
})

</script>

<template>
	<header class="header">
		<img class="logo" src="../assets/img/logoPinaColaPong2.png" @click="redirectToHome()" draggable="false" alt="logo">
		<router-link to="/profile" class="profile" draggable="false">
			<img class="img_profile" v-bind:src=avatar draggable="false" alt="avatar">
			<div class="profile_name">
				<span class="name">{{ name }}</span>
			</div>
		</router-link>
	</header>
</template>
<style>
@import url('https://fonts.googleapis.com/css2?family=Happy+Monkey&display=swap');

.header {
	font-family: 'Poppins', sans-serif;
	display: flex;
	height: 10vh;
	width: 100vw;
	border-bottom: 2px solid #515151;
	background: white;
	justify-content: space-between;
	align-items: center;
	min-height: 40px;
	position: relative;
}

.logo {
	height: 90%;
	margin-left: 0.8%;
	cursor: pointer	;
}
.name{
	z-index: 2;
}

.profile {
	display: flex;
	flex-direction: row;
	text-decoration: none;
	align-items: center;
	color: black;
	font-size: clamp(0.8125rem, 0.476rem + 1.0769vw, 1.25rem);
	font-weight: bold;
	max-width: 50%;
	height: 90%;
	border: 2px solid #515151;
	margin-right: 0.1%;
	border-radius: 27px;
	overflow: hidden;
	overflow-wrap: anywhere;
	position: relative;
}


.profile::before{
	content: "";
	z-index: 1;
	background-color: #97d4ece0;
	width: 0;
	height: 9vh;
	position: absolute;
	border-radius: 27px;
	top: 0.1%;
	transition: width 700ms ease-in-out;
	opacity: 50%;
}

.profile:hover::before {
	width: 100%;
	opacity: 50%;
	border-radius: 27px;
}

.img_profile{
	z-index: 1;

	height: 90%;
	padding-left: 5px;
	aspect-ratio: 1;
	border-radius:27px 27px 27px 27px;
}

.profile_name {
	width: 30vh;
	display: flex;
	justify-content: center;
	align-items: center;
	height: 100%;
}
</style>