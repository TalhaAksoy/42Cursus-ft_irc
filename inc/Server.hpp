#pragma once

#include "irc.hpp"
#include "User.hpp"

class Server
{
private:
	uint32_t	serverFD;
	std::vector<User*> userList;

public:
	void setServerFD(uint32_t);
	void setUserList(std::vector<User*>);
	uint32_t getServerFD();
	std::vector<User*> getUserList();
	Server(/* args */);
	~Server();
};
