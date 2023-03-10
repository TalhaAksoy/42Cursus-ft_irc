#ifndef SERVER_HPP
# define SERVER_HPP

#include "Execute.hpp"
#include <unistd.h>
#include <vector>
#include <iostream>
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
	void 				removeUser(int userFd);
	int					isExistChannel(std::string channelName);
	Server(/* args */);
	~Server();
};
#endif
