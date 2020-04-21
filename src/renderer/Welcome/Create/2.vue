<template>
    <div id="container">
        <div id="bar-top-bottom">
            <div class="progress-box">
                <div class="progress-bar" style="width:50%"></div>
            </div>
        </div>
        <div id="content">
            <div>
                <h3>Select company type</h3>
                Select the type of business that best suits or is close to the business type you operate under.
                <br>
                <input type="radio" id="Charity" value="Charity" v-model="type" v-on:change="typeComplete">
                <label for="Charity">Charity</label>
                <br>
                <input type="radio" id="CIC" value="CIC" v-model="type" v-on:change="typeComplete">
                <label for="CIC">Community Interest Company</label>
                <br>
                <input type="radio" id="LTD" value="LTD" v-model="type" v-on:change="typeComplete">
                <label for="LTD">Limited Company</label>
                <br>
                This selects the correct nominal codes for the type of business that you operate as.
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
            complete: false,
            type: ''
        }
    },
    created: function(){
        var self = this;
        self.type = self.company.type;
        self.typeComplete();
    },
    methods: {
        typeComplete: function(){
            var self = this;
            if(self.type!==''){
                self.complete = true;
                self.company.type = self.type;
            }else{
                self.complete = false;
            }
        },
        cancel: function() {
            this.$router.push({ path: '/Welcome' });
        },
        back: function() {
            this.$router.push({ path: '/Welcome/Create/1' });
        },
        next: function() {
            var step = this;
            if(step.complete){
                this.$router.push({ path: '/Welcome/Create/3' });
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