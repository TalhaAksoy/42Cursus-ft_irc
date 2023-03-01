#pragma once



#include "irc.hpp"
#include "Users.hpp"

class Server
{
private:
	uint32_t	serverFD;
	//User		*userList;
	
public:
	Server(/* args */);
	~Server();
};
