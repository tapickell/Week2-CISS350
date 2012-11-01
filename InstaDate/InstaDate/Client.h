#pragma once

const int MAX_ITEMS = 5;
enum RelationType  {LESS, GREATER, EQUAL};

class Client
{
public:
	Client(void);
	Client(char, std::string, std::string, int, std::string);
	Client(char, std::string, std::string, int, std::string, std::string);
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

	bool matched();
	RelationType ComparedTo(Client) const;
private:
	char sex;
	std::string name;
	std::string phone;
	int numInterest;
	std::string listInterest;
	std::string match;

};

