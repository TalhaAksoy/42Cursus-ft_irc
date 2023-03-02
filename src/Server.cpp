#include "Server.hpp"
Server::Server()
{
	std::cout << "Server Created Baby" << std::endl;
}

Server::~Server()
{
	std::cout << "Server Closed Baby" << std::endl;
}
void	Server::setServerFD(uint32_t fd)
{
	this->serverFD = fd;
}

void	Server::setUserList(std::vector<User*> userList)
{
	this->userList = userList;
}

uint32_t Server::getServerFD()
{
	return (this->serverFD);
}

std::vector<User*> Server::getUserList(){
	return (this->userList);
}