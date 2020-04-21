<template>
    <div id="container">
        <div id="bar-top-bottom">
            <div class="progress-box">
                <div class="progress-bar" style="width:10%"></div>
            </div>
        </div>
        <div id="content">
            <div>
                <h3>Welcome to Accounts</h3>
                Please select one of the following options.
                <br>
                <input type="radio" id="New" value="New" v-model="picked">
                <label for="New">Set-up new company</label>
                <br>
                <input type="radio" id="Existing" value="Existing" v-model="picked">
                <label for="Existing">Use existing data stored</label>
                <br>
            </div>
        </div>
        <div id="bar-top-bottom">
            <a v-on:click="cancel">CANCEL</a>
            <div class="bartop-right">
                <a v-on:click="back" :class="{ 'inactive' : picked == ''}">BACK</a>
                <a v-on:click="next" :class="{ 'inactive' : picked == ''}">NEXT</a>
            </div>
        </div>
    </div>
</template>

<script>
export default {
    created: function(){
        var step = this;
    },
    data(){
        return{
            picked: ''
        }
    },
    methods: {
        cancel: function() {
            this.$router.push({ path: '/Welcome' });
        },
        back: function() {
            var step = this;
            if(step.picked!='')
                this.$router.push({ path: '/Welcome' });
        },
        next: function() {
            var step = this;
            if(step.picked!=''){
                switch(step.picked){
                    case 'New':
                        this.$router.push({ name: 'addCompanyPage', params:{mode: 'Create', page: '1'}});
                        break;
                    case 'Existing':
                        this.$router.push({ path: '/Welcome' });
                        break;
                }
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