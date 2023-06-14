<template>
    <div class="container-xxl ">
      <GotToMenu :context="dashboard" :x="20" :y="10"></GotToMenu>
      <br><br><br><br>
      <div class="menu-wrapper core-left">
        <div class="menu d-flex flex-column px-4 py-5" data-augmented-ui="tl-2-clip-x tr-2-clip-x border">
          <div v-for="item in menu_items" @click="handleMenuItemClick(item)" v-bind:key="item.label" class="menu-item py-2">{{ item.label }}</div>
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
              'confirmation': this.restartApp,
              'data': 'Do you want to restart the application?',
              'arg': null
            },
            {
              'label': 'Update app',
              'confirmation': this.updateApp,
              'data': 'Do you want to update and restart the application?',
              'arg': null
            },
            // {
            //   'label': 'Visible params',
            //   'options': this.getSimpleParamsOptions(),
            // },
            {
              'label': 'About',
              'info': this.about,
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
  methods: {
    handleMenuItemClick(item) {
      console.log(typeof item.callback)
      if(typeof item.callback === 'function') {
        item.callback();
      } else if(typeof item.confirmation === 'function') {
        setTimeout(() => {
          if(this.displayConfirmation(item.data))
          item.confirmation();
        }, 50);
        
      }
    },
    displayConfirmation(text) {
      return window.confirm(text);
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
.menu-item:active{
  color: #49FF18;
  text-shadow: 0 0 10px #49FF18, 0 0 10px #49FF18, 0 0 10px #49FF18, 0px 0px 10px rgba(206,89,55,0);
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
  --aug-border: initial;
    --aug-border-all: 2px;
    --aug-border-bg: var(--hot-blue);
    background: rgb(33,36,0);
background: linear-gradient(180deg, rgba(33,36,0,0.1) 0%, rgba(111,121,9,0.5) 100%, rgba(89,93,0.9) 10%);
    /* background: rgb(33,36,0);
background: linear-gradient(180deg, rgba(33,36,0,1) 10%, rgba(111,121,9,0.5438550420168067) 0%, rgba(89,93,0,1) 100%); */
  /* background: linear-gradient(to bottom right, var(--c2), transparent), repeating-radial-gradient(var(--c0-a), var(--c0-a) 1px, transparent 2px, transparent 50px), repeating-linear-gradient(to right, transparent, transparent 24px, var(--c0-a) 25px, transparent 26px, transparent 100px), repeating-linear-gradient(to bottom, transparent, transparent 24px, var(--c0-a) 25px, transparent 26px, transparent 100px), linear-gradient(var(--c0-a), var(--c0-a)), var(--c1); */
}
div {
  --c0-l: var(--media-prefers-light) #257ae4;
    --c0-l-a: var(--media-prefers-light) rgba(37, 122, 228, 0.25);
    --c0-l-i: var(--media-prefers-light) gold;
    --c1-l: var(--media-prefers-light) #fffffd;
    --c1-l-i: var(--media-prefers-light) #1e1e1c;
    --c2-l: var(--media-prefers-light) #fdfdfa;
    --c3-l: var(--media-prefers-light) #e4e4e4;
    --c4-l: var(--media-prefers-light) #fcfcfa;
    --c0: var(--c0-l, gold);
    --c0-a: var(--c0-l-a, rgba(255, 215, 0, 0.25));
    --c0-i: var(--c0-l-i, #257ae4);
    --c1: var(--c1-l, #1e1e1c);
    --c1-i: var(--c1-l-i, #fffffd);
    --c2: var(--c2-l, #1d1d1b);
    --c3: var(--c3-l, #2c2c2a);
    --c4: var(--c4-l, #312d18);
    --hbl: var(--media-prefers-light) #4039a5;
    --hot-blue: var(--hbl, #b1ffff);
    --hot-red: #ff604d;
    --hot-green: #b9ffb1;
}
</style>