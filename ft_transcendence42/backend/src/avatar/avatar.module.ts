import { Module } from '@nestjs/common';
import { AvatarController } from './avatar.controller';
import { AvatarService } from './avatar.service';
import { UserModule } from 'src/user/user.module';

@Module({
	imports: [UserModule],
	controllers: [AvatarController],
	providers: [AvatarService]
})
export class AvatarModule {}
