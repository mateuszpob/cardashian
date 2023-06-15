<script>

export default {
    data()  {
        return {
            visible: false
        }
    },
    created() {
    this.emitter.on("ux", o => {
      switch(o) {
        case "openpopup":
            this.visible = true;
          break;
        // case "closepopup":
        //   this.$refs.menucontainer.classList.remove('faded')
        //   break;
      }
    });
  },
    mounted() {
        // this.$refs.menucontainer.classList.add('faded')
        console.log(this.$refs.popololek)
    },
    beforeUnmount() {
        this.$refs.popo
    },
    methods: {
        show() {
            this.visible = true;
        },
        hide() {
            this.visible = false;
            this.emitter.emit("ux", "closepopup");
        },
        yAction() {
            this.yCallback();
            this.hide();
        }
    },
    props: {
        text: String,
        yButton: String,
        yCallback: Function,
        nButton: {
            type: String,
            default: "Close"
        }
    }
}
</script>

<template>
        <div ref="popololek" v-if="visible" class="popup-one  border-blu ylo-d1-cnt d-flex flex-column px-4 py-5 justify-content-center align-items-center" data-augmented-ui="tl-2-clip-x tr-2-clip-x border" >
            <p class="light-text-3">{{ text }}</p>
            
            <div class="d-flex justify-content-around w-100">
                <button @click="hide" class="button-light border-blu ylo-d1-cnt mt-5 px-3 py-2" data-augmented-ui="tl-2-clip-x tr-2-clip-x border">{{ nButton }}</button>
                <button v-if="yButton.length > 0" @click="yAction" class="button-light border-blu ylo-d1-cnt mt-5" data-augmented-ui="tl-2-clip-x tr-2-clip-x border">{{ yButton }}</button>
            </div>
        </div>
</template>

<style scoped>
    .popup-one {
        z-index: 9999;
        position: absolute;
        width: 60%;
        left: 50%;
        top: 50%;
        transform: translateX(-50%) translateY(-50%);
    }
    .popup-one p {
        font-size: 40px;
    }
    button {
        width: 40%;
    }
</style>