#include "irc.hpp"

void Server::mode(Client &client, std::vector<std::string> const &args)
{
	char sign = '!';
	size_t mode_args = 0;
	std::string charset;
	Channel::iter_member target;
	if (args.size() < 1)
		throw(NeedMoreParamsException(client.getServerName(), client.getNickName(), "MODE"));
	if (args[0][0] == '&' || args[0][0] == '#')
	{
		Channel::iter_channel channel = search_channel(args[0]);
		if (channel == _channels.end())
			throw(NoSuchChannelException(client.getServerName(), client.getNickName(), args[0]));
		if (args.size() == 1)
		{
			send_to_user(client, format_reply(client, RPL_CHANNELMODEIS, args[0]) + channel->getChannelMode() + "\r\n");
			return ;
		}
		Channel::iter_member member_cli = channel->search_user_in_channel(client.getNickName());
		if (member_cli == channel->getChannelMembers().end())
			throw (NotOnChannelException(client.getServerName(), client.getNickName(), args[0]));
		if (args[1] == "b")
			return ;
		if (member_cli->second == 0)
			throw (ChanoPrivsNeededException(client.getServerName(), client.getNickName(), args[0]));
		charset = "tiomsn";
		for (size_t i = 0; i < args[1].size(); i++)
		{
			if (args[1][i] == '+')
				sign = '+';
			else if (args[1][i] == '-')
				sign = '-';
			else if (sign != '!' && (charset.find(args[1][i]) != std::string::npos))
			{
					if (args[1][i] == 'o')
					{
						mode_args++;
						if (args.size() < mode_args + 2) {
							mode_args--;
							continue ;
						}
						target = channel->search_user_in_channel(args[1 + mode_args]);
						if (target == channel->getChannelMembers().end()) {
							send_to_user(client, ":" + client.getServerName() + " 441 " + args[0] + " MODE " + args[1 + mode_args] + " :They aren't on that channel\r\n");
							continue ;
						}
						if ((sign == '+') && (target->first->getMode() & MODE_R)) {
							send_to_user(client, ":" + client.getServerName() + " 484 " + args[0] + " MODE " + args[1] + " :Can't chanop, " + target->first->getNickName() + " is a restricted (+r) user\r\n"); 
							continue ;
						}
						(sign == '+') ? target->second = 1 : target->second = 0;
						send_to_members_in_chan(*channel, format_msg(client) + "MODE " + args[0] + " :" + sign + args[1][i] + " " + args[mode_args + 2] + "\r\n", std::string());
					}
					else {
						(sign == '+') ? channel->setChannelMode(args[1][i]) : channel->unsetChannelMode(args[1][i]);
						send_to_members_in_chan(*channel, format_msg(client) + "MODE " + args[0] + " :" + sign + args[1][i] + "\r\n", std::string());
					}
			}
			else
				send_to_user(client, ":" + client.getServerName() + " 501 " + args[0] + " MODE " + args[1][i] + " :Unknown mode flag\r\n");
		}
	}
	else
	{
		Client::iterator cli = search_client(args[0]);
		if (cli == _clients.end())
			throw(NoSuchNickException(client.getServerName(), client.getNickName(), args[0]));
		if (args[0] != client.getNickName())
			throw(UserDontMatchException(client.getServerName(), client.getNickName()));
		if (args.size() == 1)
		{
			send_to_user(client, format_reply(client, RPL_UMODEIS, std::string()) + client.getClientMode() + "\r\n");
			return ;
		}
		charset = "iroO";
		for (size_t i = 0; i < args[1].size(); i++)
		{
			if (args[1][i] == '+')
				sign = '+';
			else if (args[1][i] == '-')
				sign = '-';
			else if (sign != '!' && (charset.find(args[1][i]) != std::string::npos))
			{
				if (((sign == '-') && (args[1][i] == 'r')) || ((sign == '+') && ((args[1][i] == 'o') || (args[1][i] == 'O'))))
					continue ;
				(sign == '+') ? (*cli)->setClientMode(args[1][i]) : (*cli)->unsetClientMode(args[1][i]);
				send_to_user(client, format_msg(client) + "MODE " + args[0] + " :" + sign + args[1][i] + "\r\n");
			}
			else
				send_to_user(client, ":" + client.getServerName() + " 501 " + client.getNickName() + " MODE :Unknown " + args[1][i] + " flag\r\n");
		}
	}
}
