<template>
    <router-view :key="$route.fullPath" />
</template>

<script>

export default {
  
  name: 'App',
  data() {
    return {

    }
  },

  methods: {

  },
  mounted() {
    this.axios.get('/labels.json').then((data) => {
            this.$store.dispatch('setLabels', data.data);
        });

    this.connection = new WebSocket("ws://localhost:30101")
    this.connection.onmessage = event => {
      let data = JSON.parse(event.data);

      switch(data.channel) {
        case "dashframe":
          let frame = data.data.emu_frame;
          frame.total_distance = data.data.total_distance;
          frame.trip_distance = data.data.trip_distance;
          // console.log(frame)
          this.emitter.emit("dashframe", frame);
          break;
        case "action":
          switch(data.data[0]) {
            case 1:
              this.emitter.emit("action", "turnLeft");
              break;
            case 2:
              this.emitter.emit("action", "turnRight");
              break;
            case 4:
              this.emitter.emit("action", "enter");
              break;
            case 7:
              this.emitter.emit("action", "escape");
              break;
          }
          break;
      }
      
    };
    document.addEventListener('keyup', (event) => {
      if (event.code === "ArrowLeft"){
        this.emitter.emit("action", "turnLeft");
      } else if (event.code === "ArrowRight"){
        this.emitter.emit("action", "turnRight");
      } else if (event.code === "Enter"){
        this.emitter.emit("action", "enter");
      }else if (event.code === "Escape"){
        this.emitter.emit("action", "escape");
      }
    });
  }
}
</script>

<style>
html, body, #app {
  height: 100%;
}
body {
  background: rgb(41, 41, 41);
}
#app {
  display: flex;
  flex-direction: row;
  justify-content: center;
  align-items: center;
  width: 1024px;
  height: 600px;
  background: #000;
  overflow: hidden;
}

</style>
