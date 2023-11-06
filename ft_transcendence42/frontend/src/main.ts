import { createApp } from 'vue'
import App from './App.vue'
import router from './router'
import type { RouteRecordName } from 'vue-router'
import { library } from '@fortawesome/fontawesome-svg-core'
import { FontAwesomeIcon } from '@fortawesome/vue-fontawesome'
import { faGear, faRightFromBracket, faPen, faLock, faUserGroup, faUserPlus,
		faCirclePlus, faCheck, faXmark, faTableTennis, faGamepad, faPaperPlane,
		faTrophy, faCircleQuestion, faCommentMedical } from '@fortawesome/free-solid-svg-icons'
import VueApexCharts from "vue3-apexcharts";
import Notifications from '@kyvg/vue3-notification'

async function isLogged() {
	const res = await fetch("http://" + import.meta.env.VITE_HOST + ":3000/auth",
		{method: "get", credentials: "include"});
	return ((res.status != 401));
}

library.add(faGear, faRightFromBracket, faPen, faLock, faUserGroup, faUserPlus,
			faCirclePlus, faCheck, faXmark, faTableTennis, faGamepad, faPaperPlane,
			faTrophy, faCircleQuestion, faCommentMedical);
const app = createApp(App)

router.beforeEach(async (to, from, next) => {
	const clearPages: RouteRecordName[] = ["/auth", "/auth/42/login", "/auth/login", "/auth/2fa/verif"]
	if (clearPages.includes(to.path))
		next();
	else {
		await isLogged() ? next() : next('/auth');
	}
})

app.component('font-awesome-icon', FontAwesomeIcon)
app.component("apexchart", VueApexCharts);
app.config.globalProperties.$redirect = (page) => {router.push(page)}
app.use(Notifications).use(router).mount('#app')
