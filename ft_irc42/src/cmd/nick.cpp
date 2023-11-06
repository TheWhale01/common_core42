#include "irc.hpp"

static void check_nickname_syntax(Client const &client, std::string const &nickname)
{
	std::string charset;

	if (nickname.length() > 9)
		throw (ErroneusNickNameException(client.getServerName(), nickname));
	charset = "[]`^_{}|";
	for (char c = 'A'; c <= 'Z'; c++)
	{
		charset.push_back(c);
		charset.push_back(c + 32);
	}
	for (char c = '0'; c <= '9'; c++)
		charset.push_back(c);
	if ((nickname[0] < 'A' || nickname[0] > 'Z') && (nickname[0] < 'a' || nickname[0] > 'z'))
		throw (ErroneusNickNameException(client.getServerName(), nickname));
	for (size_t i = 0; i < nickname.length(); i++)
		if (charset.find(nickname[i]) == std::string::npos)
			throw (ErroneusNickNameException(client.getServerName(), nickname));
}

void Server::nick(Client &client, std::vector<std::string> const &args)
{
	std::string welcome;
	std::string old_nickname;
	if (!args.size())
		throw (NoNickNameGivenException(client.getServerName(), client.getNickName()));
	if (client.getMode() & MODE_R) {
		send_to_user(client, ":" + client.getServerName() + " 484 " + args[0] + " :Your connection is restricted! (+r)\r\n");
		return ;
	}
	for (size_t i = 0; i < this->getClients().size(); i++)
		if (this->getClients()[i]->getNickName() == args[0])
			throw (NickNameInUseException(client.getServerName(), client.getNickName(), args[0]));
	check_nickname_syntax(client, args[0]);
	old_nickname = client.getNickName();
	client.setNickName(args[0]);
	if (!client.getUserName().empty() && !client.getRegist())
	{
		welcome = format_reply(client, RPL_WELCOME, "") + "Welcome to the fucked up IRC server!\r\n";
		client.setRegist(true);
		send(client.getPoll().fd, welcome.c_str(), welcome.length(), 0);
	}
	else if (client.getRegist())
	{
		welcome = ":" + old_nickname + "!" + client.getUserName() + "@" + client.getServerName() + " NICK " + client.getNickName() + "\r\n";
		std::vector<Channel> user_channels = getChannels(client);
		for (Client::iterator it = _clients.begin(); it != _clients.end(); it++)
			send((*it)->getPoll().fd, welcome.c_str(), welcome.length(), 0);
	}
}