<template>
	<div class="chart">
		<div v-if="show">
			<apexchart type="donut" :options="chartOptions" :series="getSerie()"></apexchart>
		</div>
    </div>
</template>

<script lang="ts">

export default{
	props: ["wins", "looses", "show"],
	data(){
		return {
			chartOptions: {
				legend: {
					position: 'right',
					show: false
				},
				title: {
					margin: 50,
					text: "Ratio Victoires / Défaites",
					align: 'center',
					style: {
						fontSize:  '16px',
						fontWeight:  'bold',
						fontFamily:  undefined,
						color:  '#263238'
					},
				},
				labels: ['Victoires', 'Défaites'],
				plotOptions: {
					pie: {
						startAngle: -90,
						endAngle: 90,
						expandOnClick: false,
					},
				},
				responsive: [{
					breakpoint: 950,
				}],
				colors:['#00A300', '#D22B2B'],
			},
		};
	},
	methods:{
		getSerie(){
			return [this.wins, this.looses];
		}
	},
	mounted(){

	}
}

</script>

<style scoped>

	.title {
		position: absolute;
		text-align: center;
		width: 100%;
		bottom: 30%;
	}

	.chart{
		padding-top: 1%;
		margin-bottom: -5%;
		display: flex;
		justify-content: center;
		align-items: center;
		position: relative;
	}

	.text-chart{
		display: none;
	}

	@media screen and (max-width: 950px) {
		.chart{
			display: none;
		}
	}

</style>