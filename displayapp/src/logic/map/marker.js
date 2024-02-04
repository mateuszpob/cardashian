import Feature from 'ol/Feature';
import Point from 'ol/geom/Point';
import { Style, Icon } from 'ol/style';
import VectorLayer from 'ol/layer/Vector';
import VectorSource from 'ol/source/Vector';

const iconPath = 'target.png';

const markerStyle = new Style({
    image: new Icon({
        anchor: [0.5, 1],
        anchorXUnits: 'fraction',
        anchorYUnits: 'fraction',
        src: iconPath,
    }),
});

let marker = null;

export function createMarkerLayer() {
    return new VectorLayer({
        source: new VectorSource(),
    });
}

export function updateMarkerLayer(markerLayer, coordinates) {
    console.log("UPDATE", markerLayer, coordinates);

    if (!marker) {
        // Jeśli marker nie istnieje, utwórz go
        marker = new Feature(new Point(coordinates));
        marker.setStyle(markerStyle);
        markerLayer.getSource().addFeature(marker);
    } else {
        // Jeśli marker istnieje, zaktualizuj jego geometrię
        marker.setGeometry(new Point(coordinates));
    }
}