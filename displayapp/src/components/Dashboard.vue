<template>
  <div style="width:100%; height: 100%">
    <IndicatorStrap @mousedown="startDrag" v-for="(settings, key) in indicators" v-bind:key="key" :style="{top: '0px', left: '0px'}" :scalePoints="settings.scalePoints" :unit="settings.unit" :total_items="1" :label="settings.label" :value="dashboard[key]"></IndicatorStrap> -->
    
  </div>
</template>

<script>
import { GridLayout, GridItem } from "vue3-grid-layout-next"

import IndicatorDigitDefault from './indicators/IndicatorDigitDefault.vue' 
import IndicatorStrap from './indicators/IndicatorStrap.vue' 
import IndicatorSpeedDigital from './indicators/IndicatorSpeedDigital.vue' 
import TableDetails from './indicators/TableDetails.vue' 
import IndicatorDigiCircle from './indicators/IndicatorDigiCircle.vue' 
import DistanceMeter from './indicators/DistanceMeter.vue' 
import GotToMenu from './buttons/GotToMenu.vue'
export default {
data()  {
  return {
    layout: [
        {"x":0,"y":0,"w":2,"h":1,"i":"0", static: false, indicator: {type: "strap", key: "TPS", label: "TPS", unit: "%", scalePoints: [0, 50, 100]}},
        {"x":2,"y":0,"w":2,"h":1,"i":"1", static: false, indicator: {type: "strap", key: "IAT", label: "INTAKE AIR TEMP", unit: "°C", scalePoints: [0, 30, 60]}},
        {"x":4,"y":0,"w":2,"h":1,"i":"2", static: false, indicator: {type: "strap", key: "Batt", label: "VOLTAGE", unit: "V", scalePoints: [0, 5, 10, 15]}},
        {"x":6,"y":0,"w":2,"h":1,"i":"3", static: false, indicator: {type: "strap", key: "wboAFR", label: "AFR", unit: "", scalePoints: [0,  15, 30]}},

        {"x":0,"y":1,"w":2.5,"h":3,"i":"8", static: false, indicator: {type: "digicircle", key: "wboAFR", label: "AFR", unit: "", scalePoints: [0,  15, 30]}},

        {"x":0,"y":5,"w":2,"h":1,"i":"4", static: false, indicator: {type: "strap", key: "CLT", label: "COOLANT TEMP", unit: "°C", scalePoints: [0, 50, 100, 150]}},
        {"x":2,"y":5,"w":2,"h":1,"i":"5", static: false, indicator: {type: "strap", key: "oilPressure", label: "OIL PRESS", unit: "bar", scalePoints: [0,  0.5, 1.0]}},
        {"x":4,"y":5,"w":2,"h":1,"i":"6", static: false, indicator: {type: "strap", key: "oilTemperature", label: "OIL TEMP", unit: "bar", scalePoints: [0, 50, 100, 150]}},
        {"x":6,"y":5,"w":2,"h":1,"i":"7", static: false, indicator: {type: "strap", key: "knockLevel", label: "KNOCK LEVEL", unit: "bar", scalePoints: [0, 250, 500]}},
    ],
    draggable: true,
    resizable: false,
    index: 0,


    dashboard: {},
    indicators: {
      "TPS": {label: "TPS", unit: "%", scalePoints: [0, 50, 100]},
      // "IAT": {label: "INTAKE AIR TEMP", unit: "°C", scalePoints: [0, 30, 60]},
      // "Batt": {label: "VOLTAGE", unit: "V", scalePoints: [0, 5, 10, 15]},
      // "wboAFR": {label: "AFR", unit: "", scalePoints: [0,  10, 20]},
    },
    indicators2: {
      "CLT": {label: "WATER TEMP", unit: "°C", scalePoints: [0, 50, 100, 150]},
      "oilPressure": {label: "OIL PRESSURE", unit: "bar", scalePoints: [0, 1, 2, 3]},
      "oilTemperature": {label: "OIL TEMP", unit: "°C", scalePoints: [0, 50, 100, 150]},
      "knockLevel": {label: "KNOCK LEVEL", unit: "", scalePoints: [0, 250, 500]},
      // "fuelLevel": {label: "FUEL", unit: "%", scalePoints: [0, 50, 100]},
    }
  }
},
props: {
  msg: String
},
created() {
  this.emitter.on("action", action => {
    if(action === "escape")
      this.escape();
  });
  this.emitter.on("dashframe", frame => {
    let menu = this.$store.getters.getMenu;
    
    Object.keys(frame).forEach((field) => {
        
          this.dashboard[field] = frame[field]
        
    })
  });
},
mounted() {
},
beforeUnmount() {  
  this.emitter.off("escape");
  this.emitter.off("dashframe");
},
methods: {
  startDrag(e) {
    console.log(e)
  },
  escape() {
    switch(true){
      default:
        this.$router.push({ name: 'menu' })
      }
    }
  },
  itemTitle(item) {
      let result = item.i;
      if (item.static) {
          result += " - Static";
      }
      return result;
  },
  components: {
    GridLayout,
    GridItem,

    IndicatorDigitDefault,
    IndicatorStrap,
    IndicatorSpeedDigital,
    TableDetails,
    IndicatorDigiCircle,
    GotToMenu,
    DistanceMeter
}
}
</script>

  <style>


.box {
  position: absolute;
}
</style>