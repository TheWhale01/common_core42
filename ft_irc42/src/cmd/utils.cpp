#include "irc.hpp"

std::string print_all_user(Client const &client, Channel const &channel, bool is_in)
{
	std::string answer;
	if (channel.getChannelModes() & MODE_S)
		answer = ":" + client.getServerName() + " " + RPL_NAMREPLY + " " + client.getNickName() + " @ " + channel.getChannelName() + " :";
	else
		answer = ":" + client.getServerName() + " " + RPL_NAMREPLY + " " + client.getNickName() + " = " + channel.getChannelName() + " :";
	for (size_t i = 0; i < channel.getChannelMembers().size(); i++)
	{
		if (!is_in && (channel.getChannelMembers()[i].first->getMode() & MODE_I))
			continue ;
		if (channel.getChannelMembers()[i].second == 1)
			answer += "@" + channel.getChannelMembers()[i].first->getNickName();
		else
			answer += channel.getChannelMembers()[i].first->getNickName();
		if (i + 1 != channel.getChannelMembers().size())
			answer += " ";
	}
	answer += "\r\n" + format_reply(client, RPL_ENDOFNAMES, channel.getChannelName()) + "End of /NAMES list\r\n";
	return (answer);
}

std::string format_reply(Client const &client, std::string const &code, std::string const &name)
{
	if (name.empty())
		return (":" + client.getServerName() + " " + code + " " + client.getNickName() + " :");
	return (":" + client.getServerName() + " " + code + " " + client.getNickName() + " " + name + " :");
}

std::string format_msg(Client const &client)
{
	return (":" + client.getNickName() + "!" + client.getUserName() + "@" + client.getServerName() + " ");
}

void send_to_user(Client const &client, std::string const &message)
{
	std::cout << "message sent for user=  " << message << std::endl;
	send(client.getPoll().fd, message.c_str(), message.length(), 0);
}

void send_to_members_in_chan(Channel const &channel, std::string const &message, std::string const &sender)
{
	std::cout << "message sent for channel= " << message << std::endl;
	for (size_t i = 0; i < channel.getChannelMembers().size(); i++)
	{
		if (!sender.empty())
		{
			if (channel.getChannelMembers()[i].first->getNickName() != sender)
				send(channel.getChannelMembers()[i].first->getPoll().fd, message.c_str(), message.length(), 0);
		}
		else
			send(channel.getChannelMembers()[i].first->getPoll().fd, message.c_str(), message.length(), 0);
	}
}

Channel::iter_channel Server::search_channel(std::string const &name)
{
	Channel::iter_channel it = _channels.begin();
	for (; it != _channels.end(); it++)
		if (it->getChannelName() == name)
			return (it);
	return (it);
}

Client::iterator Server::search_client(std::string const &name)
{
	Client::iterator it = _clients.begin();
	for (; it != _clients.end(); it++)
		if ((*it)->getNickName() == name)
			return (it);
	return (it);
}

Channel::iter_member Channel::search_user_in_channel(std::string const &name)
{
	Channel::iter_member it = _channelmembers.begin();
	for (; it != _channelmembers.end(); it++)
		if (it->first->getNickName() == name)
			return (it);
	return (it);
}

Client::iterator Channel::search_invite(std::string const &name)
{
	Client::iterator it = _invitelist.begin();
	for (; it != _invitelist.end(); it++)
		if ((*it)->getNickName() == name)
			return (it);
	return (it);
}