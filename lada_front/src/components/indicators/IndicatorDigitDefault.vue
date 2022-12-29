<template>
    <div class="box d-flex flex-column">
        <h2 class="value d-flex justify-content-end">{{ value }}</h2>
        <h1 class="label d-flex justify-content-end">{{ label }}</h1>
    </div>
</template>

<script>
export default {
  name: 'IndicatorDigitDefault',
  props: {
    label: String,
    value: String
  },
  mounted() {

  },
  methods: {
    // escape() {
    //   switch(true){
    //     default:
    //       this.$router.push({ name: 'menu' })
    //   }
    // }
  }
}
</script>

<style scoped>
.box{
  width: 80px;
  overflow: hidden;
}
.box .label {
  font-size:16px;
  color:rgb(0, 189, 0);
}
.box .value {
  font-size:44px;
  color:rgb(0, 189, 0);
  text-align: right;
  font-family: digitalDisplay;
}
</style>