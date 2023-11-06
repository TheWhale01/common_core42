import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import { BadRequestException, NotAcceptableException, ValidationPipe } from '@nestjs/common';
import { NestExpressApplication } from '@nestjs/platform-express';
import * as cookieParser from "cookie-parser";

async function bootstrap() {
	const app = await NestFactory.create(AppModule);
	const allowedDomains = ["http://localhost:8080", "http://" + process.env.HOST + ":8080"];
	app.enableCors({origin: true, credentials: true});
	app.useGlobalPipes(
		new ValidationPipe({
		  exceptionFactory: (errors) => {
			const result = errors.map((error) => ({
			  property: error.property,
			  message: error.constraints[Object.keys(error.constraints)[0]],
			}));
			return new NotAcceptableException(result);
		  },
		  stopAtFirstError: true,
		}),
	  );
	app.use(cookieParser());
	await app.listen(3000);
}
bootstrap();
