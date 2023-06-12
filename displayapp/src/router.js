import { createRouter, createWebHistory } from 'vue-router';

import Menu from './components/Menu.vue';
import SimpleParams from './components/SimpleParams.vue';
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
