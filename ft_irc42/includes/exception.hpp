#pragma once

#include <errno.h>
#include <cstring>
#include <stdexcept>

class AIrcStandardException: public std::exception
{
	public:
		virtual const char *what(void) const throw() = 0;
		virtual ~AIrcStandardException(void) throw();

	protected:
		std::string _cmd;
		std::string _user;
		std::string _nickname;
		std::string _servername;
		std::string *_error_msg;
};

class NotRegisteredException: public AIrcStandardException
{
	public:
		explicit NotRegisteredException(std::string const &servername, std::string const &nickname, std::string const &cmd);
		~NotRegisteredException(void) throw();

		const char *what(void) const throw();
};

class NoTextToSendException: public AIrcStandardException
{
	public:
		explicit NoTextToSendException(std::string const &servername, std::string const &nickname);
		~NoTextToSendException(void) throw();

		const char *what(void) const throw();
};

class NoRecipientException: public AIrcStandardException
{
	public:
		explicit NoRecipientException(std::string const &servername, std::string const &nickname);
		~NoRecipientException(void) throw();

		const char *what(void) const throw();
};

class UserDontMatchException: public AIrcStandardException
{
	public:
		explicit UserDontMatchException(std::string const &servername, std::string const &nickname);
		~UserDontMatchException(void) throw();

		const char *what(void) const throw();
};

class UModeUnknowFlagsException: public AIrcStandardException
{
	public:
		explicit UModeUnknowFlagsException(std::string const &servername, std::string const &nickname);
		~UModeUnknowFlagsException(void) throw();

		const char *what(void) const throw();
};

class CannotSendToChanException: public AIrcStandardException
{
	public:
		explicit CannotSendToChanException(std::string const &servername, std::string const &nickname, std::string const &channel);
		~CannotSendToChanException(void) throw();

		const char *what(void) const throw();
};

class NoSuchNickException: public AIrcStandardException
{
	public:
		explicit NoSuchNickException(std::string const &servername, std::string const &nickname, std::string const &cmd);
		~NoSuchNickException(void) throw();

		const char *what(void) const throw();
};

class UnknownModeException: public AIrcStandardException
{
	public:
		explicit UnknownModeException(std::string const &servername, std::string const &nickname, std::string const &cmd);
		~UnknownModeException(void) throw();

		const char *what(void) const throw();
};

class NotOnChannelException: public AIrcStandardException
{
	public:
		explicit NotOnChannelException(std::string const &servername, std::string const &nickname, std::string const &cmd);
		~NotOnChannelException(void) throw();

		const char *what(void) const throw();
};

class UserNotInChannelException: public AIrcStandardException
{
	public:
		explicit UserNotInChannelException(std::string const &servername, std::string const &nickname, std::string const &cmd, std::string const &user);
		~UserNotInChannelException(void) throw();

		const char *what(void) const throw();
};

class UserOnChannelException: public AIrcStandardException
{
	public:
		explicit UserOnChannelException(std::string const &servername, std::string const &nickname, std::string const &cmd, std::string const &user);
		~UserOnChannelException(void) throw();

		const char *what(void) const throw();
};

class NoSuchChannelException: public AIrcStandardException
{
	public:
		explicit NoSuchChannelException(std::string const &servername, std::string const &nickname, std::string const &cmd);
		~NoSuchChannelException(void) throw();

		const char *what(void) const throw();
};

class AlreadyRegistredException: public AIrcStandardException
{
	public:
		explicit AlreadyRegistredException(std::string const &servername, std::string const &nickname);
		~AlreadyRegistredException(void) throw();

		const char *what(void) const throw();
};

class NickNameInUseException: public AIrcStandardException
{
	public:
		explicit NickNameInUseException(std::string const &servername, std::string const &nickname, std::string const &cmd);
		~NickNameInUseException(void) throw();

		const char *what(void) const throw();
};

class ErroneusNickNameException: public AIrcStandardException
{
	public:
		explicit ErroneusNickNameException(std::string const &servername, std::string const &nickname);
		~ErroneusNickNameException(void) throw();

		const char *what(void) const throw();
};

class UnknownCommandException: public AIrcStandardException
{
	public:
		explicit UnknownCommandException(std::string const &servername, std::string const &nickname, std::string const &cmd);
		~UnknownCommandException(void) throw();

		const char *what(void) const throw();
};

class NeedMoreParamsException: public AIrcStandardException
{
	public:
		explicit NeedMoreParamsException(std::string const &servername, std::string const &nickname, std::string const &cmd);
		~NeedMoreParamsException(void) throw();

		const char *what(void) const throw();
};

class InviteOnlyChanException: public AIrcStandardException
{
	public:
		explicit InviteOnlyChanException(std::string const &servername, std::string const &nickname, std::string const &cmd);
		~InviteOnlyChanException(void) throw();

		const char *what(void) const throw();
};

class NoNickNameGivenException: public AIrcStandardException
{
	public:
		explicit NoNickNameGivenException(std::string const &servername, std::string const &nickname);
		~NoNickNameGivenException(void) throw();

		const char *what(void) const throw();
};

class ChanoPrivsNeededException: public AIrcStandardException
{
	public:
		explicit ChanoPrivsNeededException(std::string const &servername, std::string const &nickname, std::string const &cmd);
		~ChanoPrivsNeededException(void) throw();

		const char *what(void) const throw();
};

class ClientCouldNotConnectException: public std::exception
{
	public:
		const char *what(void) const throw();
};

class ServerException: public std::exception
{
	public:
		const char *what(void) const throw();
};

class KillServerException: public std::exception
{
	public:
		const char *what(void) const throw();
};