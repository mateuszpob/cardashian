<template>
    <div>
      <GotToMenu :context="dashboard" :x="20" :y="20"></GotToMenu>
      <iframe width="1024" height="600" src="//www.google.com/maps" ></iframe>
    </div>
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