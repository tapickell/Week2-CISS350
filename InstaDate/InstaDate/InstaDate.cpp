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


#define nc = ;
#define um = ;
#define pm = ;
#define pf = ;
#define qt = ;

using namespace std;

void createNewClient(vector<string>);
void unmatchClient(Client&);
void printList(UnsortedList&);

int _tmain(int argc, _TCHAR* argv[])
{
	UnsortedList males;
	UnsortedList females;

	cout << "Welcome to the InstaDate computer dating system" << endl;
	
	bool done = false;
	while (!done)
	{
		string str;
		vector<string> vecStr;
		//get input from user
		cout << "Enter command: " << endl;
		getline(cin, str);
		cout << endl;
		//Tokenizer::splitIt(str, vecStr, " "); //split by white space !May Not Work Well!
		//pass thru switch statement

		if (vecStr[0] == "NEWCLIENT")
		{
			createNewClient(vecStr); // may have to pass lists in as well
		} else if (vecStr[0] == "UNMATCH")
		{

		} else if (vecStr[0] == "PRINTMATCH")
		{

		} else if (vecStr[0] == "PRINTFREE")
		{

		} else if (vecStr[0] == "QUIT")
		{
			done = true; //exit program
		} else {
			cout << "Error Unkown Command!" << endl; //default
		}
	}

	std::system("pause");
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
	clientIN.setMatch(" ");
	//find clients name in opposite sex list under match
	//matchedClient.setMatch(" ");
}

void printList(UnsortedList &listIn)
{

}

//Client findClientByName(UnorderedList & searchList, string nameIn)
//{

//}