<template>
    <div class=" d-flex flex-row justify-content-center align-items-center">
          <div class="label hidden">
          {{ $store.getters.labels[label] ? $store.getters.labels[label].label : label.replace(/([A-Z])/g, ' $1').trim() }}
          </div>
          <div class="digital-font default">
          {{ value }}
          <!--<span style="font-size: 30px; line-height: 30px" >
          {{ $store.getters.labels[label] ? $store.getters.labels[label].unit : '' }}
          </span>-->
          </div>
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
      return 600 / Math.ceil(this.total_items / 2.9) + 'px'
    },
    boxWidth() {
      return (1024 / Math.ceil(this.total_items / 3)) - 4 + 'px'
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
  /* width: 120px;s */
  height: 60px;
  overflow: hidden;

  /* border: solid red 1px; */
  /* height: 140px; */
}
.label {
  font-size:22px;
  line-height: 20px;
  color:rgb(255, 255, 255);
  width: 110px;
  text-transform: capitalize;
  font-weight: 200;

}
.default {
  font-size: 50px;
  width: 100px;
  line-height: 50px;
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