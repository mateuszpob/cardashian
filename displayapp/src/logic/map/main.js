import { initializeMap } from './initializeMap';
import { createMarkerLayer, updateMarkerLayer } from './marker';
import { createRouteLayer, updateRouteLayer } from './route';
import { createWebSocket } from './websocket';
import { fromLonLat } from 'ol/proj';
import { tools } from './tools';

const box = {
    currentCoordinates: null,
    map: null
};

export function samuraje(targetElement) {
    box.map = initializeMap(targetElement);
    const markerLayer = createMarkerLayer();
    const routeLayer = createRouteLayer([]);

    box.map.addLayer(markerLayer);
    box.map.addLayer(routeLayer);

    tools.setBox(box)

    const socket = createWebSocket();

    socket.onmessage = function (event) {
        const data = JSON.parse(event.data);
        box.currentCoordinates = fromLonLat([parseFloat(data.longitude), parseFloat(data.latitude)]);

        updateMarkerLayer(markerLayer, box.currentCoordinates);

        const routeCoordinates = routeLayer.getSource().getFeatures()[0].getGeometry().getCoordinates();
        routeCoordinates.push(box.currentCoordinates);
        updateRouteLayer(routeLayer, routeCoordinates);

        if (tools.autoPositionUpdate) {
            box.map.getView().setCenter(box.currentCoordinates);
        }
    };

    box.map.on('pointerdown', function () {
        console.log('pointerdown');
        tools.autoPositionUpdate = false;
    });

    socket.onclose = function (event) {
        console.error('Połączenie WebSocket zostało zamknięte:', event);
    };

    socket.onerror = function (error) {
        console.error('Błąd WebSocket:', error);
    };

    let map = box.map
    return { map, tools };
}