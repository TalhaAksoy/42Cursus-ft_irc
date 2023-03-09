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

int executeCommand(std::vector<std::string> vector, std::string password, int userFd, Server& server)
{

	static int passFlag[MAX_CLIENTS];
	std::string errorMessage;
	for (int i = 0; i < vector.size(); i++)
	{
		std::cout << "{" << vector[i] << "}" << std::endl;
	}
	if (!vector[0].compare(0, 4, "PASS") && vector.size() == 2)
	{
		std::cout << "My Password > " << vector[1] << "Server Password " << password << std::endl;
		if (!vector[1].compare(0, vector[1].length() - 2, password.c_str()))
		{
			passFlag[userFd - 4] = 1;
			errorMessage = "Server: Login Successfull\r\n";
			send(userFd, errorMessage.c_str(), errorMessage.size(), 0);
		}
		else
		{
			errorMessage = "Error :Password Incorrect\r\n";
			send(userFd, errorMessage.c_str(), errorMessage.size(), 0);
			return (1);
		}
	}
	if (passFlag[userFd - 4] != 1)
	{
		errorMessage = "Error :Please Login First\r\n";
		send(userFd, errorMessage.c_str(), errorMessage.size(), 0);
		return (1);
	}
	std::cout << vector[0] << " < vector[0]" << std::endl << vector[0].length() << " len[0]" << std::endl; 
	if (!vector[0].compare(0, 4, "NICK"))
	{
		std::cout << "NICK GELDI" << std::endl;
		if (vector.size() != 2)
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
	if (!vector[0].compare(0,4, "QUIT"))
	{
		std::cout << "QUIT GELDI" << std::endl;
		server.removeUser(userFd);
		passFlag[userFd - 4] = 0;	
	}
	return (0);
}