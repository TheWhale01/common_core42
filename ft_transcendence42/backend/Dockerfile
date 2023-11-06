FROM alpine:latest

RUN apk update ; \
	apk add procps; \
	apk add curl ;\
	curl -sL https://deb.nodesource.com/setup_18.x | bash ;\
	apk add --update nodejs npm
RUN npm i -g @nestjs/cli
RUN mkdir /workspace

WORKDIR /workspace

EXPOSE 3000
EXPOSE 5432

ENTRYPOINT [ "/bin/sh", "-c", "npm install --save && npm run start:dev" ]
# ENTRYPOINT [ "/bin/sh", "-c", "npm install --save && npm run build && npm run start:prod" ]
