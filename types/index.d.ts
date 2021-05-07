declare class WinProcess {
    killProcess(pid: number): boolean;
    findProcess(pname: string): Array<number>;
    findProcessId(pname: string): Array<number>;
    findProcessName(pid: number): string | boolean;
    findProcessPath(pid: number): string | boolean;
}

declare const winProcess: WinProcess

export default winProcess