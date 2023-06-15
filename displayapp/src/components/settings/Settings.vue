

<script>
import OptionCheckBox from './OptionCheckBox.vue';
import GotToMenu from '../buttons/GotToMenu.vue';
import PopupOne from './PopupOne.vue';
import { restartApplication, updateApplication } from '../../core_actions';

export default {
  name: 'Settings',
  data()  {
    return {
      popupText: '',
      nButton: 'Close',
      yButton: 'OK',
      yCallback: null,

      faded: false,


      dashboardFrame: null,
      settings_option: 0,
      currentMenuLength: 2,
      selected_items: [],
      menu_items: [
            {
              'label': 'Restart app',
              'confirmation': this.restartApp,
              'data': 'Do you want to restart the application?',
              'arg': null,
              'yBtn': 'Yes',
              'nBtn': 'No',
            },
            {
              'label': 'Update app',
              'confirmation': this.updateApp,
              'data': 'Do you want to update and restart the application?',
              'arg': null,
              'yBtn': 'Yes',
              'nBtn': 'No',
            },
            // {
            //   'label': 'Visible params',
            //   'options': this.getSimpleParamsOptions(),
            // },
            {
              'label': 'About',
              'info': this.about,
              'data': 'About'
            },
            {
              'label': 'Info',
              'info': this.about,
              'data': 'Info page'
            },

            {
              'label': 'Back to menu',
              'callback': this.escape,
              'data': 'Info page'
            },
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
  created() {
    this.emitter.on("ux", o => {
      switch(o) {
        case "openpopup":
          this.faded = true;
          break;
        case "closepopup":
          this.faded = false;
          break;
      }
    });
  },
  methods: {
    handleMenuItemClick(item) {
      if(typeof item.callback === 'function') {
        item.callback();
      } else if(typeof item.confirmation === 'function') {
        this.displayConfirmation(item);
        // if(this.displayConfirmation(item.data))
        //   item.confirmation();
      } else if(typeof item.info === 'function') {
        this.displayInfo(item);
      }
    },
    displayInfo(item) {
      this.popupText = item.data;
      this.yButton = '';
      this.emitter.emit("ux", "openpopup");
    },
    displayConfirmation(item) {
      this.popupText = item.data;
      this.yButton = item.yBtn;
      this.nButton = item.nBtn;
      this.yCallback = item.confirmation;
      this.emitter.emit("ux", "openpopup");
    },
    restartApp() {
      restartApplication();
    },
    updateApp() {
      updateApplication();
    },
    about() {
      alert("Smoli trochę?");
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
    GotToMenu,
    PopupOne
  }
}
</script>

<template>
  <div class="container-xxl h-100">
    <PopupOne ref="popupone" :text="popupText" :yButton="yButton" :nButton="nButton" :yCallback="yCallback"></PopupOne>
    <!-- <GotToMenu :context="dashboard" :x="20" :y="10"></GotToMenu> -->
    <div ref="menucontainer" :class="{faded: faded}" class="menu-wrapper h-100 d-flex justify-content-center align-items-center">
      <div class="menu border-blu ylo-cnt w-50 d-flex flex-column px-4 py-5" data-augmented-ui="tl-2-clip-x tr-2-clip-x border">
        <div v-for="item in menu_items" @click="handleMenuItemClick(item)" v-bind:key="item.label" class="menu-item light-text-3 py-2">{{ item.label }}</div>
      </div>
    </div>
 </div>
</template>

<style scoped>
.container-xxl {
  background: url('/./public/bckg_1.jpg');
  /* width: 100%; */
  height: 100%;
}
.menu-item {
  padding-left: 20px;
}
.menu-item:active{
  color: var(--zi-def);
  /* text-shadow: 0 0 10px var(--zi-def), 0 0 10px var(--zi-def), 0 0 10px var(--zi-def), 0px 0px 10px rgba(206,89,55,0); */
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
.menu {

    /* background: rgb(33,36,0);
background: linear-gradient(180deg, rgba(33,36,0,1) 10%, rgba(111,121,9,0.5438550420168067) 0%, rgba(89,93,0,1) 100%); */
  /* background: linear-gradient(to bottom right, var(--c2), transparent), repeating-radial-gradient(var(--c0-a), var(--c0-a) 1px, transparent 2px, transparent 50px), repeating-linear-gradient(to right, transparent, transparent 24px, var(--c0-a) 25px, transparent 26px, transparent 100px), repeating-linear-gradient(to bottom, transparent, transparent 24px, var(--c0-a) 25px, transparent 26px, transparent 100px), linear-gradient(var(--c0-a), var(--c0-a)), var(--c1); */
}

</style>