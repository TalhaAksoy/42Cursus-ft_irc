#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <iostream>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>

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
#endif