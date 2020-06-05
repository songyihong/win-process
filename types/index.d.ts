declare class WinProcess {
    killProcess(pid: number): boolean;
    findProcess(pname: string): Array<number>;
}

declare const winProcess: WinProcess

export default winProcess