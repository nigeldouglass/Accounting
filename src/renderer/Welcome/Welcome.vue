<template>
    <div id="container">
        <div id="bar-top">
            <router-link to="/Welcome/0">Add Company</router-link>
            <a v-on:click="do_action">Remove Company</a>
            <div class="bartop-right">
                <a v-on:click="do_action">Open Company Location</a>
            </div>
        </div>
        <div id="content">
            <table style="width:90%; margin:auto; border: var(--dark) 1px solid; margin-top:10px;border-spacing: 0;empty-cells: show;">
                <tr>
                    <th style="width:60%; background: var(--cream); height: 18px; border-right:var(--dark) 1px solid;">Company Name</th>
                    <th style="background: var(--cream);">Location</th>
                </tr>
                <tr v-for="company in companies">
                <td style=" border-right:var(--dark) 1px solid;">{{ company.name }}</td>
                <td>{{ company.location }}</td>
                </tr>
                <tr v-for="n in (15-companies.length)">
                <td style="height: 24px; border-right:var(--dark) 1px solid;"></td>
                <td></td>
                </tr>
            </table>
        </div>
        <div id="bar-bottom">
            Companies: {{companies.length}}
        </div>
    </div>
</template>

<script>
const { ipcRenderer } = require('electron');
export default {
    props:['companies'],
    data(){
        return {
        }
    },
    created: function (){
      console.log(window.location.href);  
    },
    methods: {
        do_action: function() {
            ipcRenderer.send('resize')
        }
    }
}
</script>

<style scoped>
*{
    font-size: 14px;
}
#container{
    height:500px;
}
#bar-top{
    display: block;
    position:fixed;
    top:0px;
    height: 132px;
    width: 100%;
    background-color:var(--primary);
    overflow: hidden;
    padding: 16px;
    border-bottom: var(--secondary) 1px solid;
}

#content{
    position:fixed;
    display: block;
    top:132px;
    width: 100%;
}

#bar-bottom{
    display: block;
    position:fixed;
    height: 32px;
    width: 100%;
    bottom:0px;
    background-color:var(--primary);
    overflow: hidden;
    padding-left: 16px;
    line-height: 32px;
    border-top: var(--secondary) 1px solid;
}

#bar-top a {
    float: left;
    text-decoration: none;
    margin-right: 16px;
    color:var(--primary);
    background-color:var(--dark);
    display: flex;
    text-align:center;
    align-items: center;
    width: 100px;
    height: 100px;
    font-size: 17px;
    border-radius: 10px;
}

#bar-top a:last-of-type {
  margin-right: 0px;
}

.bartop-right {
  float: right;
}

table tr:nth-child(odd) td{
    background-color: var(--primary);
}

table tr td{
    padding: 3px;
}
table tr th{
    padding: 3px;
}
</style>