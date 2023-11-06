<script lang="ts">
	export default {
		props: ['path', 'editable'],
		methods:{
			openFileUpload() {
				this.$refs.fileInput.click();
			},
			uploadFile(event) {
				const file = event.target.files[0];
				let formData = new FormData();
				formData.append("file", file);
				const res = fetch("http://" + import.meta.env.VITE_HOST + ":3000/avatar/update",
				{
					method: "post",
					credentials: 'include',
					body: formData,
				})
				.then(res => {
					if (res.status != 201)
						this.$emit('failure');
					else
						this.$emit('updated')
				})
			}
		}
	}
</script>

<template>
	<div class="avatar-container">
		<img :src="path" class="image" draggable="false" alt="avatar"/>
		<button class="change-button" @click="openFileUpload" v-if="editable != 0">
			<font-awesome-icon icon="fa-solid fa-pen"/>
		</button>
		<input type="file" ref="fileInput" style="display: none" @change="uploadFile" accept="image/*"/>
	</div>

</template>

<style>
	.avatar-container{
		position: relative;
		width: 15%;
	}

	.image{
		filter: drop-shadow(0 0 8px #1f81dd);
		aspect-ratio: 1;
		width: 100%;
		border-radius: 50%;
		border: 2px solid #b5dbdb;
	}

	.change-button {
		position: absolute;
		top: 8%;
		padding: 2%;
		right: 8%;
		background-color: #ffffff;
		color: #000000;
		cursor: pointer;
		border: none;
		border-radius: 20px;
		font-size: clamp(0.75rem, 0.5577rem + 0.6154vw, 1rem);
	}

</style>
