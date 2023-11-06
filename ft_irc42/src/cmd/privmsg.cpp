#include "irc.hpp"

void Server::privmsg(Client &client, std::vector<std::string> const &args)
{
	if (args.size() < 2 || args[1].empty())
		throw (NoRecipientException(client.getServerName(), client.getNickName()));
	std::vector<std::string> targ = split(args[0], ",");
	for (size_t i = 0; i < targ.size(); i++)
	{
		try
		{
			if (targ[i][0] == '#' || targ[i][0] == '&')
			{
				Channel::iter_channel channel = search_channel(targ[i]);
				if (channel == _channels.end())
					throw (CannotSendToChanException(client.getServerName(), client.getNickName(), targ[i]));
				Channel::iter_member member = channel->search_user_in_channel(client.getNickName());
				if (channel->getChannelModes() & MODE_N)
				{
					if (member == channel->getChannelMembers().end())
						throw (CannotSendToChanException(client.getServerName(), client.getNickName(), targ[i]));
				}
				if (channel->getChannelModes() & MODE_M) {
					if ((member == channel->getChannelMembers().end()) || (member->second == 0))
						throw (ChanoPrivsNeededException(client.getServerName(), client.getNickName(), targ[i]));
				}
				if (args[args.size() - 1] == "!weather" && channel->search_user_in_channel(bot->getNickName()) != channel->getChannelMembers().end())
					bot->weather(*this, *channel);
				else if (args[args.size() - 1] == "!bot" && channel->search_user_in_channel(bot->getNickName()) == channel->getChannelMembers().end())
				{
					std::vector<std::string> chan_name;
					chan_name.push_back(targ[i]);
					join(*bot, chan_name);
				}
				send_to_members_in_chan(*channel, format_msg(client) + "PRIVMSG " + targ[i] + " :" + args[1] + "\r\n", client.getNickName());
			}
			else
			{
				Client::iterator cli = search_client(targ[i]);
				if (cli == _clients.end())
					throw (NoSuchNickException(client.getServerName(), client.getNickName(), targ[i]));
				send_to_user(*(*cli), format_msg(client) + "PRIVMSG " + targ[i] + " :" + args[1] + "\r\n");
			}
		}
		catch (std::exception const &e) {
			std::string error_msg(e.what());
			send_to_user(client, error_msg);
		}
	}
}
