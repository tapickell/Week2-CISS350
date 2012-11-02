/* ***************************************************************************

Programmer: Todd Pickell

Filename: Client.h

Requirements: None

Includes: 

Course: CISS-350A

Date: 11-1-12

Assignment: Week 2

Description: header for Client ADT.

************************************************************************* */
#pragma once

const int MAX_ITEMS = 5;
enum RelationType  {LESS, GREATER, EQUAL};

class Client
{
public:
	/* constructors */
	Client(void);
	Client(int);
	Client(std::string nameIn);
	Client(char, std::string, std::string, int, std::string);
	Client(char, std::string, std::string, int, std::string, std::string);
	/* destructor */
	~Client(void);

	/* getters */
	char getSex();
	std::string getName();
	std::string getPhone();
	int getNumInterest();
	std::vector<std::string>  getListInterest();
	std::string getMatch();

	/* setters */
	void setSex(char);
	void setName(std::string);
	void setPhone(std::string);
	void setNumInterest(int);
	void setListInterest(std::string);
	void setMatch(std::string);

	/* instance methods */
	bool matched();
	RelationType ComparedTo(Client) const;
	std::vector<std::string> split_by_token(std::string, std::string);


private:
	char sex;
	std::string name;
	std::string phone;
	int numInterest;
	std::string listInterest;
	std::string match;

};

