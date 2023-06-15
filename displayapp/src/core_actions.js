//import { createStore } from 'vuex';
import Axios from 'axios'

export function restartApplication() {
    Axios.get('http://localhost:9001/action/restart_app').then((data) => {
    });
}

export function updateApplication() {
    Axios.get('http://localhost:9001/action/update_app').then((data) => {
    });
}

export function getInfo() {
    
}