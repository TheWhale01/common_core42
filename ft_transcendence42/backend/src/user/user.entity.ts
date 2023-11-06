import { Column, Entity, PrimaryColumn, Generated, BeforeInsert, JoinColumn, OneToOne, ManyToMany, JoinTable, OneToMany } from "typeorm";
import * as bcrypt from 'bcrypt';
import { StatsDetail } from '../stats/stats.entity';
import { Channel } from "src/chat/entities/channel.entity";

export enum State {
	OFFLINE,
	ONLINE,
	INGAME,
}

@Entity()
export class User {
	@PrimaryColumn()
	@Generated('increment')
	public id: number;

	@Column({ unique: true })
	public email: string;

	@Column({ unique: true })
	public name: string;

	@Column({ default: ""})
	public password: string;

	@Column({ default: false })
	public auth2f: boolean

	@Column({ default: ""})
	public auth2fSecret: string

	@Column({ default: ""})
	public avatarLink: string

	@OneToOne(() => StatsDetail, (stats: StatsDetail) => stats.id, {
		cascade: true,
		eager: true,
	})

	@JoinColumn()
	public stats: StatsDetail;

	@ManyToMany(() => Channel)
	@JoinTable()
	public channels: Channel[];

	@Column('int', { array: true, default: [] })
	public blockList: number[];

	@BeforeInsert()
	async hashPassword() {
		this.password = await bcrypt.hash(this.password, 8);
	}

	async validatePassword(password: string): Promise<boolean> {
		return await bcrypt.compare(password, this.password);
	}
}