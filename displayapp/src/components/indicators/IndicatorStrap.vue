<template>
    <div class="box" @click="customize" ref="componentA">
      <IndicatorMenu :isVisible="isMenuVisible" />
      <div class="scale-box d-flex justify-content-between w-100">
        <div v-for="point in scalePoints" v-bind:key="point" class="scale-point d-flex flex-column align-items-center">
          <div>{{ point }}</div>
          <div class="scale-bar"></div>
        </div>
        
      </div>
      <div class="scale-under-bar">
      </div>

      <div class="strap-box">
          <div class="strap-empty">
          <div :style="{'width': width}" class="strap-value">
            <div class="value">{{ value ? (value + "&nbsp;" + unit) : '?' }}</div>
          </div>
        </div>
      </div>

      <div class="label-box d-flex justify-content-between">
        <div class="label">{{ label }}</div>
      </div>
    </div>





</template>

<script>
import IndicatorMenu from './IndicatorMenu.vue' 

export default{
  data() {
    return {
      isMenuVisible: false,
        componentA: null
    }
  },
  name: 'IndicatorStrap',
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
        document.addEventListener('click', this.handleClickOutside);
    },
  methods: {
    handleClickOutside(event) { console.log('asdadsdsd', this.componentA, event)
        if (this.componentA && !this.componentA.contains(event.target)) {
            this.isMenuVisible = false;
        }
    },
    customize() {
      this.isMenuVisible = !this.isMenuVisible;
    }
  },
  components: {
    IndicatorMenu
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
  font-size: 20px;
    color: #000;
    line-height: 22px;
    font-weight: bold;
}
.strap-box {
  height: 20px;
  padding: 0 14px;
}
.strap-empty {
  width: 100%;
  height: 100%;
  background-color: rgb(45, 51, 77);
  /* position: absolute;
  bottom: 0; */
}
.strap-value {
  height: 100%;
  background-color: #49FF18;
  padding-left: 5px;
  /* position: absolute; */
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