<template>
	<button class="blue-button">
		<div class="blue-button-text" v-if="this.displayText"> 
			{{ this.text }}
		</div>
		<font-awesome-icon class="icon" v-if="this.icon" :icon="this.icon"/>
	</button>
</template>

<script lang="ts">

export default{
	props: {
		text: {
			type: String,
		},
		icon: {
			type: String,
		},
		displayText: {
			type: Boolean,
			default: true
		}
	}
}

</script>

<style>

.blue-button{
	position: relative;
	font-family: 'Poppins';
    font-weight: bold;
	font-size: clamp(0.625rem, 0.4861rem + 0.4444vw, 0.75rem);
	background-color: rgb(34, 158, 230);
	border-radius: 10px;
	box-shadow: rgb(37, 18, 121) 0px 4px 0px 0px;
	padding: 10px;
	background-repeat: no-repeat;
	box-sizing: border-box;
	color: #fff;
	display: flex;
	justify-content: center;
	align-items: center;
	border: none;
	transition: all .3s ease-in-out;
	overflow: hidden;
	overflow-wrap: break-word;
	cursor: pointer;
}


.blue-button-text{
	width: 100%;
}

.blue-button::before{
	content: "";
	background-color: rgb(255, 255, 255);
	width: 0;
	height: 100%;
	position: absolute;
	top: 0;
	left: 0;
	transition: width 700ms ease-in-out;
	opacity: 50%;
}

.blue-button:hover::before {
	width: 100%;
	opacity: 50%;
}

.icon{
	width: 30%;
}

</style>