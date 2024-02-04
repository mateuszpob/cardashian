import Feature from 'ol/Feature';
import LineString from 'ol/geom/LineString';
import { Style, Stroke } from 'ol/style';
import VectorLayer from 'ol/layer/Vector';
import VectorSource from 'ol/source/Vector';

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
}