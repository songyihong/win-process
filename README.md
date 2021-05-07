# win-process
Node.js native addon for find or kill win process. When the window system is unable to use tasklist/taskkill to get the process list or kill the process under some UAC settings, you can use this library

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
killProcess(pid: number): boolean
```

```js
const winProcess = require('@songyh/win-process')

const isSuccess = winProcess.killProcess(111)
```

## find process id by process name

```
findProcessId(processName: string): Array<number> | boolean
```

```js
const winProcess = require('@songyh/win-process')

const pidArr = winProcess.findProcess('chrome.exe')
```

## find process name by process id

```
findProcessName(pid: number): string | boolean
```

```js
const winProcess = require('@songyh/win-process')

const pname = winProcess.findProcessName(1)
```

## find process path by process id

```
findProcessPath(pid: number): string | boolean
```

```js
const winProcess = require('@songyh/win-process')

const processPath = winProcess.findProcessPath(1)
```