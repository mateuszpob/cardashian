<template>
  <div class="wrapper d-flex flex-column align-items-center justify-content-between">
      <!-- <IndicatorStrap v-for="(value, label) in dashboard" :scalePoints="[0, 50, 100]" :total_items="Object.keys(dashboard).length" :label="label" :value="value" v-bind:key="label"/> -->
  
      <div class="d-flex justify-content-around flex-wrap ">
        <IndicatorStrap v-for="(settings, key) in indicators" v-bind:key="key" :scalePoints="settings.scalePoints" :unit="settings.unit" :total_items="1" :label="settings.label" :value="dashboard[key]"></IndicatorStrap>
      </div>
      
      <div style="width:100%;margin-top: -100px" class="d-flex justify-content-around">
        <!-- <TableDetails></TableDetails> -->
        <IndicatorDigiCircle :max-val="6000" :max-angle="270" :value="Math.round(dashboard['RPM'])" :value2="Math.round(dashboard['vssSpeed'])"></IndicatorDigiCircle>
        <!-- <IndicatorSpeedDigital :unit="''" :total_items="1" :label="'SPEED'" :value="Math.round(dashboard['vssSpeed'])"></IndicatorSpeedDigital> -->
        <!-- <div class="d-flex flex-row justify-content-between">
          <div class="medium-label digital-font">GEAR: {{ dashboard['gear'] }}</div>
          <div class="medium-label digital-font">RPM: {{ dashboard['RPM'] }}</div>
        </div> -->

        <div style="" class="d-flex flex-column justify-content-center">
          <div class="d-flex flex-row align-items-end mt-5">
            <div class="w-label fnt-20" style="width:70px;"></div>
            <div class="digital-font fnt-100">{{ dashboard['gear'] }}</div>
          </div>
          <div class="d-flex flex-row align-items-end mt-5">
            <div class="w-label fnt-16" style="width:70px;">TOTAL</div>
            <div class="digital-font fnt-50">{{ dashboard['total_distance'] }}</div>
          </div>
          <div class="d-flex flex-row align-items-end mt-2">
            <div class="w-label fnt-16" style="width:70px;">TRIP</div>
            <div class="digital-font fnt-50">{{ dashboard['trip_distance'] }}</div>
          </div>
        </div>
s
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
export default {
name: 'Desktop',
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
    IndicatorDigiCircle
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