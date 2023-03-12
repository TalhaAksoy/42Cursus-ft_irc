#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <iostream>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include "Server.hpp"

class Channel
{
private:
	std::string			name;
	std::string			topic;
	std::string			password;
	std::vector<int>	userFdNumber;
public:
	void				setPassword(std::string);	
	void				setName(std::string);	
	void				setTopic(std::string);
	std::string			getPassword();	
	std::string			getName();	
	std::string			getTopic();	
	void				addUserToChannel(int);
	void				removeUser(int);
	void				showUser(Server &server);
};
#endif