<template>
    <i @click="escape()" class="menu-button bi bi-grid-3x3-gap"></i>
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
.menu-button {
    color: #49FF18;
    font-size: 60px;
    position: absolute;
    left: 20px;
    top: 10px;
}
</style>