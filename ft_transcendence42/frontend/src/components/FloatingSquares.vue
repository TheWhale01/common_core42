<template>
<ul class="background">
   <li></li>
   <li></li>
   <li></li>
   <li></li>
   <li></li>
   <li></li>
   <li></li>
   <li></li>
   <li></li>
   <li></li>
   <li></li>
   <li></li>
   <li></li>
   <li></li>
   <li></li>
   <li></li>
   <li></li>
   <li></li>
   <li></li>
   <li></li>
   <li></li>
   <li></li>
   <li></li>
   <li></li>
   <li></li>
   <li></li>
</ul>
</template>

<style lang="scss">

@keyframes animate {
    0%{
		transform: translateY(0) rotate(0deg);
        opacity: 1;
        border-radius: 0;
    }
    100%{
		transform: translateY(-1000px) rotate(720deg);
        opacity: 0;
        border-radius: 50%;
    }
}

.background {
    position: fixed;
    width: 100vw;
    height: 100vh;
    top: 0;
    left: 0;
    margin: 0;
    padding: 0;
    background: #92ccf0;
    overflow: hidden;
	z-index: -1;
}
.background li {
    position: absolute;
    display: block;
    list-style: none;
    width: 20px;
    height: 20px;
    background: rgb(255, 255, 255, 0.4);
    animation: animate 10s linear infinite;
}




.background li:nth-child(0) {
    left: 24%;
    width: 117px;
    height: 117px;
    bottom: -117px;
    animation-delay: 1s;
}
.background li:nth-child(1) {
    left: 27%;
    width: 142px;
    height: 142px;
    bottom: -142px;
    animation-delay: 3s;
}
.background li:nth-child(2) {
    left: 21%;
    width: 126px;
    height: 126px;
    bottom: -126px;
    animation-delay: 10s;
}
.background li:nth-child(3) {
    left: 70%;
    width: 179px;
    height: 179px;
    bottom: -179px;
    animation-delay: 5s;
}
.background li:nth-child(4) {
    left: 21%;
    width: 111px;
    height: 111px;
    bottom: -111px;
    animation-delay: 13s;
}
.background li:nth-child(5) {
    left: 77%;
    width: 137px;
    height: 137px;
    bottom: -137px;
    animation-delay: 9s;
}
.background li:nth-child(6) {
    left: 16%;
    width: 187px;
    height: 187px;
    bottom: -187px;
    animation-delay: 19s;
}
.background li:nth-child(7) {
    left: 75%;
    width: 151px;
    height: 151px;
    bottom: -151px;
    animation-delay: 21s;
}
.background li:nth-child(8) {
    left: 89%;
    width: 124px;
    height: 124px;
    bottom: -124px;
    animation-delay: 2s;
}
.background li:nth-child(9) {
    left: 60%;
    width: 134px;
    height: 134px;
    bottom: -134px;
    animation-delay: 24s;
}
.background li:nth-child(10) {
    left: 16%;
    width: 148px;
    height: 148px;
    bottom: -148px;
    animation-delay: 8s;
}
.background li:nth-child(11) {
    left: 32%;
    width: 102px;
    height: 102px;
    bottom: -102px;
    animation-delay: 16s;
}
.background li:nth-child(12) {
    left: 18%;
    width: 116px;
    height: 116px;
    bottom: -116px;
    animation-delay: 1s;
}
.background li:nth-child(13) {
    left: 60%;
    width: 162px;
    height: 162px;
    bottom: -162px;
    animation-delay: 3s;
}
.background li:nth-child(14) {
    left: 83%;
    width: 116px;
    height: 116px;
    bottom: -116px;
    animation-delay: 18s;
}
.background li:nth-child(15) {
    left: 31%;
    width: 128px;
    height: 128px;
    bottom: -128px;
    animation-delay: 4s;
}
.background li:nth-child(16) {
    left: 59%;
    width: 177px;
    height: 177px;
    bottom: -177px;
    animation-delay: 39s;
}
.background li:nth-child(17) {
    left: 80%;
    width: 164px;
    height: 164px;
    bottom: -164px;
    animation-delay: 27s;
}
.background li:nth-child(18) {
    left: 82%;
    width: 193px;
    height: 193px;
    bottom: -193px;
    animation-delay: 19s;
}
.background li:nth-child(19) {
    left: 56%;
    width: 130px;
    height: 130px;
    bottom: -130px;
    animation-delay: 25s;
}
.background li:nth-child(20) {
    left: 4%;
    width: 101px;
    height: 101px;
    bottom: -101px;
    animation-delay: 64s;
}
.background li:nth-child(21) {
    left: 13%;
    width: 156px;
    height: 156px;
    bottom: -156px;
    animation-delay: 78s;
}
.background li:nth-child(22) {
    left: 56%;
    width: 183px;
    height: 183px;
    bottom: -183px;
    animation-delay: 27s;
}
.background li:nth-child(23) {
    left: 86%;
    width: 100px;
    height: 100px;
    bottom: -100px;
    animation-delay: 13s;
}
.background li:nth-child(24) {
    left: 68%;
    width: 188px;
    height: 188px;
    bottom: -188px;
    animation-delay: 76s;
}
.background li:nth-child(25) {
    left: 22%;
    width: 161px;
    height: 161px;
    bottom: -161px;
    animation-delay: 25s;
}

</style>