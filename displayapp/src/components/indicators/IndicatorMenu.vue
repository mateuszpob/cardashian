<template>
    <div v-if="isVisible" class="menu" @click.stop>
      <ul>
        <li v-for="item in menuItems" :key="item.id">{{ item.name }}</li>
      </ul>
    </div>
  </template>
  
  <script>
  import axios from 'axios';
  
  export default {
    name: 'IndicatorMenu',
    props: {
      isVisible: {
        type: Boolean,
        required: true
      }
    },
    data() {
      return {
        menuItems: []
      };
    },
    watch: {
      isVisible(val) {
        if (val) {
          this.fetchMenuItems();
        }
      }
    },
    methods: {
      async fetchMenuItems() {
        try {
          const response = await axios.get('https://api.example.com/menu-items');
          this.menuItems = response.data;
        } catch (error) {
          console.error('Error fetching menu items:', error);
          this.menuItems = [
                { name: 'option 1'}, 
                { name: 'option 2'}, 
                { name: 'option 3'}, 
            ];
        }
      }
    }
  };
  </script>
  
  <style scoped>
  .menu {
    position: absolute;
    top: 0;
    left: 0;
    background: white;
    border: 1px solid #ccc;
    width: 200px;
    box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
    max-height: 300px; /* Opcjonalne ograniczenie maksymalnej wysokości */
    overflow-y: auto;
  }
  
  ul {
    list-style-type: none;
    padding: 0;
    margin: 0;
  }
  
  li {
    padding: 10px;
    cursor: pointer;
  }
  
  li:hover {
    background-color: #f0f0f0;
  }
  </style>