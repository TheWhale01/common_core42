import { createRouter, createWebHistory } from 'vue-router'

export default createRouter({
	history: createWebHistory(),
	routes: [
		{
			path: '/home',
			component: () => import('@/views/Home.vue'),
		},
		{
			path: '/',
			redirect: "/home"
		},
		{
			path: '/verif',
			component: () => import('@/views/Verif.vue'),
		},
		{
			path: '/profile',
			component: () => import('@/views/Profile.vue'),
		},
		{
			path: '/pong',
			component: () => import('@/views/Pong.vue'),
		},

		{
			path: '/auth',
			component: () => import('@/views/Auth.vue'),
			children: [
				{
					path: '42/login',
					component: () => import('@/views/Auth.vue'),
					beforeEnter(to, from, next) {
						window.location.href = "http://" + import.meta.env.VITE_HOST + ":3000/auth/42/login";
					}
				},
				{
					path: 'logout',
					component: () => import('@/views/Auth.vue'),
					beforeEnter(to, from, next) {
						window.location.href = "http://" + import.meta.env.VITE_HOST + ":3000/auth/logout";
					}
				},
				{
					path: 'login',
					component: () => import('@/views/Auth.vue'),
					beforeEnter(to, from, next) {
						window.location.href = "http://" + import.meta.env.VITE_HOST + ":3000/auth/login";
					}
				},
			]
		},

		{
			path: '/auth/2fa',
			children: [
				{
					path: 'home',
					component: () => import('@/views/Auth2f.vue')
				},
				{
					path: 'off',
					component: () => import('@/views/Verif.vue'),
				},
				{
					path: 'verif',
					component: () => import('@/views/Verif.vue'),
				},
				{
					path: 'generate',
					component: () => import('@/views/Auth2f.vue'),
					beforeEnter(to, from, next) {
						window.location.href = "http://" + import.meta.env.VITE_HOST + ":3000/auth/2fa/generate";
					}
				},
			],
		},

		{
			path: '/:pathMatch(.*)',
			redirect: "/notfound"
		},

		{
			path: '/notfound',
			name: 'PageNotFound',
			component: () => import('@/views/NotFound.vue'),
		},
	],
})
