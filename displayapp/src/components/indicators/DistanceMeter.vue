
<script>
export default {
    data() {
        return {
        }
    },
    props: {
        data: Array
    }
}
</script>

<template>
    <div class="d-flex flex-column justify-content-center">
        <div class="d-flex flex-row align-items-end mt-5">
        <div class="w-label fnt-20" style="width:70px;">SPEED</div>
        <div class="digital-font fnt-100" style="width:80px;">{{ Math.round(data['vssSpeed']) }}</div>
        <div class="w-label fnt-16" style="margin-left: 10px;">km/h</div>
        </div>
        <div class="d-flex flex-row align-items-end mt-4">
        <div class="w-label fnt-16" style="width:70px;">TOTAL</div>
        <div class="digital-font fnt-50" style="width:80px;">{{ data['total_distance'] }}</div>
        <div class="w-label fnt-16" style="margin-left: 10px;">km</div>
        </div>
        <div class="d-flex flex-row align-items-end mt-2">
        <div class="w-label fnt-16" style="width:70px;">TRIP</div>
        <div class="digital-font fnt-50" style="width:80px;">{{ data['trip_distance'] }}</div>
        <div class="w-label fnt-16" style="margin-left: 10px;">km</div>
        </div>
    </div>
</template>