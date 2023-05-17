import { createRouter, createWebHistory } from 'vue-router';

import Menu from './components/Menu.vue';
import Dashboard from './components/Dashboard.vue';
import Settings from './components/Settings.vue';
import Desktop from './components/Desktop.vue';

const router = createRouter({
    history: createWebHistory(),
    routes: [
        // {
        //     path: '/',
        //     name: 'home',
        //     component: HelloWorld,
        // },
        {
            path: '/',
            name: 'desktop',
            component: Desktop,
        },
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
