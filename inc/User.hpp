#ifndef USER_HPP
# define USER_HPP

# ifndef IRC_HPP
#  include "irc.hpp"
# endif
//#include "Execute.hpp"
//#include "Server.hpp"

class User
{
private:
	std::string	name;
	std::string	iw;
	std::string	fullName;
	std::string	nick;
	int32_t		fd;
	bool		passRequire;
	bool		getCap;
public:
	User();
	void setName(std::string);
	void setIw(std::string);
	void setFullName(std::string);
	void setNick(std::string);
	std::string getName();
	std::string getIw();
	std::string getFullName();
	std::string getNick();
	bool getGetCap();
	void setGetCap(bool);
	void setFd(int32_t);
	bool getPassRequire();
	void setPassRequire(bool);
	int32_t getFd();
};

#endif