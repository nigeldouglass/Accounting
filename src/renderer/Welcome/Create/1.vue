<template>
    <div id="container">
        <div id="bar-top-bottom">
            <div class="progress-box">
                <div class="progress-bar" style="width:30%"></div>
            </div>
        </div>
        <div id="content">
            <div>
                <h3>Enter company details</h3>
                <table style="width:100%;">
                    <tr>
                        <td style="width:150px;">
                            Company Name:
                        </td>
                        <td style="width:250px;">
                            <input v-model="company.name" :placeholder="company.name" @change="nameComplete" style="font-size:12px;">
                        </td>
                    </tr>
                    <tr>
                        <td style="width:150px;">
                            Street 1:
                        </td>
                        <td style="width:250px;">
                            <input v-model="company.street1" :placeholder="company.street1" style="font-size:12px;">
                        </td>
                    </tr>
                    <tr>
                        <td style="width:150px;">
                            Street 2:
                        </td>
                        <td style="width:250px;">
                            <input v-model="company.street2" :placeholder="company.street2" style="font-size:12px;">
                        </td>
                    </tr>
                    <tr>
                        <td style="width:150px;">
                            Town:
                        </td>
                        <td style="width:250px;">
                            <input v-model="company.town" :placeholder="company.town" style="font-size:12px;">
                        </td>
                    </tr>
                    <tr>
                        <td style="width:150px;">
                            County:
                        </td>
                        <td style="width:250px;">
                            <input v-model="company.county" :placeholder="company.county" style="font-size:12px;">
                        </td>
                    </tr>
                    <tr>
                        <td style="width:150px;">
                            Country:
                        </td>
                        <td style="width:250px;">
                            <input v-model="company.country" :placeholder="company.country" style="font-size:12px;">
                        </td>
                    </tr>
                    <tr>
                        <td style="width:150px;">
                            Post Code:
                        </td>
                        <td style="width:250px;">
                            <input v-model="company.postcode" :placeholder="company.postcode" style="font-size:12px;">
                        </td>
                    </tr>
                    <tr>
                        <td style="width:150px;">
                            Telephone:
                        </td>
                        <td style="width:250px;">
                            <input v-model="company.telephone" :placeholder="company.telephone" style="font-size:12px;">
                        </td>
                    </tr>
                    <tr>
                        <td style="width:150px;">
                            Fax:
                        </td>
                        <td style="width:250px;">
                            <input v-model="company.fax" :placeholder="company.fax" style="font-size:12px;">
                        </td>
                    </tr>
                    <tr>
                        <td style="width:150px;">
                            Email:
                        </td>
                        <td style="width:250px;">
                            <input v-model="company.email" :placeholder="company.email" style="font-size:12px;">
                        </td>
                    </tr>
                    <tr>
                        <td style="width:150px;">
                            Website:
                        </td>
                        <td style="width:250px;">
                            <input v-model="company.website" :placeholder="company.website" style="font-size:12px;">
                        </td>
                    </tr>
                </table>
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
            complete: false
        }
    },
    created: function(){
        var self = this;
        self.nameComplete();
    },
    methods: {
        nameComplete: function(){
            var self = this;
            console.log(self.company.name.split(" ").length - 1+" | "+self.company.name.length);
            if(self.company.name.length!=0&&(self.company.name.split(" ").length - 1)!=self.company.name.length){
                self.complete = true
            }else{
                self.complete = false;
            }
        },
        cancel: function() {
            this.$router.push({ path: '/Welcome' });
        },
        back: function() {
            this.$router.push({ path: '/Welcome/0' });
        },
        next: function() {
            var step = this;
            if(step.complete){
                this.$router.push({ path: '/Welcome/Create/2' });
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