#include "irc.hpp"

void Server::user(Client &client, std::vector<std::string> const &args)
{
	if (args.size() < 4)
		throw (NeedMoreParamsException(client.getServerName(), client.getNickName(), "USER"));
	if (client.getRegist())
		throw (AlreadyRegistredException(client.getServerName(), client.getNickName()));
	client.setUserName(args[0]);
	client.setHostName(args[1]);
	client.setServerName(args[2]);
	client.setRealName(args[3]);
	if (!client.getNickName().empty() && !client.getRegist())
	{
		std::string welcome;

		welcome = format_reply(client, RPL_WELCOME, "") + "Welcome to the fucked up IRC server!\r\n";
		client.setRegist(true);
		send(client.getPoll().fd, welcome.c_str(), welcome.length(), 0);
	}
}