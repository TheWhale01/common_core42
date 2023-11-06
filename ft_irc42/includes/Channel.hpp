#pragma once

class Client;

class Channel
{
	public:

		Channel();
		Channel(std::string const &channel);
		~Channel();

		typedef std::vector<Channel>::iterator iter_channel;
		typedef std::vector<std::pair<Client*, int> >::iterator iter_member;

		const int &getChannelModes(void) const;
		const std::string getChannelMode(void) const;
		const std::string &getChannelName(void) const;
		const std::string &getChannelTopic(void) const;
		const std::vector<Client*> &getChannelInviteList(void) const;
		const std::vector<std::pair<Client*, int> > &getChannelMembers(void) const;

		void setChannelMode(char const &mode);
		void setChannelTopic(std::string const &topic);

		void unsetChannelMode(char const &mode);
		void addUserToInviteList(Client &client);
		void deleteChannelMember(iter_member it);
		void addMemberToChannel(Client &client, int modes);
		void deleteUserfromInviteList(Client::iterator it);

		Client::iterator search_invite(std::string const &name);
		Channel::iter_member search_user_in_channel(std::string const &name);

	private:
		int										_mode;
		std::string								_topic;
		std::vector<Client*>					_invitelist;
		std::string								_channelname;
		std::vector<std::pair<Client*, int> >	_channelmembers;
};