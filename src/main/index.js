const {app, BrowserWindow, ipcMain, dialog} = require('electron');
const os = require('os'); 
const path = require('path');
const url = require('url');

const cppDB = require('../../build/Release/CppDB')

const isDevelopment = process.env.NODE_ENV !== 'production'

let win;

var login = false;


function createWindow(){
    console.log(os.platform());
    const jsonObj = {
        location:   '/Users/nigeldouglass/Documents/Accounts/',
        name:       'Nigel',
        type:       'db',
        username:   'Manager',
        password:   'Password',
        os:         os.platform()
    }
    const jsonString = JSON.stringify(jsonObj)
/*
    console.log(jsonObj);
    console.log(cppDB.jsonParse(jsonString));

    console.log(jsonString);
    console.log(cppDB.jsonStringify(jsonObj));
*/

    console.log(cppDB.CreateDatabase(jsonString));
    var q = cppDB.Query("SELECT * FROM USERS");
    console.log(q);
    if(q.passed){
        console.log(q.data);
    }

    win = new BrowserWindow({
        width: 800,
        height: 600,
        minWidth: 800,
        minHeight: 600,
        resizable: false,
        icon: path.join(__dirname, '/assets/icons/icon.png'),
        webPreferences:{
            nodeIntegration: true
        }
    });
    if(isDevelopment){
        win.loadURL(`http://localhost:${process.env.ELECTRON_WEBPACK_WDS_PORT}/#/Welcome`)
    }else{
        win.loadURL(url.format({
            pathname: path.join(__dirname, 'index.html'),
            protocol: 'file',
            slashes: true,
            hash: 'Welcome'
        }));
    }

    win.on('closed', ()=>{
        win = null;
    });
}
 
ipcMain.on('err_dir', function(event){
    var err = ((login)?"Dashboard":"Welcome");
    if(isDevelopment){
        win.loadURL(`http://localhost:${process.env.ELECTRON_WEBPACK_WDS_PORT}/#/`+err)
    }else{
        win.loadURL(url.format({
            pathname: path.join(__dirname, 'index.html'),
            protocol: 'file',
            slashes: true, 
            hash: err
        }));
    }
});

ipcMain.handle('create_company', (event, arg) => {
    console.log(arg)
    cppDB.CreateDatabase({
        location:   'NigelDouglass/Documents/Accounts/',
        name:       'Nigel',
        type:       'db',
        username:   'Manager',
        password:   ''
    })
    setTimeout(() => {
        event.sender.send('create_company_reply', {pass: false, company:{name: arg.name, location: 'C://Accounts/'+arg.name}})
    }, 2000);
  })

ipcMain.on('resize', function(event){
    win.setSize(1280,720);
    win.setMinimumSize(1280,720);
    win.setResizable(true);
});


app.on('ready', createWindow);