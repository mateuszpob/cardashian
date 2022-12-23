<template>
    <div class="hello">
        <h1>dash</h1>
    </div>
</template>

<script>
export default {
  name: 'Dashboard',
  props: {
    msg: String
  },
  created() {
    this.emitter.on("escape", isOpen => {
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
  }
}
</script>