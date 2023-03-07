#ifndef SERVER_HPP
# define SERVER_HPP

# ifndef IRC_HPP
#  include "irc.hpp"
# endif
# ifndef EXECUTE_HPP
#  include "Execute.hpp"
# endif
class Server
{
private:
	uint32_t				serverFD;
	std::vector<User>		userList;
	std::vector<Channel>	channelList;

public:
	uint32_t			getServerFD();
	std::vector<User>	getUserList();
	Execute				serverExec;

	void				setServerFD(uint32_t);
	void				setUserList(std::vector<User>);
	void				addUser(std::string name, int userFd);
	void				writeUserList();
	void				createChannel(std::string channelName, int userFd, std::string password, std::string topic); // Mode Eklenicek
	void				joinChannel(std::string channelName, int userFd, std::string password);
	void				leaveChannel(std::string channelName, int userFd);
	void				writeChannelList();
	Server(/* args */);
	~Server();
};
#endif
