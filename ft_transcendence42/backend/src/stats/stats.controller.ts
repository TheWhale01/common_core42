import { Body, Controller, Get, Param, Req, Res, UseGuards } from '@nestjs/common';
import { StatsService } from './stats.service';
import { JwtAuthGuard } from 'src/auth/guards/jwt-auth.guard';
import { Request, Response } from 'express'
import { UserService } from 'src/user/user.service';

@Controller('stats')
export class StatsController {
	constructor(private readonly statsService: StatsService, private readonly userService: UserService) {}

	@Get()
	async getAllStats(){
		return await this.statsService.getAllStats();
	}

	@UseGuards(JwtAuthGuard)
	@Get('/me')
	async getMyStats(@Req() req: Request){
		return await this.statsService.getPersonnalStats(req);
	}

	@Get(":name")
	async getUserStats(@Param('name') name: string, @Res({passthrough: true}) res: Response){
		const user = await this.userService.getByName(name);
		if (!user)
			res.statusCode = 401;
		else{
			return await this.statsService.getUserStats(user["stats"]["id"]);
		}
	}

	@Get('/rank/:id')
	async getRank(@Param('id') id : number){
		return await this.statsService.getRankPosition(id);
	}
}
