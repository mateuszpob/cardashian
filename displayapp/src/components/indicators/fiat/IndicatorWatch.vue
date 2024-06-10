<template>
    <div class="" @click="customize">
      <div class="scale-box d-flex justify-content-between w-100">
        <div class="dial">
          <div class="tiper">
            <div class="label">{{ label }}</div>
            <div class="tiper">
              <div v-for="point in scalePoints" v-bind:key="point" class="scale-point d-flex flex-column align-items-center">
                <div>{{ point }}</div>
                <div class="scale-bar"></div>
              </div>
            </div>
            <!-- <div class="lineczka"></div> -->
            <div class="tip" :style="{'transform': rotateValue}"></div>
          </div>
        </div>
      </div>
    </div>





</template>

<script>
export default {
  name: 'IndicatorWatch',
  props: {
    label: String,
    value: Number,
    total_items: Number,
    scalePoints: Array,
    unit: String,
    multi: Number
  },
  computed: {
    rotateValue() {

      const minValue = this.scalePoints[0];
      const maxValue = this.scalePoints[this.scalePoints.length - 1];

      let val = this.value;
      if (this.multi) {
       val = val / this.multi
      }

      // Mapowanie wartości na zakres od -36 do 36 stopni
      const normalizedValue = (val - minValue) / (maxValue - minValue) * 72 - 36;
      
      return 'rotate(' + normalizedValue + 'deg)'
    },
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
.tiper {
  position: relative;
  background-color: rgba(0,0,0,0.5);
  border: 1px solid rgb(118, 118, 118);
  width: 20vw;
  height: 13vw;
  overflow: hidden;
  box-shadow: rgb(15, 0, 0) 0px 6px 12px 6px;
}
.tip {
  background: linear-gradient(to bottom, #ff0000 5%, transparent 30%);
  width: 4px;
  height: 20vw;
  /* transform: rotate(-36deg); */
  position: absolute;
  left: 50%;
  top: 4vw;
}

.lineczka {
  border-top: 2px solid #fff;
    border-radius: 10vw;
    height: 20vw;
    top: 1.5vw;
    position: relative;
}

.scale-point {
  color: #fff;
  text-align: center;
  width: 28px;
  position: absolute;
  font-size: 2vw;
  transform-origin: 50% 100%; /* Ustawienie punktu transformacji w dolnej części elementu */
  left: 8.5vw;
  bottom: 0.1svw;
}

.scale-point:nth-child(1) { transform: rotate(-40deg) translate(0, -9vw); }
.scale-point:nth-child(2) { transform: rotate(-13.3deg) translate(0, -9vw); }
.scale-point:nth-child(3) { transform: rotate(13.3deg) translate(0, -9vw); }
.scale-point:nth-child(4) { transform: rotate(40deg) translate(0, -9vw); }



.label {
  text-align: center;
  font-size:1.7vw;
  color: #fff;
  position: absolute;
  width: 100%;
  top: 70%;
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