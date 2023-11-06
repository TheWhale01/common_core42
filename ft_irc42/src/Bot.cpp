#include "irc.hpp"

Bot::Bot(void)
{
	setClientMode('i');
	bzero(&_poll, sizeof(_poll));
	_username = "bot";
	_nickname = "bot";
	_realname = "Super Bot";
	_hostname = "127.0.0.1";
	_servername = "127.0.0.1";
	_regist = true;
	_domain_name = "api.open-meteo.com";
}

Bot::~Bot(void) {}

void Bot::weather(Server &serv, Channel const &chan)
{
	(void)serv;
	addrinfo_t *addr;
	std::stringstream response_sstream;
	std::string request;
	std::map<std::string, std::string> mp;

	_poll.fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_poll.fd == -1)
		throw (ServerException());
	_poll.events = POLLIN;
	_poll.revents = 0;
	bzero(&_hints, sizeof(_hints));	
	_hints.ai_family = AF_INET;
	_hints.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(_domain_name.c_str(), "80", &_hints, &_server_info))
		throw (ServerException());
	for (addr = _server_info; addr != NULL; addr = addr->ai_next)
		if (connect(_poll.fd, addr->ai_addr, addr->ai_addrlen) != -1)
			break ;
	if (!addr)
	{
		std::cout << "(error) >> Bot could not connect." << std::endl;
		close(_poll.fd);
		freeaddrinfo(_server_info);
		return ;
	}
	freeaddrinfo(_server_info);
	request = _get_request("/v1/forecast?latitude=48.85&longitude=2.35&current_weather=true&timezone=auto&hourly=cloudcover&forecast_days=1");
	send(_poll.fd, request.c_str(), request.length(), 0);
	size_t bytes = recv(_poll.fd, _buff, BUFF_SIZE, 0);
	_buff[bytes] = '\0';
	response_sstream << _buff;
	mp = _parse_json(response_sstream.str());
	close(_poll.fd);
	send_to_channel(chan, mp);
}

std::map<std::string, std::string> Bot::_parse_json(std::string json_str) const
{
	int start;
	int key_len = 0;
	std::string value;
	std::vector<std::string> keys;
	std::map<std::string, std::string> mp;

	keys.push_back("temperature");
	keys.push_back("is_day");
	keys.push_back("cloudcover");

	for (std::vector<std::string>::iterator key = keys.begin();
		key != keys.end(); key++)
	{
		if (key + 1 == keys.end())
		{
			start = json_str.rfind(*key) + key->length() + 3;
			for (int i = 0; i < _get_current_hour(); i++)
				start = json_str.find(',', start) + 1;
		}
		else
			start = json_str.find(*key) + key->length() + 2;
		key_len = json_str.find(',', start) - start;
		value = json_str.substr(start, key_len);
		mp.insert(std::make_pair(*key, value));
	}
	mp["temperature"] += "°C";
	mp["is_day"] = (mp["is_day"] == "1" ? "Day" : "Night");
	if (atoi(mp["cloudcover"].c_str()) <= 25)
		mp["cloudcover"] = "Sunny";
	else if (atoi(mp["cloudcover"].c_str()) > 25 && atoi(mp["cloudcover"].c_str()) <= 50)
		mp["cloudcover"] = "Partly Cloudy";
	else if (atoi(mp["cloudcover"].c_str()) > 50 && atoi(mp["cloudcover"].c_str()) <= 85)
		mp["cloudcover"] = "Mostly Cloudy";
	else
		mp["cloudcover"] = "Overcast";
	return (mp);
}

void Bot::send_to_channel(Channel const &chann, std::map<std::string, std::string> const &mp) const
{
	std::string msg;
	std::map<std::string, std::string>::const_iterator it;

	msg = format_msg(*this) + "PRIVMSG " + chann.getChannelName() + " :";
	for (it = mp.begin(); it != mp.end(); it++)
		msg += (it->first + " " + it->second + " ");
	msg += "\r\n";
	send_to_members_in_chan(chann, msg, _nickname);
}

std::string Bot::_get_request(std::string endpoint) const
{
	std::string request;

	request =
        "GET " + endpoint + " HTTP/1.1\r\n"
		"Host: " + _domain_name + "\r\n"
		"Connection: close\r\n"
		"\r\n";
	return (request);
}

int Bot::_get_current_hour(void) const
{
	std::time_t now = std::time(NULL);
	std::tm *tm_ptr = std::localtime(&now);
	return (tm_ptr->tm_hour);
}