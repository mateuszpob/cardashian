import { initializeMap } from './initializeMap';
import { createMarkerLayer, updateMarkerLayer } from './marker';
import { createRouteLayer, updateRouteLayer } from './route';
import { createWebSocket } from './websocket';
import { fromLonLat } from 'ol/proj';

export function samuraje(targetElement) {
    const { map, tools } = initializeMap(targetElement);
    const markerLayer = createMarkerLayer();
    const routeLayer = createRouteLayer([]);

    map.addLayer(markerLayer);
    map.addLayer(routeLayer);

    const socket = createWebSocket();

    socket.onmessage = function (event) {
        const data = JSON.parse(event.data);
        const coordinates = fromLonLat([parseFloat(data.longitude), parseFloat(data.latitude)]);

        updateMarkerLayer(markerLayer, coordinates);

        const routeCoordinates = routeLayer.getSource().getFeatures()[0].getGeometry().getCoordinates();
        routeCoordinates.push(coordinates);
        updateRouteLayer(routeLayer, routeCoordinates);

        // if (tools.autoPositionUpdate) {
            map.getView().setCenter(coordinates);
        // }
    };

    map.on('pointerdown', function () {
        console.log('pointerdown');
        tools.autoPositionUpdate = false;
    });

    socket.onclose = function (event) {
        console.error('Połączenie WebSocket zostało zamknięte:', event);
    };

    socket.onerror = function (error) {
        console.error('Błąd WebSocket:', error);
    };

    return { map, tools };
}