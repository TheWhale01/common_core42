import { Column, Entity, Generated, PrimaryColumn } from "typeorm";

@Entity()
export class StatsDetail{
	@PrimaryColumn()
	@Generated('increment')
	id: number

	@Column({ default: 0})
	wins: number

	@Column({ default: 0})
	looses: number

	@Column({ default: 1000})
	mmr: number

	@Column("decimal", { precision: 5, scale: 2, default: 0.0 })
	meanScore: number

	@Column({ default: 0})
	winPoints: number

	@Column({ default: 0})
	loosePoints: number

	@Column({ default: 0})
	highScore: number

	@Column({ default: 0})
	totalGames: number

	@Column({ default: 0})
	totalClassicGames: number

	@Column({ default: 0})
	totalArcadeGames: number

	@Column({ default: 0})
	totalRankedGames: number

	@Column({ default: 0})
	totalFriendsDuel: number

	@Column({ default: 0})
	totalPowerups: number

	@Column({ default: 0})
	totalMessages: number

	@Column({ default: 0})
	totalEmotes: number
}