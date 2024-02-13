<template>
  <GridLayout style="height: 600px" :layout.sync="layout"
               :col-num="8"
               :max-rows="6"
               :is-bounded="false"
               :row-height="90"
               :is-draggable="draggable"
               :is-resizable="resizable"
               :vertical-compact="false"
               :use-css-transforms="true"
               :restore-on-drag="true"
  >
      <GridItem v-for="item in layout" v-bind:key="item.i" class="d-flex justify-content-center align-items-center p-0"
                 :static="item.static"
                 :x="item.x"
                 :y="item.y"
                 :w="item.w"
                 :h="item.h"
                 :i="item.i"
      >
        <IndicatorStrap v-if="item.indicator.type === 'strap'" v-bind:key="key" :scalePoints="item.indicator.scalePoints" :unit="item.indicator.unit" :total_items="1" :label="item.indicator.label" :value="dashboard[item.indicator.key]"></IndicatorStrap>
        
        <IndicatorDigiCircle v-if="item.indicator.type === 'digicircle'" :max-val="6000" :max-angle="270" :value="Math.round(dashboard['RPM'])" :value2="(Math.round(dashboard['vssSpeed']) === 0 ? 'N' : dashboard['gear'])"></IndicatorDigiCircle>
      
      </GridItem>
      <!-- <IndicatorStrap v-for="(settings, key) in indicators" v-bind:key="key" :scalePoints="settings.scalePoints" :unit="settings.unit" :total_items="1" :label="settings.label" :value="dashboard[key]"></IndicatorStrap> -->
    
  </GridLayout>
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
      "IAT": {label: "INTAKE AIR TEMP", unit: "°C", scalePoints: [0, 30, 60]},
      "Batt": {label: "VOLTAGE", unit: "V", scalePoints: [0, 5, 10, 15]},
      "wboAFR": {label: "AFR", unit: "", scalePoints: [0,  10, 20]},
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









  .vue-grid-layout {
    /* background: #eee; */
    width:100%;
}
.vue-grid-item:not(.vue-grid-placeholder) {
    /* background: #ccc; */
    /* border: 1px solid var(--zi-def); */
}
.vue-grid-item .resizing {
    opacity: 0.9;
}
.vue-grid-item .static {
    /* background: #cce; */
}
.vue-grid-item .text {
    font-size: 24px;
    text-align: center;
    position: absolute;
    top: 0;
    bottom: 0;
    left: 0;
    right: 0;
    margin: auto;
    height: 100%;
    width: 100%;
}
.vue-grid-item .no-drag {
    height: 100%;
    width: 100%;
}
.vue-grid-item .minMax {
    font-size: 12px;
}
.vue-grid-item .add {
    cursor: pointer;
}
.vue-draggable-handle {
    position: absolute;
    width: 20px;
    height: 20px;
    top: 0;
    left: 0;
    background: url("data:image/svg+xml;utf8,<svg xmlns='http://www.w3.org/2000/svg' width='10' height='10'><circle cx='5' cy='5' r='5' fill='#999999'/></svg>") no-repeat;
    background-position: bottom right;
    padding: 0 8px 8px 0;
    background-repeat: no-repeat;
    background-origin: content-box;
    box-sizing: border-box;
    cursor: pointer;
}
</style>