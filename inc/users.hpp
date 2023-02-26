#pragma once

#include "irc.hpp"

class User
{
private:
	std::string name;
	std::string iw;
	std::string fullName;
	std::string nick;
public:
	void setName(std::string);
	void setIw(std::string);
	void setFullName(std::string);
	void setNick(std::string);
	std::string getName();
	std::string getIw();
	std::string getFullName();
	std::string getNick();
};
