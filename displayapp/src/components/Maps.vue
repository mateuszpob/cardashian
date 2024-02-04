<template>
  <div class="map-container">
    <GotToMenu :context="dashboard" :x="20" :y="20"></GotToMenu>
    <div id="map" class="map-container"></div>
        <button @click="centerMap" id="autoUpdateButton">CR</button>
  </div>
</template>

<script>
import { samuraje } from '../logic/map/main.js';
// import { initializeMap } from  '../logic/maps.js';

import GotToMenu from './buttons/GotToMenu.vue';


export default {
  data() {
    return {
      map: null,
      tools: null
    }
  },
  mounted() {
    // Inicjalizacja mapy OpenLayers
    // const map = initializeMap('map');
    const { map, tools } = samuraje('map');
    this.map = map;
    this.tools = tools
  },
  beforeUnmount() {
    // Zniszczenie mapy przed usunięciem komponentu
    if (this.map) {
      this.map.setTarget(null);
      this.map = null;
    }
  },
  methods: {
    centerMap() {
      console.log("CENTER", this.tools )
      this.tools.centerMap()
    }
  },
  components: {
    GotToMenu,
  },
};
</script>

<style scoped>
  .map-container {
    width: 100%;
    height: 100vh; /* Zmieniona wysokość na 100% widoku */
  }
  #autoUpdateButton {
    position: absolute;
    top: 100px;
    left: 9px;
    z-index: 1000;
    border: none;
    border-radius: 2px;
  }
  .ol-zoom {
    right: 10px;
  }

  .ol-control {
    top: initial;
    bottom: 10px;
  }
</style>