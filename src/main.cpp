#include "irc.hpp"

void print_err(std::string message)
{
	std::cerr << message << std::endl;
	exit(1);
}

int main(int ac, char *av[])
{
	if (ac != 3){
		std::cout << "Usage : ./irc <port> <password>" << std::endl;
		return (0);
	}
	int port = std::atoi(av[1]);
	const std::string password = (const std::string)av[2];
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (server_socket == -1)
		print_err("Error: Failed Create Server Socket");
	
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(port);
	/*Create connection with internet*/

	if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
		print_err("Error: Failed to Bind Socket");
	/*Bind fonksiyonu ile sockete address atamasi yapilir*/

	if (listen(server_socket, 5) == -1)
		print_err("Error: Failed to Listen on Socket");
	/*listen ile socketin maks kac baglanti alabilecegi belirlenir ve veri almaya hazir oldugunu belirtiriz.*/

	std::cout << "Listenin port on => [" << port << "]" << std::endl;
	
	while (true)
	{
		struct sockaddr_in client_address;
		socklen_t client_addrlen = sizeof(client_address);
		int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_addrlen);
		if (client_socket == -1)
			print_err("Error: Failed to accept incoming connection");
		
		char client_address_str[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(client_address.sin_addr), client_address_str, INET6_ADDRSTRLEN);
		std::cout << "Connection From " << client_address_str << std::endl;

		while (true)
		{
			char buffer[1024];
			ssize_t bytes_recived = recv(client_socket, buffer, sizeof(buffer), 0);
			if (bytes_recived == -1)
			{
				std::cerr << "Error: Failed To Recive Data" << std::endl;
				break;
			}
			if (bytes_recived == 0)
			{
				std::cout << "Connection Closed By Client" << std::endl;
				break;
			}
			buffer[bytes_recived] = '\0';
			std::cout << buffer << std::endl;
		}
		close(client_socket);
	}
	close(server_socket);
}

// //https://irc.dalexhd.dev/