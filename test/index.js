const winProcess = require('../build/Release/win-process');

const chrome = winProcess.findProcess('chrome.exe');

console.log(chrome);

chrome.forEach(pid => {
    console.log(winProcess.findProcessName(pid));
    console.log(winProcess.findProcessPath(pid));
});

console.log(winProcess.killProcess(9999999999999));