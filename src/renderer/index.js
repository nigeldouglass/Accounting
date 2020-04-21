import Vue from 'vue';
import VueRouter from 'vue-router';
import Welcome from './Welcome/Welcome.vue';
import Default from './Default.vue';
import WelcomeView from './Welcome/View.vue';
import App from './App.vue';

import './style.css';

Vue.use(VueRouter);

var companies = [
    {name: 'Nigel Ltd', location: 'C://Accounts/nigelltd001'},
    {name: 'Nigel Ltd', location: 'C://Accounts/nigelltd002'},
    {name: 'Nigel Ltd', location: 'C://Accounts/nigelltd003'},
]

const routes = [
    { path: '/Welcome', component: Welcome, props: {companies: companies}, name: 'Welcome'},
    { path: '/Welcome/:mode', component: WelcomeView, props: {companies: companies}, name: 'addCompany'},
    { path: '/Welcome/:mode/:page', component: WelcomeView, props: {companies: companies}, name: 'addCompanyPage'},
    { path: '*', component: Default},
];

const router = new VueRouter({
    routes
}); 

new Vue({
    el: '#app',
    router,
    data(){
        return {
        }
    },
    render: h => h(App)
});