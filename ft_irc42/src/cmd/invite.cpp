#include "irc.hpp"

void Server::invite(Client &client, std::vector<std::string> const &args)
{
	if (args.size() < 2)
		throw (NeedMoreParamsException(client.getServerName(), client.getNickName(), "INVITE"));
	Channel::iter_member member;
	Channel::iter_channel channel = search_channel(args[0]);
	if (channel != _channels.end())
	{
		member = channel->search_user_in_channel(client.getNickName());
		if (member == channel->getChannelMembers().end())
			throw (NotOnChannelException(client.getServerName(), client.getNickName(), args[0]));
		if (channel->getChannelModes() & MODE_I) {
			if (member->second == 0)
				throw (ChanoPrivsNeededException(client.getServerName(), client.getNickName(), args[0]));
		}
		member = channel->search_user_in_channel(args[1]);
		if (member != channel->getChannelMembers().end())
			throw (UserOnChannelException(client.getServerName(), client.getNickName(), args[0], args[1])); 
	}
	Client::iterator target = search_client(args[1]);
	if (target == _clients.end())
		throw (NoSuchNickException(client.getServerName(), client.getNickName(), "INVITE"));
	if ((channel != _channels.end()) && (channel->search_invite(args[1]) == channel->getChannelInviteList().end()))
		channel->addUserToInviteList(*(*target));
	send_to_user(*(*target), format_msg(client) + "INVITE " + args[1] + " " + args[0] + "\r\n");
	send_to_user(client, ":" + client.getServerName() + " " + RPL_INVITING + " " + client.getNickName() + " " + args[1] + " :" + args[0] + "\r\n");
}