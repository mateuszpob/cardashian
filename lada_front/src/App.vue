<template>
  <div id="app">
    <router-view :key="$route.fullPath" />
    
  </div>
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
    this.axios.get('/labels.json').then((data) => { console.log(data.data)
            this.$store.dispatch('setLabels', data.data);
        });

    this.connection = new WebSocket("ws://localhost:30101")
    this.connection.onmessage = event => {
      let data = JSON.parse(event.data);

      switch(data.channel) {
        case "dashframe":
          this.emitter.emit("dashframe", data.data);
          break;
        case "action": console.log(data.data[0])
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
          }
          break;
      }
      
    };
    document.addEventListener('keyup', (event) => {
      // console.log(event.key)
      // console.log(event.code)

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
    width: 800px;
    height: 400px;
  background: #000;
}

</style>
