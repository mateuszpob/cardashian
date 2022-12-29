import { createRouter, createWebHistory } from 'vue-router';

import Menu from './components/Menu.vue';
import Dashboard from './components/Dashboard.vue';
import Settings from './components/Settings.vue';
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
            path: '/settings',
            name: 'settings',
            component: Settings,
        },
        {
            path: '/:catchAll(.*)*',
            name: 'menu',
            component: Menu,
        },
    ],
});

export default router;
