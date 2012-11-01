#include "stdafx.h"
#include "Client.h"
#include "Tokenizer.h"


Client::Client(void)
{
}

Client::Client(char charIN, std::string str1, std::string str2, int intIN, std::string str3)
{
	setSex(charIN);
	setName(str1);
	setPhone(str2);
	setNumInterest(intIN);
	setListInterest(str3);
	setMatch(" ");
}

Client::Client(char charIN, std::string str1, std::string str2, int intIN, std::string str3, std::string str4)
{
	setSex(charIN);
	setName(str1);
	setPhone(str2);
	setNumInterest(intIN);
	setListInterest(str3);
	setMatch(str4);
}

Client::~Client(void)
{
}

/* getters */
char Client::getSex()
{
	return sex;
}
std::string Client::getName()
{
	return name;
}
std::string Client::getPhone()
{
	return phone;
}
int Client::getNumInterest()
{
	return numInterest;
}
std::vector<std::string>  Client::getListInterest()
{
	std::vector<std::string> strStack;
	//remove period at end of string
	std::string workingStr;
	workingStr.assign(listInterest, 0, listInterest.size() - 1);
	//split strings up by commas 
	//push substrings to stack
	Tokenizer::splitIt(workingStr, strStack, ",");
	return strStack;
}
std::string Client::getMatch()
{
	return match;
}

/* setters */
void Client::setSex(char charIN)
{
	sex = charIN;
}
void Client::setName(std::string strIN)
{
	name = strIN;
}
void Client::setPhone(std::string strIN)
{
	phone = strIN;
}
void Client::setNumInterest(int intIN)
{
	numInterest = intIN;
}
void Client::setListInterest(std::string strIN)
{
	listInterest = strIN;
}
void Client::setMatch(std::string strIN)
{
	match = strIN;
}