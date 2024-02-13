import { createRouter, createWebHistory } from 'vue-router';

import Menu from './components/Menu.vue';
import SimpleParams from './components/SimpleParams.vue';
import Settings from './components/settings/Settings.vue';
import Dashboard from './components/Dashboard.vue';
import DashboardStatic from './components/DashboardStatic.vue';
import Multimedia from './components/Multimedia.vue';
import Maps from './components/Maps.vue';

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
            name: 'dashboard',
            // component: Dashboard,
            component: DashboardStatic,
        },
        {
            path: '/multimedia',
            name: 'multimedia',
            component: Multimedia,
        },
        {
            path: '/maps',
            name: 'maps',
            component: Maps,
        },
        {
            path: '/simple-params',
            name: 'simpleParams',
            component: SimpleParams,
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
