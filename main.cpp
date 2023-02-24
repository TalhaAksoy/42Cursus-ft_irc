#include "irc.hpp"

int main(int argc, char *argv[]) {
	std::string message;
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return 1;
    }

    int port = atoi(argv[1]);
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket == -1) {
        std::cerr << "Error: Failed to create socket." << std::endl;
        return 1;
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY; // Listen on all network interfaces
    server_address.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        std::cerr << "Error: Failed to bind socket." << std::endl;
        return 1;
    }

    if (listen(server_socket, 5) == -1) {
        std::cerr << "Error: Failed to listen on socket." << std::endl;
        return 1;
    }

    std::cout << "Listening on port " << port << std::endl;

    while (true) {
        struct sockaddr_in client_address;
        socklen_t client_addrlen = sizeof(client_address);
        int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_addrlen);

        if (client_socket == -1) {
            std::cerr << "Error: Failed to accept incoming connection." << std::endl;
            continue;
        }

        char client_address_str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(client_address.sin_addr), client_address_str, INET_ADDRSTRLEN);
        std::cout << "Connection from " << client_address_str << std::endl;

        while (true) {
            char buffer[1024];
            ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

            if (bytes_received == -1) {
                std::cerr << "Error: Failed to receive data." << std::endl;
                break;
            }

            if (bytes_received == 0) {
                std::cout << "Connection closed by client." << std::endl;
                break;
            }

            buffer[bytes_received] = '\0'; // Make sure the buffer is null-terminated
			std::getline(std::cin, message);
			std::cout << "Received " << message.size() << " bytes from client: " << message << std::endl;
			send(client_socket, message.c_str(), sizeof(message), 0);PONG 
			std::cout << "Received " << bytes_received << " bytes from client: " << buffer << std::endl;
        }

        close(client_socket);
    }

    close(server_socket);
}

// int main(int argc, char *argv[])
// {
// 	if (argc != 3)
// 		return (1);
// 	int	port = atoi(argv[1]);
// 	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
// 	if (server_socket == -1)
// 	{
// 		std::cout << "Socket Error" << std::endl;
// 		return 1;
// 	}

// 	struct sockaddr_in server_address;
// 	server_address.sin_family = AF_INET;
// 	server_address.sin_addr.s_addr = INADDR_ANY;
// 	server_address.sin_port = htons(port);

// 	if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
// 	{
// 		std::cout << "Bind Error" << std::endl;
// 		return 1;
// 	}

// 	if (listen(server_socket, 5) == -1)
// 	{
// 		std::cout << "Listen Error" << std::endl;
// 		return 1;
// 	}

// 	struct sockaddr_in client_address;
// 	socklen_t client_addrlen = sizeof(client_address);
// 	ssize_t bytes_received = 0;
// 	int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_addrlen);
// 	if (client_socket == -1) {
// 		std::cout << "client error" << std::endl;
// 		return 1;
// 	}
// 	std::cout << client_socket << " => client_socket" << std::endl;
// 	while(1){
// 		char buffer[1024];
// 		bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
// 		if (bytes_received == -1){
// 			std::cout << " recv error" << std::endl;
// 			return 1;
// 		}

// 		buffer[bytes_received] = '\0'; // make sure the buffer is null-terminated
// 		std::string sendd = ":127.0.0.1 001 saksoy :Welcome to Internet Relay Chat \r\n"; // num erik lere bak
// 		send(client_socket, sendd.c_str(), sizeof(sendd), 0);
// 		printf("Received %ld bytes: %s\n", bytes_received, buffer);
// 		std::vector<std::string> splittedString =  splitString(buffer, ' ');
// 		for (int i = 0 ; i < splittedString.size(); i++)
// 			std::cout << splittedString[i] << std::endl;
// 		//send(client_socket, "5", 3, 0);
// 	}
// 	// rest of your code
// 	return 0;
// }
