<template>
    <div class="wrapper d-flex  flex-wrap ">
        <IndicatorDigitDefault class="d-flex gx-4 gy-1" v-for="(value, label) in dashboard" :label="label" :value="value" v-bind:key="index"/>
    </div>
</template>

<script>
import IndicatorDigitDefault from './indicators/IndicatorDigitDefault.vue' 
export default {
  name: 'Dashboard',
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
    this.emitter.on("dashframe", frame => {
      console.log("FRAME", frame)
      this.dashboard = frame;
    });
  },
  mounted() {

  },
  beforeUnmount() {  
    this.emitter.off("escape");
    this.emitter.off("dashframe");
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
    IndicatorDigitDefault
  }
}
</script>

<style scoped>
.wrapper {
  padding: 5px;
}
</style>