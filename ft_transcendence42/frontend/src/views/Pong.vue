<template>
	<div class="pong_body">
		<div class="pong_content">
			<div class="tooltip_pong">
				<font-awesome-icon icon="fa-solid fa-circle-question" />
				<span class="tooltip_pong_text">Utilisez les flèches du clavier pour déplacer la raquette</span>
			</div>
			<div class="left_column_pong">
				<PongPlayerCard v-if="dataLoaded" :id="player1Id" side="0" :emote="emote1.emoji"></PongPlayerCard>
			</div>
			<div class="middle_column_pong" v-if="dataLoaded">
				<div class="top_infos" v-if="state === 1">
					<div class="timer">
						<span>{{ timer }}</span>
						<label>-</label>
					</div>
					<div class="scores">
						<span id="score1">{{ score1 }}</span>
						<span id="score1">{{ score2 }}</span>
					</div>
				</div>
				<div v-else class="top_infos">
					<span id="state_msg">{{ messageTop }}</span>
				</div>
				<PongCanvas :socket="this.socket" :playId1="this.player1Id" :playId2="this.player2Id"
					:score1="score1" :score2="score2" @toggleBackground="toggleBackground" 
					@setState="setState"/>
				<div class="button_panel">
					<div class="reaction_panel">
						<EmoteButton emoji="🤣" :socket="socket"></EmoteButton>
						<EmoteButton emoji="😬" :socket="socket"></EmoteButton>
						<EmoteButton emoji="😭" :socket="socket"></EmoteButton>
						<EmoteButton emoji="🤝" :socket="socket"></EmoteButton>
					</div>
					<BlueButton id="exit_button" text="Quitter la partie" @click="$router.push('/')"></BlueButton>
				</div>
			</div>
			<div class="right_column_pong">
				<PongPlayerCard v-if="dataLoaded && player2Id.length !== 0" :id="player2Id" side="1" :emote="emote2.emoji">
				</PongPlayerCard>
			</div>
		</div>
	</div>
</template>

<script lang="ts">

import io from 'socket.io-client';
import { useRoute } from 'vue-router';
import PongPlayerCard from '@/components/PongPlayerCard.vue';
import EmoteButton from '@/components/EmoteButton.vue'
import PongCanvas from '@/components/PongCanvas.vue'
import { SocketService } from '@/services/SocketService';
import { State } from './Home.vue';
import BlueButton from '@/components/BlueButton.vue';

interface emote {
	emoji: string,
	changed: Boolean,
	timeout: ReturnType<typeof setTimeout>,
}

export default {
	data() {
		return {
			myUser: {} as any,
			player1Id: "",
			player2Id: "",
			dataLoaded: false,
			socket: io(),
			timer: "",
			score1: 0,
			score2: 0,
			emote1: { emoji: '' } as emote,
			emote2: { emoji: '' } as emote,
			state: 0,
		};
	},
	components: {
		PongPlayerCard,
		EmoteButton,
		PongCanvas,
		BlueButton
	},
	computed: {
		messageTop() {
			return (!this.state ? "En attente de joueur..." : "");
		}
	},
	methods: {
		setState(newState: number){
			this.state = newState;
		},
		getIdMode(mode: string) {
			const modes: string[] = ["classic", "arcade", "ranked", "duelClassic", "duelArcade"];
			if (!modes.includes(mode)) {
				this.$router.push('/notfound');
				return;
			}
			return modes.indexOf(mode);
		},

		toggleBackground(){
			this.$emit('toggleBackground');
		},

		emoteHandling(side: number, emoji: string) {
			let emote = side === 1 ? this.emote1 : this.emote2;
			if (emote.emoji !== '') {
				if (!emote.changed) {
					emote.emoji = '';
					emote.changed = true;
					setTimeout(() => {
						emote.emoji = emoji;
						emote.changed = false;
					}, 500)
				}
			}
			else
				emote.emoji = emoji;
			if (emote.timeout)
				clearTimeout(emote.timeout);
			emote.timeout = setTimeout(() => {
				emote.emoji = "";
			}, 2000);
		},


		initKeyHandler() {
			var keyArrowUp: Boolean = false
			var keyArrowDown: Boolean = false
			document.addEventListener('keydown', (event) => {
				if (event.key === "ArrowUp" && !keyArrowUp) {
					keyArrowUp = true;
					this.socket.emit("arrowUpdate", "arrowUp");
				}
				if (event.key === "ArrowDown" && !keyArrowDown) {
					keyArrowDown = true;
					this.socket.emit("arrowUpdate", "arrowDown");
				}
			});
			document.addEventListener('keyup', (event) => {
				if (event.key === "ArrowUp" && keyArrowUp) {
					keyArrowUp = false;
					this.socket.emit("arrowUpdate", "stopArrowUp");
				}
				if (event.key === "ArrowDown" && keyArrowDown) {
					keyArrowDown = false;
					this.socket.emit("arrowUpdate", "stopArrowDown");
				}
			});
		},
	},
	async mounted() {

		const route = useRoute();
		const mode: string | undefined = route.query["mode"]?.toString();
		if (!mode) {
			this.$router.push('notfound');
			return;
		}

		this.myUser = await (await fetch("http://" + import.meta.env.VITE_HOST + ":3000/user/me", { credentials: 'include' })).json()
		SocketService.getInstance.emit('setStatus', this.myUser["id"], State.INGAME);

		this.socket = io("http://" + import.meta.env.VITE_HOST + ":3000/pong", { query: { userId: this.myUser["id"] } }); //CHANGE TO GET ID
		this.socket.emit('onJoinGame', sessionStorage.getItem('token'), this.getIdMode(mode), route.query["id"]);

		this.initKeyHandler();

		this.socket.on('disconnect', () => {
			this.socket.disconnect();
			sessionStorage.setItem('timer', this.timer);
		});

		this.socket.on('ids', (player1: string, player2: string) => {
			this.player1Id = player1;
			this.player2Id = player2;
			this.dataLoaded = true;
		});

		this.socket.on('updateScore', (score1, score2) => {
			this.score1 = score1;
			this.score2 = score2;
		});

		this.socket.on('time', (time) => {
			this.timer = time;
		});

		this.socket.on('emote', (player, emoji) => {
			if (player == 0)
				this.emoteHandling(1, emoji);
			else
				this.emoteHandling(2, emoji);
		});
	},
	async beforeUnmount() {
		this.socket.disconnect();
		this.dataLoaded = false;
	}
}
</script>

<style>
.image {
	filter: drop-shadow(0 0 8px #1f81dd);
	aspect-ratio: 1;
	width: 100%;
	border-radius: 50%;
	border: 2px solid #b5dbdb;
}

.pong_body {
	width: 100vw;
	height: 90%;
	display: flex;
	align-items: center;
	justify-content: center;
}

.pong_content {
	position: relative;
	height: 90%;
	width: 90%;
	display: flex;
	justify-content: center;
	align-items: center;
	background: white;
	min-height: 300px;
	border: 3px solid #515151;
	border-radius: 20px;
	gap: 10px;
}

.left_column_pong, .right_column_pong {
	height: 100%;
	width: 15%;
	display: flex;
	flex-direction: column;
	align-items: center;
	justify-content: center;
}

.middle_column_pong {
	height: 100%;
	width: 80%;
	display: flex;
	flex-direction: column;
	align-items: center;
	justify-content: center;
}

.timer {
	display: flex;
	flex-direction: column;
	height: 100%;
	width: 100%;
	align-items: center;
	justify-content: center;
	font-family: 'digital-clock-font', monospace;
	font-size: clamp(1.25rem, 0.5769rem + 2.1538vw, 2.125rem);
	margin-bottom: -10px;
	margin-top: 10px;
}

.timer label{
	height: min-content;
	margin-top: clamp(-10px, -4%, -20px);
}

.button_panel {
	display: flex;
	height: 10%;
	width: 100%;
	align-items: center;
	justify-content: space-between;
}

.reaction_panel {
	display: flex;
	flex-direction: row;
	gap: 0.1vw;
	margin-left: 20px;
}

#exit_button {
	position: relative;
	min-width: 100px;
	font-size: clamp(0.6875rem, 0.2548rem + 1.3846vw, 1.25rem);
	padding: 10px;
	margin-right: 1vw;
	border-radius: 40px;
}

@font-face {
	font-family: 'digital-clock-font';
	src: url('/public/fonts/digital-7.mono.ttf');
}

.scores {
	display: flex;
	flex-direction: row;
	width: 100%;
	justify-content: center;
	gap: 50%;
	font-size: clamp(1.75rem, 1.1731rem + 1.8462vw, 2.5rem);
	margin-top: -25px;
	text-align: center;
	height: 100%;
	font-family: 'digital-clock-font', regular;
}

.top_infos {
	min-height: 80px;
	width: 100%;
	display: flex;
	height: 10%;
	flex-direction: column;
	justify-content: center;
	align-items: center;
	max-width: 1200px;
}

#state_msg {
	font-size: clamp(1.25rem, 0.5769rem + 2.1538vw, 2.125rem);
}

.tooltip_pong{
	display: inline-block;
	position: absolute;
	text-align: center;
	font-size: 2em;
	top: 0px;
	left: 10px;
	color: #2d8dc4;
	height: 50px;
}

.tooltip_pong .tooltip_pong_text {
  visibility: hidden;
  width: 80px;
  background-color: #032f3d;

  color: #fff;
  text-align: center;
  padding: 5px 0;
  border-radius: 6px;
 
  position: absolute;
  z-index: 1;

  width: 120px;
  top: 100%;
  left: 50%;
  margin-left: -40px;
  font-size: clamp(0.625rem, 0.4327rem + 0.6154vw, 0.875rem);
}

.tooltip_pong_text::after {
	content: " ";
  position: absolute;
  bottom: 100%;
  left: 33%;
  margin-left: -5px;
  border-width: 5px;
  border-style: solid;
  border-color: transparent transparent black transparent;
}

.tooltip_pong:hover {
	cursor: pointer;
}

.tooltip_pong:hover .tooltip_pong_text {
  visibility: visible;
}


</style>