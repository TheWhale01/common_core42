<template>
	<div class="input-field"  :class="[props.isInvalidCode ? 'shakeAnimation' : ' ']">
		<form class="form_2f">
			<input
			v-for="(n, index) in codeArr"
			:key="index"
			type="number"
			pattern="\d*"
			:id="'input_' + index"
			maxlength="1"
			v-model="codeArr[index]"
			@input="handleInput"
			@keypress="isKeyNumeric"
			@keydown.delete="handleDelete"
			@paste="onPaste"
			/>
		</form>
	</div>
</template>

<script setup lang="ts">
	import { ref } from 'vue';
	let status = ref("");
	const emit = defineEmits(['complete', 'reset']);
	const props = defineProps(['isInvalidCode']);

	let codeArr: string[] = ["", "", "", "", "", ""];
	let inputData: string[] | undefined;

	function isNumeric(str: string){
		const isNumeric = /^[0-9]+$/.test(str);
		return (isNumeric);
	}
	
	function isKeyNumeric(event: Event){
		(event.currentTarget as HTMLInputElement).value = "";
		const keyPressed: string = (event as KeyboardEvent).key;
		if (!isNumeric(keyPressed))
			event.preventDefault();
	}
	
	function handleInput(event: Event){
		const inputType = (event as InputEvent).inputType;
		let currentActiveElement = event.target as HTMLInputElement;
		if (props.isInvalidCode){
			emit('reset');
		}
		if (inputType === "insertText")
			(currentActiveElement.nextElementSibling as HTMLElement)?.focus();
		if (inputType === "insertFromPaste" && inputData) {
			for (const n of inputData){
				let i: number = parseInt(currentActiveElement.id.split("_")[1]);
				currentActiveElement.value = n;
				codeArr[i] = n;
				if (currentActiveElement.nextElementSibling) {
					currentActiveElement = currentActiveElement.nextElementSibling as HTMLInputElement;
					(currentActiveElement.nextElementSibling as HTMLElement)?.focus();
				}
			}
		}
		if (!codeArr.includes('')){
			sendCode(codeArr.join(''));
			codeArr = ["", "", "", "", "", ""];
		}
	}
	
	function handleDelete(event: Event) {
		let value = (event.target as HTMLInputElement).value;
		let currentActiveElement = event.target as HTMLInputElement;
		if (!value)
			(currentActiveElement.previousElementSibling as HTMLElement)?.focus();
	}

	async function sendCode(code: string){
		emit('complete', code);
		codeArr = ["", "", "", "", "", ""];
	}
	
	function onPaste(event: Event) {
		inputData = (event as ClipboardEvent).clipboardData
			?.getData("text")
			.trim()
			.split("");
	
		if (inputData) {
			for (const num of inputData) {
				if (!isNumeric(num))
					event.preventDefault();
			}
			if (!inputData.includes('')){
				sendCode(codeArr.join(''));
			}
		}
	}
</script>

<style>
	@import url('https://fonts.googleapis.com/css2?family=Ubuntu:wght@300;400;500;700&display=swap');
	.form_2f {
		display: flex;
		flex-direction: row;
		justify-content: space-evenly;
		gap: 6px;
	}

	.input-field{
		background-color: rgba(34, 158, 230, 0.103);
		padding: 10px;
		border-radius: 40px;
	}

	.input-field input {
		width: 30px;
		height: 30px;
		border-radius: 80px;
		outline: none;
		font-size: clamp(0.875rem, 0.25rem + 2vw, 1.375rem);
		text-align: center;
		border: 1px solid #515151;
	}
	.input-field input:focus {
		box-shadow: 0 1px 0 rgba(0, 0, 0, 0.1);
	}

	.input-field input::-webkit-outer-spin-button,
	.input-field input::-webkit-inner-spin-button {
		-webkit-appearance: none;
		margin: 0;
	}

	input[type="number"] {
		-moz-appearance: textfield;
	}

	.text-red{
		color: rgb(172, 42, 42);
	}

	.text-green{
		color: rgb(12, 167, 12);
	}

	.status{
		margin-top: 15px;
	}

	@keyframes shake {
		0% {
			transform: translateX(0px);
		}
		25% {
			transform: translateX(20px);
		}
		75% {
			transform: translateX(-20px);
		}
		100% {
			transform: translateX(0px);
		}
	}

	.shakeAnimation{
		animation: shake 0.2s ease-in-out 0s 2;
	}

</style>

