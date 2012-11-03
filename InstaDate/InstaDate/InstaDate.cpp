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

// function declarations
void createNewClient(vector<string>, UnsortedList&, UnsortedList&);
void unmatchClient(Client&, UnsortedList&);
Client findClientByName(string, UnsortedList&);
UnsortedList grepListForMatched(bool , UnsortedList&);
void printMatchList(UnsortedList&);
void printFreeList(UnsortedList&);
vector<string> split_by_whitespace(string);

// **** main ****
int _tmain(int argc, _TCHAR* argv[])
{
	//create lists for clients
	UnsortedList males;
	UnsortedList females;
	//put contents of clients file into lists
	fileHandler clientsFile("Clients.mf");
	vector<string> clientsFromFile = clientsFile.getFile();
	for (int i = 0; i < clientsFromFile.size(); i++)// for each client in file
	{
		//split string by spaces to vector
		vector<string> clientString = split_by_whitespace(clientsFromFile[i]);
		//create new client to add to list
		createNewClient(clientString, males, females);
	}

	// **** main loop ****
	cout << "Instadate computer dating system" << endl;
	bool done = false;
	while (!done)
	{
		cout << endl << "Known commands:" << endl;
		cout << endl << "NEWCLIENT: Sex Name Phone #interests listOfInterests" << endl;
		cout << "UNMATCH: Name" << endl;
		cout << "PRINTMATCH" << endl;
		cout << "PRINTFREE" << endl;
		cout << "QUIT" << endl;
		string sexCharM = "M";
		string sexCharF = "F";
		string cinString;
		//get input from user
		cout << endl << "Enter a command: " << endl;
		getline(cin, cinString);
		//split string by spaces to vector
		vector<string> vString = split_by_whitespace(cinString);

		//pass choice to switch
		if (vString[0] == "NEWCLIENT")  /**** New Client Option ****/
		{
			//create new client
			vString.erase(vString.begin());//pop 1st entry out of vector to make createNewClient reusable elswhere
			createNewClient(vString, males, females);

		} else if (vString[0] == "UNMATCH")  /**** Unmatch Client Option ****/
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
			

		} else if (vString[0] == "PRINTMATCH")  /**** Print Matched Clients Option ****/
		{
			//print clients that are matched ( can do one or other doesnt matter )
			printMatchList(grepListForMatched(true, males));

		} else if (vString[0] == "PRINTFREE")  /**** Print Free Clients Option ****/
		{
			//print clients without matches
			printFreeList(grepListForMatched(false, males));
			printFreeList(grepListForMatched(false, females));

		} else if (vString[0] == "QUIT")  /**** QUIT ****/
		{
			//exit program
			done = true;
		} else
		{
			//default
			cout << endl << "ERROR: Unknown Command!" << endl;

		}//end if else (switch)
	}//end main while loop


	cout << endl << "Thank you for using InstaDate" << endl; // exit message
	system("pause");
	return 0;
}


/*
	function:
	pre:
	post:
*/
void createNewClient(vector<string> stringsIN, UnsortedList &maleList, UnsortedList &femaleList)
{
	string sexCharM = "M";
	string sexCharF = "F";
	//create client object
	string strChar = stringsIN[0]; //to go to char easily
	if (stringsIN.size() > 5 && stringsIN[5] != " ") // client string allready has match in it (came from file)
	{
		try
		{
			Client newClientWithMatch = Client(strChar[0], stringsIN[1], stringsIN[2], atoi(stringsIN[3].c_str()), stringsIN[4], stringsIN[5]);
			if (newClientWithMatch.getSex() == sexCharM[0])// new client is male
			{
				maleList.PutItem(newClientWithMatch);

			} else if (newClientWithMatch.getSex() == sexCharF[0])// new client is female
			{
				femaleList.PutItem(newClientWithMatch);

			} else
			{
				throw PatError();
			}
		}
		catch (PatError &e)
		{
			cerr << endl << "ERROR: " << e.what() << endl;
		}
	} else //new client from prompt without match
	{
		Client newClient = Client(strChar[0], stringsIN[1], stringsIN[2], atoi(stringsIN[3].c_str()), stringsIN[4]); //got subscript out of range
		//check for match with opposite sex list
		vector<string> clientInterests = newClient.getListInterest();
		try
		{
			if (newClient.getSex() == sexCharM[0])// new client is male
			{
				bool found = false;
				//UnsortedList unmatchedFemales = grepListForMatched(false, femaleList); // get only unmatched females
				for (int i = 0; i < femaleList.GetLength(); i++) // for each client on list
				{
					int matches = 0;
					Client nextOne = femaleList.GetNextItem();
					vector<string> matchInterests = nextOne.getListInterest(); // get interest list to check against
					for (size_t i = 0; i < clientInterests.size(); i++) //for each male interest
					{
						for (size_t j = 0; j < matchInterests.size(); j++) //for each female interest
						{
							if (clientInterests[i] == matchInterests[j]) //if interest match found
								matches++; // increment counter
						}
						if (matches >= 3) break; // no need to check all if 3 matches found
					}
					if (matches >= 3)
					{
						// if 3 or more interests match set as each others matches
						newClient.setMatch(nextOne.getName());
						bool foundInList;
						femaleList.GetItem(nextOne, foundInList).setMatch(newClient.getName()); //needs to be matched client from original list passed in 
						cout << endl << newClient.getName() << " : " << newClient.getPhone() << " => " << nextOne.getName() << " : " << nextOne.getPhone() << endl;
					}// if not a match move onto next on list
					if (matches >= 3) break; // no need to check all if 3 matches found
				}
				//when finished with list if still no matches found the spitout msg
				if (newClient.getMatch() == " ") cout << endl << "No matches found for new client" << endl; 

				//add client to appropriate list
				maleList.PutItem(newClient);

			} else if (newClient.getSex() == sexCharF[0])// new client is female
			{
				//add client to appropriate list
				//UnsortedList unmatchedMales = grepListForMatched(false, maleList); // get only unmatched males
				for (int i = 0; i < maleList.GetLength(); i++) // for each client on list
				{
					int matches = 0;
					Client nextOne = maleList.GetNextItem(); // error from here ***************************************************!!!
					vector<string> matchInterests = nextOne.getListInterest(); // get interest list to check against
					for (size_t i = 0; i < clientInterests.size(); i++) //for each male interest
					{
						for (size_t j = 0; j < matchInterests.size(); j++) //for each female interest
						{
							if (clientInterests[i] == matchInterests[j]) //if interest match found
								matches++; // increment counter
						}
						if (matches >= 3) break; // no need to check all if 3 matches found
					}
					if (matches >= 3)
					{
						// if 3 or more interests match set as each others matches
						newClient.setMatch(nextOne.getName());
						bool foundInList;
						maleList.GetItem(nextOne, foundInList).setMatch(newClient.getName()); //needs to be matched client from original list passed in 
						cout << endl << newClient.getName() << " : " << newClient.getPhone() << " => " << nextOne.getName() << " : " << nextOne.getPhone() << endl;
					}// if not a match move onto next on list
					if (matches >= 3) break; // no need to check all if 3 matches found
				}
				//when finished with list if still no matches found the spitout msg
				if (newClient.getMatch() == " ") cout << endl << "No matches found for new client" << endl; 

				//add client to appropriate list
				femaleList.PutItem(newClient);

			} else
			{
				throw PatError();
			}
		}
		catch (PatError &e)
		{
			cerr << endl << "ERROR: " << e.what() << endl;
		}
	}
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


/*
	function:
	pre:
	post:
*/
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
	
	//iterate thru list to check each client
	for (int i = 0; i < theList.GetLength(); i++)
	{
		//get next item (will cycle back to first at end of list)
		Client nextOne = theList.GetNextItem();
		//check if matched then add or not to list
		if (matched)
		{
			if (nextOne.matched() == true)
				newList.PutItem(nextOne);
		} else //not matched
		{
			if (nextOne.matched()== false)
				newList.PutItem(nextOne);
		}
		
	}
	return newList;
}


/*
	function:
	pre:
	post:
*/
void printMatchList(UnsortedList &listIn)
{
	cout << endl << "Matched Pairs" << endl;
	//print out list passed in using matched
	for (int i = 0; i < listIn.GetLength(); i++)
	{
		Client nextOne = listIn.GetNextItem();
		cout << nextOne.getName() << " => " << nextOne.getMatch() << endl; 
	}
}


/*
	function:
	pre:
	post:
*/
void printFreeList(UnsortedList &listIn)
{
	cout << endl << "Free Clients" << endl;
	//print out list passed in using free format
	for (int i = 0; i < listIn.GetLength(); i++)
	{
		Client nextOne = listIn.GetNextItem();
		cout << nextOne.getName() << " : " << nextOne.getPhone() << endl; 
	}
}


/*
	function:
	pre:
	post:
*/
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


/*
	function:
	pre:
	post:
*/
//spitOUT() method that outputs strings to cout and to fileHandler
void spitout(string strIN)
{
	fileHandler outFile("Dates.out");

}