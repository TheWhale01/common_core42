#pragma once

class Server;

class Client
{
	public:
		Client(void);
		Client(Server &serv);
		virtual ~Client(void);

		typedef std::vector<Client*>::iterator iterator;

		int		_can_co;

		const int &getMode(void) const;
		const bool &getRegist(void) const;
		const pollfd_t &getPoll(void) const;
		const std::string &getRealName(void) const;
		const std::string &getNickName(void) const;
		const std::string &getUserName(void) const;
		const std::string &getHostName(void) const;
		const std::string &getServerName(void) const;
		const std::string getClientMode(void) const;

		void setRegist(bool val);
		void setClientMode(char const &mode);
		void unsetClientMode(char const &mode);
		void setUserName(std::string const &username);
		void setNickName(std::string const &nickname);
		void setRealName(std::string const &realname);
		void setHostName(std::string const &hostname);
		void setServerName(std::string const &servername);

	protected:
		int			_mode;
		pollfd_t 	_poll;
		std::string	_username;
		std::string	_nickname;
		std::string	_realname;
		std::string _hostname;
		std::string _servername;
		bool		_regist;
};