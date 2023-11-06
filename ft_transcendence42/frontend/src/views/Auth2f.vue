<template>
	<div class="auth">
		<div class="auth-card">
			<h1 class="title">Double Authentification</h1>
			<div class="auth-container">
				<img v-if="generated === true" :src="getUrl()" :class="[blur  ? 'blur' : ' ']" @click="toggleBlur" class="img-2fa">
				<img v-else src="@/assets/img/lock.png" class="img-2fa">
				<div class="info-box">
					<BlueButton v-if="!generated" text="Activer" icon="fa-solid fa-check" class="card-button" @click="redirect({ path: '/auth/2fa/generate'})"/>

					<BlueButton v-else-if="activated === false" text="Activer" icon="fa-solid fa-check" class="card-button"
						@click="redirect({ path: '/auth/2fa/verif', query: { plan: 'on' }})"/>

					<BlueButton v-else-if="activated === true" text="Désactiver" icon="fa-solid fa-xmark" class="card-button"
						@click="redirect({ path:'/auth/2fa/off', query: { plan: 'off' }})"/>
				</div>
			</div>
		</div>
	</div>
</template>

<script lang="ts">

import { ref } from 'vue';
import BlueButton from '@/components/BlueButton.vue';
import router from '@/router';

export default{
    data() {
        return { user: Promise<any>, "activated": false, "generated": false, blur: ref(true), };
    },
    methods: {
        getStatus: async (vm: any) => {
            const res = await fetch("http://" + import.meta.env.VITE_HOST + ":3000/auth/2fa/completeStatus", { method: "get", credentials: "include" });
            const text = (await res.json());
            vm.activated = text["activated"];
            vm.generated = text["generated"];
        },
        getUser: async (vm: any) => {
            const res = await fetch("http://" + import.meta.env.VITE_HOST + ":3000/user/me", { credentials: "include" });
            const user = await res.json();
            vm.user = user;
        },
        toggleBlur() {
            this.blur = !this.blur;
        },
		getUrl(){
			return ("http://" + import.meta.env.VITE_HOST + ":3000/auth/2fa/qrcode")
		},
		redirect(redirectObject: any){
			router.push(redirectObject);
		}
    },
    mounted() {
        this.getUser(this);
        this.getStatus(this);
    },
    components: { BlueButton }
}
</script>

<style>

.auth{
	height: 100%;
	display: flex;
    justify-content: center;
    align-content: center;
    align-items: center;
}

.auth-card{
	display: flex;
	flex-direction: column;
	align-items: center;
	border-radius: 50px;
	justify-content: space-evenly;
	background-color: aliceblue;
	width: 60vw;
	height: 60vh;
}

.title{
	font-size: clamp(0.625rem, -0.2083rem + 2.6667vw, 1.375rem);
}

.auth-container{
	display: flex;
	background-color: rgba(34, 158, 230, 0.103);
	flex-direction: row;
	align-items: center;
	justify-content: space-between;
	width: 90%;
	height: 90%;
	border-radius: 60px;
	margin-bottom: 30px;
}

.card-button{
	font-size: clamp(0.625rem, 0.0694rem + 1.7778vw, 1.125rem);
	width: 50%;
	margin: 20%;
}

.info-box{
	display: flex;
	flex-direction: column;
	justify-content: center;
	height: 100%;
	width: 50%;
}

.img-2fa { 
    image-rendering: optimizeSpeed;
    image-rendering: -moz-crisp-edges;
    image-rendering: -o-crisp-edges;
    image-rendering: -webkit-optimize-contrast;
	image-rendering: pixelated;
    image-rendering: optimize-contrast;
    -ms-interpolation-mode: nearest-neighbor;
	transition: filter 0.5s ease-in-out;
	width: clamp(100px, 40%, 400px);
	margin-left: 30px;
	aspect-ratio: 1;
}

.qrcode{
	position: relative;
	display: inline-block;
}

.blur{
	filter: blur(10px);
	transition: filter 0.5s ease-in-out;
}

</style>