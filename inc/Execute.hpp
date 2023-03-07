#ifndef EXECUTE_HPP
# define EXECUTE_HPP
# ifndef IRC_HPP
#  include "irc.hpp"
# endif
# ifndef USER_HPP
#  include "User.hpp"
# endif
# ifndef CHANNEL_HPP
#  include "Channel.hpp"
# endif

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

class Execute
{
private:
	std::string					command;
	std::vector<std::string>	argv;
	int							luckyNumber = 31;
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

#endif