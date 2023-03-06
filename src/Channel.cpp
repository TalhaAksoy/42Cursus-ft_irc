#include "Channel.hpp"

void Channel::addUser(int userFd)
{
	this->userFdNumber.push_back(userFd);
}

void Channel::setName(std::string name)
{
	this->name = name;
}

void Channel::setPassword(std::string password)
{
	this->password = password;
}

void Channel::setTopic(std::string topic)
{
	this->topic = topic;
}

std::string Channel::getName()
{
	return (this->name);
}

std::string Channel::getPassword()
{
	return (this->password);
}

std::string Channel::getTopic()
{
	return (this->topic);
}

void Channel::removeUser(int userFd)
{
	for (int index = 0; index < this->userFdNumber.size(); index++)
	{
		if (this->userFdNumber[index] == userFd)
		{
			this->userFdNumber.erase(this->userFdNumber.begin() + index);
			return;
		}
	}
	std::string errorMessage = "ERROR :This Ip address already registered this irc server\r\n";
	send(userFd, errorMessage.c_str(), errorMessage.size(), 0);
}