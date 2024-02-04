export const tools = {
    box: null,
    autoPositionUpdate: true,
    centerMap: function() {
        console.log('this.box', this.box)
        this.autoPositionUpdate = true;
        if (this.box.currentCoordinates) {
            this.box.map.getView().setCenter(this.box.currentCoordinates);
        }
    },
    setBox: function(box) { 
        this.box = box;
        console.log('this.box', this.box)
    }
};