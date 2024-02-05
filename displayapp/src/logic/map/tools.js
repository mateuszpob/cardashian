export const tools = {
    box: null,
    autoPositionUpdate: true,
    centerMap: function() {
        this.autoPositionUpdate = true;
        if (this.box.currentCoordinates) {
            this.box.map.getView().setCenter(this.box.currentCoordinates);
        }
    },
    setBox: function(box) { 
        this.box = box;
    }
};