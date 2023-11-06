#include "irc.hpp"

AIrcStandardException::~AIrcStandardException(void) throw() {}

const char *ServerException::what(void) const throw() {return (strerror(errno));}
const char *KillServerException::what(void) const throw() {return ("(info) >> Stopping server.");}
const char *ClientCouldNotConnectException::what(void) const throw() {return ("ERROR :Client could not connect.\r\n");}