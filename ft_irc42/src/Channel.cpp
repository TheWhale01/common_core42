#include "irc.hpp"

Channel::Channel(void) {}
Channel::Channel(std::string const &channel) : _mode(0), _channelname(channel) {}
Channel::~Channel(void) {}

const int &Channel::getChannelModes(void) const {return (_mode);}
const std::string &Channel::getChannelTopic(void) const {return (_topic);}
const std::string &Channel::getChannelName(void) const {return (_channelname);}
const std::vector<Client*> &Channel::getChannelInviteList(void) const {return (_invitelist);}
const std::vector<std::pair<Client*, int> > &Channel::getChannelMembers(void) const {return (_channelmembers);}

void Channel::setChannelTopic(std::string const &topic) {_topic = topic;}
void Channel::addUserToInviteList(Client &client) {_invitelist.push_back(&client);}
void Channel::addMemberToChannel(Client &client, int oper) {_channelmembers.push_back(std::make_pair(&client, oper));}

std::string const Channel::getChannelMode(void) const
{
	std::string modes;
	if (_mode & MODE_T)
		modes += "+t ";
	if (_mode & MODE_I)
		modes += "+i ";
	if (_mode & MODE_M)
		modes += "+m ";
	if (_mode & MODE_S)
		modes += "+s ";
	if (_mode & MODE_N)
		modes += "+n ";
	return (modes);
}

void Channel::setChannelMode(char const &mode)
{
	if (mode == 't')
		_mode |= MODE_T;
	else if (mode == 'i')
		_mode |= MODE_I;
	else if (mode == 'm')
		_mode |= MODE_M;
	else if (mode == 's')
		_mode |= MODE_S;
	else if (mode == 'n')
		_mode |= MODE_N;
}

void Channel::unsetChannelMode(char const &mode)
{
	if (mode == 't')
		_mode &= -(MODE_T) - 1;
	else if (mode == 'i')
		_mode &= -(MODE_I) - 1;
	else if (mode == 'm')
		_mode &= -(MODE_M) - 1;
	else if (mode == 's')
		_mode &= -(MODE_S) - 1;
	else if (mode == 'n')
		_mode &= -(MODE_N) - 1;
}

void Channel::deleteUserfromInviteList(Client::iterator it) {_invitelist.erase(it);}
void Channel::deleteChannelMember(Channel::iter_member it) {_channelmembers.erase(it);}