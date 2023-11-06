import { User } from "src/user/user.entity";
import { Channel } from "./channel.entity";
import { Column, Entity, Generated, JoinColumn, ManyToOne, PrimaryColumn } from "typeorm";

@Entity()
export class Message {
	@PrimaryColumn()
	@Generated('increment')
	public id: number;

	@Column()
	public channel: number;

	@Column()
	public text: string;

	@Column()
	public sender: number;
}