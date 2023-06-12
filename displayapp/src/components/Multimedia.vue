<template>
    <GotToMenu :context="dashboard" :x="20" :y="20"></GotToMenu>
    <iframe width="1024" height="600" src="https://www.youtube.com/embed/ThVPOdaVvlA" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>
</template>

<script>
import GotToMenu from './buttons/GotToMenu.vue';

export default {
  data()  {
    return {
      dashboard: {}
    }

  },
  props: {
    msg: String
  },
  created() {
    this.emitter.on("action", action => {
      if(action === "escape")
        this.escape();
    });

  },
  mounted() {

  },
  beforeUnmount() {  
    this.emitter.off("escape");
  },
  methods: {
    escape() {
      switch(true){
        default:
          this.$router.push({ name: 'menu' })
      }
    }
  },
  components: {
    GotToMenu
  }
}
</script>

<style scoped>
.wrapper {
}
</style>