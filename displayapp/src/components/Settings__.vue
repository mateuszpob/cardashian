<template>
    <div class="container-xxl ">
      <div class="row">
        <div class="col-2">
            <div v-for="(value, key) in currentMenuOption" v-bind:key="key" :class="value.active ? 'active' : ''" data-index="{{ key }}">
              {{ value.label }}
            </div>
        </div>
        <!-- <div class="col-8">
            <div v-for="(value, key) in settings[selected_items[0]]" v-bind:key="key">
              {{ value[selected_items[1]].label }}
            </div>
        </div> -->
      </div>
   </div>
</template>

<script>
export default {
  name: 'Settings',
  data()  {
    return {
      settings_option: 0,
      selected_items: [],
      settings: [
        {
          'label': 'Dashboard',
          'active': '1',
          'options': [
            {
              'label': 'widoczne elementy',
              'options': [
                {'label': 'opcja 1'},
                {'label': 'opcja 2'},
                {'label': 'opcja 3'},
              ]
            },
            {
              'label': 'Themes',
              'options': [
                {'label': 'standard'},
                {'label': 'cyberpunk'},
                {'label': 'Universum Szkolna 17'}
              ]
            }
          ]
        },
        {
          'label': 'YouTube',
          'options': [
            {
              'label': 'Ulubione nuty',
              'options': [
                {'label': 'opcja 1'},
                {'label': 'opcja 2'},
                {'label': 'opcja 3'},
              ]
            },
            {
              'label': 'Pierdoły',
              'options': [
                {'label': 'standard'},
                {'label': 'cyberpunk'},
                {'label': 'Universum Szkolna 17'}
              ]
            }
          ]
        },
      ]
    }
  },
  props: {
    msg: String
  },
  created() {
    this.emitter.on("escape", isOpen => {
      this.escape();
    });
    this.emitter.on("action", action => {
      switch(action) {
        case "turnLeft":
          // this.selected_items[this.settings_option]++;
          break;
        case "turnRight":
          this.clearOptions();
          this.settings_option++;
          this.settings_option = this.settings_option % this.settings.length
          this.settings[this.settings_option].active = 1;
          // this.selected_items[this.settings_option]--;
          break;
      }

    });
  },
  mounted() {

  },
  computed: {
    currentMenuOption() {
      let op = this.settings;
      //  this.settings[0].options[0].options
    
      this.selected_items.forEach(o => {
        op = op[o].options
      });


      return op
    }
  },
  beforeUnmount() {  
    this.emitter.off("escape");
  },
  methods: {
    clearOptions(options) {
      options.forEach(o => {
        o.active = 0;
      })
    },
    escape() {
      switch(true){
        default:
          this.$router.push({ name: 'menu' })
      }
    }
  },
  components: {
    
  }
}
</script>

<style scoped>
.wrapper {
  padding: 5px;
}
.active {
  border: 1px solid #00ee00;
}
</style>