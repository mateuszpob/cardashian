<template>
    <div class="container-xxl ">
      <div class="row">
        <div class="menu-col col-4">
           <option-check-box v-for="(value, key) in currentMenuOption" :data-index="key" v-bind:key="key" :label="value.label" :class="settings_option == key ? 'active' : ''" />
        </div>
        <div class="menu-col col-8 " v-if="currentMenuOption && currentMenuOption[settings_option]">
            <option-check-box  v-for="(subvalue, key) in currentMenuOption[settings_option].options" :label="subvalue.label" :data-index="key" v-bind:key="key" />
          
        </div>
      </div>
   </div>
</template>

<script>
import OptionCheckBox from './settings/OptionCheckBox.vue';
export default {
  name: 'Settings',
  data()  {
    return {
      dashboardFrame: null,
      settings_option: 0,
      currentMenuLength: 0,
      selected_items: [],
      settings: [
        {
          'label': 'Dashboard',
          'active': '1',
          'options': [
            {
              'label': 'widoczne elementy',
              'options': this.getDashboardOptions(),
            },
            {
              'label': 'Themes',
              'options': [
                {'label': 'standard'},
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
    this.emitter.on("dashframe", data => {
      if(!this.$store.getters.getMenu) {
        let sideMenu = {};
        Object.keys(data).forEach((k) => { 
          sideMenu[k] = 1;
        });
        this.$store.dispatch('setMenu', sideMenu)

      }

      // this.dashboardFrame = data;
      this.emitter.off("dashframe");
      
      let ob = [];
      for(let k in data) {
        ob.push({'label': k, 'callback': this.setVisibility, 'arg': k})
      }

      this.settings[0].options[0].options = ob
    });
    this.emitter.on("action", action => {
      switch(action) {
        case "turnLeft":
          if(this.settings_option > 0)
          this.settings_option--;
          break;
        case "turnRight":
          if(this.settings_option < this.currentMenuLength - 1)
          this.settings_option++;
          break;
        case "enter":
          this.selected_items.push(this.settings_option);
          

          let ob = this.settings;
          this.selected_items.forEach((i) => {
            if(ob[i].callback instanceof Function) {
              ob[i].callback(ob[i].arg);

              this.selected_items.pop()
            } else {
              ob = ob[i].options;
              this.currentMenuLength = ob.length;
            }
          });
          break;
        case "escape":
          if(this.selected_items.length === 0) {
            this.escape();
          }
          this.selected_items.pop();
          this.settings_option = 0;
          break;
      }

    });
  },
  mounted() {

  },
  computed: {
    sideMenu: {
        get() {
            return this.$store.getters.getMenu;
        },
    },
    currentMenuOption() {
      let op = this.settings;
      this.selected_items.forEach(o => {
        op = op[o].options
      });


      return op
    }
  },
  beforeUnmount() {  
    this.emitter.off("action");
  },
  methods: {
    setVisibility(id) {
      this.$store.dispatch('toggle', id)
    },
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
    },
    moveMenuDown() {
      
    },
    getDashboardOptions() {
      // return [
      //           {'label': 'RPM', 'callback': this.setVisibility, 'arg': 'RPM'},
      //           {'label': 'TPS', 'callback': this.setVisibility, 'arg': 'TPS'},
      //           {'label': 'IAT', 'callback': this.setVisibility, 'arg': 'IAT'},
      //         ]
      
    }
  },
  components: {
    OptionCheckBox
    
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
.menu-option-sm {
  color: #ffffff;
}

.container-xxl, .row, .menu-col {
  height: 400px;
}
.menu-col {
    display: flex;
    flex-wrap: wrap;
    flex-direction: column;
}
</style>