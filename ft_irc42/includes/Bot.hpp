#include "irc.hpp"

class Bot: public Client
{
	public:
		Bot(void);
		~Bot(void);

		void weather(Server &serv, Channel const &chann);
	
	private:
		char _buff[BUFF_SIZE];
		addrinfo_t _hints, *_server_info;
		std::string _domain_name;
		std::string _chann_name;

		std::string _get_request(std::string endpoint) const ;
		std::map<std::string, std::string> _parse_json(std::string json_str) const ;
		int _get_current_hour(void) const ;
		void send_to_channel(Channel const &chann, std::map<std::string, std::string> const &mp) const ;
};