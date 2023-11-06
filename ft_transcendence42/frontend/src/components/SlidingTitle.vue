<template>
	<div class="container-sliding-title">
		<div class="box-sliding">
			<div class="title-sliding">
				<div class="text-sliding">{{ text }}<span>
				</span></div>
			</div>
		</div>
	</div>
</template>

<script lang="ts">

export default {
	props: ["text"],

}

</script>

<style lang="scss">

.text-sliding{
	display: block;
    margin-top: 0em;
    margin-bottom: 1em;
    margin-left: 0;
    margin-right: 0;
    font-weight: bold;
}

.container-sliding-title{
	display: flex;
	justify-content: center;
	align-items: center;

	.box-sliding {
		width: 100%;
		height: 20%;
		position: relative;
		display: flex;
		justify-content: center;
		flex-direction: column;

		.title-sliding {
			width: 100%;
			position: relative;
			display: flex;
			font-family: 'Poppins', sans-serif;
			align-items: center;
			height: 50px;

			.block-sliding {
				width: 0%;
				height: inherit;
				background: rgb(34, 158, 230);
				position: absolute;
				animation: mainBlock 0.5s cubic-bezier(.74, .06, .4, .92) forwards;
				display: flex;
			}

			.text-sliding {
				color: #636363;
				font-size: clamp(1.25rem, 0.5288rem + 2.3077vw, 2.1875rem);

				-webkit-animation: mainFadeIn 0.5s forwards;
				-o-animation: mainFadeIn 0.5s forwards;
				animation: mainFadeIn 0.5s forwards;
				opacity: 0;
				display: flex;
				align-items: baseline;
				position: relative;

				span {
					width:0px;
					height: 0px;
					-webkit-border-radius: 50%;
					-moz-border-radius: 50%;
					border-radius: 50%;

					background: rgb(34, 158, 230);
					-webkit-animation: load 0.6s cubic-bezier(.74, .06, .4, .92) forwards;
					animation: popIn 0.8s cubic-bezier(.74, .06, .4, .92) forwards;
					animation-delay: 0.5s;
					margin-left: 5px;
					margin-top: -10px;
					position: absolute;
					bottom: 13px;
					right: -12px;
				}
			}
		}
	}
}





@keyframes mainBlock {
  0% {
    width: 0%;
    left: 0;

  }
  50% {
    width: 100%;
    left: 0;

  }
  100% {
    width: 0;
    left: 100%;
  }
}

@keyframes secBlock {
  0% {
    width: 0%;
    left: 0;

  }
  50% {
    width: 100%;
    left: 0;

  }
  100% {
    width: 0;
    left: 100%;
  }
}

@keyframes mainFadeIn {
  0% {
    opacity: 0;
  }
  100% {
    opacity: 1;
  }
}


@keyframes popIn {
  0% {
    width: 0px;
    height: 0px;
    background: rgb(34, 158, 230);;
    border: 0px solid #ddd;
    opacity: 0;
  }
  50% {
    width: 10px;
    height: 10px;
    background: rgb(34, 158, 230);
    opacity: 1;
    bottom: 45px;
  }
   65% {
      width: 7px;
    height: 7px;
      bottom: 0px;
      width: 15px
   }
   80% {
      width: 10px;
    height: 10px;
      bottom: 20px
   }
  100% {
    width: 7px;
    height: 7px;
    background: rgb(34, 158, 230);
    border: 0px solid #222;
    bottom: 13px;

  }
}

</style>