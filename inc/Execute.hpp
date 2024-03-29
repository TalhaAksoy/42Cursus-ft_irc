#pragma once

#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <string>

# define MAX_CLIENTS 10

typedef enum
{
	NICK,
	JOIN,
	PRIVMSG,
	KICK
} commandSwitch;

typedef enum
{
	CAP,
	REQ,
	DONE
}	statement;

class User;
class Channel;

class Execute
{
private:
	std::string					command;
	std::vector<std::string>	argv;
	int							luckyNumber;
	u_int32_t					commandType;
	int							fd_array[MAX_CLIENTS][2];
public:
	Execute();
	~Execute();

	void		setLuckyNumber();
	void		cap(User&, int);
	void		findCommad();
	User		addUser(std::string name, int userFd);
	Channel		createChannel(std::string channelName, int userFd, std::string password, std::string topic);
};

#include "User.hpp"
#include "Channel.hpp"