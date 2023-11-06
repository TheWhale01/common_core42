<template>
	<div class="panel">
		<div class="left-panel">
			<div class="centered-panel-item" id="ch">
				<div v-if="dataLoaded && (stats.wins + stats.looses)">
					<div v-if="windowWidth > 950" class="chart">
						<WinCharts :wins="stats.wins" :looses="stats.looses" :show="dataLoaded"></WinCharts>
					</div>
					<div v-else class="small-winrate">
						<div class="small-winrate-title">
							Ratio victoires / défaites: {{ ((this.stats.wins * 100) /  (this.stats.wins +this.stats.looses)).toFixed(2) }}%
						</div>
						<div class="small-winrate-text">
							Victoires: {{ stats.wins }}
						</div>
						<div class="small-winrate-text">
							Défaites: {{ stats.looses }}
						</div>
					</div>
				</div>
				<div v-else class="empty-stats">
					Aucune victoire ou défaite enregistrée !
				</div>
			</div>
			<div class="centered-panel-item">
				<div class="rank_container">
					<div class="titleRank">Classement</div>
					<span class="rank">{{userRank}}{{ userRank === 1 ? "er" : "e" }} / {{ totalUsers }}</span>
				</div>
				<div class="split-stats">
					<div class="rank-stat">
						<h5>Côte</h5>
						{{ stats.mmr }} pts					
					</div>
					<div class="rank-stat">
						<h5>Score Moyen</h5>
						{{ stats.meanScore }} pts
					</div>
				</div>
			</div>
		</div>
		<div class="right-panel">
			<div class="stat-panel-item">
				<h3>Statistiques</h3>
				<div class="list-stats">
					<h5>Nombre de points marqués</h5>
					{{ this.stats["winPoints"] }}
					<h5>Nombre de points perdus</h5>
					{{ this.stats["loosePoints"] }}
					<h5>Score Maximal</h5>
					{{ this.stats["highScore"] }}
					<h5>Nombre total de parties</h5>
					{{ this.stats["totalGames"] }}
					<h5>Nombre de parties classiques</h5>
					{{ this.stats["totalClassicGames"] }}
					<h5>Nombre de parties arcades</h5>
					{{ this.stats["totalArcadeGames"] }}
					<h5>Nombre de parties classées</h5>
					{{ this.stats["totalRankedGames"] }}
					<h5>Nombre de duels amis</h5>
					{{ this.stats["totalFriendsDuel"] }}
					<h5>Nombre de powerups activés</h5>
					{{ this.stats["totalPowerups"] }}
					<h5>Nombre de messages envoyés</h5>
					{{ this.stats["totalMessages"] }}
					<h5>Nombre d'emotes envoyées</h5>
					{{ this.stats["totalEmotes"] }}
				</div>
			</div>
		</div>
	</div>
</template>

<script lang="ts">

import WinCharts from './WinCharts.vue';

export default{
	components:{
		WinCharts
	},
	props: ["user"],
	data(){
		return {stats: Object,
				dataLoaded: false,
				windowWidth: window.innerWidth,
				userRank: 0,
				totalUsers: 0,
		};
	},

	methods:{
		handleResize() {
			this.windowWidth = window.innerWidth;
		},
	},
	async mounted(){
		window.addEventListener('resize', this.handleResize);
		this.stats = this.user.stats;
		const json = await (await fetch('http://' + import.meta.env.VITE_HOST + ':3000/stats/rank/' + this.stats.id,
		{credentials: 'include',})).json()
		this.userRank = json["rank"];
		this.totalUsers = json["total"];
		this.dataLoaded = true;
	},
}

</script>



<style scoped>

#ch{
	max-height: 50%;
}

.rank_container {
	width: 100%;
	display: flex;
	justify-content: center;
	flex-direction: column;
	align-items: center;
}

.rank {
	text-align: center;
	font-size: clamp(0.625rem, 0.4327rem + 0.6154vw, 0.875rem);
}

.titleRank{
    font-weight: bold;
	font-size: clamp(0.6875rem, 0.1319rem + 1.7778vw, 1.1875rem);
}

.small-winrate{
	height: 100px;
	display: flex;
	flex-direction: column;
	justify-content: space-around;
	align-items: center;
	width: 95%;
	margin: 2.5%;
	text-align: center;
	border-radius: 50px;
}

.small-winrate-title{
	font-size: clamp(0.625rem, 0.3365rem + 0.9231vw, 1rem);
	font-weight: bold;
}

.small-winrate-text{
	font-size: clamp(0.625rem, 0.3365rem + 0.9231vw, 1rem);
}

.panel{
	display: flex;
	flex-direction: row;
	width: 100%;
	height: 100%;
}

.left-panel, .right-panel{
	height: 100%;
	width: 50%;
 	display: flex;
	flex-direction: column;
	font-size: clamp(0.625rem, 0.1442rem + 1.5385vw, 1.25rem);
}

.centered-panel-item {
	margin: 10px;
	background-color: rgba(34, 158, 230, 0.103);
	border-radius: 50px;
	display: flex;
	height: 100%;
	flex-direction: column;
	align-items: center;
	justify-content: center;
}

.stat-panel-item {
	margin: 10px;
	background-color: rgba(34, 158, 230, 0.103);
	border-radius: 50px;
	display: flex;
	height: 97%;
	flex-direction: column;
	align-items: center;
	justify-content: center;
}

.split-stats{
	margin-top: -10px;
	display: flex;
	width: 80%;
	flex-basis: 50%;
	border-radius: 20px;
	flex-direction: row;
	justify-content: space-between;
	align-items: center;
}

h5{
	margin: 0;
}

h3{
	text-align: center;
}

.list-stats::-webkit-scrollbar {
  display: none;
}

.list-stats {
  -ms-overflow-style: none;
  scrollbar-width: none;
}

.rank-stat{
	text-align: center;
}

.list-stats {
	text-align: center;
	overflow-y: auto;
	height: 80%;
	width: 90%;
	border-radius: 20px;
}

h5{
	font-size: clamp(0.625rem, 0.3365rem + 0.9231vw, 1rem);
}

h3{
	font-size: clamp(0.6875rem, -0.0764rem + 2.4444vw, 1.375rem);
}

.empty-stats {
	text-align: center;
	width: 90%;
}

</style>