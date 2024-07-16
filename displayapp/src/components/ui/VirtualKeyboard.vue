<template>
    <div>
        <div ref="keyboard" class="simple-keyboard"></div>
    </div>
  </template>
  
  <script>
  import Keyboard from "simple-keyboard";
  import "simple-keyboard/build/css/index.css";
  
  export default {
    name: "VirtualKeyboard",
    data() {
      return {
        keyboard: null,
        selectedInput: null
      };
    },
    created() {
        this.emitter.on("ux", o => {
        switch(o) {
            case "openkeyboard":
            this.visible = true;
            break;
        }
        });
    },
    mounted() {
        this.keyboard = new Keyboard(this.$refs.keyboard, {
            onChange: input => this.onChange(input),
            onKeyPress: button => this.onKeyPress(button),
            mergeDisplay: true,
        layoutName: "default",    
            layout: {
            default: [
                "q w e r t y u i o p",
                "a s d f g h j k l",
                "{shift} z x c v b n m {backspace}",
                "{numbers} {space} {ent} {close}"
            ],
            shift: [
                "Q W E R T Y U I O P",
                "A S D F G H J K L",
                "{shift} Z X C V B N M {backspace}",
                "{numbers} {space} {ent}"
            ],
            numbers: ["1 2 3", "4 5 6", "7 8 9", "{abc} 0 {backspace}"]
            },
            display: {
                "{numbers}": "123",
                "{ent}": "confirm",
                "{escape}": "esc ⎋",
                "{tab}": "tab ⇥",
                "{backspace}": "⌫",
                "{capslock}": "caps lock ⇪",
                "{shift}": "⇧",
                "{controlleft}": "ctrl ⌃",
                "{controlright}": "ctrl ⌃",
                "{altleft}": "alt ⌥",
                "{altright}": "alt ⌥",
                "{metaleft}": "cmd ⌘",
                "{metaright}": "cmd ⌘",
                "{abc}": "ABC",
                "{close}": "reject"
            }
        });

        this.keyboard.setOptions({
            theme: "hg-theme-default hg-layout-default"
        });

        // document.querySelector(".input").addEventListener("focus", event => {
        //     this.selectedInput = event.target;
        //     keyboard.setInput(event.target.value);
        // });
        document.querySelectorAll(".input").forEach(input => {
            input.addEventListener("focus", event => {
                this.selectedInput = event.target;
                this.keyboard.setInput(event.target.value);
            });
        });
    },
    props: {
        enterAction: {
            type: Function
        }
    },
    methods: {
        onChange(input) {
            if (this.selectedInput) {
                this.selectedInput.value = input;    
            }
            
            // console.log("Input changed", input);
        },
        onKeyPress(button) {
            if (button === "{shift}") {
                this.isShift = !this.isShift;
                this.keyboard.setOptions({
                layoutName: this.isShift ? "shift" : "default"
                });
            } else if (button === "{numbers}") {
                this.keyboard.setOptions({ layoutName: "numbers" });
            } else if (button === "{abc}") {
                this.keyboard.setOptions({ layoutName: "default" });
            } else if (button === "{close}") {
                this.emitter.emit("ux", "closepopup");
            } else if (button === "{ent}") {
                this.enterAction()
            }
        }
    }
  };
  </script>
  <style>
/* Ciemny zielony motyw z półprzezroczystością dla simple-keyboard */
.simple-keyboard {
  background-color: rgba(34, 49, 34,1); /* Ciemnozielone tło klawiatury z półprzezroczystością */
  color: #e0f2f1; /* Jasny zielony kolor liter */
  border-radius: 10px; /* Zaokrąglenie rogów klawiatury */
  box-shadow: 0 4px 8px rgba(0, 0, 0,1); /* Cień pod klawiaturą */
  font-size: 1.5rem; /* Rozmiar czcionki */
}

/* Styl dla przycisków klawiatury */
.simple-keyboard .hg-button {
  background-color: rgba(21, 128, 61,1); /* Ciemnozielone tło przycisków z półprzezroczystością */
  color: #e0f2f1; /* Jasny zielony kolor liter */
  border: 1px solid rgba(21, 128, 61,1); /* Ciemnozielona obwódka przycisków z półprzezroczystością */
  border-radius: 5px; /* Zaokrąglenie rogów przycisków */
  padding: 25px; /* Wewnętrzne marginesy przycisków */
  margin: 5px 10px; /* Margines między przyciskami */
}

/* Styl dla przycisków klawiatury w trybie Shift */
.simple-keyboard .hg-button.hg-shift {
  background-color: rgba(15, 100, 47,1); /* Jaśniejsze ciemnozielone tło dla przycisków Shift */
  color: #ffffff; /* Biały kolor liter w trybie Shift */
}

/* Styl dla przycisków klawiatury w trybie Numbers */
.simple-keyboard .hg-button.hg-numbers {
  background-color: rgba(21, 128, 61,1); /* Ciemnozielone tło przycisków Numbers */
  color: #ffffff; /* Biały kolor liter w trybie Numbers */
}

/* Styl dla przycisków specjalnych */
.simple-keyboard .hg-button.hg-space {
  background-color: rgba(34, 49, 34,1); /* Ciemniejsze tło dla spacji z półprzezroczystością */
  color: #e0f2f1; /* Jasny zielony kolor liter na spacji */
  border: none; /* Brak obwódki dla spacji */
}

/* Styl dla przycisków w trybie Shift - gdy jest aktywowany */
.simple-keyboard .hg-button.hg-shift-active {
  background-color: rgba(9, 72, 34,1); /* Ciemniejsze tło w trybie aktywnego Shift */
}

/* Styl dla przycisków w trybie Numbers - gdy jest aktywowany */
.simple-keyboard .hg-button.hg-numbers-active {
  background-color: rgba(9, 72, 34,1); /* Ciemniejsze tło w trybie aktywnego Numbers */
}

/* Styl dla przycisków po najechaniu */
.simple-keyboard .hg-button:hover {
  background-color: rgba(28, 104, 54,1); /* Jaśniejsze ciemnozielone tło przy najechaniu na przycisk */
  color: #ffffff; /* Biały kolor liter przy najechaniu */
}

/* Styl dla przycisków aktywnych - np. klikniętych */
.simple-keyboard .hg-button:active {
  background-color: rgba(21, 128, 61,1); /* Jaśniejsze ciemnozielone tło podczas kliknięcia */
  color: #ffffff; /* Biały kolor liter podczas kliknięcia */
}
.simple-keyboard{
    position: relative;
    top: 0;
}
</style>