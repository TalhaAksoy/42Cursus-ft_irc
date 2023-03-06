#pragma once
#include "irc.hpp"

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
	void				addUser(int);
	void				removeUser(int);
};