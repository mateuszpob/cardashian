

<script>
export default {
    data() {
        return {
            pointsNumber: 55,
            pointSize: 5,
            yellowTipsFrom: 30,
            redTipsFrom: 45,
        }
    },
    name: 'IndicatorDigiCircle',
    props: {
        maxVal: Number,
        minVal: {type: Number, default: 0},
        startAngle: {type: Number, default: 270},
        value: String,
        maxAngle: Number,
        value2: Number
    },
    computed: {
        handAngle() {
            let angle  = this.maxAngle / (this.maxVal - this.minVal) * this.value;
            angle += this.startAngle;
            return 'rotate(' + angle + 'deg)';
        },
        
    },
    mounted() {

    },
    methods: {
        pointIsVisible(i) {
            let angle  = this.maxAngle / (this.maxVal - this.minVal) * this.value;


            if(angle > (i * this.pointSize)) {
                return 'block';
            }
                
            
            return 'none';
        }
        // escape() {
        //   switch(true){
        //     default:
        //       this.$router.push({ name: 'menu' })
        //   }
        // }
    }
}
</script>

<template>
    <div class="box d-flex flex-column align-items-center ">
        <div class="face-box">
            <div v-for="i in [...Array(pointsNumber).keys()]" v-bind:key="i" class="hand-box" :style="{'transform': 'rotate(' + (startAngle + (i * pointSize)) + 'deg)', 'display': pointIsVisible(i)}">
                <div class="hand"><div class="tip" :class="{'tip-y': i > yellowTipsFrom && i < redTipsFrom, 'tip-r': i >= redTipsFrom}"></div></div>
            </div>
        </div>
        <div class="speed-meter digital-font">{{ value2 }}</div>
        <div class="d-flex w-100 flex-row ">
            <div class="value2-label">km/h</div>
            <div class="value-d-box d-flex flex-column align-items-start ">
                <div class="digital-font rpm-val">{{ value }}</div>
                <div class=" rpm-lab">{{ 'RPM' }}</div>
            </div>
        </div>
        
        
    </div>
</template>

<style scoped>
.box {
    /* position: relative; */
    padding: 30px;
    width: 200px;
    height: 200px;
}
.face-box {
    width: 200px;
    height: 200px;
    /* border: 1px solid green; */
    border-radius: 50%;
    position: absolute;
}
.hand-box {
    width: 200px;
    height: 200px;
    position: absolute;
    transform: rotate(30deg);
    border-radius: 50%;
}
.hand {
    width:120px;
    height: 6px;
    position: absolute;
    top: 50%;
    right: 50%;
}
.tip {
    background: rgb(73, 240, 8);
    height: 100%;
    width: 20px;
}
.tip-y {
    background: rgb(240, 205, 8) !important;
}
.tip-r {
    background: rgb(240, 8, 8) !important;
}


.speed-meter {
    /* position: absolute;
    top: 50%;
    bottom: 50%;
    left: 50%;
    right: 50%; */
    /* transform: translateX(-100%) translateY(-50%); */
    font-size:  150px;
    line-height: 150px;
}
.value2-label {
    color: #fff;
}
.rpm-val {
    font-size: 50px;
    line-height: 50px;
}
.rpm-lab {
    font-size: 20px;
    line-height: 20px;
    color: #fff;
}
.value2-label {
    width: 60%;
    font-size: 20px;
    margin-left: 20px;
    margin-top: -10px
}
.value-d-box {
    width: 40%;
    text-align: left;
    /* margin-top: 0px; */
}
</style>