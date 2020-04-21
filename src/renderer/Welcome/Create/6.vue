<template>
    <div id="container">
        <div id="bar-top-bottom">
            <div class="progress-box">
                <div class="progress-bar" style="width:100%;"></div>
            </div>
        </div>
        <div id="content">
            <div>
                <h3 v-if="!error">Creating Company</h3>
                <center>
                    <canvas v-if="!error" width="27" height="27" id="myCanvas"></canvas>
                    <h3 v-if="error" style="color:red;">{{error}}<br>Returning home in 3 seconds.</h3>
                </center>
                
            </div>
        </div>
        <div id="bar-top-bottom">
            <a v-on:click="cancel">CANCEL</a>
        </div>
    </div>
</template>

<script>
export default {
    props:['company', 'error'],
    data(){
        return{
            complete: false,
            si: Object
        }
    },
    created: function(){
        var self = this;
        self.complete = true;
        init(self);
    },
    beforeDestroy: function(){
        var self = this;
        clearInterval(self.si);
    },
    methods: {
        cancel: function() {
            this.$router.push({ path: '/Welcome' });
        }
    }
}
var cog = new Image();
            function init(self) {
                cog.src = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABsAAAAbCAYAAACN1PRVAAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5ccllPAAABK1JREFUeNqMVt1ZGzkUvVfS4IW1l8GO82w6IBXE7mCpAFMB+Pt4Z6iApALcAe4AU0HoAJfg7BPYHinnXmmciX+y0YdmJHnQ0bk/R5cvh5cUyFPwRD4EChgEvGWMB36R3+JaiTkmD5gOs8yNb25uLlerFf1pM2yIGA82TEY7xow1oj4GBU6S6yywPNG4JwDH+XGv0Whs7ndN8n97mmPsLCSYgy7ImPQE/pFDyAF+7L0fgTNFUDBcLal90taD1doQ/T6NT9DnW8zkT+jJuQVYukG3hifCVk/L3JOxMBa8VVlSp9MhHKLaB+zpNo1fdgEpmByuMqUAV5viOQLwXNax9KBAFNEEpN1pUwnQmvl6aTza6zNjrCKaymeyOdYAMgfg18iG4T/qw+AC94zvpzDjcwqOXo3VGH26H0xMZ7jPxgT0R2zUi4BYt6bAfEbJvJFZKA4ODgZ5nhcJLE9mk35X21vWC/TXKmiwr2xszoQd/PQv3t/QCzY2twpqBpb5FKOp+hCgzWaTWq0W1Xx0ij5An9WC5VtiLMwvNBrVaSGMvQk5jHQVPN7sb0HzAtE+QJrNgrcUNEARieWCut0ugR0tl8sKcJ5Ahc3jRviPK8ZGTaaBwGKyT+gTiwM4a3Jrba6MbeVXo5F4kp9shn29ndUYC9vLirGDXzRhrYhD8DME5Hkg22df5rDYS/RXmVIsaP/Q/SXs600YnifTjbeSWliEdTYb3QyTqYfdDKTL4B1KS6tVqf6SgGq3P9BvZGpvNIrPCgVKZlGlCDQDxJiCjVppCab05DJHzb+b1Gm36X80cVjLuzozexs0f6IgRkA5XRhzIixRL1+IzhwdHVHrn1Y9oXe1i10aKT6bGGhg1CKK+cT0zCGCs0oXTIogybJMw/779//o48duMvnO9rzLn+Kz8wgS5Shqo4njpCoOQA5Ajb8adHh4SMvVghaLhYb/HsBip88krNVISSEigOlhjmi0LziNhr6wOsgO9C1339vbGznnNAU2AM9Svk235cqKieKGkldAf7DGvTrjnjJnzyQoMu0ZTuZgUqvmlYR+f39XIE4uqCX1E/rDZpCYmKwOOmivAfYK9KF1AM7EdG4uAMLAOjmQideQXOJQkyUisqYiFRhtSFbxCxj8do0T30dmTvLhC+an0MZZVBHX09tBTG4qFigZEJEChjTIEwtRik81Qa7uOQU0IrYAe7FRjqYw6SlYjgAyN1GmHsFIGPfVnxzFuFITKEkfYK+oWZ5qKlIkcZ7UE92oXBmeIgIxtAO5UtSHqo9uiLW+sme5ejSIRASeAFR4LYy8MMzL1aq3EYWzJF28BgMEzGYpBkrMKelgl+P6uTcVY8NjLYyYPwMTCcufSaouH6al9xNJcjC82vDb9uVZKbrWIumNO+waVsu1TCC+Wxcg6xaSpsZSYM2wLO9/U8qZWH+wztQnsfAxV/E3MIKZVf1FsmJVV8mamhEmxZ0X7sSsABsGv1tZJGejmptU7FBUDYzPAXQBwFEEl+9+stFEroJEci2ELwIMmZuWoSTE9DYYcWVCjlJrZWMpeBhlAEqBiulPE84S3ixU5gSTwGGOdyEVNJXxA8nPevshwABHktBS1YoQ+QAAAABJRU5ErkJggg=='; // Set source path
                if(self.complete){
                   self.si = setInterval(updateLoading,10);
                }
            }
            var rotation = 0;
            function updateLoading(){
                if(document.getElementById('myCanvas').getContext){
                    var ctx = document.getElementById('myCanvas').getContext('2d');
                    ctx.globalCompositeOperation = 'destination-over';
                    ctx.save();
                    ctx.clearRect(0,0,27,27);
                    ctx.translate(13.5,13.5); // to get it in the origin
                    rotation +=1;
                    ctx.rotate(rotation*Math.PI/64); //rotate in origin
                    ctx.translate(-13.5,-13.5); //put it back
                    ctx.drawImage(cog,0,0);
                    ctx.restore();
                }
            }
</script>

<style scoped>
#container{
    display: flex;
    flex-flow: column;
    height: 100%;
}

#content{
  transform: translate(40%, 40%);
}

#content div canvas{
    padding-top:20px;
}
</style>