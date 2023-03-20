#ifndef IRC_HPP
# define IRC_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <iostream>
#include <string>
#include <vector>
# include "Server.hpp"

class Server;

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024



std::vector<std::string> splitString(std::string str, char delimiter);
int executeCommand(std::vector<std::string> vector, std::string password, int userFd, Server& server);
#endif