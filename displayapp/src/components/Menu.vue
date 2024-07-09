
<template>
  <div ref="menu" id="menu-wrapper">
    <div class="menu-item" @click="dashboard"><i class="bi bi-speedometer"></i></div>
    <div class="menu-item" @click="settings"><i class="bi bi-gear"></i></div>
    <div class="menu-item" @click="simpleParams"><i class="bi bi-car-front"></i></div>
    <div class="menu-item" @click="maps"><i class="bi bi-geo-alt"></i></div>
    <div class="menu-item" @click="dashboard"><i class="bi bi-browser-chrome"></i></div>
    <div class="menu-item" @click="multimedia"><i class="bi bi-cassette"></i></div>
  </div>
  <div id="version">v1.0.0</div>
</template>

<script>

export default {
  props: {
    msg: String,
  },
  data() {
    return {
    }
  },
  created() {
   
  },
  mounted() {
  },
  timers: {
    updateLayout: {
      autostart: false,
      repeat: true,
      immediate: true,
      time: 200
    }
  },
  methods: {

    multimedia() {
      this.$router.push({ name: 'multimedia' })
    },
    dashboard() {
      this.$router.push({ name: 'dashboard' })
    },
    simpleParams() {
      this.$router.push({ name: 'simpleParams' })
    },
    chrom() {
    },
    maps() {
      this.$router.push({ name: 'maps' })
    },
    settings() {
      this.$router.push({ name: 'settings' })
    },

    
  }
}

</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
#menu-wrapper{
	/* background-color: blue; */
	height: 300px;
	width: 500px;
  display: flex;
  flex-wrap: wrap;
  flex-direction: row;
  justify-content: space-between;
}
.menu-item {
  text-shadow: 0 0 30px #49FF18, 0 0 20px #49FF18, 0 0 25px #49FF18, 0px 0px 10px rgba(206,89,55,0);
  color: #fff;
  font-size: 12vh;
  padding: 3vw;
}
#version {
  position: absolute;
  left: 4px;
  bottom: 2px;
  color: #c7c7c7;
  font-size: medium;
}
</style>
