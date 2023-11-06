#pragma once

class Client;
class Channel;

class Server
{
	public:
		Bot *bot;
		socklen_t addrlen;
		sockaddr_in_t client_addr;

		Server(int port, std::string passwd);
		~Server(void);

		const pollfd_t &getPoll(void) const;
		const sockaddr_in_t &getAddr(void) const;
		const std::string &getPasswd(void) const;
		const std::vector<Client*> &getClients(void) const;
		const std::vector<Channel> &getChannels(void) const;

		void run(void);

		void who(Client &client, std::vector<std::string> const &args);
		void pass(Client &client, std::vector<std::string> const &args);
		void nick(Client &client, std::vector<std::string> const &args);
		void user(Client &client, std::vector<std::string> const &args);
		void quit(Client &client, std::vector<std::string> const &args);
		void join(Client &client, std::vector<std::string> const &args);
		void part(Client &client, std::vector<std::string> const &args);
		void kick(Client &client, std::vector<std::string> const &args);
		void oper(Client &client, std::vector<std::string> const &args);
		void mode(Client &client, std::vector<std::string> const &args);
		void ping(Client &client, std::vector<std::string> const &args);
		void list(Client &client, std::vector<std::string> const &args);
		void names(Client &client, std::vector<std::string> const &args);
		void whois(Client &client, std::vector<std::string> const &args);
		void topic(Client &client, std::vector<std::string> const &args);
		void notice(Client &client, std::vector<std::string> const &args);
		void invite(Client &client, std::vector<std::string> const &args);
		void privmsg(Client &client, std::vector<std::string> const &args);

		void create_channel(Client &client, std::string const &name);
		void sendToChannels(Client const &client, std::string const &msg);

		Client::iterator search_client(std::string const &name);
		Channel::iter_channel search_channel(std::string const &name);

		std::vector<Channel> getChannels(Client const &client);

		friend void Bot::weather(Server &serv, Channel const &chan);

	private:
		int _bytes;
		char _buff[BUFF_SIZE + 1];
		pollfd_t _poll;
		std::string _passwd;
		std::string _opername;
		std::string _operpasswd;
		sockaddr_in_t _addr;
		std::vector<Client*> _clients;
		std::vector<Channel> _channels;
		std::vector<pollfd_t> _pollfds;

		void _exec_cmd(Client &client, std::string str);
		void _get_commands(std::vector<std::string> &cmds);
		void _get_commands_ptr(void (Server::*cmds_ptr[])(Client &, std::vector<std::string> const &));

		void _who_user(Client const &client, Client const &target, bool in, bool c);
};