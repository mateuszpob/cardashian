<template>
    <div class="box">
      <div class="outer">
        <div class="inner">


          <div class="circle-wrap">
    <div class="circle">
      <div class="mask full-1">
        <div class="fill-1"></div>
      </div>
      <div class="mask half">
        <div class="fill-1"></div>
      </div>
      <div class="inside-circle"> 85% </div>
    </div>
  </div>

  
          <div :style="{'font-size':'200px', 'line-height': '200px'}" class="label digital-font">{{ value }}</div>
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
.circle-wrap {
  display: grid;
  grid-template-columns: repeat(1, 160px);
  grid-gap: 80px;
  margin-top: 100px;
  margin-left: 50px;
  width: 150px;
  height: 150px;
  background: #d9d7da;
  border-radius: 50%;
}

.circle-wrap .circle .mask,
.circle-wrap .circle .fill-1,
.circle-wrap .circle .fill-2,
.circle-wrap .circle .fill-3 {
  width: 150px;
  height: 150px;
  position: absolute;
  border-radius: 50%;
}

.circle-wrap .circle .mask {
  clip: rect(0px, 150px, 150px, 75px);
}

.circle-wrap .inside-circle {
  width: 124px;
  height: 124px;
  border-radius: 50%;
  background: #212020;
  line-height: 120px;
  text-align: center;
  margin-top: 13px;
  margin-left: 13px;
  color: white;
  position: absolute;
  z-index: 100;
  font-weight: 700;
  font-size: 2em;
}

/* color animation */

.mask .fill-1 {
  clip: rect(0px, 75px, 150px, 0px);
  background-color: #ec0c0c;
}

.mask.full-1,
.circle .fill-1 {
  animation: fill-1 ease-in-out 3s;
  transform: rotate(153deg);
}




</style>