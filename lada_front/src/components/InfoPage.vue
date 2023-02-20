<template>
<div>

</div>
</template>

<script>
export default {
  name: 'InfoPage',
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
    this.axios.get('/labels.json').then((data) => { console.log(data.data)
      this.$store.dispatch('setLabels', data.data);
    });
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
    
  }
}
</script>

<style scoped>
.wrapper {
}
</style>