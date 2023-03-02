#include "Execute.hpp"

Execute::Execute()
{
	return ;
}

Execute::~Execute()
{
	return ;
}

void Execute::cap(User &user, int fd)
{
	if (luckyNumber == 31)
	{
		if (user.getGetCap() == false)
		{
			std::cout << "{False}" << std::endl;
			std::string message = "CAP * LS :multi-prefix sasl\r\n";
			send(fd, message.c_str(), sizeof(message), 0);
			user.setGetCap(true);
		}
		else
		{
			std::cout << "{True}" << std::endl;
			std::string message = "CAP * ACK multi-prefix\r\n";
			send(fd, message.c_str(), sizeof(message), 0);
			user.setGetCap(false);
		}
	}
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

void		Execute::executeCommand()
{
	switch (commandType)
	{
	case NICK:
		break;
	case JOIN:
		break;
	case PRIVMSG:
		break;
	case KICK:
		break;
	default:
		break;
	}
}