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
    this.connection = new WebSocket("ws://localhost:30101")
    this.connection.onmessage = event => {
      console.log(event);
      switch(event.data) {
        case "1":
          this.emitter.emit("turnLeft");
          break;
        case "2":
          this.emitter.emit("turnRight");
          break;
        case "4":
          this.emitter.emit("enter");
          break;

      }
    };
    document.addEventListener('keyup', (event) => {
      console.log(event.key)
      console.log(event.code)

      if (event.code === "ArrowLeft"){
        this.emitter.emit("turnLeft");
      } else if (event.code === "ArrowRight"){
        this.emitter.emit("turnRight");
      } else if (event.code === "Enter"){
        this.emitter.emit("enter");
      }else if (event.code === "Escape"){
        this.emitter.emit("escape");
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
