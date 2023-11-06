<template>
	<div class="list">
		<ul v-if="channels_computed.length > 0">
			<li v-for="channel in channels_computed" :class="clickedChannel(channel['id'])" @click="$emit('showChannel', channel)">
				<span>{{ channel['name'] }}</span></li>
		</ul>
		<div v-else class="empty_chans">
			Vous n'avez pas encore rejoint de channel !
		</div>
	</div>
</template>
<script lang="ts">
export default {
	props: ['channels', 'selectedChannel'],

	computed: {
		channels_computed() {
			let channels: any[] = [];
			for (const channel of this.$props.channels)
				if (!channel.isPrivate)
					channels.push(channel);
			return (channels)
		}
	},

	methods: {
		clickedChannel(channelId: number) {
			return (this.selectedChannel['id'] === channelId ? 'selectedChannel' : '');
		},
	},
}
</script>
<style>
.list {
	display: flex;
	flex-direction: column;
	width: 100%;
	height: 100%;
	align-items: center;
	overflow-y: scroll;
}

.list::-webkit-scrollbar {
  display: none;
}

.list ul {
	margin: 0;
	padding: 0;
	list-style-type: none;
	width: 100%;
	height: 100%;
	display: flex;
	flex-direction: column;
	align-items: center;
}

.list ul li {
	margin-top: 10px;
	width: 90%;
	height: 10%;
	display: flex;
	border-radius: 20px;
	justify-content: center;
	align-items: center;
}

.list ul li:hover {
	background-color: #F0F8FF;
}

.list ul li span {
	font-family: 'Poppins', sans-serif;
	font-weight: bold;
	font-size: 1em;
}

.selectedChannel {
	background-color: #F0F8FF;
}

.empty_chans {
	text-align: center;
	height: 100%;
	width: 90%;
}

</style>