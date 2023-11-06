<script lang="ts">

import Avatar from '@/components/Avatar.vue'
import ModalSettings from '@/components/ModalSettings.vue';
import ChangeUsernameModal from './ChangeUsernameModal.vue';
import BlueButton from './BlueButton.vue';
import router from '../router';
import { useNotification } from "@kyvg/vue3-notification";
import Switch from './switch.vue';
import { SocketService } from '@/services/SocketService';
import  ModalQrcode from '@/components/ModalQrcode.vue';

export default {
	components: {
		Avatar,
		ModalSettings,
		BlueButton,
		ChangeUsernameModal,
		Switch,
		ModalQrcode,
	},
	props: ["editable", "user"],
	data(){
		return ({
				showModal: false,
				windowWidth: window.innerWidth,
				showQrcode: false,
				showBlockButton: true,
				showAddButton: true,
			});
	},

	methods: {
		logout(){
			router.push("/auth/logout");
		},

		notify(title: string, text: string, type: string){
			const notification = useNotification()
			notification.notify({
				title: title,
				text: text,
				type: type,
				group: 'notif-center'
			});
		},
		handleResize() {
			this.windowWidth = window.innerWidth;
		},
		handle2fa(){
			router.push('/auth/2fa/home');
		},
		addFriendNotif (text: string, status: string) {
			const notification = useNotification()
			notification.notify({
				title: text,
				type: status,
				group: 'notif-center'
			});
		},
		async addUser() {
			const response = await fetch('http://' + import.meta.env.VITE_HOST + ':3000/friend/add',{
				credentials: 'include',
				method: 'POST',
				headers: {
					'Content-Type': 'application/json'
				},
				body: JSON.stringify({
					username: this.user.name,
					sender: SocketService.getUser["id"],
				})
			})
			const ret = await (await response.blob()).text();
			if (ret.length == 0) {
				this.addFriendNotif("Demande d'ami envoyé", "success");
				this.$emit('close');
				SocketService.getInstance.emit('refreshFriendList', this.user.name);
				SocketService.getInstance.emit('addFriendNotif', this.user.name);
				this.showAddButton = false;
			}
		},
		async deleteFriend() {
			const response = await fetch(`http://${import.meta.env.VITE_HOST}:3000/friend/delete?id1=${this.user.id}&id2=${SocketService.getUser.id}`,{
				credentials: 'include',
				method: 'DELETE',
				headers: {
					'Content-Type': 'application/json'
				},
			});
			SocketService.getInstance.emit('refreshFriendListId', this.user.id);
			SocketService.getInstance.emit('refreshFriendListId', SocketService.getUser.id);
			const text = await response.text();
			SocketService.getInstance.emit('hideChan', this.user.id, text);
			SocketService.getInstance.emit('hideChan', SocketService.getUser.id, text);
		},

		async blockUser() {
			const response = await fetch(`http://${import.meta.env.VITE_HOST}:3000/user/block/blocked`,{
				credentials: 'include',
				method: 'POST',
				headers: {
					'Content-Type': 'application/json'
				},
				body: JSON.stringify({
					userId: SocketService.getUser.id,
					blockId: this.user.id,
				}),
			});
			this.showBlockButton = false;
			this.showAddButton = false;
			await this.deleteFriend();
		},

		async init(){
			const response = await fetch('http://' + import.meta.env.VITE_HOST + ':3000/friend/isFriend',{
				credentials: 'include',
				method: 'POST',
				headers: {
					'Content-Type': 'application/json'
				},
				body: JSON.stringify({
					username: this.user.name,
					sender: SocketService.getUser["id"],
				})
			})
			const ret = await (await response.blob()).text();
			const isBlockedRes = await fetch(`http://${import.meta.env.VITE_HOST}:3000/user/isBlocked`,{
				credentials: 'include',
				method: 'POST',
				headers: {
					'Content-Type': 'application/json'
				},
				body: JSON.stringify({
					userId: SocketService.getUser.id,
					blockId: this.user.id,
				}),
			});
			const retBlocked = await isBlockedRes.json();
			this.showAddButton = ret === "true" ? false : true;
			this.showAddButton = this.showAddButton && !retBlocked;
			this.showBlockButton = !retBlocked;
		},
	},
	async created(){
		window.addEventListener('resize', this.handleResize);
		await this.init();
	},
}

</script>

<template>
	<div class="card">
		<Avatar :editable="editable" :path="user.avatarLink" @updated="$emit('update')" @failure="notify('Erreur', 'Mauvais format d\'image !', 'error')" ></Avatar>
		<div class="userInfos">
			<h1>{{ user.name }}</h1>
		</div>
		<div class="buttons">
			<Teleport to="body">
				<transition name="slide-fade" mode="out-in">
					<ChangeUsernameModal v-show="showModal" @close-modal="showModal = false"
											@updated="notify('', 'Nom d\'utilisateur changé !', 'success'); $emit('update');"
											@already-exist="notify('Erreur', 'Ce nom d\'utilisateur existe déjà !', 'error')"
											@bad-format="notify('Erreur', 'Veuillez entrer un format valide !', 'error')">
					</ChangeUsernameModal>
				</transition>
			</Teleport>

			<Teleport to="body">
				<transition name="slide-fade" mode="out-in">
					<ModalQrcode v-if="showQrcode" @close="showQrcode = false"></ModalQrcode>
				</transition>
			</Teleport>

			<div class="buttons-items" v-if="editable != 0"> 
				<BlueButton class="button-profile" text="Changer Nom " icon="fa-solid fa-pen" :display-text="windowWidth >= 1250" @click="showModal = true"></BlueButton>
				<BlueButton class="button-profile" text="Double Authentification " icon="fa-solid fa-lock" :display-text="windowWidth >= 1250" @click="showQrcode = true"></BlueButton>
				<BlueButton class="button-profile"  text="Déconnection " icon="fa-solid fa-right-from-bracket" @click="logout" :display-text="windowWidth >= 1250"></BlueButton>
			</div>
			<div v-else class="buttons-items">
				<BlueButton class="button-profile" v-if="showAddButton" @click="addUser" text="Ajouter en ami " icon="fa-solid fa-user-group" :display-text="windowWidth >= 1250" ></BlueButton>
				<BlueButton class="button-profile" v-if="showBlockButton" @click="blockUser" text="Bloquer" icon="fa-solid fa-lock" :display-text="windowWidth >= 1250" ></BlueButton>
			</div>
		</div>
	</div>
</template>

<style>

.card {
	display: flex;
	border: 2px solid #515151;
	justify-content: space-between;
	padding: 2%;
	align-items: center;
	background-color: white;
	flex-direction: row;
	border-radius: 50px;
	font-size: clamp(0.8125rem, 0.476rem + 1.0769vw, 1.25rem);
}

.buttons {
	display: flex;
	flex-direction: column;
	min-width: 70px;
}

.slide-fade-default-button {
	float: right;
}

.slide-fade-enter-from {
	opacity: 0;
}

.slide-fade-leave-to {
	opacity: 0;
}

.slide-fade-enter-from .modal-container,
.slide-fade-leave-to .modal-container {
	-webkit-transform: scale(1.5);
	transform: scale(1.5);
}

.button-profile {
	margin: 10px;
	height: 50px;
}

.buttons {
	display: flex;
	width: 15%;
}

.tfa {
	background: rgb(34, 158, 230);
	border-radius: 10px;
	box-shadow: rgb(37, 18, 121) 0px 4px 0px 0px;
	padding: 10px;
	margin: 10px;
	display: flex;
	font-family: 'Poppins';
	font-weight: bold;
	color: white;
	flex-direction: row;
	justify-content: space-around;
	align-items: center;
	font-size: 1em;
}

.tfa-extra {
	display: flex;
	gap: 30px;
	align-items: center;
}

.buttons-items {
	display: flex;
	flex-direction: column;
}

</style>
