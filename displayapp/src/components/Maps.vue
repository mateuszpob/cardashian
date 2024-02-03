<template>
  <div class="map-container">
    <GotToMenu :context="dashboard" :x="20" :y="20"></GotToMenu>
    <div id="map" class="map-container"></div>
  </div>
</template>

<script>
import { initializeMap } from '../logic/maps.js';
import GotToMenu from './buttons/GotToMenu.vue';

export default {
  mounted() {
    // Inicjalizacja mapy OpenLayers
    const map = initializeMap('map');
    this.$data.map = map;
  },
  beforeUnmount() {
    // Zniszczenie mapy przed usunięciem komponentu
    if (this.$data.map) {
      this.$data.map.setTarget(null);
      this.$data.map = null;
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
</style>