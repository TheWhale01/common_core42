#include "irc.hpp"

void Server::list(Client &client, std::vector<std::string> const &args)
{
	std::string answer;
	Channel::iter_channel channel = _channels.begin();
	if (args.size() == 0)
	{
		for(; channel != _channels.end(); channel++)
		{
			if (channel->getChannelModes() & MODE_S)
			{
				Channel::iter_member member = channel->search_user_in_channel(client.getNickName());
				if (member == channel->getChannelMembers().end())
					continue ;
			}
			answer += format_reply(client, RPL_LIST, channel->getChannelName()) + "Topic :" + channel->getChannelTopic() + "\r\n";
		}
	}
	else
	{
		std::vector<std::string> targ = split(args[0], ",");
		for (size_t i = 0; i < targ.size(); i++)
		{
			channel = search_channel(targ[i]);
			if (channel == _channels.end())
				continue ;
			if (channel->getChannelModes() & MODE_S)
			{
				Channel::iter_member member = channel->search_user_in_channel(client.getNickName());
				if (member == channel->getChannelMembers().end())
					continue ;
			}
			answer += format_reply(client, RPL_LIST, channel->getChannelName()) + "Topic :" + channel->getChannelTopic() + "\r\n";
		}
	}
	send_to_user(client, answer + format_reply(client, RPL_LISTEND, "") + "End of /LIST\r\n");
}
