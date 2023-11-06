#!/bin/sh

sleep 40

#Install WP-CLI
wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
chmod +x wp-cli.phar
mv wp-cli.phar /usr/local/bin/wp

#Install wordpress
cd /var/www/html/wordpress
wp core download --allow-root
chown -R www-data:www-data /var/www/html/wordpress
cp /tmp/wp-config.php ./
find /var/www/html/wordpress -type f -exec chmod 644 {} \;
find /var/www/html/wordpress -type d -exec chmod 755 {} \;

#create wordpress site
wp core install --url=hubretec.42.fr --title=hubretec\'s\ inception \
	--admin_user=$WP_ADMIN_USER --admin_password=$WP_ADMIN_PASSWD \
	--admin_email=hubretec@student.42.fr --skip-email --allow-root

/usr/sbin/php-fpm7 -RF
