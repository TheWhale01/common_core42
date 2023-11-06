#include "irc.hpp"

void Server::ping(Client &client, std::vector<std::string> const &args)
{
	(void)client;
	std::string pong_msg = "PONG " + args[0] + "\r\n";
	send(client.getPoll().fd, pong_msg.c_str(), pong_msg.length(), 0);
}