FROM alpine:3.16

RUN apk update ; apk add nginx openssl

RUN mkdir /etc/nginx/ssl/
RUN openssl req -newkey rsa:4096 -x509 -sha256 -days 365 -nodes \
        -out /etc/nginx/ssl/server.pem \
        -keyout /etc/nginx/ssl/server.key \
        -subj "/C=FR/ST=Paris/L=Paris/O=42 Paris/OU=hubretec/CN=hubretec/"

COPY conf/nginx.conf /etc/nginx/http.d/default.conf

EXPOSE 443
ENTRYPOINT ["nginx", "-g", "daemon off;"]