SRCS_DIR=srcs/
COMPOSE_F=$(SRCS_DIR)docker-compose.yml
COMPOSE=docker compose -f $(COMPOSE_F)

all:
	mkdir -p ~/data/wp_data
	mkdir -p ~/data/db
	$(COMPOSE) up -d --build

down:
	$(COMPOSE) down

clean: down
	docker system prune --force --volumes --all
	sudo rm -rf /home/hubretec/data

status:
	docker ps -a
	docker network ls

re: down all

.PHONY: all down re status clean
