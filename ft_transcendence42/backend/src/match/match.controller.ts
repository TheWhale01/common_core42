import { Body, Controller, Get, Param, Post, Req, UseGuards } from '@nestjs/common';
import { MatchService } from './match.service';
import { MatchDto } from './match.dto';
import { UserService } from 'src/user/user.service';
import { JwtAuthGuard } from 'src/auth/guards/jwt-auth.guard';
import { Request } from 'express';
import { StatsService } from 'src/stats/stats.service';

@Controller('match')
export class MatchController {
	constructor(private readonly matchService: MatchService, private readonly userService: UserService) {}

	@Get()
	async getAllMatch(){
		return await this.matchService.getAllMatches();
	}

	@UseGuards(JwtAuthGuard)
	@Get('/me')
	async getMyMatches(@Req() req: Request){
		return await this.matchService.getMyMatches(req);
	}

	@Get(':name')
	async getUserMatches(@Param('name') name: string){
		const user = await this.userService.getPartialUser(await this.userService.getByName(name));
		return (await this.matchService.getUserMatches(user));
	}
}
