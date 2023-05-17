import { createStore } from 'vuex';
import menu from './store/menu';

export function setupStore() {
    return createStore({
        modules: {
            menu,
        },
    });
}
