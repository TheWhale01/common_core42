<template>
	<div class="add_container">
		<button @mouseenter="showTooltip = true" @mouseleave="showTooltip = false" class="add-button"><font-awesome-icon :icon="this.icon"/> {{ this.text }}</button>
		<transition name="fade2" mode="out-in">
			<span v-if="showTooltip" class="tooltiptext">{{tooltip_text}}</span>
		</transition>
	</div>
</template>

<script lang="ts">

export default{
	props: ["text", "icon", "tooltip_text"],

	data() {
		return ({showTooltip: false})
	}
}

</script>

<style scoped>

.add_container {
	height: 90%;
	width: 25%;
	position: relative;
	display: inline-block;
	border-radius: 120px;
}

.add_container .tooltiptext {
  visibility: hidden;
  width: 120px;
  background-color: #032f3d;

  color: #fff;
  text-align: center;
  padding: 5px 0;
  border-radius: 6px;
 
  position: absolute;
  z-index: 1;

  width: 120px;
  bottom: 120%;
  left: 50%;
  margin-left: -60px;
  font-size: clamp(0.625rem, 0.4327rem + 0.6154vw, 0.875rem);
}

.add_container .tooltiptext::after {
    content: " ";
    position: absolute;
    top: 100%;
    left: 50%;
    margin-left: -5px;
    border-width: 5px;
    border-style: solid;
    border-color: black transparent transparent transparent;
}

.add_container:hover .tooltiptext {
  visibility: visible;
}

.add-button{
	border-radius: 120px;
	background-color: #046280;
	height: 100%;
	width: 100%;;
	color: white;
	border: none;
	font-size: clamp(0.625rem, 0.3365rem + 0.9231vw, 1rem);
	overflow: hidden;
	cursor: pointer;
}

.add-button:hover {
	background-color: #032f3d;
}

.fade2-enter-active,
.fade2-leave-active {
  transition: opacity 0.2s ease;
  opacity: 1;
}

.fade2-enter-from,
.fade2-leave-to {
  opacity: 0;
}

</style>