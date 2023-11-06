<template>
	<div class="modal-overlay" @click="$emit('close-modal')">
		<div class="modal" @click.stop>
			<SlidingTitle text="Paramètres"></SlidingTitle>
			<div class="buttons-parameters">
				<div class="tfa">
					<div class="icon-tfa">
						<font-awesome-icon icon="fa-solid fa-lock"/>
					</div>
					<Switch/>
				</div>

				<BlueButton text="Changer Nom " icon="fa-solid fa-pen" @click="showModal = true"></BlueButton>
				<Teleport to="body">
					<transition name="slide-fade" mode="out-in">
						<ChangeUsernameModal v-show="showModal" @close-modal="showModal = false"
											@updated="updateNotif" @already-exist="alreadyExistNotif"
											@bad-format="badFormatNotif"></ChangeUsernameModal>
					</transition>
				</Teleport>
			</div>
		</div>
	</div>
</template>
  
<script lang="ts">
	import Switch from '@/components/switch.vue';
	import FileUpload from '@/components/FileUpload.vue'
	import ChangeUsernameModal from '@/components/ChangeUsernameModal.vue'
	import BlueButton from './BlueButton.vue';
	import SlidingTitle from './SlidingTitle.vue';
	import { useNotification } from "@kyvg/vue3-notification";



	export default{
		components: {
			Switch,
			FileUpload,
			ChangeUsernameModal,
			BlueButton,
			SlidingTitle
		},
		data(){
			return ({showModal: false});
		},
		methods:{
			updateNotif(){
				this.$emit('updated');
				const notification = useNotification()
				notification.notify({
					title: "Nom d'utilisateur changé !",
					type: 'success',
					group: 'notif-center'
				});
			},
			alreadyExistNotif(){
				const notification = useNotification()
				notification.notify({
					title: "Erreur",
					text: "Ce nom d'utilisateur existe déjà !",
					type: 'error',
					group: 'notif-center'
				});
			},
			badFormatNotif(){
				const notification = useNotification()
				notification.notify({
					title: "Erreur",
					text: "Veuillez entrer un format valide !",
					type: 'error',
					group: 'notif-center'
				});
			}
		}
	}
</script>
  
  <style scoped>
.modal-overlay {
	position: fixed;
	top: 0;
	bottom: 0;
	left: 0;
	right: 0;
	display: flex;
	justify-content: center;
	background-color: #242424d0;
	transition: opacity 0.3s ease;
	transition: all 0.3s ease;
}

.modal {
	text-align: center;
	background-color: white;
	height: 55%;
	width: 30%;
	margin-top: auto;
	margin-bottom: auto;
	padding: 60px 0;
	border-radius: 20px;
	display: flex;
	flex-direction: column;
	align-items: center;
}

.title-parameters {
	font-size: 50px;
	font-family: 'poppins'
}
.buttons-parameters{
	display: flex;
	flex-direction: column;
	gap: 90px;
	flex: 1;
	margin-top: 40px;
	width: 80%;
}

.buttons button{
	margin-top: 15%;
	margin-left: auto;
	margin-right: auto;
	width: 40%;
}
.tfa{
	background: rgb(34, 158, 230);
	border-radius: 10px;
	box-shadow: rgb(37, 18, 121) 0px 4px 0px 0px;
	padding: 10px;
	display: flex;
	font-family: 'Poppins';
	font-weight: bold;
	color: white;
	flex-direction: row;
	justify-content: space-around;
	align-items: center;
	font-size: 1em;
}
.icon-tfa{
	font-size: 2em;
}
  </style>