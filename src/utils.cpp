#include "irc.hpp"
#include "Server.hpp"

std::vector<std::string> splitString(std::string str, char delimiter)
{
	std::vector<std::string> substrings;
	std::string substring = "";
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] != delimiter)
		{
			substring += str[i];
		}
		else
		{
			substrings.push_back(substring);
			while (str[i] == delimiter)
				i++;
			i--;
			substring = "";
		}
	}
	substrings.push_back(substring);
	return substrings;
}

int executeCommand(std::vector<std::string> vector, std::string password, int userFd, Server server)
{

	int passFlag = 0;
	std::string errorMessage;
	if (!vector[0].compare(0, 4, "PASS") && vector.size() == 2)
	{
		if (vector[1] == password)
			passFlag = 1;
		else
		{
			errorMessage = "Error :Password Incorrect\r\n";
			send(userFd, errorMessage.c_str(), errorMessage.size(), 0);
			return (1);
		}
	}
	if (passFlag != 1)
		return (1);
	if (!vector[0].compare(0, 5, "NICK"))
	{
		std::cout << "NICK GELDI" << std::endl;
		if (vector.size() != 3)
		{
			errorMessage = "Error :Few or More Arguments Error\r\n";
			send(userFd, errorMessage.c_str(), errorMessage.size(), 0);
			return (1);
		}
		server.addUser(vector[1], userFd); //password muhabbetleri kalkicak
		server.writeUserList();
	}
	if (!vector[0].compare(0, 5, "JOIN"))
	{
		std::cout << "JOIN GELDI" << std::endl;
		server.createChannel(vector[1], userFd, password, "");
	}
	return (0);
}