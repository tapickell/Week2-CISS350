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
void unmatchClient(Client&, UnsortedList&);
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
			Client foundClient = findClientByName(vString[1], males);
			if (foundClient.getName() == "NOTFOUND")
			{
				foundClient = findClientByName(vString[1], females);
				if (foundClient.getName() == "NOTFOUND")
				{
					cout << endl << "ERROR: Client not found!" << endl;
				}
			}
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

/* 
	function: unmatch a client from current match
	pre: client has been found using findClientByName() 
		 checked sex to pass in correct list
		 client has a match and match can be found
	post: both client and matched client will have match set to " "
*/
void unmatchClient(Client &clientIN, UnsortedList &theList)
{
	if (clientIN.getMatch() != " ")
	{
		//find matched client by name
		Client matchedClient = findClientByName(clientIN.getMatch(), theList);
		
		if (matchedClient.getName() != "NOTFOUND")
		{
			//clear matches for both clients
			clientIN.setMatch(" ");
			matchedClient.setMatch(" ");
		} else {
			cout << endl << "ERROR: Matched client not found!" << endl;
		}
	} else {
		cout << endl << "ERROR: Client is not matched!" << endl;
	}
}

Client findClientByName(string nameIn, UnsortedList &theList)
{
	Client searchFor = Client(nameIn);
	//search list for client with matching name
	bool isFound;
	Client found = theList.GetItem(searchFor, isFound);
	if (!isFound)
	{
		found = Client(-1);
		cout << endl << "ERROR: Client Not Found!" << endl;
	}
	//return Client object once found
	return found;
}

void printList(UnsortedList &listIn)
{
	//print out list passed in
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