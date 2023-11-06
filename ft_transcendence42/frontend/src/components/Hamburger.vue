<script lang="ts">
import { SocketService } from '@/services/SocketService';
import BlueButton from './BlueButton.vue';

export default {
	components: {
		BlueButton
	},
	props: {
		id1: Number,
		id2: Number,
		username: String,
		show: Boolean
	},

	methods: {
		async deleteFriend() {
			const response = await fetch(`http://${import.meta.env.VITE_HOST}:3000/friend/delete?id1=${this.id1}&id2=${this.id2}`,{
				credentials: 'include',
				method: 'DELETE',
				headers: {
					'Content-Type': 'application/json'
				},
			});
			SocketService.getInstance.emit('refreshFriendListId', this.id1);
			SocketService.getInstance.emit('refreshFriendListId', this.id2);
			const text = await response.text();
			SocketService.getInstance.emit('hideChan', this.id1, text);
			SocketService.getInstance.emit('hideChan', this.id2, text);
		},

		async blockUser() {
			const response = await fetch(`http://${import.meta.env.VITE_HOST}:3000/user/block/blocked`,{
				credentials: 'include',
				method: 'POST',
				headers: {
					'Content-Type': 'application/json'
				},
				body: JSON.stringify({
					userId: this.id1,
					blockId: this.id2,
				}),
			});
		},
	}
}
</script>

<template>
	<Transition name="slide-fade" mode="out-in">
		<div v-if="show" class="modal_overlay" @click="$emit('close')">
			<div class="modal_friend" @click.stop>
				<p>Attention, <b> {{ username }}</b> va être :</p>
				<div class="button_box">
					<BlueButton text="Bloquer" v-on:click="blockUser(); deleteFriend(); $emit('close')"></BlueButton>
					<BlueButton text="Supprimer" v-on:click="deleteFriend(); $emit('close')"></BlueButton>
				</div>
			</div>
		</div>
	</Transition>
</template>

<style scoped>

.button_box {
	display: flex;
	height: 40%;
	justify-content: space-around;
	align-items: center;
	font-size: larger;
}

.button_box button {
	font-size: clamp(0.75rem, 0.6176rem + 0.7059vw, 1.125rem);
	display: flex;
	justify-content: center;
	align-items: center;
	height: 50%;
	width: 35%;
	border-radius: 20px;
}

.modal_overlay {
	position: fixed;
	display: flex;
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
	z-index: 3;
}

.modal_friend {
	min-width: 300px;
	display: flex;
	flex-direction: column;
	justify-content: center;
	right: 70%;
	width: 40%;
	height: 30%;
	background-color: white;
	border-radius: 20px;
}

.modal_friend p {
	text-align: center;
	font-size: 1.3em;
}

</style>
