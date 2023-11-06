#include "irc.hpp"

void Server::part(Client &client, std::vector<std::string> const &args)
{
	if (args.size() == 0)
		throw (NeedMoreParamsException(client.getServerName(), client.getNickName(), "PART"));
	std::vector<std::string> targ = split(args[0], ",");
	for (size_t i = 0; i < targ.size(); i++)
	{
		try
		{
			Channel::iter_channel channel = search_channel(targ[i]);
			if (channel == _channels.end())
				throw (NoSuchChannelException(client.getServerName(), client.getNickName(), targ[i]));
			Channel::iter_member member = channel->search_user_in_channel(client.getNickName());
			if (member == channel->getChannelMembers().end())
				throw (NotOnChannelException(client.getServerName(), client.getNickName(), targ[i]));
			if (args.size() >= 2)
				send_to_members_in_chan(*channel, format_msg(client) + "PART " + targ[i] + " :" + args[1] + "\r\n", std::string());
			else
				send_to_members_in_chan(*channel, format_msg(client) + "PART " + targ[i] + " :" + client.getNickName() + "\r\n", std::string());
			channel->deleteChannelMember(member);
			if (channel->getChannelMembers().size() == 0)
				_channels.erase(channel);
		}
		catch (std::exception const &e)
		{
			std::string error_msg(e.what());
			send_to_user(client, error_msg);
		}
	}
}