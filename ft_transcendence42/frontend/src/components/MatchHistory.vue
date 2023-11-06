<template>
	<div class="history_container">
		<div class="history" v-if="matches.length">
			<div class="history-title">Historique de Match</div>
			<div class="matches">
				<Match v-for="match in matches" class="match" :match-object="match" :update-timestamp="updateTimestamp"></Match >
			</div>
		</div>
		<div v-else class="no-match">
			Pas de matchs joués ! 
		</div>
	</div>
</template>

<script lang="ts">
	import Match from '@/components/Match.vue'
	export default{
		components:{
			Match
		},

		props: ["user", "updateTimestamp"],

		data() {
			return {matches: ""}
		},

		methods:{
			async getMatches(){
				this.matches = await (await fetch("http://" + import.meta.env.VITE_HOST + ":3000/match/" + this.user.name, {credentials: "include"})).json()
			}
		},
		async created() {
			await this.getMatches();
		},

		watch: {
			async updateTimestamp() {
				await this.getMatches();
			}
		},
	}
</script>

<style>

.history-title{
	margin-top: 5px;
	font-size: clamp(0.6875rem, 0.2548rem + 1.3846vw, 1.25rem);
}

.history_container{
	display: flex;
	justify-content: center;
	align-items: center;
	height: 100%;
	width: 100%;
	border-radius: 50px;
	overflow: hidden;
}

.no-match{
	display: flex;
	text-align: center;
	justify-content: center;
	align-items: center;
	background-color: rgba(34, 158, 230, 0.103);
	font-size: clamp(0.625rem, 0.1442rem + 1.5385vw, 1.25rem);
	border-radius: 50px;
	width: 96%;
	height: 96%;
}

.matches{
	display: flex;
	flex-direction: column;
	align-items: center;
	overflow-y: auto;
	height: 92%;
	width: 100%;
}

.history{
	display: flex;
	flex-direction: column;
	width: 100%;
	height: 100%;
	align-items: center;
	justify-content: center;
}

.match{
	margin-top: 2%;
	margin-bottom: 2%;
}

.matches::-webkit-scrollbar {
  display: none;
}

.matches {
  -ms-overflow-style: none;
  scrollbar-width: none;
}

</style>
