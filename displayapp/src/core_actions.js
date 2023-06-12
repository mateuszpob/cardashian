//import { createStore } from 'vuex';
import Axios from 'axios'

export function restartApplication() {
    console.log('resatret app')
    Axios.get('http://localhost:8080/action/restart_app').then((data) => {
    });
}

export function updateApplication() {
    console.log('update app')
}