import 'ol/ol.css';
import Map from 'ol/Map';
import View from 'ol/View';
import TileLayer from 'ol/layer/Tile';
import XYZ from 'ol/source/XYZ';
import { fromLonLat } from 'ol/proj';
import Feature from 'ol/Feature';
import Point from 'ol/geom/Point';
import { Style, Icon } from 'ol/style';
import VectorLayer from 'ol/layer/Vector';
import VectorSource from 'ol/source/Vector';

export function initializeMap(targetElement) {
  const map = new Map({
    target: targetElement,
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

  // Dodanie warstwy wektorowej z markerem
  const vectorLayer = new VectorLayer({
    source: new VectorSource({
      features: [new Feature(new Point(fromLonLat([21.0122, 52.2297])))],
    }),
    style: new Style({
      image: new Icon({
        anchor: [0.5, 46],
        anchorXUnits: 'fraction',
        anchorYUnits: 'pixels',
        src: 'https://openlayers.org/en/latest/examples/data/icon.png', // Ścieżka do ikony markera
      }),
    }),
  });
  map.addLayer(vectorLayer);

  return map;
}