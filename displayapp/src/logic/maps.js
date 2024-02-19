import 'ol/ol.css';
import Map from 'ol/Map';
import View from 'ol/View';
import TileLayer from 'ol/layer/Tile';
import XYZ from 'ol/source/XYZ';
import Feature from 'ol/Feature';
import Point from 'ol/geom/Point';
import LineString from 'ol/geom/LineString';
import { Style, Icon, Stroke } from 'ol/style';
import VectorLayer from 'ol/layer/Vector';
import VectorSource from 'ol/source/Vector';
import { fromLonLat } from 'ol/proj';
import { OSM, Vector } from 'ol/source';
import { Draw, Modify, Snap } from 'ol/interaction';

export function initializeMap(targetElement) {

    let autoPositionUpdate = true;
    let coordinates = fromLonLat([21.0122, 52.2297]);
    let routeCoordinates = [coordinates]; // Array to store route coordinates


    const tools = {
        centerMap: function() {
            autoPositionUpdate = true;
            map.getView().setCenter(coordinates);
        },
    };
    
    const map = new Map({
        target: targetElement,
        layers: [
            new TileLayer({
                source: new XYZ({
                url: '/get/map/{z}/{x}/{y}',
                }),
            }),
        ],
        view: new View({
            center: fromLonLat([21.0122, 52.2297]),
            zoom: 16,
        }),
    });

    // Ustaw ścieżkę do własnej ikony
    const iconPath = 'target.png';

    const markerStyle = new Style({
      image: new Icon({
        anchor: [0.5, 1], // Ustaw punkt zakotwiczenia na środek dolnej krawędzi ikony
        anchorXUnits: 'fraction',
        anchorYUnits: 'fraction',
        src: iconPath,
      }),
    });

    const routeStyle = new Style({
        stroke: new Stroke({
            color: 'purple',
            width: 3,
        }),
    });

    const routeFeature = new Feature(new LineString(routeCoordinates));
    routeFeature.setStyle(routeStyle);

    const markerLayer = new VectorLayer({
        source: new VectorSource(),
    });

    const routeLayer = new VectorLayer({
        source: new VectorSource({
            features: [routeFeature],
        }),
    });

    map.addLayer(markerLayer);
    map.addLayer(routeLayer);

    // Utwórz WebSocket
    const socket = new WebSocket('ws://localhost:50250');

    socket.onmessage = function (event) {
        const data = JSON.parse(event.data);

        // Aktualizuj pozycję na mapie
        coordinates = fromLonLat([parseFloat(data.longitude), parseFloat(data.latitude)]);
        const marker = new Feature(new Point(coordinates));
        marker.setStyle(markerStyle);

        // Usuń poprzednią warstwę z markerem
        markerLayer.getSource().clear();

        // Dodaj nową warstwę z aktualnym markerem
        if (marker)
        markerLayer.getSource().addFeature(marker);

        // Dodaj aktualną pozycję do trasy
        routeCoordinates.push(coordinates);
        routeFeature.getGeometry().setCoordinates(routeCoordinates);

        if(autoPositionUpdate) {
            // Ustaw nowy środek widoku mapy na aktualną lokalizację
            map.getView().setCenter(coordinates);
        }
    };

    map.on('pointerdown', function () {
        console.log('pointerdown');
        autoPositionUpdate = false
    });

    // Dodaj obsługę zamknięcia WebSocket
    socket.onclose = function (event) {
        console.error('Połączenie WebSocket zostało zamknięte:', event);
    };

    // Dodaj obsługę błędu WebSocket
    socket.onerror = function (error) {
        console.error('Błąd WebSocket:', error);
    };

    return { map, tools };
}