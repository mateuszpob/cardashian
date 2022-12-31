
const state = {
    menu: localStorage.getItem('menu') ? localStorage.getItem('menu') : null,
};

const actions = {
    async setMenu({ commit }, data) {
        console.log("COMMIT SIDE MENU", data)
        commit('setMenu', JSON.stringify(data));
    },
    async toggle({ commit }, field) {
        let actualValue = JSON.parse(state.menu)[field];
        let menu = JSON.parse(state.menu);
        console.log(field, actualValue)
        menu[field] = actualValue ^ 1;
        console.log(field, menu)
        commit('setMenu', JSON.stringify(menu));
    }
};

const getters = {
    getMenu: (state) => JSON.parse(state.menu),
    isMenuLoaded: (state) => state.menu
};

const mutations = {
    setMenu(state, menu) {
        state.menu = menu;
        localStorage.setItem('menu', menu);
    },
};

export default {
    state,
    mutations,
    actions,
    getters,
};