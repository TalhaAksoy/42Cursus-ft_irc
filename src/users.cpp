#include "users.hpp"

void User::setName(std::string name){
	this->name = name;
}

void User::setFullName(std::string fullName){
	this->fullName = fullName;
}

void User::setIw(std::string iw){
	this->iw = iw;
}

void User::setNick(std::string nick){
	this->nick = nick;
}

std::string User::getFullName()
{
	return(this->fullName);
}

std::string User::getName(){
	return(this->name);
}

std::string User::getIw(){
	return(this->iw);
}

std::string User::getNick(){
	return (this->nick);
}
