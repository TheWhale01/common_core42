<script lang="ts">
import { defineComponent } from 'vue';
import SlidingTitle from './SlidingTitle.vue';
import BlueButton from './BlueButton.vue';

export default defineComponent({
	components: {
		SlidingTitle,
		BlueButton
	},
	data() {
		return ({
			input: '' as string,
			channelId: -1 as number,
			inputValue: "",
		});
	},

	props: ['title', 'show', 'placeholder', 'callback', 'isDigit', 'isPassword'],

	methods: {
		isNumber(evt: KeyboardEvent): void {
			const keysAllowed: string[] = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'];
			const keyPressed: string = evt.key;
			if (!keysAllowed.includes(keyPressed)) {
				evt.preventDefault();
			}
		},
	}
});

</script>

<template>
	<div class="channel_options_modal">
		<SlidingTitle class="channel_options_title" :text="title"></SlidingTitle>
		<input v-if="isPassword" type="password" :maxlength="32" v-model="input" class="channel_options_input" :placeholder=placeholder />
		<input v-else-if="isDigit" :maxlength="5" v-model="input" @keypress="isNumber($event)" class="channel_options_input" :placeholder=placeholder />
		<input v-else v-model="input" class="channel_options_input" type="text" :placeholder=placeholder />
		<BlueButton class="channel_options_button" text="Confirmer" @click="$emit('callback', input)"></BlueButton>
	</div>
</template>

<style>
.channel_options_modal {
	display: flex;
	flex-direction: column;
	justify-content: center;
	align-items: center;
	width: 75%;
	max-width: 500px;
	height: 50%;
	background-color: white;
	border-radius: 20px;
	gap: 15%;
}

.channel_options_input {
	border-radius: 20px;
	width: 70%;
	height: 15%;
	text-align: center;
	font-size: larger;
}

.channel_options_button {
	border: none;
	height: 15%;
	width: 60%;
	font-size: clamp(0.75rem, 0.3654rem + 1.2308vw, 1.25rem);
}
</style>