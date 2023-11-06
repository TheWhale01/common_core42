import { io, type Socket } from "socket.io-client";

export class SocketService {
	private static socket: Socket;
	private static isUp: boolean = false;
	private static myUser: any;
	private static isUpdateNeeded: boolean = false;

	static get getUpdateStatus(){
		return (this.isUpdateNeeded);
	}

	static setUpdateStatus(status: boolean){
		SocketService.isUpdateNeeded = status;
	}

	static get getInstance(){
		return (this.socket);
	}

	static async setSocket(url: string, args: any){
		SocketService.socket = io(url, args);
		this.isUp = true;
	}

	static async fetchUser(){
		this.myUser = await (await fetch('http://' + import.meta.env.VITE_HOST + ':3000/user/me', {credentials: 'include'})).json();
	}

	static get getStatus(){
		return (this.isUp);
	}

	static get getUser(){
		return (this.myUser);
	}
}