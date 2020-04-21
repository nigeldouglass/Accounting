<template>
    <div>
        <h1>You should not be here!</h1>
        <h3>If you have been brought here automatically</h3> 
        <h3>and have not been redirected please contact Nigel</h3>
    </div>
</template>

<script>
const { ipcRenderer } = require('electron');
export default {
    created: function (){
        console.log(window.location.href);  
        ipcRenderer.send('err_dir')
    }
}

</script>