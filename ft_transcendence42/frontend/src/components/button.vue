<script setup lang="ts">
import {ref} from 'vue'

const getStr = defineProps(['str'])
const input = ref('')

const emit = defineEmits(['updateInput'])

const handleUpdate = (event) => {
	emit('updateInput', event.target.value)
}

</script>

<template>

<div class="field">
	<button class="btn" @click="handleUpdate">connection</button>
</div>

</template>

<style>

.btn{

	color: #595959;

}
.btn:focus{
	color: #3498db;
	box-shadow:  4px 4px 4px #606060,
             -4px -4px 4px #c9c9c9;
}

</style>