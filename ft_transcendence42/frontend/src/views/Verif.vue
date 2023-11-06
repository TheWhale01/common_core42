<template>
	<div class="verify-container">
		<div class="verify">
			<h4>Entrez le code</h4>
			<div class="input-field"  :class="[status === 'Failure' ? 'shakeAnimation' : ' ']">
				<form>
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
			<div v-if="status" class="status" :class="[status === 'Success' ? 'text-green' : 'text-red']">
				{{ status === "Failure" ? "Échec" : "Réussite" }}
			</div>
		</div>
	</div>

</template>
	
	
	
	
<script setup lang="ts">

	import router from '@/router';
	import { ref } from 'vue';
	import { useRoute } from 'vue-router';
	
	const route = useRoute();
	let status = ref("");
	
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
		}
		else
			status.value = "";
	}
	
	function handleDelete(event: Event) {
		let value = (event.target as HTMLInputElement).value;
		let currentActiveElement = event.target as HTMLInputElement;
		if (!value)
			(currentActiveElement.previousElementSibling as HTMLElement)?.focus();
	}
	
	function delay(ms: number) {
    	return new Promise( resolve => setTimeout(resolve, ms) );
	}

	async function sendCode(code: string){
		const res = await fetch("http://" + import.meta.env.VITE_HOST + ":3000/auth/2fa/verify",
			{
				method: 'POST',
				credentials: 'include',
				headers: {
					'Content-Type': 'application/json'
				},
				body: JSON.stringify({
					code: code,
				})
			})
			const json = await res.json();
			status.value = json["status"];
			if (status.value === "Success"){
				sessionStorage.setItem('tokens', json["token"]);
				delay(1000).then(any=>{router.push('/home');});
			}
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
	form {
		display: flex;
		flex-direction: row;
	}

	.verify-container{
		margin-top: 20vh;
		height: 60%;
	}

	.verify {
		display: flex;
		flex-direction: column;
		align-items: center;
		width: 270px;
		height: 170px;
		margin: auto;
		background: rgb(255, 255, 255);
		border-radius: 50px;
		box-shadow: 0 5px 10px rgba(0, 0, 0, 0.2);
	}
	.verify h4 {
		font-size: 1.25em;
		color: #333;
		font-weight: 500;
	}

	.input-field input {
		width: 10%;
		margin: auto;
		border-radius: 6px;
		margin-left: 10px;
		margin-right: 10px;
		outline: none;
		font-size: 1.125rem;
		text-align: center;
		border: 1px solid #ddd;
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
			margin-left: 0rem;
			margin-right: 0rem;
		}
		25% {
			margin-left: 0.75rem;
			margin-right: 0.75rem;
		}
		75% {
			margin-left: -0.5rem;
			margin-right: -0.5rem;
		}
		100% {
			margin-left: 0rem;
			margin-right: 0rem;
		}
	}

	.shakeAnimation{
		animation: shake 0.2s ease-in-out 0s 2;
	}

</style>