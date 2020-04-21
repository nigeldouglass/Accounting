<template>
    <div id="container">
        <div id="bar-top-bottom">
            <div class="progress-box">
                <div class="progress-bar" style="width:70%"></div>
            </div>
        </div>
        <div id="content">
            <div>
                <h3>Select financial year end</h3>
                Select the month in which the financial year starts at.
                <br>
                <table style="width:100%;">
                    <tr>
                        <td style="width:150px;">
                            Month:
                        </td>
                        <td style="width:250px;">
                            <select v-model="month" @change="calcFinancialYear">
                            <option v-for="m in months" v-bind:value="m">
                                {{ m }}
                            </option>
                            </select>
                        </td>
                    </tr>
                    <tr>
                        <td style="width:150px;">
                            Year:
                        </td>
                        <td style="width:250px;">
                            <select v-model="year" @change="calcFinancialYear">
                            <option v-for="y in years" v-bind:value="y">
                                {{ y }}
                            </option>
                            </select>
                        </td>
                    </tr>
                </table>
                <br>
                <fieldset style="border: 1px solid var(--primary); padding: 5px;">
                    <legend style="margin-left:10px; font-weight:bold;">Financial Year</legend>
                    <p>{{financialYear}}</p>
                </fieldset>
                <br>
                <br>
                If you need to override the start and end date, tick the box below and pick the correct dates. 
                <br>
                <fieldset style="border: 1px solid var(--primary); padding: 5px;">
                    <legend style="margin-left:10px; font-weight:bold;">Override</legend>
                    <table style="width:100%;">
                        <tr>
                            <td style="width:150px;">
                                Override year:
                            </td>
                            <td style="width:250px;">
                            <input type="checkbox" id="override" v-model="override">
                            </td>
                        </tr>
                        <tr v-if="override">
                            <td style="width:150px;">
                                Start Date:
                            </td>
                            <td style="width:250px;">
                                <select v-model="month" @change="calcFinancialYear">
                                <option v-for="m in months" v-bind:value="m">
                                    {{ m }}
                                </option>
                                </select>
                            </td> 
                        </tr>
                        <tr v-if="override">
                            <td style="width:150px;">
                                End Date:
                            </td>
                            <td style="width:250px;">
                                <select v-model="year" @change="calcFinancialYear">
                                <option v-for="y in years" v-bind:value="y">
                                    {{ y }}
                                </option>
                                </select>
                            </td>
                        </tr>
                    </table>
                </fieldset>
            </div>
        </div>
        <div id="bar-top-bottom">
            <a v-on:click="cancel">CANCEL</a>
            <div class="bartop-right">
                <a v-on:click="back">BACK</a>
                <a v-on:click="next" :class="{ 'inactive' : !complete}">NEXT</a>
            </div>
        </div>
    </div>
</template>

<script>
export default {
    props:['company'],
    data(){
        return{
            complete: true,
            day: '1',
            month: 'January',
            months: [
                 'January'   ,
                 'February'  ,
                 'March'     ,
                 'April'     ,
                 'May'       ,
                 'June'      ,
                 'July'      ,
                 'August'    ,
                 'Septembe'  ,
                 'October'   ,
                 'November'  ,
                 'December'  
            ],
            year: '',
            years: [],
            financialYear:'',
            override: false
        }
    },
    created: function(){
        var self = this;
        var startYear = new Date().getFullYear()-2;
        self.year = startYear;
        for(var i = 0; i<5;i++){
            self.years.push(startYear+i);
        }
        self.type = self.company.type;
        console.log("------");
        console.log(self.company.financialYear.start);
        console.log(self.company.financialYear.end);
        self.year = self.company.financialYear.start.getFullYear();
        self.month = self.months[self.company.financialYear.start.getMonth()];
        self.data = self.company.financialYear.start.getDate();
        self.calcFinancialYear();
    },
    methods: {
        calcFinancialYear: function(){
            console.log("fdhaisu");
            var self = this;
            var mth = 1;
            for(var i = 1; i<=12;i++){
                if(self.month==self.months[i-1]){
                    mth = i;
                    break;
                }
            }
            var startDate = new Date(self.year+" "+mth+" "+self.data);
            var endDate = new Date(startDate.getFullYear()+1, startDate.getMonth(), startDate.getDate());
            endDate.setDate(endDate.getDate()-1);
            self.financialYear =    startDate.getDate()+" "+self.months[startDate.getMonth()]+" "+startDate.getFullYear()+" - "+
                                    endDate.getDate()+" "+self.months[endDate.getMonth()]+" "+endDate.getFullYear();
            self.company.financialYear.start = startDate;
            self.company.financialYear.end = endDate;
        },
        cancel: function() {
            this.$router.push({ path: '/Welcome' });
        },
        back: function() {
            this.$router.push({ path: '/Welcome/Create/2' });
        },
        next: function() {
            var step = this;
            if(step.complete){
                this.$router.push({ path: '/Welcome/Create/4' });
            }
        }
    }
}
</script>

<style scoped>
#container{
    display: flex;
    flex-flow: column;
    height: 100%;
}
</style>