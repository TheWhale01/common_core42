import { User } from "src/user/user.entity";
import { Column, Entity, Generated, ManyToOne, PrimaryColumn } from "typeorm";

@Entity()
export class Match{
	@PrimaryColumn()
	@Generated('increment')
	id: number

	@ManyToOne(() => User, (player1: User) => player1.id, {cascade: true, eager: true})
	player1: Partial<User>;
	
	@ManyToOne(() => User, (player2: User) => player2.id, {cascade: true, eager: true,})
	player2: Partial<User>;

	@Column({ default: 0})
	scorePlayer1: number;

	@Column({ default: 0})
	scorePlayer2: number;

	@Column({ default: "" })
	mode: string;

	@Column({ default: -1 })
	leaverId: number;
}