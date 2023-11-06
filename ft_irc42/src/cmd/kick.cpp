#include "irc.hpp"

void Server::kick(Client &client, std::vector<std::string> const &args)
{
	if (args.size() < 2)
		throw (NeedMoreParamsException(client.getServerName(), client.getNickName(), "KICK"));
	std::vector<std::string> targ = split(args[0], ",");
	for (size_t i = 0; i < targ.size(); i++)
	{
		try {
			Channel::iter_channel channel = search_channel(targ[i]);
			if (channel == _channels.end())
				throw (NoSuchChannelException(client.getServerName(), client.getNickName(), targ[i]));
			Channel::iter_member member = channel->search_user_in_channel(client.getNickName());
			if (member == channel->getChannelMembers().end())
				throw (NotOnChannelException(client.getServerName(), client.getNickName(), targ[i]));
			if (member->second == false)
				throw (ChanoPrivsNeededException(client.getServerName(), client.getNickName(), targ[i]));
			Channel::iter_member member2 = channel->search_user_in_channel(args[1]);
			if (member2 == channel->getChannelMembers().end())
				throw(UserNotInChannelException(client.getServerName(), client.getNickName(), targ[i], args[1]));
			if (args.size() >= 3)
				send_to_members_in_chan(*channel, format_msg(client) + "KICK " + targ[i] + " " + args[1] + " :" + args[2] + "\r\n", std::string());
			else
				send_to_members_in_chan(*channel, format_msg(client) + "KICK " + targ[i] + " " + args[1] + " :" + args[1] + "\r\n", std::string());
			channel->deleteChannelMember(member2);
			if (channel->getChannelMembers().size() == 0)
				_channels.erase(channel);
		}
		catch (std::exception const &e) {
			std::string error_msg(e.what());
			send_to_user(client, error_msg);
		}
	}
}