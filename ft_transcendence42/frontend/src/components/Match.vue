<template>
	<div class="match-card">
		<div class="player-card">		
			<img alt="avatar" class="avatar-match" draggable="false" :src="getAvatarUrl(matchObject.player1.id)" @click="redirecToProfil(matchObject.player1.name)"/>
			{{ matchObject.player1.name }}
		</div>
		<div class="score-card">
			<div class="score-text">
				<div :class="getColorClass(1)">
					{{ matchObject.scorePlayer1 }}
				</div>
				-
				<div :class="getColorClass(2)">
					{{ matchObject.scorePlayer2 }}
				</div>
			</div>
			<div class="mode">
				{{ matchObject.mode }}
			</div>
		</div>
		<div class="player-card">
			<img alt="avatar" class="avatar-match" draggable="false" :src="getAvatarUrl(matchObject.player2.id)" @click="redirecToProfil(matchObject.player2.name)"/>
			{{ matchObject.player2.name }}
		</div>
	</div>
</template>
	
<script lang="ts">
	import router from '@/router';
import { SocketService } from '@/services/SocketService';
	export default{
		props: ["matchObject", "updateTimestamp"],
		methods:{
			redirecToProfil(name: string){
				if (SocketService.getUser.name === name)
					router.push({path:'/profile'});
				else
					router.push({path:'/profile', query: { user: name }});
			},
			getAvatarUrl(id: number){
				return ("http://" + import.meta.env.VITE_HOST + ":3000/avatar/user/id/" + id.toString() + "?" + this.updateTimestamp);
			},
			getColorClass(playerId: number){
				if (this.matchObject["scorePlayer" + playerId] === "ABD" || this.matchObject["leaverId"] === this.matchObject["player" + playerId]["id"]){
					this.matchObject["scorePlayer" + playerId] = "ABD";
					return ("text-red");
				}
				else if (this.matchObject["scorePlayer" + playerId] === this.matchObject["scorePlayer" + (playerId ^ 3)])
					return ("text-blue");
				else if (this.matchObject["scorePlayer" + playerId] < this.matchObject["scorePlayer" + (playerId ^ 3)])
					return ("text-red");
				else
					return ("text-green");
			}
		},
	}
</script>
	
<style>

.match-card {
	border-radius: 30px;
	background-color: rgba(34, 158, 230, 0.103);
	width: 90%;
	display: flex;
	flex-direction: row;
	justify-content: space-between;
	text-align: center;
	font-size: clamp(0.875rem, 0.5077rem + 0.6186vw, 1.25rem);
}

.player-card {
	display: flex;
	flex-direction: column;
	align-items: center;
	margin-top: 2%;
	width: 45%;
	border-radius: 30px;
	font-size: clamp(0.75rem, 0.2603rem + 0.8247vw, 1.25rem);
}

.score-card {
	width: 30%;
	display: flex;
	justify-content: center;
	flex-direction: column;
}

.avatar-match {
	border-radius: 50%;
	width: 20%;
	aspect-ratio: 1;
	border: 2px solid #b5dbdb;
	transition: background-color 0.5s ease;
}

.avatar-match:hover {
	opacity: 0.5;
	cursor: pointer;
}

@media screen and (max-width: 950px) {
	.match-card {
		width: 95%;
		height: 25%;
	}
	.player-card {
		justify-content: center;
		font-size: clamp(0.5rem, 0.2115rem + 0.9231vw, 0.875rem);
		font-weight: bold;
	}
	.mode {
		margin-top: 1px;
		font-size: 1.7vw;
	}
	.avatar-match {
		display: none;
	}
	.score-text {
		font-size: clamp(0.75rem, 0.5577rem + 0.6154vw, 1rem);
	}
}

.score-text{
	display: flex;
	flex-direction: row;
	justify-content: center;
	font-weight: bold;
}

.text-red{
	color: red;
}	

.text-green{
	color: green;
}

.text-blue{
	color: blue;
}

</style>