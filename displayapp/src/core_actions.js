//import { createStore } from 'vuex';
import Axios from 'axios'

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
    let req = {};
    data.forEach(o => {
        console.log(o)
        
        if(o.label === 'SSID') {
            req.ssid = o.val;
        }
        if(o.label === 'PASS') {
            req.pass = o.val;
        }
    });
    Axios.post('http://localhost:9001/action/set_wifi', req).then((data) => {
    });
}

export function getInfo() {

}