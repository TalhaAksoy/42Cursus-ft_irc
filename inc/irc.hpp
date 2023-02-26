#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> splitString(std::string str, char delimiter);
