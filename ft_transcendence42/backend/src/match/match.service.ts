import { Injectable, } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { Match } from './match.entity';
import { MatchDto } from './match.dto';
import { UserService } from 'src/user/user.service';
import { Request } from 'express';
import { StatsService } from 'src/stats/stats.service';
import { Room } from 'src/pong/interface/room.interface';

@Injectable()
export class MatchService {
	constructor(@InjectRepository(Match) private matchRepository: Repository<Match>,
		private userService: UserService,
		private statsService: StatsService) { }

	async filterMatchesEntry(matches: Match[]) {
		const test = matches.map((match) => {
			const { player1, player2, ...rest } = match;
			const { password: password1, auth2fSecret: auth1, ...player1WithoutPassword } = player1;
			const { password: password2, auth2fSecret: auth2, ...player2WithoutPassword } = player2;
			return {
				...rest,
				player1: player1WithoutPassword,
				player2: player2WithoutPassword,
			};
		})
		return (test);
	}

	async getAllMatches() {
		const matches: Match[] = await this.matchRepository.find();
		return (await this.filterMatchesEntry(matches));
	}

	updateStats(match: Match) {
		match.player1.stats.winPoints += match.scorePlayer1;
		match.player2.stats.winPoints += match.scorePlayer2;
		match.player1.stats.loosePoints += match.scorePlayer2;
		match.player2.stats.loosePoints += match.scorePlayer1;
		match.player1.stats.highScore = Math.max(match.player1.stats.highScore, match.scorePlayer1);
		match.player2.stats.highScore = Math.max(match.player2.stats.highScore, match.scorePlayer2);
		switch (match["mode"]) {
			case "Classique":
				match.player1.stats.totalClassicGames++;
				match.player2.stats.totalClassicGames++;
				break;
			case "Arcade":
				match.player1.stats.totalArcadeGames++;
				match.player2.stats.totalArcadeGames++;
				break;
			case "Classée":
				match.player1.stats.totalRankedGames++;
				match.player2.stats.totalRankedGames++;
				break;
			default:
				match.player1.stats.totalFriendsDuel++;
				match.player2.stats.totalFriendsDuel++;
				break;
		}
		match.player1.stats.totalGames++;
		match.player2.stats.totalGames++;
		if (match.scorePlayer1 != match.scorePlayer2 || match.leaverId != -1) {
			if ((match.scorePlayer1 > match.scorePlayer2
				&& match.player1.id !== match.leaverId) || match.player2.id === match.leaverId) {
				match.player1.stats.wins++;
				match.player2.stats.looses++;
			}
			else {
				match.player2.stats.wins++;
				match.player1.stats.looses++;
			}
		}
		match.player1.stats.meanScore = match.player1.stats.winPoints / match.player1.stats.totalGames;
		match.player2.stats.meanScore = match.player2.stats.winPoints / match.player2.stats.totalGames;
	}

	async createMatch(matchDto: MatchDto, isRanked: boolean, room: Room) {
		const match = this.matchRepository.create(matchDto);
		match.player1 = room.players[0].user;
		match.player2 = room.players[1].user;
		match.player1.stats = await this.statsService.getUserStats(match.player1.stats.id);
		match.player2.stats = await this.statsService.getUserStats(match.player2.stats.id);
		if (!match.player1 || !match.player2)
			return;
		this.updateStats(match);
		if (isRanked)
			await this.statsService.getUpdatedMmr(match)
		await this.userService.saveUser(match.player1);
		await this.userService.saveUser(match.player2);
		return (await this.matchRepository.save(match));
	}

	async getMyMatches(req: Request) {
		const user = req["user"]["user"];
		const matches: Match[] = await this.matchRepository.find({
			where: [{ player1: user }, { player2: user }],
			order: {
				id: 'DESC'
			},
		});
		return (await this.filterMatchesEntry(matches));
	}

	async getUserMatches(user) {
		const matches: Match[] = await this.matchRepository.find({
			where: [{ player1: user }, { player2: user }],
			order: {
				id: 'DESC'
			},
		})
		return (await this.filterMatchesEntry(matches));
	};
}
