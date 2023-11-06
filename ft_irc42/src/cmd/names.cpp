#include "irc.hpp"

void Server::names(Client &client, std::vector<std::string> const &args)
{
	bool in = 0;
	std::string answer;
	if (args.size() != 0)
	{
		std::vector<std::string> targ = split(args[0], ",");
		for (size_t i = 0; i < targ.size(); i++)
		{
			Channel::iter_channel channel = search_channel(targ[i]);
			if (channel == _channels.end()) {
				answer += format_reply(client, RPL_ENDOFNAMES, targ[i]) + "End of /NAMES list\r\n";
				continue ;
			}
			Channel::iter_member member = channel->search_user_in_channel(client.getNickName());
			if (member != channel->getChannelMembers().end())
				in = 1;
			if (channel->getChannelModes() & MODE_S) {
				if (!in) {
					answer += format_reply(client, RPL_ENDOFNAMES, channel->getChannelName()) + "End of /NAMES list\r\n";
					continue ;
				}
			}
			answer += print_all_user(client, *channel, in);
		}
		send_to_user(client, answer);
	}
}
