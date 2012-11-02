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
#include "ClientNotFoundError.h"
#include "PatErrror.h"


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
			try
			{
				Client foundClient = findClientByName(vString[1], males);
				if (foundClient.getName() == "NOTFOUND")
				{
					foundClient = findClientByName(vString[1], females);
					if (foundClient.getName() == "NOTFOUND")
					{
						throw ClientNotFoundError();
					}
				}
				//unmatch client
				string sexCharM = "M";
				string sexCharF = "F";
				if (foundClient.getSex() == sexCharM[0])
				{
					//call unmatch passing males list
					unmatchClient(foundClient, males);

				} else if (foundClient.getSex() == sexCharF[0])
				{
					//call unmatch passing females list
					unmatchClient(foundClient, females);

				} else
				{
					//defualt if sex doesnt equal either M || F
					throw PatError();
				}
			}
			catch (ClientNotFoundError &e)
			{
				cerr << endl << "ERROR: " << e.what() << endl;
			}
			catch (PatError &e)
			{
				cerr << endl << "ERROR: " << e.what() << endl;
			}
			

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

		}//end if else (switch)
	}//end main while loop


	cout << endl << "Thank you for using InstaDate" << endl;
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

/*
	function: to search thru a list finding clients that are matched || notMatched
			  depending on bool passed in, creating new list of clients that fit
	pre: list is instantiated, are searching for matched or unmatched clients
	post: returns a new list of either matched or unmatched clients
		  doesnt alter list passed in
*/
UnsortedList grepListForMatched(bool matched, UnsortedList &theList)
{
	UnsortedList newList;
	//getLength() on list
	return newList;
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