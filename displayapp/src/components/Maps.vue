<template>
  
    <div id="map"></div>

</template>

<script>
import 'ol/ol.css';
import Map from 'ol/Map';
import View from 'ol/View';
import TileLayer from 'ol/layer/Tile';
import XYZ from 'ol/source/XYZ';
import { fromLonLat } from 'ol/proj';

export default {
  mounted() {
    // Inicjalizacja mapy OpenLayers
    const map = new Map({
      target: 'map',
      layers: [
        new TileLayer({
          source: new XYZ({
            url: 'http://localhost:9001/get-map/{z}/{x}/{y}',
          }),
        }),
      ],
      view: new View({
        center: fromLonLat([21.0122, 52.2297]),
        zoom: 12,
      }),
    });

    // Dodanie mapy do danych komponentu
    this.$data.map = map;
  },
  beforeUnmount() {
    // Zniszczenie mapy przed usunięciem komponentu
    if (this.$data.map) {
      this.$data.map.setTarget(null);
      this.$data.map = null;
    }
  },
};
</script>

<style scoped>
#map {
  width: 100%;
  height: 100vh; /* Zmieniona wysokość na 100% widoku */
}
</style>