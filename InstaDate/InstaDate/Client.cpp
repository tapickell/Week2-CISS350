/* ***************************************************************************

Programmer: Todd Pickell

Filename: Client.cpp

Requirements: None

Includes: 
#include "stdafx.h"
#include "Client.h"
#include "Tokenizer.h"

Course: CISS-350A

Date: 11-1-12

Assignment: Week 2

Description: implementation of Client ADT.

************************************************************************* */
#include "stdafx.h"
#include "Client.h"


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
	std::string workingStr;
	//remove period at end of string
	workingStr.assign(listInterest, 0, listInterest.size() - 1);
	//split strings up by commas && push substrings to stack
	std::string theDelim = ",";
	return split_by_token(workingStr, theDelim);
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


/* instance methods */
bool Client::matched()
{
	return (match == " ") ? false : true;
}

RelationType Client::ComparedTo(Client otherClient) const 
{
	if (numInterest < otherClient.numInterest)
	{
		return LESS;
	} else if (numInterest > otherClient.numInterest)
	{
		return GREATER;
	} else { 
  		return EQUAL;
	}	
}

//pass in the string to split, the vector to store the substrings in and the token to split with
std::vector<std::string> Client::split_by_token(std::string myStr, std::string myDelim)
{
    std::vector<std::string> result;

	int i = 0;
	int j = 0;

    while ( i+myDelim.size() <= myStr.size() )
    {
        if ( myStr[i] == myDelim[0] && myStr.substr( i, myDelim.size() ) == myDelim )
        {
            result.push_back( myStr.substr( j, i - j ) );
            i = j = i + myDelim.size();
        }
        else
        {
            i++;
        }
    }

    result.push_back( myStr.substr( j, myStr.size()-j ) );

	return result;
}