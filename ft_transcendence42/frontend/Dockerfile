FROM node:lts-alpine

VOLUME /frontend

EXPOSE 8080

ENTRYPOINT [ "/bin/sh", "-c", "cd frontend && npm install && npm run dev" ]
# ENTRYPOINT [ "/bin/sh", "-c", "cd frontend && npm install && npm run build && npm run preview" ]
