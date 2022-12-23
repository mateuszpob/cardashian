import { createRouter, createWebHistory } from 'vue-router';

import Menu from './components/Menu.vue';
import Dashboard from './components/Dashboard.vue';
// import HelloWorld from './components/HelloWorld.vue';

const router = createRouter({
    history: createWebHistory(),
    routes: [
        // {
        //     path: '/',
        //     name: 'home',
        //     component: HelloWorld,
        // },
        {
            path: '/dashboard',
            name: 'dashboard',
            component: Dashboard,
        },
        {
            path: '/:catchAll(.*)*',
            name: 'menu',
            component: Menu,
        },
    ],
});

export default router;
