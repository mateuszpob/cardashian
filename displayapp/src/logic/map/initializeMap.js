import 'ol/ol.css';
import Map from 'ol/Map';
import View from 'ol/View';
import TileLayer from 'ol/layer/Tile';
import XYZ from 'ol/source/XYZ';
import { fromLonLat } from 'ol/proj';

export function initializeMap(targetElement) {
    let coordinates = fromLonLat([21.0122, 52.2297]);

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
            zoom: 16,
        }),
    });

    return map ;
}