<template>
  <div class="wrapper d-flex flex-column align-items-center justify-content-center">
      <!-- <IndicatorStrap v-for="(value, label) in dashboard" :scalePoints="[0, 50, 100]" :total_items="Object.keys(dashboard).length" :label="label" :value="value" v-bind:key="label"/> -->
  
      <div class="d-flex justify-content-around flex-wrap mt-3">
        <IndicatorStrap v-for="(settings, key) in indicators" v-bind:key="key" :scalePoints="settings.scalePoints" :unit="settings.unit" :total_items="1" :label="settings.label" :value="dashboard[key]"></IndicatorStrap>
      </div>
      <br>
      <div>
        <IndicatorSpeedDigital :unit="'Km/h'" :total_items="1" :label="'SPEED'" :value="Math.round(dashboard['vssSpeed'])"></IndicatorSpeedDigital>
        <div class="d-flex flex-row justify-content-between">
          <div class="medium-label digital-font">GEAR: {{ dashboard['gear'] }}</div>
          <div class="medium-label digital-font">RPM: {{ dashboard['RPM'] }}</div>
        </div>
      </div> 
      
      <div class="d-flex justify-content-around flex-wrap mt-3">
        <IndicatorStrap v-for="(settings, key) in indicators2" v-bind:key="key" :scalePoints="settings.scalePoints" :unit="settings.unit" :total_items="1" :label="settings.label" :value="dashboard[key]"></IndicatorStrap>
      </div>

  </div>
</template>

<script>
import IndicatorDigitDefault from './indicators/IndicatorDigitDefault.vue' 
import IndicatorStrap from './indicators/IndicatorStrap.vue' 
import IndicatorSpeedDigital from './indicators/IndicatorSpeedDigital.vue' 
export default {
name: 'Desktop',
data()  {
  return {
    dashboard: {},
    indicators: {
      "TPS": {label: "TPS", unit: "%", scalePoints: [0, 50, 100]},
      "IAT": {label: "INTAKE AIR TEMP", unit: "°C", scalePoints: [0, 50, 100]},
      "Batt": {label: "VOLTAGE", unit: "V", scalePoints: [0, 5, 10, 15]},
      "wboAFR": {label: "AFR", unit: "", scalePoints: [0,  10, 20]},
    },
    indicators2: {
      "CLT": {label: "WATER TEMP", unit: "°C", scalePoints: [0, 50, 100, 150]},
      "oilPressure": {label: "OIL PRESSURE", unit: "bar", scalePoints: [0, 2, 4, 6]},
      "oilTemperature": {label: "OIL TEMP", unit: "°C", scalePoints: [0, 50, 100, 150]},
      "afrTarget": {label: "TARGET AFR", unit: "", scalePoints: [0, 50, 100]},
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
  IndicatorSpeedDigital
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