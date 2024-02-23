<template>
  <div class="super-wrapper w-100 px-5 wrapper d-flex flex-column align-items-center justify-content-around">
    <GotToMenu :context="dashboard" :x="20" :y="20"></GotToMenu>
    
      <div class="w-100 d-flex justify-content-between flex-wrap ">
        <IndicatorWatch v-for="(settings, key) in indicators1" v-bind:key="key" :scalePoints="settings.scalePoints" :unit="settings.unit" :total_items="1" :label="settings.label" :value="dashboard[key]" :strap="settings.strap" :multi="settings.multi"></IndicatorWatch>
      </div>
      
      <div class="w-100 d-flex flex-row justify-content-between">
       
        <Thermometer v-for="(settings, key) in thermometer" v-bind:key="key" :scalePoints="settings.scalePoints" :unit="settings.unit" :total_items="1" :label="settings.label" :value="dashboard[key]" :strap="settings.strap"></Thermometer>

      </div> 
      
      <div class="w-100 d-flex justify-content-between flex-wrap ">
        <IndicatorWatch v-for="(settings, key) in indicators2" v-bind:key="key" :scalePoints="settings.scalePoints" :unit="settings.unit" :total_items="1" :label="settings.label" :value="dashboard[key]" :strap="settings.strap" :multi="settings.multi"></IndicatorWatch>
      </div>

  </div>
</template>

<script>
import IndicatorDigitDefault from './indicators/IndicatorDigitDefault.vue' 
import IndicatorStrap from './indicators/IndicatorStrap.vue' 
import IndicatorSpeedDigital from './indicators/IndicatorSpeedDigital.vue' 
import TableDetails from './indicators/TableDetails.vue' 
import IndicatorDigiCircle from './indicators/IndicatorDigiCircle.vue' 
import DistanceMeter from './indicators/DistanceMeter.vue' 
import GotToMenu from './buttons/GotToMenu.vue'
import Thermometer from './indicators/fiat/Thermometer.vue'
import IndicatorWatch from './indicators/fiat/IndicatorWatch.vue'
export default {
data()  {
  return {
    dashboard: {},
    indicators2: {
      "IgnAngle": {label: "IGN. ANGLE", unit: "°", scalePoints: [0, 10, 20, 30]},
      "wboAFR": {label: "AFR", unit: "", scalePoints: [0,  10, 20, 30]},
      "Batt": {label: "VOLTAGE", unit: "V", scalePoints: [0, 5, 10, 15]},
      "RPM": {label: "RPM", unit: "V", scalePoints: [0, 2, 4, 6], 'multi': 1000},
    },
    indicators1: {
      // "Batt": {label: "VOLTAGE", unit: "V", scalePoints: [0, 5, 10, 15], strap: 'rasta-r'},
      // "TPS": {label: "TPS", unit: "%", scalePoints: [0, 50, 100]},
      "IAT": {label: "INTAKE AIR TEMP", unit: "°C", scalePoints: [0, 15, 30, 45]},
      "CLT": {label: "WATER TEMP", unit: "°C", scalePoints: [0, 50, 100, 150]},
      "oilPressure": {label: "OIL PRESSURE", unit: "bar", scalePoints: [0, 3, 6, 9]},
      "oilTemperature": {label: "OIL TEMP", unit: "°C", scalePoints: [0, 50, 100, 150]},
    //   "knockLevel": {label: "KNOCK LEVEL", unit: "", scalePoints: [0, 250, 500]},
    },
    // indicators3: {
    //   "boost": {label: "BOOST", unit: "bar", scalePoints: [-100, 0, 100]},
    //   "IgnAngle": {label: "IGN. ANGLE", unit: "°", scalePoints: [0, 10, 20, 30]},
    //   "pulseWidth": {label: "INJ. PULSE WIDTH", unit: "ms", scalePoints: [0, 5, 10]},
    //   "dwellTime": {label: "DWELL TIME", unit: "ms", scalePoints: [0, 5, 10]},
    // },
    thermometer: {
      "vssSpeed": {label: "TPS", unit: "%", scalePoints: [0, 20, 40, 60, 80, 100, 120, 140, 160, 180]},
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
  components: {
    IndicatorDigitDefault,
    IndicatorStrap,
    IndicatorSpeedDigital,
    TableDetails,
    IndicatorDigiCircle,
    GotToMenu,
    DistanceMeter,
    Thermometer,
    IndicatorWatch
}
}
</script>

  <style scoped>
  .super-wrapper {
    background-color: #272727;
    background-image: url('/./public/plastic.jpg');
  }
  .wrapper {
    padding: 5px;
    height: 100%;
  }
  .medium-label {
    font-size: 50px;
    line-height: 50px;
  }
</style>