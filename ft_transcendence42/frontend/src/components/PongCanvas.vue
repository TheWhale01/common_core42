<template>
	<div class="pong_screen">
		<canvas id="pongCanvas" width="1200" height="600"></canvas>
	</div>
</template>

<script lang="ts">

const TPI = 6.2831853;

import type { ball } from '@/interfaces/ball.interface'
import type { gameInfos } from '@/interfaces/gameInfos.interface'
import type { paddle } from '@/interfaces/paddle.interface'
import confetti from 'canvas-confetti';

export default {
	props: ["socket", "playId1", "playId2", "score1", "score2"],

	data() {
		return {
			sprites: [] as Array<ImageBitmap>,
			animId: -1,
			ball: { speed: -1 } as ball,
			user1Img: new Image,
			user2Img: new Image,
			user1Id: 0,
			user2Id: 0,
			user1Name: "",
			user2Name: "",
			pad1: {} as paddle,
			pad2: {} as paddle,
			gameInfos: {} as gameInfos,
			lastUpdate: -1 as number,
			angle: 0,
			offsetX: 0,
			isInGame: false,
			confettiId: -1,
			discoUserId: -1,
			
			domCtx: {} as CanvasRenderingContext2D,
			isLoaded: false,
			lastTimeStamp: window.performance.now(),
		}
	},
	methods: {
		async loadImage(path: string): Promise<HTMLImageElement> {
			return new Promise(r => { let i = new Image(); i.onload = (() => r(i)); i.src = path; });
		},

		async init() {
			this.sprites.push(await createImageBitmap(await this.loadImage("/powerups/big_pad.png")));
			this.sprites.push(await createImageBitmap(await this.loadImage("/powerups/lil_pad.png")));
			this.sprites.push(await createImageBitmap(await this.loadImage("/powerups/speed.png")));
			this.sprites.push(await createImageBitmap(await this.loadImage("pong_background.png")));
			this.sprites.push(await createImageBitmap(await this.loadImage("paddle.png")));
			this.sprites.push(await createImageBitmap(await this.loadImage("queueing_background.png")));
			this.sprites.push(await createImageBitmap(await this.loadImage("queueing_ananas.png")));
			this.domCtx = (<HTMLCanvasElement>document.getElementById('pongCanvas')).getContext('2d') as CanvasRenderingContext2D;
			this.isLoaded = true;

		},

		animate(ctx: CanvasRenderingContext2D, canvas: HTMLCanvasElement) {
			this.animId = requestAnimationFrame(() => { this.animate(ctx, canvas) });
			const msNow = window.performance.now()
			const msPassed = msNow - this.lastTimeStamp

			if (msPassed < (1000 / 60))
				return

			const excessTime = msPassed % (1000 / 60)
			this.lastTimeStamp = msNow - excessTime;
			this.$emit('setState', 0)
			ctx.clearRect(0, 0, canvas.width, canvas.height);
			ctx.drawImage(this.sprites[5], 0, 0, canvas.width, canvas.height);

			this.angle += 0.02;
			this.offsetX += 1;
			let offsetY = canvas.height / 2.2 + Math.sin(this.angle) * 20;
			if (this.offsetX > canvas.width) {
				this.offsetX = -this.sprites[6].width;
			}
			ctx.drawImage(this.sprites[6], this.offsetX, offsetY - canvas.height / 6);
		},


		confettiEffect(end: number) {
				let drift = Math.random() * 5
				confetti({
					particleCount: 5,
					angle: 60,
					spread: 70,
					origin: { x: 0 },
					gravity: 0.8,
					drift: drift,
				});
				confetti({
					particleCount: 5,
					angle: 120,
					spread: 70,
					origin: { x: 1 },
					gravity: 0.8,
					drift: -drift,
				});

				if (Date.now() < end) {
					this.confettiId = requestAnimationFrame(() => {this.confettiEffect(end)});
				}
			},

		async drawEndPage(ctx: CanvasRenderingContext2D, canvas: HTMLCanvasElement) {

			ctx.fillStyle = 'white dark'
			ctx.textBaseline = "middle";
			ctx.textAlign = "center";

			let offsetX1;
			let offsetX2;
			this.score1 <= 9 ? offsetX1 = 70 : offsetX1 = 105;
			this.score2 <= 9 ? offsetX2 = 70 : offsetX2 = 105;

			ctx.font = "60px poppins";
			ctx.fillText(this.user1Name, canvas.width / 4, canvas.height - canvas.height / 5)
			ctx.fillText(this.user2Name, canvas.width - canvas.width / 4, canvas.height - canvas.height / 5)

			ctx.font = "150px poppins";
			ctx.fillText(this.score1, offsetX1, canvas.height / 2 + canvas.height / 20);
			ctx.fillText(this.score2, canvas.width - offsetX2, canvas.height / 2 + canvas.height / 20);
			ctx.drawImage(this.user1Img, canvas.width / 6, canvas.height / 3, 200, 200)
			ctx.drawImage(this.user2Img, canvas.width - canvas.width / 3,canvas.height / 3, 200, 200)

			ctx.font = "100px poppins";
			let text1: string;
			let text2: string;


			if (this.discoUserId !== -1){
				text1 = this.user1Id === this.discoUserId ? "ABD" : "Victoire";
				text2 = this.user2Id === this.discoUserId ? "ABD" : "Victoire";
			}
			else {
				text1 = this.score1 > this.score2 ? "Victoire" : (this.score2 > this.score1) ? "Défaite" : "Égalité";
				text2 = this.score2 > this.score1 ? "Victoire" : (this.score1 > this.score2) ? "Défaite" : "Égalité";
			}
			ctx.fillText(text1, canvas.width / 4, canvas.height / 6 + canvas.height / 20);
			ctx.fillText(text2, canvas.width - canvas.width / 4, canvas.height / 6 + canvas.height / 20);
		},

		async animateEnd(ctx: CanvasRenderingContext2D, canvas: HTMLCanvasElement) {
			ctx.clearRect(0,0,canvas.width, canvas.height)
			ctx.drawImage(this.sprites[3], 0, 0);
			var end = Date.now() + (1000 * 1);
			this.confettiEffect(end);

			const player1Json = await (await (fetch("http://" + import.meta.env.VITE_HOST + ":3000/user/id/" + this.playId1, {credentials: 'include'}))).json();
			this.user1Id = player1Json["id"];
			this.user1Name = player1Json["name"]
			this.user1Img.src = player1Json["avatarLink"]

			const player2Json = await (await (fetch("http://" + import.meta.env.VITE_HOST + ":3000/user/id/" + this.playId2, {credentials: 'include'}))).json();
			this.user2Id = player2Json["id"];
			this.user2Name = player2Json["name"]
			this.user2Img.src = player2Json["avatarLink"]
			
			await this.drawEndPage(ctx, canvas);
			this.$emit('setState', 2)
		},


		drawRect(ctx: CanvasRenderingContext2D, x: number, y: number, width: number, size: number, color: string) {
			ctx.beginPath();
			ctx.rect(x, y, width, size);
			ctx.fillStyle = color;
			ctx.fill();
			ctx.closePath();
		},

		drawText(ctx: CanvasRenderingContext2D, canvas: HTMLCanvasElement, text: string) {
			ctx.clearRect(0, 0, canvas.width, canvas.height);
			ctx.font = "200px serif";
			ctx.fillText(text, 50, canvas.height / 2);
			ctx.fillStyle = 'white'
		},

		drawCircle(ctx: CanvasRenderingContext2D, x: number, y: number, radius: number, color: string) {
			ctx.beginPath();
			ctx.arc(x, y, radius, 0, TPI);
			ctx.fillStyle = color;
			ctx.lineWidth = 6;
			ctx.strokeStyle = "white";
			ctx.stroke();
			ctx.fill();
			ctx.closePath();
		},

		drawPowerups(ctx: CanvasRenderingContext2D) {
			if (!this.gameInfos.powerups)
				return;
			for (var item of this.gameInfos.powerups as any[]) {
				ctx.drawImage(this.sprites[item.effect], item.pos.x, item.pos.y, item.radius, item.radius);
			}
		},

		draw(time: number) {
			this.animId = requestAnimationFrame(this.draw);
			if (this.lastUpdate === -1) {
				this.lastUpdate = time;
			}
			if (this.ball.speed === -1) {
				this.ball = this.gameInfos.ball;
				this.pad1 = this.gameInfos.pad1;
				this.pad2 = this.gameInfos.pad2;
			}
			this.ball.position.x += (this.gameInfos.ball.position.x - this.ball.position.x) * 0.5;
			this.ball.position.y += (this.gameInfos.ball.position.y - this.ball.position.y) * 0.5;

			this.pad1.pos.x += (this.gameInfos.pad1.pos.x - this.pad1.pos.x) * 0.2;
			this.pad1.pos.y += (this.gameInfos.pad1.pos.y - this.pad1.pos.y) * 0.2;

			this.pad2.pos.x += (this.gameInfos.pad2.pos.x - this.pad2.pos.x) * 0.2;
			this.pad2.pos.y += (this.gameInfos.pad2.pos.y - this.pad2.pos.y) * 0.2;

			this.domCtx.clearRect(0, 0, this.domCtx.canvas.width, this.domCtx.canvas.height);
			this.domCtx.drawImage(this.sprites[3], 0, 0);
			this.domCtx.drawImage(this.sprites[4], ~~this.pad1.pos.x, ~~this.pad1.pos.y,
				this.gameInfos.pad1.width, this.gameInfos.pad1.size);
			this.domCtx.drawImage(this.sprites[4], ~~this.pad2.pos.x, ~~this.pad2.pos.y,
				this.gameInfos.pad2.width, this.gameInfos.pad2.size);

			this.drawCircle(this.domCtx, ~~this.ball.position.x, ~~this.ball.position.y,
				this.ball.radius, this.ball.speed === 30 ? "#F44E1A" : "#515151");

			this.drawPowerups(this.domCtx);
		},
	},
	async mounted() {
		await this.init();
		this.domCtx.drawImage(this.sprites[5], 0, 0);
		this.socket.on('updateGame', () => {
			this.$emit('setState', 1)
			if (this.animId === -1 || !this.isInGame) {
				if (this.animId !== -1)
					cancelAnimationFrame(this.animId);
				this.isInGame = true;
				this.animId = requestAnimationFrame(this.draw);
			}
		});

		this.socket.on('updateBall', (ball: ball) => {
			this.gameInfos.ball = ball;
		})

		this.socket.on('updatePads', (pad1: paddle, pad2: paddle)=> {
			this.gameInfos.pad1 = pad1;
			this.gameInfos.pad2 = pad2;
		})

		this.socket.on('updatePowerups', (powerups: []) =>{
			this.gameInfos.powerups = powerups;
		})

		this.socket.on('text', (data: string) => {
			cancelAnimationFrame(this.animId);
			this.isInGame = false;
			this.animId = -1;
			if (data === "QUEUEING" || data === "WAITING") {
				this.animId = requestAnimationFrame(() => { this.animate(this.domCtx, this.domCtx.canvas) });
			} else if (data === "ENDGAME") {
				requestAnimationFrame(async () => { await this.animateEnd(this.domCtx, this.domCtx.canvas) })
			}
		});

		this.socket.on('userDisco', (id: string) =>{
			this.discoUserId = parseInt(id);
		})
	},
	unmounted() {
		if (this.animId !== -1)
			cancelAnimationFrame(this.animId);
			cancelAnimationFrame(this.confettiId)
	},
}
</script>

<style>
.pong_screen {
	max-width: 100%;
	max-height: 80%;
	min-width: auto;
	border: 3px solid #515151;
	border-radius: 20px;
	overflow: hidden;

}

#pongCanvas {
	width: 100%;
	height: 100%;
}
</style>