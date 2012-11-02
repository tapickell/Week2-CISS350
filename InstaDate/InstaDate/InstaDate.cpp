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
void printList(UnsortedList&);

int _tmain(int argc, _TCHAR* argv[])
{
	UnsortedList males;
	UnsortedList females;

	//main loop
	bool done = false;
	while (!done)
	{
		cout << "Instadate computer dating system" << endl;
		//get input from user
		cout << endl << "Enter a command: " << endl;
		//pass choice to switch
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
	clientIN.setMatch(" ");
	//find clients name in opposite sex list under match
	//matchedClient.setMatch(" ");
}

void printList(UnsortedList &listIn)
{

}