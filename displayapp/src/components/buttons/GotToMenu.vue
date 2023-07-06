<template>
    <i @click="escape()" :style="{left: x + 'px', top: y + 'px'}" class="menu-button bi bi-box-arrow-in-left"></i>
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
        y: Number
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
}
</style>