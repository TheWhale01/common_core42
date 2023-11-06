#include "irc.hpp"

void Server::oper(Client &client, std::vector<std::string> const &args)
{
	std::string answer;
	if (args.size() < 2)
		throw (NeedMoreParamsException(client.getServerName(), client.getNickName(), "OPER"));
	if (args[0] != _opername)
		send_to_user(client, ":" + client.getServerName() + " " + ERR_NOOPERHOST + " " + client.getNickName() + " :No O-lines for your host\r\n");
	else if (args[1] != _operpasswd)
		send_to_user(client, ":" + client.getServerName() + " " + ERR_PASSWDMISMATCH + " " + client.getNickName() + " :Password incorrect\r\n");
	else
	{
		client.setClientMode('o');
		client.setClientMode('O');
		answer = format_msg(client) + "MODE " + client.getNickName() + " :+o\r\n";
		answer += format_msg(client) + "MODE " + client.getNickName() + " :+O\r\n";
		if (client.getMode() & MODE_R) {
			client.unsetClientMode('r');
			answer += format_msg(client) + "MODE " + client.getNickName() + " :-r\r\n";
		}
		send_to_user(client, answer + ":" + client.getServerName() + " " + RPL_YOUREOPER + " " + client.getNickName() + " :You are now an IRC operator\r\n" +
		format_reply(client, RPL_UMODEIS, std::string()) + client.getClientMode() + "\r\n");
	}
}
