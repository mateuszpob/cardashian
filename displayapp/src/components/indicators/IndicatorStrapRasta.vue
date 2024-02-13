<template>
    <div class="box" @click="customize">
      <div class="scale-box d-flex justify-content-between w-100">
        <div v-for="point in scalePoints" v-bind:key="point" class="scale-point d-flex flex-column align-items-center">
          <div>{{ point }}</div>
          <div class="scale-bar"></div>
        </div>
        
      </div>
      <div class="scale-under-bar">
      </div>

      <div class="strap-box">
          <div class="strap-empty" :class="{['strap-' + strap]: true}">
          <div class="value">{{ value ? (value + "&nbsp;" + unit) : '?' }}</div>
          <div :style="{'width': width}" class="strap-value">
          </div>
        </div>
      </div>

      <div class="label-box d-flex justify-content-between">
        <div class="label">{{ label }}</div>
      </div>
    </div>





</template>

<script>
export default {
  name: 'IndicatorStrap',
  props: {
    label: String,
    value: String,
    total_items: Number,
    scalePoints: Array,
    unit: String,
    strap: {
      type: String,
      default: 'green'
    }
  },
  computed: {
    width() {
      return 100 - (this.value / this.scalePoints[this.scalePoints.length - 1] * 100) + '%';
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
    customize() {
      
    }
  }
}
</script>

<style scoped>

.box{
  position: relative;
  width: 20vw;
  height: 90px;
  /* border: 1px solid #fff; */
}
.label-box {
  text-align: center;
  padding: 0 14px;
}
.label {
  text-align: center;
}
.label {
  font-size:16px;
  color: #fff;
}
.value {
  position: absolute;
  font-size: 20px;
    color: #000;
    line-height: 22px;
    font-weight: bold;
    padding-left: 4px;
}
.strap-box {
  height: 20px;
  padding: 0 14px;
}
.strap-green {
  background-color: #49FF18; 
}
.strap-rasta {
  background: rgb(26,249,0);
  background: linear-gradient(90deg, rgba(26,249,0,1) 0%, rgba(245,255,8,1) 67%, rgba(255,0,0,1) 100%);
}
.strap-rasta-r {
  background: rgb(255,0,0);
  background: linear-gradient(90deg, rgba(255,0,0,1) 25%, rgba(245,255,8,1) 67%, rgba(26,249,0,1) 100%);
}
.strap-empty {
  position: relative;
  width: 100%;
  height: 100%;
}
.strap-value {
  background-color: rgb(45, 51, 77);
  height: 100%;
  float: right;
  padding-left: 5px;
}

.scale-point{
  color: #fff;
  text-align: center;
    width: 28px;
}
.scale-bar {
  border-left: 2px solid #fff;
  height: 8px;
}
.scale-under-bar {
  margin: 0 14px 8px 14px;
  border-top: 2px solid #fff;
}

/* .box .value {
  font-size:44px;
    text-shadow: 0 0 1px #49FF18, 0 0 10px #49FF18, 0 0 5px #49FF18, 0px 0px 10px rgba(206,89,55,0);
  color: rgb(140, 255, 136);
  text-align: right;
  font-family: digitalDisplay;
  text-shadow: 4px 4px 9px green;
}
.cntnt {
  text-shadow: 0 0 30px #49FF18, 0 0 20px #49FF18, 0 0 25px #49FF18, 0px 0px 10px rgba(206,89,55,0);
  color: #fff;
  transform: rotate(59deg);
  position: absolute;
  top: 26%;
  left: 0%;
  font-size: 60px;
  transform: rotateX(90deg) rotateY(0deg) rotateZ(180deg);
  text-align: center;
 } */

</style>