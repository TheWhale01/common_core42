<template>
	<Transition name="slide-fade" mode="out-in" @click="$emit('close')">
		<div v-if="show && isDataLoaded" class="leaderboard_container">
			<div class="leaderboard" @click.stop>
				<h2>🏆Classement Général🏆</h2>
				<div class="rankings">
					<div v-for="(user, index) in leaderboardData" class="player_card" ref="userRef">
						<div class="card_content">
							<span class="position">{{ getMedal(index) }}</span>
							<div class="player_content">
								<img draggable="false" :src="user.avatarLink" alt="avatar" class="avatar" @click="redirecToProfil(user.name)">
								<span>{{ user.name }}</span>
							</div>
							<span><strong></strong>{{ user.stats.mmr }}pts</span>
						</div>
					</div>
				</div>
			</div>
		</div>
	</Transition>

</template>

<script lang="ts">

import { SocketService } from '@/services/SocketService';
import SlidingTitle from './SlidingTitle.vue';
import router from '@/router';

export default{
	props: ['show'],
	components: {
		SlidingTitle
	},
	data() {
		return ({
			leaderboardData: [] as any,
			isDataLoaded: false,
		});
	},
	async mounted(){
		this.leaderboardData = await (await fetch("http://" + import.meta.env.VITE_HOST + ":3000/user/leaderboard")).json();
		this.isDataLoaded = true;
	},

	async updated(){
		if (this.$refs.userRef.length){
			this.leaderboardData = await (await fetch("http://" + import.meta.env.VITE_HOST + ":3000/user/leaderboard")).json();
			for (let i = 0; i < this.leaderboardData.length; i++ ){
				if (this.leaderboardData[i].id === SocketService.getUser.id){
					setTimeout(() => {
						this.$refs.userRef[i].scrollIntoView({behavior: 'smooth'});
						this.$refs.userRef[i].classList.value = ['my_card']
					}, 50);
				}
			}
		}
	},
	methods: {
		getMedal(position: number){
			const medals: string[] = ["🥇", "🥈", "🥉"];
			return (position <= 2 ? medals[position] : position + 1);
		},

		redirecToProfil(name: string) {
			router.push({path:'/profile', query: { user: name }});
		},
	}
}

</script>

<style scoped>

.leaderboard_container {
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
.leaderboard {
	display: flex;
	flex-direction: column;
	height: 80%;
	width: 75%;
	max-width: 600px;
	background-color: white;
	border-radius: 20px;
	align-items: center;
	justify-content: center;
}

.rankings {
	display: flex;
	flex-direction: column;
	align-items: center;
	overflow-y: scroll;
	height: 85%;
	width: 90%;
	gap: 20px;
	padding: 10px;
	border-radius: 20px;
}

.rankings::-webkit-scrollbar {
  display: none;
}

.position {
	font-weight: bold;
	font-size: 2em;
	width: 10%;
	text-align: center;
}
.rankings {
  -ms-overflow-style: none;
  scrollbar-width: none;
  
}

.player_card {
	width: 90%;
	height: 15%;
	max-height: 100px;
	display: flex;
	flex-direction: column;
	justify-content: center;	
	border-radius: 20px;
	background-color: rgba(80, 179, 236, 0.178);
}
.card_content {
	display: flex;
	justify-content: space-around;
	align-items: center;
	height: 100%;
}


.avatar {
	width: 30%;
	aspect-ratio: 1;
	border-radius: 1000px;
}

.avatar:hover{
	opacity: 0.5;
	cursor: pointer;
}

.player_content {
	display: flex;
	justify-content: center;
	align-items: center;
	width: 45%;
	gap: 15%;
	padding: 5px;
}

.player_content span{
	width: 40%;
}

.medal {
	margin-left: -20px;
}

.medal span {
	font-size: 1.50em;
}

.my_card {
	width: 100%;
	height: 15%;
	max-height: 100px;
	display: flex;
	flex-direction: column;
	justify-content: center;	
	border-radius: 20px;
	background-color: rgba(32, 103, 236, 0.288);
}

</style>