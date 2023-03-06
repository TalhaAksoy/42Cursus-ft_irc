#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <iostream>
#include <string>
#include <vector>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

std::vector<std::string> splitString(std::string str, char delimiter);
