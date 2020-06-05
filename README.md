# win-process
When the window system is unable to use tasklist/taskkill to get the process list or kill the process under certain permission settings, you can use this library

# Usage
If you not install window build tools, please install first
```sh
npm install --global --production windows-build-tools --vs2015
```

```sh
npm i @songyh/win-process
```

```js
const winProcess = require('@songyh/win-process')
```
# Api

## kill process
```
boolean killProcess(int pid)
```

```js
const winProcess = require('@songyh/win-process')

const isSuccess = winProcess.killProcess(111)
```

## find process id by process name

```
array<int> findProcess(string processName)
```

```js
const winProcess = require('@songyh/win-process')

const pidArr = winProcess.findProcess('chrome.exe')
```