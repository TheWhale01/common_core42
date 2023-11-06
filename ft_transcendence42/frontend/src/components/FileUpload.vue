<template>
	<div class="container-upload">
		<div>
			<h2>Change Avatar</h2>
			<label>
				<input type="file" @change="handleFileUpload( $event )" accept="image/*"/>
			</label>
			<button @click="addFile">Submit</button>
		</div>
	</div>
</template>

<script lang="ts">

	export default {
		data(){
			return {
				file: ''
			}
		},
		
		methods: {
			handleFileUpload( event ){
				this.file = event.target.files[0];
			},
			
			addFile(){
				let formData = new FormData();
				formData.append("file", this.file);
				const res = fetch("http://" + import.meta.env.VITE_HOST + ":3000/avatar/update",
				{
					method: "post",
					credentials: 'include',
					body: formData,
				})
				.then(res => this.$emit('updated'));
			}
		}
	}
</script>
