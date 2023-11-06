<script setup lang="ts">
import {ref} from 'vue'

const getStr = defineProps(['str'])
const input = ref()

const emit = defineEmits(['updateInput'])

const handleUpdate = (event) => {
	emit('updateInput', event.target.value)
}

</script>

<template>
	
<div class="field">
	<input  type="text" required v-model="input" @input="handleUpdate">
	<label>{{ str }}</label>
</div>

</template>

<style>

.field{
	height: 50px;
	width: 100%;
	display: flex;
	position: relative;
}
.field:nth-child(2){
	margin-top: 20px;
}.field:nth-child(3){
	margin-top: 20px;
}
.field input{
	height: 100%;
	width: 100%;
	padding-left: 25px;
	padding-right: 25px;
	outline: none;
	border: none;
	font-size: 18px;
	background: #dde1e7;
	color: #595959;
	border-radius: 25px;
	box-shadow: inset 2px 2px 5px #BABECC,
				inset -5px -5px 10px #ffffff73;
}
.field input:focus{
	box-shadow: inset 1px 1px 2px #BABECC,
				inset -1px -1px 2px #ffffff73;
}
.field span{
	position: absolute;
	color: #595959;
	width: 50px;
	line-height: 50px;
}
.field label{
	position: absolute;
	top: 50%;
	transform: translateY(-50%);
	left: 25px;
	pointer-events: none;
	color: #666666;
}
.field input:valid ~ label{
	opacity: 0;
}

</style>