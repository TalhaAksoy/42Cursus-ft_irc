#include "Server.hpp"

Server::Server()
{
	std::cout << "Server Created" << std::endl;
}

Server::~Server()
{
	std::cout << "Server Closed" << std::endl;
}
void	Server::setServerFD(uint32_t fd)
{
	this->serverFD = fd;
}

void	Server::setUserList(std::vector<User> userList)
{
	this->userList = userList;
}

uint32_t Server::getServerFD()
{
	return (this->serverFD);
}

std::vector<User> Server::getUserList(){
	return (this->userList);
}

void Server::addUser(std::string name, int userFd)
{
	for (int i = 0; i < this->userList.size(); i++)
	{
		if (this->userList[i].getFd() == userFd)
		{
			std::cout << "buradan bir kod geldi gecti i, userfd=" << i <<", "<< userFd << std::endl; 
			std::string nickErrorMessage = "ERROR :This Ip address already registered this irc server\r\n";
			send(userFd, nickErrorMessage.c_str(), nickErrorMessage.size(), 0);
			return;
		}
	}
	this->userList.push_back(this->serverExec.addUser(name, userFd));
	std::string nickMessage = "001 " + name + " :Welcome to Internet Relay Chat \r\n";
	send(userFd, nickMessage.c_str(), nickMessage.size(), 0);
}

void Server::writeUserList()
{
	for (uint_fast64_t i = 0; i < this->userList.size(); i++)
		std::cout << i << ".user Name => " << this->userList[i].getName() << " | fd => " << this->userList[i].getFd() << std::endl;
		std::cout << "--------------------------" << std::endl;
}
void Server::createChannel(std::string channelName, int userFd, std::string password, std::string topic)
{
	Channel channel = this->serverExec.createChannel(channelName, userFd, password, topic);
	this->channelList.push_back(channel);
}

void Server::joinChannel(std::string channelName, int userFd, std::string password)
{
	for (int i = 0; i < this->channelList.size(); i++)
	{
		if (this->channelList[i].getName() == channelName)
		{
			if (this->channelList[i].getPassword() == password)
			{
				this->channelList[i].addUser(userFd);
				std::string joinMessage = "JOIN " + channelName + "\r\n";
				send(userFd, joinMessage.c_str(), joinMessage.size(), 0);
				return;
			}
			else
			{
				std::string joinErrorMessage = "ERROR :Wrong password\r\n";
				send(userFd, joinErrorMessage.c_str(), joinErrorMessage.size(), 0);
				return;
			}
		}
	}
	std::string joinErrorMessage = "ERROR :Channel not found\r\n";
	send(userFd, joinErrorMessage.c_str(), joinErrorMessage.size(), 0);
}
void Server::writeChannelList()
{
	for (uint_fast64_t i = 0; i < this->channelList.size(); i++)
		std::cout << i << ".channel Name => " << this->channelList[i].getName() << " | fd => " << std::endl; //channel fd gelicek
		std::cout << "--------------------------" << std::endl;
}

void Server::leaveChannel(std::string channelName, int userFd)
{
	for (int i = 0; i < this->channelList.size(); i++)
	{
		if (this->channelList[i].getName() == channelName)
		{
			this->channelList[i].removeUser(userFd);
			std::string leaveMessage = "PART " + channelName + "\r\n";
			send(userFd, leaveMessage.c_str(), leaveMessage.size(), 0);
			return;
		}
	}
	std::string leaveErrorMessage = "ERROR :Channel not found\r\n";
	send(userFd, leaveErrorMessage.c_str(), leaveErrorMessage.size(), 0);
}