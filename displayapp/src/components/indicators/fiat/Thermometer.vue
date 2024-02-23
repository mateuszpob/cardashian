<template>
  <div class="rameczka d-flex justify-content-between" @click="customize">
    <div class="units-label s d-flex align-items-center"><div>Smolnia<br>Motorsport</div></div>
    <div class="box">
      <div class="scale-box d-flex justify-content-between w-100">
        <div v-for="point in scalePoints" v-bind:key="point" class="scale-point dick d-flex flex-column align-items-center">
          <div>{{ point }}</div>
        </div>
        
      </div>


      <div class="strap-box">
        <div class="strap-box-fill"></div>
        <div class="strap-empty">
          <div :style="{'width': width}" class="strap-value">
            <!-- <div class="value">{{ value ? (value + "&nbsp;" + unit) : '?' }}</div> -->
          </div>
        </div>
      </div>


      <div class="scale-box d-flex justify-content-between w-100 mt-1">
        <div v-for="point in ((scalePoints.length * 2) - 1)" v-bind:key="point" class="scale-point d-flex flex-column align-items-center">
          <div class="scale-bar"></div>
        </div>
        
      </div>
    </div>

    <div class="units-label d-flex align-items-center"><div>km/h</div></div>


  </div>

</template>

<script>
export default {
  name: 'Thermometer',
  props: {
    label: String,
    value: String,
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
    customize() {
      
    }
  }
}
</script>

<style scoped>
.units-label {
  color: #fff;
  text-align: center;
  padding: 1vw;
  font-size: 2vw;
  /* position: absolute; */
  /* right: 0; */
  /* top: 50%; */
  
}
.units-label.s {
  font-size: 1.5vw;
}
.rameczka{
  position: relative;
  border: 1px solid rgb(118, 118, 118);
  /* padding: 1vw 12vw 5vw 10vw;s */
  width: 100%;
  background-color: rgba(0,0,0,0.5);
  box-shadow: rgb(15, 0, 0) 0px 7px 18px 14px;
}
.box{
  position: relative;
  width: 100%;
  height: 10vw;
  margin: 1vw 4vw 3vw 5vw;

}
.label-box {
  text-align: center;
  padding: 0 14px;
}
.label {
  text-align: center;
}
.label {
  font-size: 12vw;
  color: #fff;
}
.strap-box {
  position: relative;
  height: 20px;
  padding: 0 14px;
}
.strap-box-fill {
  background-color: rgba(0, 0, 0, 0.6);
  position: absolute;
  top: 0;
  left: 20px;
  height: 20px;
  width: 100%;
  z-index: 100;
}
.strap-empty {
  /* width: 105%; */
  height: 100%;
  background-color: rgba(0, 0, 0, 0.6);
  /* position: absolute;
  bottom: 0; */
}
.strap-value {
  position: absolute;
  left: 0;
  height: 100%;
  background-color: #ff1818;
  padding-left: 5px;
  z-index: 101;
  /* position: absolute; */
}

.scale-point.dick:first-child {
  visibility: hidden;
}
.scale-point{
  color: #fff;
  text-align: center;
    width: 28px;
  font-size: 3.5svw;
  font-weight: lighter;
}
.scale-bar {
	border-left: 6px solid #fff;
  height: 18px;
}
.scale-point:nth-child(2n) .scale-bar{
  border-left: 3px solid #fff;
  height: 12px;
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