//import { createStore } from 'vuex';
import Axios from 'axios';

export function restartApplication() {
    console.log("restartApplication");
    Axios.get('http://localhost:9001/action/restart_app').then((data) => {
    });
}

export function restartDevice() {
    console.log("restartDevice");
    Axios.get('http://localhost:9001/action/restart_dev').then((data) => {
    });
}

export function updateApplication() {
    console.log("updateApplication");
    Axios.get('http://localhost:9001/action/update_app').then((data) => {
    });
}

export function setWifiCredentials(data) {
    console.log("setWifiCredentials ca", data);

    let values = [];
    document.querySelectorAll('.settings-field').forEach(field => {
        values.push(field.value);
    });
    
    Axios.get('http://localhost:9001/action/set_wifi/' + values[0] + '/' + values[1]).then((data) => {
    });

    window.sendEventToVue("ux", "closepopup");
}

export function getInfo() {

}