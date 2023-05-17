<template>
        <div  class="menu-option-sm d-flex flex-row" >
            <div class="selected bi bi-check-square-fill" v-if="this.$store.getters.getMenu[label] === 1"></div>
            <div class="selected bi bi-check-square" v-else-if="this.$store.getters.getMenu[label] === 0"></div>
            {{ label }} 
        </div>

</template>

<script>

export default {
    name: 'OptionCheckBox',
    props: ['label']
}
</script>
