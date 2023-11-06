FROM alpine:3.16

RUN echo "https://dl-cdn.alpinelinux.org/alpine/v3.15/community" >> /etc/apk/repositories ;\
	apk update ; apk upgrade ;\
	apk add php7 php7-common php7-session \
	php7-iconv php7-json php7-gd php7-curl php7-xml php7-mysqli \
	php7-imap php7-cgi fcgi php7-pdo php7-pdo_mysql php7-soap \
	php7-xmlrpc php7-posix php7-mcrypt php7-gettext php7-ldap \
	php7-ctype php7-dom php7-simplexml php7-fpm php7-phar

RUN mkdir -p /var/www/html/wordpress ; adduser -u 82 -D -S -G www-data www-data \
	; cd /var/www/html/wordpress
COPY script/script.sh /tmp/script.sh
COPY conf/default.conf /etc/php7/php-fpm.d/www.conf
COPY conf/wp-config.php /tmp

EXPOSE 9000
ENTRYPOINT [ "sh", "/tmp/script.sh" ]
