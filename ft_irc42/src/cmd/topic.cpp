#include "irc.hpp"

void Server::topic(Client &client, std::vector<std::string> const &args)
{
	if (args.size() == 0)
		throw (NeedMoreParamsException(client.getServerName(), client.getNickName(), "TOPIC"));
	Channel::iter_channel channel = search_channel(args[0]);
	if (channel == _channels.end())
		throw (NoSuchChannelException(client.getServerName(), client.getNickName(), args[0]));
	Channel::iter_member member = channel->search_user_in_channel(client.getNickName());
	if (member == channel->getChannelMembers().end())
		throw (NotOnChannelException(client.getServerName(), client.getNickName(), args[0]));
	if (args.size() == 2)
	{
		if ((channel->getChannelModes() & MODE_T) != 0)
		{
			if (member->second == false)
				throw (ChanoPrivsNeededException(client.getServerName(), client.getNickName(), args[0]));
		}
		channel->setChannelTopic(args[1]);
		send_to_members_in_chan(*channel, format_reply(client, RPL_TOPIC, channel->getChannelName()) + channel->getChannelTopic() + "\r\n", std::string());
	}
	else
	{
		if (channel->getChannelTopic().empty())
			send_to_user(client, format_reply(client, RPL_NOTOPIC, channel->getChannelName()) + "No topic is set\r\n");
		else
			send_to_user(client, format_reply(client, RPL_TOPIC, channel->getChannelName()) + channel->getChannelTopic() + "\r\n");
	}
}