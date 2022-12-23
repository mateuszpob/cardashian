import { createApp, h } from 'vue'
import App from './App.vue'
import Router from './router';
import mitt from 'mitt';

const emitter = mitt();
// const app = createApp(App).mount('#app')

const app = createApp({
    render: () => h(App),
});

app.config.globalProperties.emitter = emitter;

app.use(Router);

app.mount('#app');