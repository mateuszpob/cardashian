<template>
    <div class="container-xxl ">
      <GotToMenu :context="dashboard" :x="20" :y="10"></GotToMenu>
      <br><br><br><br>
      <div class="menu-wrapper core-left" data-augmented-ui="tl-clip-x tr-clip-x l-clip-y br-clip">
        <div class="menu-item" data-augmented-ui="" v-for="item in menu_items" v-bind:key="item.label">{{ item.label }}</div>
      </div>
      
      <div class="row mt-5">
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
import GotToMenu from './buttons/GotToMenu.vue';
import { restartApplication, updateApplication } from '../core_actions';

export default {
  name: 'Settings',
  data()  {
    return {
      dashboardFrame: null,
      settings_option: 0,
      currentMenuLength: 2,
      selected_items: [],
      menu_items: [
            {
              'label': 'Restart app',
              'callback': this.restartApp,
              'arg': null
            },
            {
              'label': 'Update app',
              'callback': this.updateApp,
              'arg': null
            },
            {
              'label': 'Visible params',
              'options': this.getSimpleParamsOptions(),
            },
            {
              'label': 'Themes',
              'options': [
                {'label': 'standard'},
              ]
            }
          ],
      emuframe: {
        "RPM": "1222",
        "MAP": "84",
        "TPS": "5",
        "IAT": "13",
        "Batt": "13.84",
        "IgnAngle": "17.0",
        "pulseWidth": "2.71",
        "scondarypulseWidth": "0.0",
        "Egt1": "0",
        "Egt2": "0",
        "knockLevel": "0.0",
        "dwellTime": "3.1",
        "wboAFR": "14.7",
        "gear": "1",
        "Baro": "104",
        "analogIn1": "0.0",
        "analogIn2": "0.98",
        "analogIn3": "0.06",
        "analogIn4": "0.0",
        "injDC": "2.5",
        "emuTemp": "32",
        "oilPressure": "0.19",
        "oilTemperature": "23",
        "fuelPressure": "0.0",
        "CLT": "88",
        "flexFuelEthanolContent": "0.0",
        "ffTemp": "0",
        "wboLambda": "1.0",
        "vssSpeed": "4.5",
        "deltaFPR": "0",
        "fuelLevel": "0",
        "tablesSet": "1",
        "lambdaTarget": "0.0",
        "afrTarget": "0.0",
        "cel": "8",
        "total_distance": "14",
        "trip_distance": "14.6"
    }
    }
  },
  props: {
    msg: String
  },
  created() {
    this.emitter.on("escape", isOpen => {
      this.escape();
    });

    if(!this.$store.getters.getMenu) {
        let sideMenu = {};
        Object.keys(this.emuframe).forEach((k) => { 
          sideMenu[k] = 1;
        });
        this.$store.dispatch('setMenu', sideMenu)

      }
      let ob = [];
      for(let k in this.emuframe) {
        ob.push({'label': k, 'callback': this.setVisibility, 'arg': k})
      }



    this.emitter.on("action", action => {

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
    restartApp() {
      restartApplication();
    },
    updateApp() {
      updateApplication();
    },
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
    getSimpleParamsOptions() {
      // return [
      //           {'label': 'RPM', 'callback': this.setVisibility, 'arg': 'RPM'},
      //           {'label': 'TPS', 'callback': this.setVisibility, 'arg': 'TPS'},
      //           {'label': 'IAT', 'callback': this.setVisibility, 'arg': 'IAT'},
      //         ]
      
    }
  },
  components: {
    OptionCheckBox,
    GotToMenu
  }
}
</script>

<style scoped>
.container-xxl {
  background: url('/./public/bckg_1.jpg');
  /* width: 100%; */
  height: 100%;
}
.menu-item {
  color: #fff;
  font-size: 3vw;
  font-weight: 100;
  padding-left: 20px;
}
.core-left, .core-right {
    --aug-border: initial;
    --aug-border-all: 0.25rem;
    --aug-border-bg: rgba(0, 200, 0, 0.3);
    padding: 1rem;
    position: relative;
    background: rgba(1, 22, 1, 0.3);
    color: #fffffd;
    transform-origin: 50% 50%;
}
</style>