<script lang="ts">
import { defineComponent } from 'vue';
import router from '@/router';
import { SocketService } from '@/services/SocketService';


export default defineComponent({
		props: ["block", "myId"],
	data() {
		return {
			friendUsername: "" as string,
		}
	},
	methods: {

		redirecToProfil(name: string) {
			router.push({path:'/profile', query: { user: name }});
		},

		getAvatarUrl(id: number) {
			if (!id)
				return ;
			return ("http://" + import.meta.env.VITE_HOST + ":3000/avatar/user/id/" + id.toString());
		},

		async unblockUser() {
			const response = await fetch(`http://${import.meta.env.VITE_HOST}:3000/user/block/unblock`,{
				credentials: 'include',
				method: 'PATCH',
				headers: {
					'Content-Type': 'application/json'
				},
				body: JSON.stringify({
					userId: this.myId,
					unblockId: this.block,
				}),
			});
			SocketService.getInstance.emit('refreshFriendListId', this.myId);
			SocketService.getInstance.emit('refreshFriendListId', this.block);
		},

		async friendInfo() {
			const response = await fetch('http://' + import.meta.env.VITE_HOST + ':3000/user/id/' + this.block,{ 
				credentials: 'include'
			});
			const userData = await response.json();
			this.friendUsername = userData.name;
		},
	},

	async mounted() {
		await this.friendInfo();
	}
});

</script>

<template>
	<div class="box">
		<div class="img_user">
			<img alt="avatar" class="img_user_profil" :src="getAvatarUrl(block)" @click="redirecToProfil(friendUsername)">
		</div>
		<div class="name">
			{{ friendUsername }}
		</div>
			<button class="unblock" v-on:click="unblockUser">Débloquer</button>
	</div>

</template>
<style scoped>

.name {
	font-size: clamp(0.6875rem, 0.2548rem + 1.3846vw, 1.25rem);
	text-align: center;
	margin-left: 5px;
}

.img_user_profil_block {
	border-radius: 25px;
	width: 100%;
	aspect-ratio: 1;
	border: 2px solid;
	border-radius: 50%;
	display: inline-block;
	border-color: rgb(107, 106, 106);
	padding: 2px;
}

.unblock {
	cursor: pointer;
	font-family: 'Poppins', sans-serif;
	font-weight: bold;
	font-size: clamp(0.5rem, 0.4118rem + 0.4706vw, 0.75rem);
	color: #ffffff;
	border: 2px solid #087ee6;
	border-radius: 7px;
	background-color: #4596d8;
}

</style>