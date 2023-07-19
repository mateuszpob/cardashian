<template>
  <div class="w-100 px-5 wrapper d-flex flex-column align-items-center justify-content-between">
    <GotToMenu :context="dashboard" :x="20" :y="20"></GotToMenu>
    
      <div class="w-100 d-flex justify-content-between flex-wrap ">
        <IndicatorStrap v-for="(settings, key) in indicators" v-bind:key="key" :scalePoints="settings.scalePoints" :unit="settings.unit" :total_items="1" :label="settings.label" :value="dashboard[key]" :strap="settings.strap"></IndicatorStrap>
      </div>
      
      <div class="w-100 d-flex flex-row justify-content-between">
        <div class="d-flex flex-column justify-content-center">
          <IndicatorStrap v-for="(settings, key) in indicators3" v-bind:key="key" :scalePoints="settings.scalePoints" :unit="settings.unit" :total_items="1" :label="settings.label" :value="dashboard[key]" :strap="settings.strap"></IndicatorStrap>
        </div>
        <IndicatorDigiCircle :max-val="6000" :max-angle="270" :value="Math.round(dashboard['RPM'])" :value2="(Math.round(dashboard['vssSpeed']) === 0 ? 'N' : dashboard['gear'])" class="d-flex"></IndicatorDigiCircle>
        <DistanceMeter :data="dashboard" class="d-flex"></DistanceMeter>
      </div> 
      
      <div style="height: 92px;" class="w-100 d-flex justify-content-between flex-wrap">
        <IndicatorStrap v-for="(settings, key) in indicators2" v-bind:key="key" :scalePoints="settings.scalePoints" :unit="settings.unit" :total_items="1" :label="settings.label" :value="dashboard[key]" :strap="settings.strap"></IndicatorStrap>
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
export default {
data()  {
  return {
    dashboard: {},
    indicators: {
      "TPS": {label: "TPS", unit: "%", scalePoints: [0, 50, 100]},
      "IAT": {label: "INTAKE AIR TEMP", unit: "°C", scalePoints: [0, 20, 40]},
      "Batt": {label: "VOLTAGE", unit: "V", scalePoints: [0, 5, 10, 15], strap: 'rasta-r'},
      "wboAFR": {label: "AFR", unit: "", scalePoints: [0,  15, 30]},
    },
    indicators2: {
      "CLT": {label: "WATER TEMP", unit: "°C", scalePoints: [0, 50, 100, 150]},
      "oilPressure": {label: "OIL PRESSURE", unit: "bar", scalePoints: [0, 1, 1.5]},
      "oilTemperature": {label: "OIL TEMP", unit: "°C", scalePoints: [0, 50, 100, 150]},
      "knockLevel": {label: "KNOCK LEVEL", unit: "", scalePoints: [0, 250, 500]},
    },
    indicators3: {
      "boost": {label: "BOOST", unit: "bar", scalePoints: [-100, 0, 100]},
      "IgnAngle": {label: "IGN. ANGLE", unit: "°", scalePoints: [0, 10, 20, 30]},
      "pulseWidth": {label: "INJ. PULSE WIDTH", unit: "ms", scalePoints: [0, 5, 10]},
      "dwellTime": {label: "DWELL TIME", unit: "ms", scalePoints: [0, 5, 10]},
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
    DistanceMeter
}
}
</script>

  <style scoped>

  .wrapper {
    padding: 5px;
    height: 100%;
  }
  .medium-label {
    font-size: 50px;
    line-height: 50px;
  }
</style>