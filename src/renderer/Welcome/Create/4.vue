<template>
    <div id="container">
        <div id="bar-top-bottom">
            <div class="progress-box">
                <div class="progress-bar" style="width:90%"></div>
            </div>
        </div>
        <div id="content">
            <div>
                <h3>Set managers password</h3>
                To keep the data of your company safe, it is recommended that you set a password to protect the data. By default there is no password set for manager account.

                <br>
                <fieldset style="border: 1px solid var(--primary); padding: 5px; margin-top:20px;">
                    <legend style="margin-left:10px; font-weight:bold;">Password</legend>
                    <table style="width:100%">
                        <tr>
                            <td>
                                Enter Password:
                            </td>
                            <td>
                            <input v-model="company.name" :placeholder="company.name" @change="nameComplete" style="font-size:12px;">
                            </td>
                        </tr>
                        <tr>
                            <td>
                                Confirm Password:
                            </td>
                            <td>
                            <input v-model="company.name" :placeholder="company.name" @change="nameComplete" style="font-size:12px;">  
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
            this.$router.push({ path: '/Welcome/Create/3' });
        },
        next: function() {
            var step = this;
            if(step.complete){
                this.$router.push({ path: '/Welcome/Create/5' });
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

#content div table tr td:nth-child(odd){
    width: 130px !important;
}

#content div table tr td:nth-child(even){
    width: auto !important;
}

#content div fieldset{
    width: 50% !important;
}
</style>