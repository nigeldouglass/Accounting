<template>
    <chooseView v-if=" viewModel === 'choose' "></chooseView>
    <createView1 v-else-if=" viewModel === 'create1' " :company="company"></createView1>
    <createView2 v-else-if=" viewModel === 'create2' " :company="company"></createView2>
    <createView3 v-else-if=" viewModel === 'create3' " :company="company"></createView3>
    <createView4 v-else-if=" viewModel === 'create4' " :company="company"></createView4>
    <createView5 v-else-if=" viewModel === 'create5' " :company="company"></createView5>
    <createView6 v-else-if=" viewModel === 'create6' " :company="company" :error="error"></createView6>
</template>

<script>
import chooseView from './0.vue';
import createView1 from './Create/1.vue';
import createView2 from './Create/2.vue';
import createView3 from './Create/3.vue';
import createView4 from './Create/4.vue';
import createView5 from './Create/5.vue';
import createView6 from './Create/6.vue';

const { ipcRenderer } = require('electron');

export default {
    props:['companies'],
    data(){
        return {
            mode: '',
            page: '',
            viewModel: '',
            company: [],
            error: ''
        }
    },
    components:{
        chooseView,
        createView1,
        createView2,
        createView3,
        createView4,
        createView5,
        createView6,
    },
    watch:{
        '$route' (to, from) {
            var self = this;
            self.handlePageChange();
            console.log("Mode: "+this.mode+" | "+this.$route.params.mode);
            console.log("Page: "+this.page+" | "+this.$route.params.page);
        }
    },
    created: function(){
        var self = this;
        helper(self);
        self.handlePageChange();
        self.company.name = '';
        self.company.street1 = '';
        self.company.street2 = '';
        self.company.town = '';
        self.company.county = '';
        self.company.country = '';
        self.company.postcode = '';
        self.company.telephone = '';
        self.company.fax = '';
        self.company.email = '';
        self.company.website = '';
        self.company.type = '';
        self.company.financialYear = [];
        self.company.financialYear.start = new Date();
        self.company.financialYear.start.setDate(new Date().getDate()-new Date().getDate()+1);
        self.company.financialYear.end = new Date();
        self.company.password = '';
    },
    methods: {
        handlePageChange: function(){
            if(this.$route.params.mode)
                this.mode = this.$route.params.mode;
            if(this.$route.params.page)
                this.page = this.$route.params.page;

            switch(this.mode){
                case 'Create':
                    switch(this.page){
                        case '1':
                            this.viewModel="create1"
                            break;
                        case '2':
                            this.viewModel="create2"
                            break;
                        case '3':
                            this.viewModel="create3"
                            break;
                        case '4':
                            this.viewModel="create4"
                            break;
                        case '5':
                            this.viewModel="create5"
                            break;
                        case '6':
                                this.viewModel="create6"
                                ipcRenderer.invoke('create_company', this.company);
                            break;
                        default:
                            this.$router.push({ path: '/Welcome' });
                    }
                    break;
                case 'Load':
                    break;
                default:
                    this.viewModel='choose'
                    break;

                console.log(this.mode);
                console.log(this.page);
            }
        }
    }
}

var self;

function helper(s){
    self = s;
}

ipcRenderer.on('create_company_reply', (event, arg) => {
    if(arg.pass){
        self.companies.push({name: arg.company.name, location: arg.company.location});
    }else{
        self.error = "Creating company failed!";
    }
    setTimeout(() => {
        self.$router.push({ path: '/Welcome' });
    }, 3000);
})

</script>

<style scoped>
>>> .inactive{
    background-color: var(--primary) !important;
    color: var(--secondary) !important;
}
>>> #container{
    display: flex;
    flex-flow: column;
    height: 100%;
}
>>> #bar-top-bottom{
    flex: 0 1 48px;
    width: 100% !important;
    background-color:var(--primary);
    overflow: hidden;
    padding: 10px;
    border-bottom: var(--secondary) 1px solid;
    border-top: var(--secondary) 1px solid;
}

>>> .progress-box{
    width: 100%;
    height: 28px;
    border: var(--secondary) 2px solid;
}

>>> .progress-bar{
    width: 100%;
    height:100%;
    background-color: var(--dark-green);
}


>>> #content{
    flex: 1 1 auto;
    padding: 16px;
    font-size: 12px;
}

>>> #content div{
    position: absolute;
}

>>> #content div input{
    margin-left: 40px;
    margin-bottom: 20px;
}

>>> #content div input:first-of-type{
    margin-top: 20px;
}


>>> #content div table{
    font-size: 12px;
}

>>> #content div table tr td input{
    top:-5px;
    width: 100%;
    border: var(--secondary) 1px solid;
    padding: 1px;
    margin:0px;
}

>>> #content div table tr td{
    padding-top:10px;
}

>>> #content div table tr:first-of-type td{
    padding-top:20px;
}

>>> #content div table input:first-of-type{
    margin-top: 0px;
}

>>> #content div table input{
    margin-bottom: 0px;
}

>>> #bar-top-bottom a {
    float: left;
    text-decoration: none;
    margin-right: 16px;
    color:var(--primary);
    background-color:var(--dark);
    border: var(--secondary) 1px solid;
    text-align:center;
    line-height: 28px;
    width: 64px;
    height: 28px;
    font-size: 12px;
    border-radius: 6px;
}

>>> #bar-top-bottom a:last-of-type {
  margin-right: 0px;
}

>>> .bartop-right {
  float: right;
}

</style>