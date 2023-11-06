#include "irc.hpp"

void Server::_who_user(Client const &client, Client const &target, bool in, bool c)
{
	std::string msg;

	if ((target.getMode() & MODE_I) && (in == 0))
		return ;
	msg = ":" + client.getServerName() + " " + RPL_WHOREPLY + " "
		+ client.getNickName() + " " + (c ? getChannels(target)[0].getChannelName() : "*")
		+ " " + target.getUserName() + " " + target.getHostName() + " "
		+ target.getServerName() + " H :1 " + target.getRealName() + "\r\n";
	send(client.getPoll().fd, msg.c_str(), msg.length(), 0);
}

void Server::who(Client &client, std::vector<std::string> const &args)
{
	std::string msg;
	Client::iterator target;
	bool in = 1;

	target = search_client(args[0]);
	if (target == _clients.end())
	{
		Channel::iter_channel chan = search_channel(args[0]);
		if (chan == _channels.end())
			return ;
		if (chan->search_user_in_channel(client.getNickName()) == chan->getChannelMembers().end())
			in = 0;
		std::vector<std::pair<Client *, int> > members = chan->getChannelMembers();
		for (size_t i = 0; i < members.size(); i++)
			_who_user(client, *(members[i].first), in, 1);
	}
	else
		_who_user(client, *(*target), (*target)->getNickName() == client.getNickName(), 0);
	msg = ":" + client.getServerName() + " " + RPL_ENDOFWHO + " " + client.getNickName()
		+ " " + args[0] + ":End of WHO list\r\n";
	send(client.getPoll().fd, msg.c_str(), msg.length(), 0);
}