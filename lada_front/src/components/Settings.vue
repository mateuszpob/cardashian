<template>
    <div class="container-xxl ">
      <div class="row">
        <div class="col-4">
            <div v-for="(value, key) in currentMenuOption" :data-index="key" v-bind:key="key" :class="settings_option == key ? 'active' : ''" data-index="{{ key }}">
              {{ value.label }}
            </div>
        </div>
        <div class="col-8" v-if="currentMenuOption[settings_option]">
            <div  v-for="(subvalue, key) in currentMenuOption[settings_option].options" :data-index="key" v-bind:key="key">
              {{ subvalue.label }}
            </div>
        </div>
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
                {'label': 'RPM', 'callback': this.setVisibility},
                {'label': 'TPS', 'callback': this.setVisibility},
                {'label': 'IAT', 'callback': this.setVisibility},
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
          console.log(this.currentMenuOption)
          this.settings_option--;
          break;
        case "turnRight":
          this.settings_option++;
          break;
        case "enter":
          let ob = [];
          
          this.selected_items.forEach((i) => {
            ob = this.settings[i]
            
          });

          console.log(ob)
            if(ob.callback) {
              ob.callback()
              return
            }

          // if(this.selected_items.callback) {
          //   console.log("CALLBACLK")
          //   this.selected_items.callback("OKKK")
          //   return;
          // }

          this.selected_items.push(this.settings_option);
          this.settings_option = 0;
          break;
        case "escape":
          this.selected_items.pop();
          this.settings_option = 0;
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
    setVisibility() {
      console.log("setVisibility: ")
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