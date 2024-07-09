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
            if(this.item.fields) {
                this.item.callback(this.item.fields);
            } else {
                this.item.callback();
            }
            
            this.hide();
        }
    },
    props: {
        item: Object
        // text: String,
        // yButton: String,
        // yCallback: Function,
        // nButton: {
        //     type: String,
        //     default: "Close"
        // }
    }
}
</script>

<template>
    <div class="popup-one" v-if="visible">
    <br><br>
        <div v-if="visible" class="border-blu ylo-d1-cnt d-flex flex-column px-4 py-5 justify-content-center align-items-center" data-augmented-ui="tl-2-clip-x tr-2-clip-x border" >
            <p v-if="item.text" class="light-text h3" v-html="item.text"></p>
            <div v-if="item.fields" class="d-flex flex-column">
                <div v-for="field in item.fields" v-bind:key="field.label" class="d-flex flex-row mt-3">
                    <label class="w-25 light-text h3 px-3">{{ field.label }}</label>
                    <input class="w-75 settings-field" v-model="field.val" />
                </div>
            </div>
            <div class="d-flex justify-content-around w-100">
                <button @click="hide" class="button-light border-blu ylo-d1-cnt mt-5 px-3 py-2" data-augmented-ui="tl-2-clip-x tr-2-clip-x border">{{ item.nBtn ?? 'Close' }}</button>
                <button v-if="item.yBtn" @click="yAction" class="button-light border-blu ylo-d1-cnt mt-5" data-augmented-ui="tl-2-clip-x tr-2-clip-x border">{{ item.yBtn }}</button>
            </div>
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
        /* opacity: 0.99; */
    }
    .popup-one p {
        font-size: 40px;
        font-family: 'RajdhaniLight';
    }
    .popup-one input {
        background: #003300;
        color: #fff;
        font-size: 4vh;
    }
    button {
        width: 40%;
        font-family: 'RajdhaniLight';
    }
    
</style>