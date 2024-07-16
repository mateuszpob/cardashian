import { createApp, h } from 'vue';
import { setupStore } from './store';
import App from './App.vue'
import Router from './router';
import mitt from 'mitt';
import Axios from 'axios';
import Vue3TouchEvents from "vue3-touch-events";

const emitter = mitt();
// const app = createApp(App).mount('#app')

const app = createApp({
    render: () => h(App),
});

app.config.globalProperties.emitter = emitter;
const store = setupStore();
const axiospro = Axios;

const customMixin = {
    data() {
        return {
            axios: axiospro,
        };
    }
};
app.mixin(customMixin);
app.use(Router);
app.use(store);
app.use(Vue3TouchEvents);

window.vueAppInstance = app;
window.sendEventToVue = function(eventName, data) {
    app.config.globalProperties.emitter.emit(eventName, data);
};


app.mount('#app');