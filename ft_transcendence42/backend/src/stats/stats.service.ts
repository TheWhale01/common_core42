import { Injectable, Req } from '@nestjs/common';
import { StatsDetail } from './stats.entity';
import { Repository } from 'typeorm';
import { InjectRepository } from '@nestjs/typeorm';
import { Request } from 'express'
import { Match } from 'src/match/match.entity';

@Injectable()
export class StatsService {
	constructor(@InjectRepository(StatsDetail) private statsRepository: Repository<StatsDetail>) { }

	async getAllStats() {
		return this.statsRepository.find()
	}

	async getPersonnalStats(@Req() req: Request): Promise<StatsDetail> {
		const user = req["user"]["user"];
		return await this.statsRepository.findOne({
			where: {
				id: user["stats"]["id"]
			},
			loadRelationIds: true
		});
	}

	async getUserStats(statsId: number) {
		return await this.statsRepository.findOne({
			where: {
				id: statsId
			},
			loadRelationIds: true
		});
	}

	async updateStats(match: Match, userId: number, indexPlayer: number, leaverId: number) {
		const stats: StatsDetail = await this.getUserStats(userId);
		const opId = indexPlayer ^ 3;
		stats.winPoints += match[`scorePlayer${indexPlayer}`];
		stats.loosePoints += match[`scorePlayer${opId}`];
		stats.highScore = Math.max(match[`scorePlayer${indexPlayer}`], stats.highScore);

		switch (match["mode"]) {
			case "Classique":
				stats.totalClassicGames++;
				break;
			case "Arcade":
				stats.totalArcadeGames++;
				break;
			case "Classée":
				stats.totalRankedGames++;
				break;
			default:
				stats.totalFriendsDuel++;
				break;
		}
		stats.totalGames++;
		if (match[`scorePlayer${indexPlayer}`] != match[`scorePlayer${opId}`] || leaverId != -1) {
			if ((match[`scorePlayer${indexPlayer}`] > match[`scorePlayer${opId}`] && userId !== leaverId) || match['player' + opId].id === leaverId)
				stats.wins += 1;
			else
				stats.looses += 1;
		}
		stats.meanScore = stats.winPoints / stats.totalGames;
		return (await this.statsRepository.save(stats));
	}

	async getUpdatedMmr(match: Match) {
		if (match.leaverId != -1) {
			const factor = match.player1.id === match.leaverId ? -20 : 20;
			match.player1.stats.mmr += factor;
			match.player2.stats.mmr += -factor;
			return;
		}
		const k = 128;
		const expectedScore1 = 1 / (1 + Math.pow(10, (match.player2.stats.mmr - match.player1.stats.mmr) / 400));
		const expectedScore2 = 1 / (1 + Math.pow(10, (match.player1.stats.mmr - match.player2.stats.mmr) / 400));

		const res1 = match.scorePlayer1 / (match.scorePlayer1 + match.scorePlayer2);
		const res2 = match.scorePlayer2 / (match.scorePlayer2 + match.scorePlayer1);

		const MMRModifier = Math.abs(match.scorePlayer1 - match.scorePlayer2) <= 2 ? 1 : 0.5;

		match.player1.stats.mmr += Math.ceil(k * (MMRModifier * (res1 - expectedScore1)));
		match.player2.stats.mmr += Math.ceil(k * (MMRModifier * (res2 - expectedScore2)));
	}

	async getRankPosition(statsId: number) {
		let allStats: StatsDetail[] = await this.statsRepository.find();
		allStats.sort((a, b) => b.mmr - a.mmr);
		for (let i = 0; i < allStats.length; i++) {
			if (allStats[i].id == statsId)
				return ({ rank: i + 1, total: allStats.length });
		}
	}
}
