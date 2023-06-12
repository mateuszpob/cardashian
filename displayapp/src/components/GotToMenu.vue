<template>
    <div class="hbw">
        <div @click="escape()" class="hidden-escape left"></div>
        <div @click="escape()" class="hidden-escape right"></div>
    </div>
</template>

<script>
export default {
    data()  {
        return {
            dashboard: {}
        }
    },
    mounted() {

    },
    methods: {
        escape() {
            switch(true){
            default:
                this.$router.push({ name: 'menu' })
            }
        }
    }
}
</script>

<style scoped>
.hbw {
    position: absolute;
}
  .hidden-escape {
    /* border: 1px solid red; */
    width: 15%;
    height: 15%;
    position: absolute;
  }
  .left {
    left: 0;
  }
  .right {
    right: 0;
  }
</style>