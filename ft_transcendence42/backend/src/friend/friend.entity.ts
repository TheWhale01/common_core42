import { Channel } from "src/chat/entities/channel.entity";
import { Column, Entity, Generated, JoinColumn, OneToOne, PrimaryColumn } from "typeorm";

@Entity()
export class Friend {
	@PrimaryColumn()
	@Generated('increment')
	public id: number;

	@Column()
	public UserId: number;

	@Column()
	public FriendId: number;

	@Column( { default: 'pending'})
	public Status: string;

	@OneToOne(() => Channel, (channel: Channel) => channel.id, {
		onDelete: "CASCADE",
		onUpdate: 'CASCADE',
		nullable: false,
		eager: true,
	})
	@JoinColumn({name: 'channel'})
	public channel: Channel;
};