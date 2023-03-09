<template>
  <div class="box">
    <div class="outer">
      <div class="inner">
        <div class="d-flex flex-row align-items-end justify-content-end">
          <div :style="{'font-size':'200px', 'line-height': '170px'}" class="label digital-font">{{ value }}</div>
          <div class="unit digital-font">{{ unit }}</div>
        </div>
      </div>
    </div>
    
  </div>
</template>

<script>
export default {
name: 'IndicatorSpeedDigital',
props: {
  label: String,
  value: Number,
  total_items: Number,
  scalePoints: Array,
  unit: String
},
computed: {
  width() {
    return (this.value / this.scalePoints[this.scalePoints.length - 1] * 100) + '%';
  },
  fontSize() {
    return 480 / Math.ceil(this.total_items / 3) + 'px'
  },
  boxWidth() {
    return (800 / Math.ceil(this.total_items / 3)) - 4 + 'px'
  }
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
.box {
height: 170px;
width:350px;
text-align: right;
}
.unit {
font-size: 80px;
}
</style>