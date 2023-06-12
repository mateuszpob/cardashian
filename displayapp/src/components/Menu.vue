
<template>
  <div ref="menu" id="menu-wrapper" v-touch:swipe.left="turnRight" v-touch:swipe.right="turnLeft" @click="handleClickEvent">
    <!-- <div class="axie"/> -->
    <!-- <div class="axie a2"/> -->
    <div v-for="item in structure" v-bind:key="item.html" class="menu-item">
      <div class="cntnt">{{ item.html }}</div>
    </div>
  </div>
</template>

<script>

export default {
  props: {
    msg: String,
    // structure: Array 
  },
  data() {
    return {
      structure: [
        {html: "Menu1", callback: this.yt},
        {html: "Desktop", callback: this.desktop},
        {html: "SimpleParams", callback: this.simpleParams},
        {html: "Smolnia4x4", callback: this.chrom},
        {html: "Settings", callback: this.settings}
      ],

      activeId: 0,
      numberOfMenuItems: 0,
      rotateAngle: 180,
      rotateStep: 10
    }
  },
  created() {
    this.emitter.on("action", action => {
      switch(action) {
        case "turnLeft":
          this.turnLeft();
          break;
        case "turnRight":
          this.turnRight();
          break;
        case "enter":
          this.structure[this.activeId].callback();
          break;
      }
    });
  },
  beforeUnmount() {  
    this.emitter.off("action");
  },
  mounted() {
    this.updateLayout();
    this.numberOfMenuItems = this.structure.length;
  },
  timers: {
    updateLayout: {
      autostart: false,
      repeat: true,
      immediate: true,
      time: 200
    }
  },
  methods: {
    handleClickEvent() {
      this.structure[this.activeId].callback();
    },
    yt() {
      this.$router.push({ name: 'youtube' })
    },
    desktop() {
      this.$router.push({ name: 'desktop' })
    },
    simpleParams() {
      this.$router.push({ name: 'simpleParams' })
    },
    chrom() {
    },
    settings() {
      this.$router.push({ name: 'settings' })
    },

    open() {

    },
    close() {

    },
    turnLeft() {
      this.activeId++;
      this.activeId = this.activeId % this.numberOfMenuItems;
      this.rotateAngle -= this.rotateStep;
      this.updateLayout();
    },
    turnRight() {
      if(this.activeId == 0) {
        this.activeId = this.numberOfMenuItems;
      }
      this.activeId--;
      this.rotateAngle += this.rotateStep;
      this.updateLayout();
    },
    updateLayout() {
      let menuItems = document.querySelectorAll(".menu-item");
      let offsetAngle = 360 / menuItems.length;
      this.rotateStep = offsetAngle;
      let i = 0;
      this.$refs.menu.style.transform = "rotateX(80deg) rotateZ("+this.rotateAngle+"deg)";
      [...menuItems].forEach((item) => {
        let rotateAngle = offsetAngle * i++;
        let selectSuffics = "";

        // item.style.opacity = "0.4"
        // if(i == activeId) {
        //   selectSuffics = "scale(2)"
        //   item.style.opacity = "1.0"
        // }

        item.style.transform = "rotateZ(" + rotateAngle + "deg) translate(0, -200px) " + selectSuffics; // rotate3d(1, 0, 0, 90deg)
      });
    }
  }
}

</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
#menu-wrapper{
	/* background-color: blue; */
	height: 400px;
	width: 400px;
	border-radius: 50%;
	position: relative;
  /* transform: rotateX(80deg) rotateY(0deg) rotateZ(0deg); */
  position: relative;
    transform-style: preserve-3d;
    transition: transform 0.5s;
}

.menu-item{
	list-style: none;
  /* border: 1px solid #ff9100; */
	height: 150px;
	width: 150px;
	position: absolute;
	top: 31%;
	left: 31%;
  transform-style: inherit;
  border-radius: 50%;
  font-size: 22px;
  /* box-shadow: 0px 1px 52px 13px rgba(255, 126, 29, 1); */
}
.axie {
  position: absolute;
  transform-style: inherit;
  width: 300px;
  height: 5px;
  background: red;
      transform: rotate3d(0, 1, 0, 90deg);
}
.axie.a2 {
  transform: rotate3d(1, 1, 0, 90deg);
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
