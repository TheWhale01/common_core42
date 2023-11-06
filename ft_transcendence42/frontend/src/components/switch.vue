<template>
	<label class="switch">
		<input type="checkbox" v-model="checkbox" @click="clickAction">
		<div class="slider round"></div>
	</label>
</template>

<script lang="ts">

import router from '../router'

	function booleanize(str: string): boolean{
		return (str === "true");
	}

	function delay(ms: number) {
    	return new Promise( resolve => setTimeout(resolve, ms) );
	}

	export default{
		data() {
			return {checkbox: false, activated: true};
		},
		methods: {
			async clickAction() {
				if (!this.activated){
					return;
				}
				this.activated = false;
				if (!this.checkbox){
					this.checkbox = !this.checkbox;
					delay(500).then(any=>{router.push('/auth/2fa/home');});
				}
				else{
					this.checkbox = !this.checkbox; 
					delay(500).then(any=>{router.push({path:'/auth/2fa/off',query: { plan: 'off' }});});
				}
				await new Promise((resolve) => setTimeout(resolve, 2000));
				this.activated = true;
			},

			getStatus: async(vm: any) => {
				const res = await fetch("http://" + import.meta.env.VITE_HOST + ":3000/auth/2fa/status", {method: "get", credentials: "include"});
				const text = await (await res.blob()).text();
				vm.checkbox = booleanize(text);
			}

		},
		mounted(){
			this.getStatus(this);
		},
	}

</script>

<style>

.switch {
  position: relative;
  display: flex;
  width: 40px;
  height: 20px;
}

.switch input {
  display: none;
}

.slider {
  position: absolute;
  cursor: pointer;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  background-color: #ccc;
  -webkit-transition: 0.4s;
  transition: 0.4s;
}

.slider:before {
  position: absolute;
  content: "";
  height: 13px;
  width: 13px;
  left: 4px;
  bottom: 4px;
  background-color: white;
  -webkit-transition: 0.4s;
  transition: 0.4s;
}

input:checked + .slider {
  background-color: #2bb81e;
}

input:focus + .slider {
  box-shadow: 0 0 1px #2bb81e;
}

input:checked + .slider:before {
  -webkit-transform: translateX(19px);
  -ms-transform: translateX(19px);
  transform: translateX(19px);
}

.slider.round {
  border-radius: 34px;
}

.slider.round:before {
  border-radius: 50%;
}

</style>