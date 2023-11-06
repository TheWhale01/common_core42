#include "irc.hpp"

void Server::whois(Client &client, std::vector<std::string> const &args)
{
	std::string msg;
	Client::iterator target;
	std::vector<Channel> user_channels;

	if (!args.size())
		throw (NoNickNameGivenException(client.getServerName(), client.getNickName()));
	target = search_client(args[0]);
	if (target == _clients.end())
		throw (NoSuchNickException(client.getServerName(), client.getNickName(), "WHOIS"));

	// Who is USER
	msg = ":" + client.getServerName() + " " + RPL_WHOISUSER + " " + client.getNickName() + " " + (*target)->getNickName()
		+ " " + (*target)->getUserName() + " " + (*target)->getServerName() + " * :" + (*target)->getRealName() + "\r\n";
	send(client.getPoll().fd, msg.c_str(), msg.length(), 0);

	// Who is CHANNEL
	msg = format_reply(client, RPL_WHOISCHANNELS, (*target)->getNickName());
	user_channels = getChannels(*(*target));
	for (Channel::iter_channel it = user_channels.begin(); it != user_channels.end(); it++)
	{
		if ((it->getChannelModes() & MODE_S) && (it->search_user_in_channel(client.getNickName()) == it->getChannelMembers().end()))
			continue ;
		msg = msg + "@" + it->getChannelName() + (it + 1 == user_channels.end() ? "" : " ");
	}
	msg += "\r\n";
	send(client.getPoll().fd, msg.c_str(), msg.length(), 0);

	//Who is SERVER
	msg = ":" + client.getServerName() + " " + RPL_WHOISSERVER + " " + client.getNickName() + " " + (*target)->getNickName()
		+ (*target)->getServerName() + " :The Fucked Up IRC Server - version " + VERSION_NB + "\r\n";
	send(client.getPoll().fd, msg.c_str(), msg.length(), 0);

	//End of who is
	msg = format_reply(client, RPL_ENDOFWHOIS, (*target)->getNickName()) + "End of WHOIS list\r\n";
	send(client.getPoll().fd, msg.c_str(), msg.length(), 0);
}