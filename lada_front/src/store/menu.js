
const state = {
    menu: localStorage.getItem('menu') ? localStorage.getItem('menu') : null,
    labels: localStorage.getItem('labels') ? localStorage.getItem('labels') : null,
};

const actions = {
    async setMenu({ commit }, data) {
        commit('setMenu', JSON.stringify(data));
    },
    async setLabels({ commit }, data) {
        commit('setLabels', JSON.stringify(data));
    },
    async toggle({ commit }, field) {
        let actualValue = JSON.parse(state.menu)[field];
        let menu = JSON.parse(state.menu);
        menu[field] = actualValue ^ 1;
        commit('setMenu', JSON.stringify(menu));
    }
};

const getters = {
    getMenu: (state) => JSON.parse(state.menu),
    isMenuLoaded: (state) => state.menu,
    labels: (state) => JSON.parse(state.labels)
};

const mutations = {
    setMenu(state, menu) {
        state.menu = menu;
        localStorage.setItem('menu', menu);
    },
    setLabels(state, labels) {
        state.labels = labels;
        localStorage.setItem('labels', labels);
    }
};

export default {
    state,
    mutations,
    actions,
    getters,
};