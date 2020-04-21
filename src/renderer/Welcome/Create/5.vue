<template>
    <div id="container">
        <div id="bar-top-bottom">
            <div class="progress-box">
                <div class="progress-bar" style="width:100%;"></div>
            </div>
        </div>
        <div id="content">
            <div>
                <h3>Confirm Details</h3>
                Please check the following information that you have entered is correct.
                <br>
                <fieldset style="border: 1px solid var(--primary); padding: 5px;">
                    <legend style="margin-left:10px; font-weight:bold;">Company Details</legend>
                    <table style="width:100%;">
                        <tr>
                            <td style="width:150px;">
                                File Location:
                            </td>
                            <td style="width:250px;">
                                LOCATION
                            </td>
                        </tr>
                        <tr>
                            <td style="width:150px;">
                                Company Name:
                            </td>
                            <td style="width:250px;">
                                {{company.name}}
                            </td> 
                        </tr>
                        <tr>
                            <td style="width:150px;">
                                Company Type:
                            </td>
                            <td style="width:250px;">
                                {{company.type}}
                            </td> 
                        </tr>
                        <tr>
                            <td style="width:150px;">
                                Financial Year:
                            </td>
                            <td style="width:250px;">
                                {{financialYear}}
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
            financialYear:'',
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
            ]
        }
    },
    created: function(){
        var self = this;
        self.financialYear =    self.company.financialYear.start.getDate()+" "+self.months[self.company.financialYear.start.getMonth()]+" "+self.company.financialYear.start.getFullYear()+" - "+
                        self.company.financialYear.end.getDate()+" "+self.months[self.company.financialYear.end.getMonth()]+" "+self.company.financialYear.end.getFullYear();
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
            this.$router.push({ path: '/Welcome/Create/4' });
        },
        next: function() {
            var step = this;
            if(step.complete){
                this.$router.push({ path: '/Welcome/Create/6' });
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