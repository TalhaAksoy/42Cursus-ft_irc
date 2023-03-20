#ifndef SERVER_HPP
# define SERVER_HPP

#include "Execute.hpp"
#include <unistd.h>
#include <vector>
#include <iostream>

class Channel;
class Execute;

class Server
{
private:
	uint32_t				sockFd;
	uint32_t				port;
	std::vector<User>		userList;

public:
	uint32_t				getServerFD();
	std::vector<User>		getUserList();
	Execute					serverExec;
	std::vector<Channel>	channelList;

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
	void				findUser(int userFd);
	Server(/* args */);
	Server(int sockFd, const int port, const std::string password);
	~Server();
};
#endif
