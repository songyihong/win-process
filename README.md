# win-process
When the window system is unable to use tasklist/taskkill to get the process list or kill the process under certain permission settings, you can use this library

# Usage
```sh
npm i win-process
```

```js
const winProcess = require('win-process')
```
# Api

## kill process
```
boolean killProcess(int pid)
```

```js
const winProcess = require('win-process')

const res = winProcess.killProcess(111)
```

## find process id by process name

```
array<int> killProcess(string processName)
```

```js
const winProcess = require('chrome.exe')

const res = winProcess.killProcess(111)
```