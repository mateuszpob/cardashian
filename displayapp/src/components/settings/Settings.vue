

<script>
import OptionCheckBox from './OptionCheckBox.vue';
import GotToMenu from '../buttons/GotToMenu.vue';
import PopupOne from './PopupOne.vue';
import { restartApplication, updateApplication, setWifiCredentials, restartDevice, openKeyboard } from '../../core_actions';
import Axios from 'axios'
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
              'label': 'Update app',
              'callback': updateApplication,
              'text': 'Do you want to update and restart the application?',
              'arg': null,
              'yBtn': 'Yes',
              'nBtn': 'No',
            },
            {
              'label': 'Restart app',
              'callback': restartApplication,
              'text': 'Do you want to restart the application?',
              'arg': null,
              'yBtn': 'Yes',
              'nBtn': 'No',
            },
            {
              'label': 'Restart device',
              'callback': restartDevice,
              'text': 'Do you want to restart the device?',
              'arg': null,
              'yBtn': 'Yes',
              'nBtn': 'No',
            },
            {
              'label': 'Open keyboard',
              'callback': openKeyboard,
              'text': 'Do you want to open screen keyboard?',
              'arg': null,
              'yBtn': 'Yes',
              'nBtn': 'No',
            },
            {
              'label': 'Wifi settings',
              'text': 'Type wifi credentails',
              'callback': setWifiCredentials,
              'fields': [{label: 'SSID', val: null}, {label: 'PASS', val: null}],
              'yBtn': 'Save'
            },
            // {
            //   'label': 'Visible params',
            //   'options': this.getSimpleParamsOptions(),
            // },
            {
              'label': 'About',
              'info': this.about,
              'text': 'EMU Display<br>v1.0.0'
            },
            {
              'label': 'Info',
              'info': this.info,
              'text': 'mateuszpob@gmail.com',
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
      this.menuItem = item; 
      this.emitter.emit("ux", "openpopup");

      // if(typeof item.callback === 'function') {
      //   item.callback();
      // } else if(typeof item.confirmation === 'function') {
      //   this.displayConfirmation(item);
      //   // if(this.displayConfirmation(item.data))
      //   //   item.confirmation();
      // } else if(typeof item.info === 'function') {
      //   this.displayInfo(item);
      // } else if(typeof item.fields === 'function') {
      //   this.displayFieldsBox(item);
      // }
    },
    displayInfo(item) {
      Axios.get('http://localhost:9001/get/info').then((data) => {
        this.popupText = data.data;
      });

      // this.popupText = getInfo();
      this.yButton = '';
      this.emitter.emit("ux", "openpopup");
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
  <div class="container-sms w-100 h-100">
    <!-- <br><br> -->
    <PopupOne ref="popupone" :item="menuItem"></PopupOne>
    <!-- <PopupOne ref="popupone" :text="popupText" :yButton="yButton" :nButton="nButton" :yCallback="yCallback"></PopupOne> -->
    <!-- <GotToMenu :context="dashboard" :x="20" :y="10"></GotToMenu> -->
    <div ref="menucontainer" :class="{faded: faded}" class="menu-wrapper h-100 d-flex justify-content-center align-items-center">
      <div class="menu border-blu ylo-cnt w-75 d-flex flex-row flex-wrap px-4 py-5" data-augmented-ui="tl-2-clip-x tr-2-clip-x border">
        <div v-for="item in menu_items" @click="handleMenuItemClick(item)" v-bind:key="item.label" class="menu-item w-50 light-text h1 py-2">{{ item.label }}</div>
        <div @click="escape()" class="menu-item w-50 light-text h1 py-2 ">Back to menu</div>
      </div>
    </div>
 </div>
</template>

<style scoped>
.menu-wrapper {
  /* opacity: 0.99; */
}
.container-sms {
  background: url('/./public/bckg_2.jpg');
}
.menu-item {
  padding-left: 20px;
  font-family: 'RajdhaniLight';
  /* font-family: 'RajdhaniRegular'; */
}
.menu-item:active{
  color: var(--zi-def);
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