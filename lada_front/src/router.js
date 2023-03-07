import { createRouter, createWebHistory } from 'vue-router';

import Menu from './components/Menu.vue';
import Dashboard from './components/Dashboard.vue';
import Settings from './components/Settings.vue';
import Youtube from './components/Youtube.vue';
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
            path: '/desktop',
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
            path: '/youtube',
            name: 'youtube',
            component: Youtube,
        },
        {
            path: '/:catchAll(.*)*',
            name: 'menu',
            component: Menu,
        },
    ],
});

export default router;
