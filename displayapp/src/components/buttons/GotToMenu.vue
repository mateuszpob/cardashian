<template>
    <i @click="escape()" :style="[ s == 'left' ? {left: x + 'px', top: y + 'px'} : {right: x + 'px', top: y + 'px'}]" class="menu-button bi bi-grid-3x3-gap"></i>
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
    props: {
        x: Number,
        y: Number,
        s: Text
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
.menu-button {
    text-shadow: 0 0 10px #49FF18, 0 0 10px #49FF18, 0 0 5px #49FF18, 0px 0px 10px rgba(206,89,55,0);
    color: #fff;
    font-size: 8vh;
    line-height: 8vh;
    position: absolute;
    z-index: 9999;
    opacity: 0.2;
}
</style>