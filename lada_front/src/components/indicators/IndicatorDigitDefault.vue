<template>
    <div class="box d-flex flex-column" :style="{'width': boxWidth}">
        <h2 :style="{'font-size': fontSize, 'line-height': 'calc(0.8 * ' + fontSize + ')'}" class="value d-flex justify-content-end align-items-end">
          {{ value }}
          <!--<span style="font-size: 30px; line-height: 30px" >
          {{ $store.getters.labels[label] ? $store.getters.labels[label].unit : '' }}
          </span>-->
          </h2>
          <h1 class="label d-flex justify-content-end hidden">
          {{ $store.getters.labels[label] ? $store.getters.labels[label].label : label }}
          </h1>
    </div>
</template>

<script>
export default {
  name: 'IndicatorDigitDefault',
  props: {
    label: String,
    value: String,
    total_items: Number
  },
  computed: {
    fontSize() {
      return 480 / Math.ceil(this.total_items / 2.9) + 'px'
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
.box{
  width: 80px;
  overflow: hidden;
  /* border: solid red 1px; */
  height: 140px;
}
.box .label {
  font-size:16px;
  color:rgb(0, 189, 0);
}
.box .value {
  /* font-size:44px; */
    text-shadow: 0 0 1px #49FF18, 0 0 10px #49FF18, 0 0 5px #49FF18, 0px 0px 10px rgba(206,89,55,0);
  color: rgb(140, 255, 136);
  text-align: right;
  font-family: digitalDisplay;
  /* text-shadow: 4px 4px 9px green; */
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
}
</style>