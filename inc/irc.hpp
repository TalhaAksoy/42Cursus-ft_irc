#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <iostream>
#include <string>
#include <vector>
#include "Users.hpp"
#include "Server.hpp"

std::vector<std::string> splitString(std::string str, char delimiter);
