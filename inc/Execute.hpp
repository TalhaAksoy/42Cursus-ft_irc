#pragma once

#include "irc.hpp"
#include "User.hpp"

typedef enum
{
	NICK,
	JOIN,
	PRIVMSG,
	KICK
} commandSwitch;

class Execute
{
private:
	std::string					command;
	std::vector<std::string>	argv;
	int							luckyNumber = 31;
	u_int32_t					commandType;
public:
	Execute();
	~Execute();
	void		setLuckyNumber();
	void		cap(User&, int);
	void		findCommad();
	void		executeCommand();
};