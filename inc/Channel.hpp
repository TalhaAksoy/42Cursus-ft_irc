#ifndef CHANNEL_HPP
# define CHANNEL_HPP
# ifndef IRC_HPP
#  include "irc.hpp"
# endif
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