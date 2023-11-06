<template>
	<div class="pongPlayerCard">
		<Transition name="bounce">
			<div v-if="emote != undefined && emote != '' " class="emote" :class="[side == 0  ? 'emote-left' : 'emote-right']" >
				{{ emote }}
			</div>
		</Transition>
		<img alt="avatar" :src="user.avatarLink" class="image" id="PongCardAvatar" draggable="false"/>
		<div class="pongPlayerCardText">
			{{ user.name }}
		</div>
	</div>
</template>

<script lang="ts">

export default {
	props: ["id", "emote", "side"],
	data() {
		return {user: Object};
	},
	mounted() {
		fetch("http://" + import.meta.env.VITE_HOST + ":3000/user/id/" + this.id, {credentials: 'include'})
		.then(res => res.json())
		.then(data => {this.user = data;});
	}
}

</script>

<style>

#PongCardAvatar{
	width: 40%;
}

.pongPlayerCard {
	display: flex;
	justify-content: center;
	align-items: center;
	flex-direction: column;
	border-radius: 10px;
}

.pongPlayerCardText {
	margin-top: 15px;
	font-size: 1.3vw;
}

.emote {
	position: absolute;
	z-index: 1;
	font-size: 3vw;
	text-align: center;
	margin-top: 10px;
}

.emote-left {
	margin-left: 6%;
}

.emote-right {
	margin-right:  6%;
}

.bounce-enter-active {
  animation: bounce-in 0.5s;
}
.bounce-leave-active {
  animation: bounce-in 0.5s reverse;
}
@keyframes bounce-in {
  0% {
    transform: scale(0);
  }
  50% {
    transform: scale(1.25);
  }
  100% {
    transform: scale(1);
  }
}

</style>

