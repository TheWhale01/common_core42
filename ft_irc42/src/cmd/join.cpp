#include "irc.hpp"

void Server::create_channel(Client &client, std::string const &name)
{
	Channel	new_channel(name);
	if (client.getMode() & MODE_R)
		new_channel.addMemberToChannel(client, false);
	else
		new_channel.addMemberToChannel(client, true);
	_channels.push_back(new_channel);
	std::string answer = format_msg(client) + "JOIN " + name + "\r\n";
	answer += print_all_user(client, new_channel, 1);
	send(client.getPoll().fd, answer.c_str(), answer.length(), 0);
}

void check_channel_syntax(Client const &client, std::string const &channel)
{
	std::string const &charset = " ,\a";
	if (channel.size() > 200)
		throw (NoSuchChannelException(client.getServerName(), client.getNickName(), channel));
	if (channel[0] != '&' && channel[0] != '#')
		throw (NoSuchChannelException(client.getServerName(), client.getNickName(), channel));
	for (size_t i = 0; i < channel.length(); i++)
		if (charset.find(channel[i]) != std::string::npos)
			throw (NoSuchChannelException(client.getServerName(), client.getNickName(), channel));
}

bool check_already_in_chan(std::string const &nickname, Channel const &channel)
{
	for (size_t i = 0; i < channel.getChannelMembers().size(); i++)
		if (channel.getChannelMembers()[i].first->getNickName() == nickname)
			return (1);
	return (0); 
}

void join_channel(Client &client, Channel &channel)
{
	Client::iterator it_inv = channel.search_invite(client.getNickName());
	if (channel.getChannelModes() & MODE_I)
	{
			if (it_inv == channel.getChannelInviteList().end())
				throw (InviteOnlyChanException(client.getServerName(), client.getNickName(), channel.getChannelName()));
	}
	if (it_inv != channel.getChannelInviteList().end())
		channel.deleteUserfromInviteList(it_inv);
	std::string answer;
	answer = "";
	if (!check_already_in_chan(client.getNickName(), channel))
	{
		channel.addMemberToChannel(client, false);
		answer = format_msg(client) + "JOIN " + channel.getChannelName() + "\r\n";
		send_to_members_in_chan(channel, answer, client.getNickName());
	}
	if (!channel.getChannelTopic().empty())
		answer += format_reply(client, RPL_TOPIC, channel.getChannelName()) + channel.getChannelTopic() + "\r\n";
	answer += print_all_user(client, channel, 1);
	send(client.getPoll().fd, answer.c_str(), answer.length(), 0);
}

void Server::join(Client &client, std::vector<std::string> const &args)
{
	if (args.size() < 1)
		throw (NeedMoreParamsException(client.getServerName(), client.getNickName(), "JOIN"));
	std::vector<std::string> targ = split(args[0], ",");
	size_t i;
	for (size_t j = 0; j < targ.size(); j++)
	{
		try
		{
			check_channel_syntax(client, targ[j]);
			for (i = 0; i < this->getChannels().size(); i++)
			{
				if (this->getChannels()[i].getChannelName() == targ[j])
				{
					join_channel(client, this->_channels[i]);
					break ;
				}
			}
			if (i == this->getChannels().size())
				create_channel(client, targ[j]);
		}
		catch (std::exception const &e)
		{
			std::string error_msg(e.what());
			send_to_user(client, error_msg);
		}
	}
}