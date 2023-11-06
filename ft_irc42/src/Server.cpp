#include "irc.hpp"

Server::Server(int port, std::string passwd): _bytes(0), _passwd(passwd), _opername("admin"), _operpasswd("admin")
{
	int temp = 1;
	bzero(&addrlen, sizeof(addrlen));
	_addr.sin_family = AF_INET;
	_poll.fd = socket(_addr.sin_family, SOCK_STREAM, 0);
	if (_poll.fd == -1)
		throw (ServerException());
	if (setsockopt(_poll.fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &temp, sizeof(temp)) < 0)
		throw (ServerException());
	_poll.events = POLLIN;
	_poll.revents = 0;
	_addr.sin_addr.s_addr = INADDR_ANY;
	_addr.sin_port = htons(port);
	if (bind(_poll.fd, (struct sockaddr *)&_addr, sizeof(_addr)) == -1)
		throw (ServerException());
	if (listen(_poll.fd, SIM_USERS) == -1)
		throw (ServerException());
	_pollfds.reserve(11);
	_clients.reserve(10);
	_channels.reserve(5);
	_pollfds.push_back(_poll);
	bot = new Bot();
	_pollfds.push_back(bot->getPoll());
	_clients.push_back(bot);
	std::cout << "Server started on port: " << ntohs(_addr.sin_port) << std::endl;
}

Server::~Server(void)
{
	for (size_t i = 0; i < _pollfds.size(); i++)
		close(_pollfds[i].fd);
	for (size_t i = 0; i < _clients.size(); i++)
		delete _clients[i];
}

const pollfd_t &Server::getPoll(void) const {return (_poll);}
const sockaddr_in_t &Server::getAddr(void) const {return (_addr);}
const std::string &Server::getPasswd(void) const {return (_passwd);}
const std::vector<Client*> &Server::getClients(void) const {return (_clients);}
const std::vector<Channel> &Server::getChannels(void) const {return (_channels);}

void Server::run(void)
{
	std::string command;
	signal(SIGINT, sigHandler);
	while (true)
	{
		if (poll(_pollfds.data(), _pollfds.size(), TIMEOUT) < 0)
			throw (ServerException());
		for (size_t i = 0; i < _pollfds.size(); i++)
		{
			if (_pollfds[i].revents & POLLIN)
			{
				if (_pollfds[i].fd == _poll.fd)
				{
					try
					{
						Client *new_client = new Client(*this);
						_pollfds.push_back(new_client->getPoll());
						_clients.push_back(new_client);
					}
					catch (const std::exception& e) {std::cerr << e.what();}
				}
				else
				{
					_bytes = recv(_pollfds[i].fd, _buff, BUFF_SIZE, 0);
					if ((_bytes > 0) && _buff[_bytes - 1] != '\n' && _buff[_bytes - 2] != '\r')
						command += std::string(_buff, _bytes);
					else if (_bytes <= 0)
					{
						command.clear();
						this->quit(*(*(_clients.begin() + (i - 1))), std::vector<std::string>());
						i--;
					}
					else
					{
						command += std::string(_buff, _bytes);
						std::cout << "message received= " << command << std::endl;
						std::vector<std::string> user_inputs = split(command, "\r\n");
						command.clear();
						std::vector<std::string>::iterator it;
						for (it = user_inputs.begin(); it != user_inputs.end(); it++)
						{
							try {_exec_cmd(*(_clients)[i  - 1], *it);}
							catch (std::exception const &e)
							{
								std::string error_msg(e.what());
								std::cerr << error_msg;
								send(_clients[i - 1]->getPoll().fd, error_msg.c_str(), error_msg.length(), 0);
							}
						}
					}
				}
			}
		}
	}
}

// PRIVATE FUNCTION MEMBERS
void Server::_exec_cmd(Client &client, std::string str)
{
	std::string cmd;
	std::string cmd_not_found;
	std::vector<std::string> cmds;
	std::vector<std::string> args = split(str);

	if (!args.size())
		return ;
	_get_commands(cmds);
	void (Server::*cmds_ptr[cmds.size()])(Client &, std::vector<std::string> const &);
	_get_commands_ptr(cmds_ptr);
	for (size_t i = 0; i < cmds.size(); i++)
	{
		str_toupper(args[0]);
		cmd = args[0];
		if (args[0] == cmds[i])
		{
			args.erase(args.begin());
			if ((!client._can_co && i) || (!client.getRegist() && i > 2))
			{
				if (!i)
					return ;
				throw (NotRegisteredException(client.getServerName(), client.getNickName(), cmds[i]));
			}
			(this->*(cmds_ptr[i]))(client, args);
			return ;
		}
	}
	cmd_not_found = ":" + (client.getServerName().empty() ? "localhost" : client.getServerName()) + " "
		+ ERR_UNKNOWNCOMMAND + " " + (client.getNickName().empty() ? "*" : client.getNickName()) + " " + cmd
		+ " :Unknown command\r\n";
	std::cerr << cmd_not_found;
	send(client.getPoll().fd, cmd_not_found.c_str(), cmd_not_found.length(), 0);
}

void Server::sendToChannels(Client const &client, std::string const &msg)
{
	for (size_t j = 0; j < _channels.size(); j++)
		if (_channels[j].search_user_in_channel(client.getNickName()) != _channels[j].getChannelMembers().end())
			send_to_members_in_chan(_channels[j], msg.c_str(), "");
}

std::vector<Channel> Server::getChannels(Client const &client)
{
	std::vector<Channel> v;

	for (Channel::iter_channel it = _channels.begin(); it != _channels.end(); it++)
		if (it->search_user_in_channel(client.getNickName()) != it->getChannelMembers().end())
			v.push_back(*it);
	return (v);
}

void Server::_get_commands(std::vector<std::string> &cmds)
{
	cmds.reserve(18);
	cmds.push_back("PASS");
	cmds.push_back("NICK");
	cmds.push_back("USER");
	cmds.push_back("QUIT");
	cmds.push_back("JOIN");
	cmds.push_back("PRIVMSG");
	cmds.push_back("NOTICE");
	cmds.push_back("PART");
	cmds.push_back("TOPIC");
	cmds.push_back("KICK");
	cmds.push_back("MODE");
	cmds.push_back("PING");
	cmds.push_back("WHOIS");
	cmds.push_back("INVITE");
	cmds.push_back("WHO");
	cmds.push_back("NAMES");
	cmds.push_back("LIST");
	cmds.push_back("OPER");
}

void Server::_get_commands_ptr(void (Server::*cmds_ptr[])(Client &, std::vector<std::string> const &))
{
	cmds_ptr[0] = &Server::pass;
	cmds_ptr[1] = &Server::nick;
	cmds_ptr[2] = &Server::user;
	cmds_ptr[3] = &Server::quit;
	cmds_ptr[4] = &Server::join;
	cmds_ptr[5] = &Server::privmsg;
	cmds_ptr[6] = &Server::notice;
	cmds_ptr[7] = &Server::part;
	cmds_ptr[8] = &Server::topic;
	cmds_ptr[9] = &Server::kick;
	cmds_ptr[10] = &Server::mode;
	cmds_ptr[11] = &Server::ping;
	cmds_ptr[12] = &Server::whois;
	cmds_ptr[13] = &Server::invite;
	cmds_ptr[14] = &Server::who;
	cmds_ptr[15] = &Server::names;
	cmds_ptr[16] = &Server::list;
	cmds_ptr[17] = &Server::oper;
}
