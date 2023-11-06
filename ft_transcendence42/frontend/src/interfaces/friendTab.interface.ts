import type { Channel } from "./channel.interface";

export interface friendTab {
	id: number;
	status: string;
	username: string;
	request: number;
	channel: Channel;
}