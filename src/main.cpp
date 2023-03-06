#include "irc.hpp"
#include "User.hpp"
#include "Server.hpp"
#include "Execute.hpp"
#include "Channel.hpp"

void print_err(std::string message)
{
	std::cerr << message << std::endl;
	exit(1);
}

int main(int ac, char *av[]) {
	if (ac != 3)
		print_err("Usage Error: ./irc <port> password");

	Server server;
	User defaultUser;
	
	int port = std::atoi(av[1]);
	const std::string password = av[2];

	struct sockaddr_in server_address, client_address;
	socklen_t client_len = sizeof(client_address);
	int server_socket, client_socket[MAX_CLIENTS], active_clients = 0;
	char buffer[BUFFER_SIZE];

	// Create server socket
	if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}

	server.setServerFD(server_socket);

	// Set server address
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(port);

	// Bind server socket
	if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
		perror("Bind failed");
		exit(EXIT_FAILURE);
	}

	std::cout << "Listenin Port on [" << port << "]" << std::endl;
	std::cout << "Server Password Is [" << password << "]" << std::endl;

	// Listen for incoming connections
	if (listen(server_socket, MAX_CLIENTS) < 0) {
		perror("Listen failed");
		exit(EXIT_FAILURE);
	}

	// Add server socket to polling structure
	struct pollfd poll_fds[MAX_CLIENTS + 1];
	poll_fds[0].fd = server_socket;
	poll_fds[0].events = POLLIN;

	// Main loop
	while (1) {
		// Poll for events
		int num_ready = poll(poll_fds, active_clients + 1, -1);

		// Check for errors
		if (num_ready < 0) {
			perror("Poll failed");
			exit(EXIT_FAILURE);
		}

		// Check for server socket events
		if (poll_fds[0].revents & POLLIN) {
			// Accept incoming connection
			if ((client_socket[active_clients] = accept(server_socket, (struct sockaddr *)&client_address, &client_len)) < 0) {
				perror("Accept failed");
				exit(EXIT_FAILURE);
			}

			// Add new client to polling structure
			poll_fds[active_clients + 1].fd = client_socket[active_clients];
			poll_fds[active_clients + 1].events = POLLIN;
			active_clients++;
		}

		// Check for client socket events
		for (int i = 0; i < active_clients; i++) {
			if (poll_fds[i + 1].revents & POLLIN) {
				// Read incoming data
				ssize_t bytes_recived = recv(client_socket[i], buffer, sizeof(buffer), 0);
				std::cout << "Client Number => " << client_socket[i] << std::endl;
				// if (i == 1)	
				// {
				// 	std::string asd;
				// 	asd = "001 CheaterAK :Welcome to Internet Relay Chat \r\n";
				// 	send(client_socket[i], asd.c_str(), sizeof(asd), 0);
				// }
				server.serverExec.cap(defaultUser, client_socket[i]);
				if (bytes_recived == -1)
					print_err("Error: Failed To Recive Data");
				if (bytes_recived == 0)
					print_err("Connection Closed By Client");
				buffer[bytes_recived] = '\0';

				//std::cout << "[" << buffer << "]" << std::endl;
				std::vector<std::string> str = splitString(buffer, ' ');
				for (size_t j = 0; j < str.size() ; j++)
				{
					std::cout << "{" + str[j] + "}" << std::endl;
					if (!str[j].compare(0,5,"NICK"))
					{
						std::cout << "NICK GELDI" << std::endl;
						server.addUser(str[j + 1], client_socket[i]);
						server.writeUserList();
					}
					if (!str[j].compare(0, 5, "JOIN"))
					{
						std::cout << "JOIN GELDI" << std::endl;
						server.createChannel(str[j + 1], client_socket[i],password, NULL);
						
					}
				}
			}
		}
	}
	close(server_socket);
	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		close(client_socket[i]);
	}
	return 0;
}

// //https://irc.dalexhd.dev/
