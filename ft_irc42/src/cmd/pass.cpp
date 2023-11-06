#include "irc.hpp"

void Server::pass(Client &client, std::vector<std::string> const &args)
{
	if (args.size() != 1)
		throw (NeedMoreParamsException(client.getServerName(), client.getNickName(), "PASS"));
	else if (client.getRegist())
		throw (AlreadyRegistredException(client.getServerName(), client.getNickName()));
	else if (this->getPasswd() != *args.begin()) {
		client._can_co = 0;
		send_to_user(client, ":localhost 464 * :Password incorrect\r\n");
	}
	else
		client._can_co = 1;
}