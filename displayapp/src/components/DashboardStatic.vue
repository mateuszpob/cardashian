<template>
  <div class="wrapper d-flex flex-column align-items-center justify-content-between">
  <GotToMenu :context="dashboard" :x="20" :y="20"></GotToMenu>
    
      <!-- <IndicatorStrap v-for="(value, label) in dashboard" :scalePoints="[0, 50, 100]" :total_items="Object.keys(dashboard).length" :label="label" :value="value" v-bind:key="label"/> -->
  
      <div class="d-flex justify-content-around flex-wrap ">
        <IndicatorStrap v-for="(settings, key) in indicators" v-bind:key="key" :scalePoints="settings.scalePoints" :unit="settings.unit" :total_items="1" :label="settings.label" :value="dashboard[key]"></IndicatorStrap>
      </div>
      
      <div style="width:100%;margin-top: -100px" class="d-flex justify-content-around">
        <!-- <TableDetails></TableDetails> -->
        <IndicatorDigiCircle :max-val="6000" :max-angle="270" :value="Math.round(dashboard['RPM'])" :value2="(Math.round(dashboard['vssSpeed']) === 0 ? 'N' : dashboard['gear'])"></IndicatorDigiCircle>
        <!-- <IndicatorSpeedDigital :unit="''" :total_items="1" :label="'SPEED'" :value="Math.round(dashboard['vssSpeed'])"></IndicatorSpeedDigital> -->
        <!-- <div class="d-flex flex-row justify-content-between">
          <div class="medium-label digital-font">GEAR: {{ dashboard['gear'] }}</div>
          <div class="medium-label digital-font">RPM: {{ dashboard['RPM'] }}</div>
        </div> -->

        <DistanceMeter :data="dashboard"></DistanceMeter>
      </div> 
      
      <div style="margin-top: -60px; height: 92px;" class="d-flex justify-content-around flex-wrap">
        <IndicatorStrap v-for="(settings, key) in indicators2" v-bind:key="key" :scalePoints="settings.scalePoints" :unit="settings.unit" :total_items="1" :label="settings.label" :value="dashboard[key]"></IndicatorStrap>
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