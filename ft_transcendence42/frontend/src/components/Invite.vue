<script lang="ts">

import { useNotification } from '@kyvg/vue3-notification';
import BlueButton from './BlueButton.vue';
import { SocketService } from '@/services/SocketService';

export default {
	components: {
		BlueButton,
	},

	props: ["myId", "friendId", "show"],

	methods: {
		goToPong(mode: string) {
			SocketService.getInstance.emit('getClientStatus', this.friendId);
			SocketService.getInstance.on('getClientStatus', (payload) =>{
				if (payload !== 1){
					const notif = useNotification();
					notif.notify({
						title: 'Erreur',
						text: "Ce joueur est déjà en jeu !",
						type: 'error',
						group: 'notif-center',
					});
				}
			});
			SocketService.getInstance.emit('pongInvite', this.myId, this.friendId,
				SocketService.getUser.name, mode);
			this.$emit('close-modals');
		}
	}
}

</script>

<template>
	<transition name="slide-fade" mode="out-in">
		<div v-if="show" class="play-modal-overlay" @click="$emit('close')">
			<div class="modal" @click.stop>
				<div class="play-modal-title">Choix du mode de jeu</div>
				<div class="buttons-play-modal">
					<BlueButton class="button-play-modal" text="Classique" @click="goToPong('duelClassic')"></BlueButton>
					<BlueButton class="button-play-modal" text="Arcade" @click="goToPong('duelArcade')"></BlueButton>
				</div>

			</div>
		</div>
	</transition>
</template>

<style></style>



