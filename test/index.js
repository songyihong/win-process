const winProcess = require('../build/Release/win-process');

const chrome = winProcess.findProcess('chrome.exe');

console.log(chrome)

console.log(winProcess.killProcess(9999999999999));