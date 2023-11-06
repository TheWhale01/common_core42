#include "irc.hpp"

void Server::quit(Client &client, std::vector<std::string> const &args)
{
	size_t i = 0;
	while (i <this->_pollfds.size() && this->_pollfds[i].fd != client.getPoll().fd)
		i++;
	std::cout << "(info) >> Client " << this->_pollfds[i].fd << " disconnected." << std::endl;
	Channel::iter_member del_member;
	for (size_t j = 0; j < _channels.size(); j++)
	{
		if ((del_member = _channels[j].search_user_in_channel(client.getNickName())) != _channels[j].getChannelMembers().end())
		{
			std::string quit_msg;
			if (args.size() == 0)
				quit_msg = format_msg(client) + "QUIT :disconnected\r\n";
			else
				quit_msg = format_msg(client) + "QUIT :" + args[0] + "\r\n";
			send_to_members_in_chan(_channels[j], quit_msg.c_str(), "");
			_channels[j].deleteChannelMember(del_member);
			if (_channels[j].getChannelMembers().size() == 0)
				_channels.erase(_channels.begin() + j);
		}
	}
	close(this->_pollfds[i].fd);
	this->_pollfds.erase(this->_pollfds.begin() + i);
	this->_clients.erase(this->_clients.begin() + (i - 1));
	delete &client;
}