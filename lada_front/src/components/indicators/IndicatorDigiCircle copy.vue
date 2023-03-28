<template>
    <div class="box">
        <div class="face-box">
            <div class="hand-box" :style="{'transform': handAngle}">
                <div class="hand"><div class="tip"></div></div>
            </div>
        </div>
    </div>
</template>

<script>
export default {
  name: 'IndicatorDigiCircle',
  props: {
    maxVal: Number,
    minVal: {type: Number, default: 0},
    startAngle: {type: Number, default: 270},
    value: String,
    maxAngle: Number
  },
  computed: {
    handAngle() {
        let angle  = this.maxAngle / (this.maxVal - this.minVal) * this.value;
        angle += this.startAngle;
        return 'rotate(' + angle + 'deg)';
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
.face-box {
    width: 200px;
    height: 200px;
    border: 1px solid green;
    border-radius: 50%;
}
.hand-box {
    width: 200px;
    height: 200px;
    border: 1px solid blue;
    position: relative;
    transform: rotate(30deg);
    border-radius: 50%;
}
.hand {
    width:120px;
    height: 6px;
    border: 1px solid red;
    position: absolute;
    top: 50%;
    right: 50%;
}
.tip {
    background: red;
    height: 100%;
    width: 20px;
}
</style>