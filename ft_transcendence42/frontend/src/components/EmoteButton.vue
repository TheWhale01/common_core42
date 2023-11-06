<template>
	<div class="emoteContainer" @click="test">
		{{ emoji }}
	</div>
</template>

<script lang="ts">
import { SocketService } from '@/services/SocketService';


export default {
	props: ["emoji", "socket"],
	methods: {
		test() {
			this.socket.emit('emote', this.emoji);
		}
	}
}

</script>

<style>
.emoteContainer {

	position: relative;
  background: #fff;
  border-radius: 50%;
  margin: 10px;
  width: 30px;
  height: 30px;
  display: flex;
  justify-content: center;
  align-items: center;
  flex-direction: column;
  box-shadow: 0 5px 10px rgba(0, 0, 0, 0.3);
  cursor: pointer;
  transition: all 0.2s cubic-bezier(0.68, -0.55, 0.265, 1.55);
  background-color: #229EE6;

  border: #0e6394 solid 1px;
	font-size: clamp(0.75rem, 0.4853rem + 1.4118vw, 1.5rem);
	padding: 3px;
}

.emoteContainer:hover {
	background-color: #91CEF2;
	cursor: pointer;
}
</style>