# ft_transcendence

Final project of 42's common core.

## Overview

This project is a single page application fullstack where you can play classical pong game with other players using a match-making system, chat with them, move up the rankings and check your statistics. You can add friends and challenge them in 2 game modes. This project uses ``NestJs`` for the backend, ``VueJs`` for the frontend and ``PostgreSQL`` for the database. It runs on 3 docker containers managed with docker compose.

## Installation

```shell
# Clone this repository
git clone https://github.com/bbordere/ft_transcendence.git

# Go into the repository
cd ft_transcendence
```

## Run

First you need to replace the 2 values in the ``env/backend.env`` file with your 42 api credentials. They are required for connection via the 42's intra. You can leave these values blank if you don't want to connect with 42.

You can now run: 
```shell
docker compose up --build
```

It may take a little time to get started. As soon as you see in the console ``Nest application successfully started``, you can go to this url in your favorite browser: 
``http://localhost:8080``
This is the default url, but you can change it by modifying the port and host in the env files.

## Features
- `Pong`: Play pong game with one other player using matchmaking or invitation
	* ***Classic Mode***: Classical pong game with a playing time limit of 1 minute and 30 seconds
	* ***Arcade Mode***: Game mode with 3 powerups available (*Big Paddle*, *Lil Paddle* and *Speedy Ball*)
	* ***Ranked Mode***: Game mode with ranking system where the first player to reach 7 points wins the game

- `Chat`: You can create and join chat rooms to chat with other people

- `2fa`: You can activate double authentication for your account using *Google Authenticator*, for example.

- `Game statistics`: All your game statistics, such as your total number of points, can be viewed on your profile page.

## Screenshots

**Home Page**
![](<images/Home.png>)

**Profile Page**
![](<images/Profile.png>)

**2FA Option**
![](<images/2FA.png>)

**Chat**
![](<images/Chat.png>)

**Waiting for a match**
![](<images/Queue.png>)

**In-game**
![](<images/Ingame.png>)
