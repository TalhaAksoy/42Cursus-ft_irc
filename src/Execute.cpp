#include "Execute.hpp"

Execute::Execute()
{
	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		this->fd_array[i][0] = -1;
		this->fd_array[i][1] = CAP;
	}
	return ;
}

Execute::~Execute()
{
	return ;
}

void Execute::cap(User &user, int fd)
{
	static int32_t fd_counter = 0;
	int32_t i;
	for (i = 0; i < MAX_CLIENTS; i++)
	{
		if (this->fd_array[i][0] == fd && this->fd_array[i][1] == DONE)
			return ;
		if (this->fd_array[i][0] == fd)
			break ;
	}
	this->fd_array[fd_counter][0] = fd;
	if (user.getGetCap() == false && this->fd_array[fd_counter][1] == CAP)
	{
		std::cout << "{False}" << std::endl;
		std::string message = "CAP * LS :multi-prefix sasl\r\n";
		send(fd, message.c_str(), sizeof(message), 0);
		user.setGetCap(true);
		this->fd_array[fd_counter][1] = REQ;
	}
	else if (this->fd_array[i][1] == REQ)
	{
		std::cout << "{True}" << std::endl;
		std::string message = "CAP * ACK multi-prefix\r\n";
		send(fd, message.c_str(), sizeof(message), 0);
		user.setGetCap(false);
		this->fd_array[fd_counter][1] = DONE;
		fd_counter++;
	}
	// std::cout << "fd_array 0 0 => " << this->fd_array[0][0] << std::endl << "fd_array 0 1 => " << this->fd_array[0][1] << std::endl;
	// std::cout << "-----------------------" << std::endl;
	// std::cout << "fd_array 1 0 => " << this->fd_array[1][0] << std::endl << "fd_array 1 1 => " << this->fd_array[1][1] << std::endl;
}

void	Execute::setLuckyNumber()
{
	this->luckyNumber += this->luckyNumber;
}

void		Execute::findCommad()
{
	std::vector<std::string> commands;

	commands = {"NICK", "JOIN", "PRIVMSG", "KICK"};
	for	(int j = 0; j < commands.size(); j++)
		if (command.compare(commands[j]))
			commandType = j;

}

User Execute::addUser(std::string name, int userFd, std::string passInput, std::string password)
{
	User user;
	if (user.getPassRequire())
	{
		if (passInput == password)
			user.setPassRequire(false);
		else
		return user;
	}
	user.setName(name);
	user.setFd(userFd);
	return (user);
}

Channel Execute::createChannel(std::string channelName, int userFd, std::string password, std::string topic)
{
	Channel channel;
	channel.setName(channelName);
	channel.setPassword(password);
	channel.addUser(userFd);
	std::cout << "kod burada" << std::endl;
	channel.setTopic(topic);
	return (channel);
}