import Feature from 'ol/Feature';
import LineString from 'ol/geom/LineString';
import { Style, Stroke } from 'ol/style';
import VectorLayer from 'ol/layer/Vector';
import VectorSource from 'ol/source/Vector';
import { toWgs84 } from '@turf/projection';
import togpx from 'togpx';

const routeStyle = new Style({
    stroke: new Stroke({
        color: 'purple',
        width: 5,
    }),
});

export function createRouteLayer(routeCoordinates) {
    const routeFeature = new Feature(new LineString(routeCoordinates));
    routeFeature.setStyle(routeStyle);

    return new VectorLayer({
        source: new VectorSource({
            features: [routeFeature],
        }),
    });
}

export function updateRouteLayer(routeLayer, routeCoordinates) {
    const routeFeature = routeLayer.getSource().getFeatures()[0];
    routeFeature.getGeometry().setCoordinates(routeCoordinates);

    console.log("routeCoordinates", routeCoordinates)
}

/**
 * We will be using python version
 */
export function saveRouteAsGPX(routeCoordinates) {
    const routeGeoJSON = {
        type: 'Feature',
        geometry: {
            type: 'LineString',
            coordinates: routeCoordinates,
        },
    };

    // Konwertuj do współrzędnych WGS84 (EPSG:4326), ponieważ GPX używa tego systemu odniesienia
    const routeGeoJSONWGS84 = toWgs84(routeGeoJSON);

    // Użyj bibiloteki togpx do utworzenia pliku GPX
    const gpxData = togpx(routeGeoJSONWGS84, { creator: 'YourAppName' });
    
    // Teraz możesz użyć 'gpxData' do zapisania trasy w formie pliku GPX lub przekazać go do serwera, itp.
    return gpxData;
}