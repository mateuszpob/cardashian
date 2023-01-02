<template>
    <div class="wrapper d-flex  flex-wrap mt-3">
        <IndicatorDigitDefault class="d-flex gx-4 gy-1" v-for="(value, label) in dashboard" :total_items="Object.keys(dashboard).length" :label="label" :value="value" v-bind:key="label"/>
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

      Object.keys(this.$store.getters.getMenu).forEach((o) => {
        if(this.$store.getters.getMenu[o])
          this.dashboard[o] = frame[o]
      });
      // this.dashboard = frame;
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