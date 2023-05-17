<template>
    <iframe src="https://www.youtube.com/" />
</template>

<script>
export default {
  name: 'Youtube',
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
    
  }
}
</script>

<style scoped>
.wrapper {
}
</style>