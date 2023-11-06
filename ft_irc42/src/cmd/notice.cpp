#include "irc.hpp"

void Server::notice(Client &client, std::vector<std::string> const &args)
{
	if (args.size() < 2 || args[1].empty())
		return ;
	std::vector<std::string> targ = split(args[0], ",");
	for (size_t i = 0; i < targ.size(); i++)
	{
		if (targ[i][0] == '#' || targ[i][0] == '&')
		{
			Channel::iter_channel channel = search_channel(targ[i]);
			if (channel == _channels.end())
				continue ;
			Channel::iter_member member = channel->search_user_in_channel(client.getNickName());
			if (channel->getChannelModes() & MODE_N)
			{
				if (member == channel->getChannelMembers().end())
					continue ;
			}
			if (channel->getChannelModes() & MODE_M) {
				if ((member == channel->getChannelMembers().end()) || (member->second == 0))
					continue ;
			}
			send_to_members_in_chan(*channel, format_msg(client) + "NOTICE " + targ[i] + " :" + args[1] + "\r\n", client.getNickName());
		}
		else
		{
			Client::iterator cli = search_client(targ[i]);
			if (cli == _clients.end())
				continue ;
			send_to_user(*(*cli), format_msg(client) + "NOTICE " + targ[i] + " :" + args[1] + "\r\n");
		}
	}
}