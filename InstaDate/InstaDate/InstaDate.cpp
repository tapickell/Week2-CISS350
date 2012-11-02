/* ***************************************************************************

Programmer: Todd Pickell

Filename: InstaDate.cpp

Requirements: None

Includes: 
#include "stdafx.h"
#include "Client.h"
#include "fileHandler.h"
#include "UnsortedList.h"

Course: CISS-350A

Date: 11-1-12

Assignment: Week 2

Description: main program file

************************************************************************* */

#include "stdafx.h"
#include "Client.h"
#include "fileHandler.h"
#include "UnsortedList.h"


#define nc = "NEWCLIENT";
#define um = "UNMATCH";
#define pm = "PRINTMATCH";
#define pf = "PRINTFREE";
#define qt = "QUIT";

using namespace std;

void createNewClient(vector<string>);
void unmatchClient(Client&);
Client findClientByName(string, UnsortedList&);
void printList(UnsortedList&);
vector<string> split_by_whitespace(string);

int _tmain(int argc, _TCHAR* argv[])
{
	//create lists
	UnsortedList males;
	UnsortedList females;

	//main loop
	bool done = false;
	while (!done)
	{
		cout << "Instadate computer dating system" << endl;
		string cinString;
		//get input from user
		cout << endl << "Enter a command: " << endl;
		getline(cin, cinString);
		//split string to vector
		vector<string> vString = split_by_whitespace(cinString);
		//pass choice to switch
		if (vString[0] == "NEWCLIENT")
		{
			//create new client
			createNewClient(vString);

		} else if (vString[0] == "UNMATCH")
		{
			//find client by name
			//unmatch client

		} else if (vString[0] == "PRINTMATCH")
		{
			//print clients that are matched

		} else if (vString[0] == "PRINTFREE")
		{
			//print clients without matches

		} else if (vString[0] == "QUIT")
		{
			//exit program
			done = true;
		} else
		{
			//default
			cout << endl << "ERROR: Unknown Command!" << endl;
		}
	}


	cout << endl << "Hello World!" << endl;
	system("pause");
	return 0;
}

void createNewClient(vector<string> stringsIN)
{
	//create client object
	string strChar = stringsIN[1];
	Client newClient = Client(strChar[0], stringsIN[2], stringsIN[3], atoi(stringsIN[4].c_str()), stringsIN[5]);
	//check for match with opposite sex list
	//add match to client object
	//update clients found match to show matching back to client
	//if (true)
	//{
	//	Client matchedClient = myList[foundAt];
	//	newClient.setMatch(matchedClient.getName());
	//	matchedClient.setMatch(newClient.getName());
	//}
	//add client to appropriate list
	//print message if match or not
}

void unmatchClient(Client &clientIN)
{
	//find matched client by name
	clientIN.setMatch(" ");
	//matchedClient.setMatch(" ");
}

Client findClientByName(string nameIn, UnsortedList &theList)
{
	Client searchFor = Client(nameIn);
	//search list for client with matching name
	bool isFound;
	Client found = theList.GetItem(searchFor, isFound);
	//return Client object once found
	return found;
}

void printList(UnsortedList &listIn)
{

}

vector<string> split_by_whitespace(string myStr)
{
	size_t i, j;
	vector<string> result;

	for (i = j = 0; i < myStr.size(); )
	{

		while ( i < myStr.size() && ::isspace( myStr[i] ) ) i++;
		j = i;

		while ( i < myStr.size() && ! ::isspace( myStr[i]) ) i++;
				
		if (j < i)
		{
			result.push_back( myStr.substr( j, i - j ));

			while ( i < myStr.size() && ::isspace( myStr[i])) i++;
			j = i;
		}
	}
	if (j < myStr.size())
	{
		result.push_back( myStr.substr( j, myStr.size() - j ));
	}
	return result;
}