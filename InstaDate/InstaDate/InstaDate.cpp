/* ***************************************************************************

Programmer: Todd Pickell

Filename: InstaDate.cpp

Requirements: None

Includes: 
#include "stdafx.h"
#include "Client.h"
#include "fileHandler.h"
#include "LinkedList.h"

Course: CISS-350A

Date: 11-1-12

Assignment: Week 2

Description: main program file

************************************************************************* */

#include "stdafx.h"
#include "Client.h"
#include "fileHandler.h"
#include "LinkedList.h"
#include "LinkedList.h"
#include "ClientNotFoundError.h"
#include "PatErrror.h"


using namespace std;

// function declarations ########################################
void createNewClient(vector<string>, LinkedList&, LinkedList&);
void unmatchClient(int, LinkedList&, LinkedList&);
int findClientByName(string, LinkedList&);
void grepListForMatched(bool , LinkedList&);
void printMatchList(LinkedList&);
void printFreeList(LinkedList&);
vector<string> split_by_whitespace(string);
void spitout(string);
void failout(string);


// main  #######################################################################
int _tmain(int argc, _TCHAR* argv[])
{
	spitout("###  Instadate Computer Dating System  ###");
	cout << endl;
	//create lists for clients
	LinkedList males;
	LinkedList females;

	//put contents of clients file into lists
	fileHandler clientsFile("Clients.mf");
	fileHandler outFile("Dates.out");
	outFile.getFile(); //create new file
	vector<string> clientsFromFile = clientsFile.getFile(); // get clients from file

	for (size_t i = 0; i < clientsFromFile.size(); i++)// for each client in file
	{
		//split string by spaces to vector
		vector<string> clientString = split_by_whitespace(clientsFromFile[i]);
		//create new client to add to list
		createNewClient(clientString, males, females);
	}

	// **** main loop ****
	bool done = false;
	while (!done)
	{
		cout << endl;
		spitout("~ : NEWCLIENT : UNMATCH : PRINTMATCH : PRINTFREE : HELP : QUIT : ~");

		string sexCharM = "M";
		string sexCharF = "F";
		string cinString;
		//get input from user
		cout << endl;
		spitout("command =>  ");
		getline(cin, cinString);
		//split string by spaces to vector
		vector<string> vString = split_by_whitespace(cinString);
		//cout << endl << vString[0] << endl;
		//pass choice to switch
		if (vString[0] == "HELP")  /**** Main Help Display ****/
		{
			//load and display help file
			fileHandler helpFile("Help.pkl");
			helpFile.catFile();

		} else if (vString[0] == "NEWCLIENT")  /**** New Client Option ****/
		{
			if (vString.size() > 1 && vString[1] == "help")
			{
				cout << endl;
				spitout("NEWCLIENT: Sex Name Phone #interests listOfInterests");
				spitout("Used to enter a new client into the system.");
			} else
			{
				//create new client
				vString.erase(vString.begin());//pop 1st entry out of vector to make createNewClient reusable elswhere
				//cout << endl << vString[0] << endl;
				createNewClient(vString, males, females);
			}

		} else if (vString[0] == "UNMATCH")  /**** Unmatch Client Option ****/
		{
			if (vString.size() > 1 && vString[1] == "help")
			{
				cout << endl;
				spitout("UNMATCH: Name");
				spitout("Used to unmatch a matched couple.");
			} else
			{
				//find client by name
				try
				{
					int foundClient = findClientByName(vString[1], males);
					bool manly = (foundClient < 0) ? false : true;
					if (foundClient < 0)
					{
						foundClient = findClientByName(vString[1], females);
						if (foundClient < 0)
						{
							throw ClientNotFoundError();
						}
					}
					if (foundClient >= 0)
					{
						//unmatch client
						if (manly)
						{
							//call unmatch passing males list
							//cout << "Found Clent is male" << endl;
							unmatchClient(foundClient, males, females);

						} else if (!manly)
						{
							//call unmatch passing females list
							unmatchClient(foundClient, females, males);

						} else
						{
							//defualt if sex doesnt equal either M || F
							throw PatError();
						}
					}
				}
				catch (ClientNotFoundError &e)
				{
					stringstream fail;
					fail << "ERROR: " << e.what();
					failout(fail.str());
				}
				catch (PatError &e)
				{
					stringstream fail;
					fail << "ERROR: " << e.what();
					failout(fail.str());
				}
			}

		} else if (vString[0] == "PRINTMATCH")  /**** Print Matched Clients Option ****/
		{
			if (vString.size() > 1 && vString[1] == "help")
			{
				cout << endl;
				spitout("Used to display a list of all matched clients with thier corresponding match.");
			} else
			{
				cout << endl;
				//print clients that are matched ( can do one or other doesnt matter )
				grepListForMatched(true, males);
			}

		} else if (vString[0] == "PRINTFREE")  /**** Print Free Clients Option ****/
		{
			if (vString.size() > 1 && vString[1] == "help")
			{
				cout << endl;
				spitout("Used to display all clients that are not matched.");
			} else
			{
				cout << endl;
				//print clients without matches
				spitout("Free Clients:");
				grepListForMatched(false, males);
				grepListForMatched(false, females);
			}

		} else if (vString[0] == "QUIT")  /**** QUIT ****/
		{
			if (vString.size() > 1 && vString[1] == "help")
			{
				cout << endl;
				spitout("Used to exit the program.");
				spitout("Upon exit all changes to the clients lists are saved to file.");
			} else
			{
				//exit program
				done = true;
			}

		} else
		{
			//if user enters client name instead of command search for user name and spitout to_str() if found
			try
			{
				int foundClient = findClientByName(vString[0], males);
				bool manly = (foundClient < 0) ? false : true;
				if (foundClient < 0)
				{
					foundClient = findClientByName(vString[0], females);
					if (foundClient < 0)
					{
						throw ClientNotFoundError();
					}
				}
				spitout(manly ? males[foundClient].to_str() : females[foundClient].to_str());
			}
			catch (ClientNotFoundError &e)
			{
				//default
				failout("!ERROR: Unknown Command!");
			}
			
		}//end if else (switch)
	}//end main while loop

	//add some persistance by writing lists back out to Clients file
	//need lists into vector<string> to pass to putFile
	vector<string> stringStack = males.toStack();
	vector<string> ladyStack = females.toStack();
	//converge lists into one
	for (size_t i = 0; i < ladyStack.size(); i++)
	{
		stringStack.push_back(ladyStack[i]);
	}
	//send lists out to file
	clientsFile.putFile(stringStack);

	cout << endl;
	spitout("Thank you for using InstaDate"); // exit message
	system("pause");
	return 0;
}


/* #####################################################
	function:
	pre:
	post:
*/
void createNewClient(vector<string> stringsIN, LinkedList &maleList, LinkedList &femaleList)
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
				maleList += newClientWithMatch;

			} else if (newClientWithMatch.getSex() == sexCharF[0])// new client is female
			{
				femaleList += newClientWithMatch;

			} else
			{
				throw PatError();
			}
		}
		catch (PatError &e)
		{
			stringstream fail;
			fail << "!ERROR: " << e.what();
			failout(fail.str());
		}
	} else //new client from prompt without match
	{
		Client newClient = Client(strChar[0], stringsIN[1], stringsIN[2], atoi(stringsIN[3].c_str()), stringsIN[4]); //got subscript out of range FIXED!
		//check for match with opposite sex list
		vector<string> clientInterests = newClient.getListInterest();
		try
		{
			if (newClient.getSex() == sexCharM[0])// new client is male
			{
				bool found = false;
				//LinkedList unmatchedFemales = grepListForMatched(false, femaleList); // get only unmatched females
				for (int i = 0; i < femaleList.count(); i++) // for each client on list
				{
					int matches = 0;
					Client nextOne = femaleList.getAt(i);
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
						nextOne.setMatch(newClient.getName()); //needs to be matched client from original list passed in 
						femaleList.removeAt(i);
						femaleList += nextOne;
						stringstream clientString;
						clientString << endl << newClient.getName() << " : " << newClient.getPhone() << " => " << nextOne.getName() << " : " << nextOne.getPhone() << endl;
						spitout(clientString.str());
					}// if not a match move onto next on list
					if (matches >= 3) break; // no need to check all if 3 matches found
				}
				//when finished with list if still no matches found the spitout msg
				if (newClient.getMatch() == " ") spitout("~No matches found for new client~"); 

				//add client to appropriate list
				maleList += newClient;

			} else if (newClient.getSex() == sexCharF[0])// new client is female
			{
				//add client to appropriate list
				//LinkedList unmatchedMales = grepListForMatched(false, maleList); // get only unmatched males
				for (int i = 0; i < maleList.count(); i++) // for each client on list
				{
					int matches = 0;
					Client nextOne = maleList.getAt(i); // error from here ***************************************************!!!
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
						nextOne.setMatch(newClient.getName()); //needs to be matched client from original list passed in 
						maleList.removeAt(i);
						maleList += nextOne;
						stringstream clientString;
						clientString << endl << newClient.getName() << " : " << newClient.getPhone() << " => " << nextOne.getName() << " : " << nextOne.getPhone() << endl;
						spitout(clientString.str());
					}// if not a match move onto next on list
					if (matches >= 3) break; // no need to check all if 3 matches found
				}
				//when finished with list if still no matches found the spitout msg
				if (newClient.getMatch() == " ") spitout("~No matches found for new client~"); 

				//add client to appropriate list
				femaleList += newClient;

			} else
			{
				throw PatError();
			}
		}
		catch (PatError &e)
		{
			stringstream fail;
			fail << "!ERROR: " << e.what();
			failout(fail.str());
		}
	}
}


/* #####################################################
	function: unmatch a client from current match
	pre: client has been found using findClientByName() 
		 checked sex to pass in correct list
		 client has a match and match can be found
	post: both client and matched client will have match set to " "
*/
void unmatchClient(int clientIN, LinkedList &list1, LinkedList &list2)
{
	if (list1[clientIN].getMatch() != " ")
	{
		//find matched client by name
		int matchedClient = findClientByName(list1[clientIN].getMatch(), list2);
		
		if (list2[matchedClient].getName() != "NOTFOUND")
		{
			spitout("~clearing matches on both clients~");
			//clear matches for both clients
			Client Bob = list1[clientIN];
			Client Barb = list2[matchedClient];
			Bob.setMatch(" ");
			Barb.setMatch(" ");
			list1.removeAt(clientIN);
			list2.removeAt(matchedClient);
			list1 += Bob;
			list2 += Barb; 
		} else {
			failout("!ERROR: Matched client not found!");
		}
	} else {
		failout("!ERROR: Client is not matched!");
	}
}


/* #####################################################
	function:searches thru list to find client name
	pre: name and list is passed into
	post: returns the index of where the name was found in the list
*/
int findClientByName(string nameIn, LinkedList &theList) //need to rework to search till name is found
{
	bool isFound = false;
	theList.to_str();
	int found;
	//traverse list loooking for client by name
	for (int i = 0; i < theList.count(); i++)
	{
		if (theList[i].getName() == nameIn) // if found return Client object index
		{
			failout("~Name Match Found~");
			found = i;
			isFound = true;
		}
	}
	if (!isFound) //if not found kickout error
	{
		found = -1;
		failout("!ERROR: Client Not Found!");
	}
	return found;
}


/* #####################################################
	function: to search thru a list finding clients that are matched || notMatched
			  depending on bool passed in, creating new list of clients that fit
	pre: list is instantiated, are searching for matched or unmatched clients
	post: returns a new list of either matched or unmatched clients
		  doesnt alter list passed in
*/
void grepListForMatched(bool matched, LinkedList &theList)
{
	LinkedList newList;
	//cout << "theLIst" << endl;
	//theList.to_str();
	//iterate thru list to check each client
	for (int i = 0; i < theList.count(); i++)
	{
		//check if matched then add or not to list
		if (matched)
		{
			if (theList[i].matched() == true)
				newList += theList[i];
		} else //not matched
		{
			if (theList[i].matched()== false)
				newList += theList[i];
		}
		
	}
	//cout << "newList" << endl;
	//newList.to_str();
	if (matched) spitout("Matched Pairs:");

	vector<string> listOutput = matched ? newList.to_str_matched() : newList.to_str_free();
	for (size_t i = 0; i < listOutput.size(); i++)
	{
		spitout(listOutput[i]);
	}
}


///*  refactored into Client, List and grepLiatForMatched to work better
//	function:
//	pre:
//	post:
//*/
//void printMatchList(LinkedList &listIn)
//{
//	cout << "listIn" << endl;
//	listIn.to_str();
//	cout << endl << "Matched Pairs" << endl;
//	//print out list passed in using matched
//	for (int i = 0; i < listIn.count(); i++)
//	{
//		Client nextOne = listIn.getAt(i);//error starting here!!!! #####################
//		cout << nextOne.getName() << " => " << nextOne.getMatch() << endl; 
//	}
//}
//
//
///*
//	function:
//	pre:
//	post:
//*/
//void printFreeList(LinkedList &listIn)
//{
//	cout << endl << "Free Clients" << endl;
//	//print out list passed in using free format
//	for (int i = 0; i < listIn.count(); i++)
//	{
//		Client nextOne = listIn.getAt(i); //error starting here!!!! #####################
//		cout << nextOne.getName() << " : " << nextOne.getPhone() << endl; 
//	}
//}


/* #####################################################
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


/* #####################################################
	function:
	pre:
	post:
*/
//spitOUT() method that outputs strings to cout and to fileHandler
void spitout(string strIN)
{
	cout << strIN << endl;
	fileHandler spitFile("Dates.out");
	vector<string> output;
	output.push_back(strIN);
	spitFile.appendFile(output);
}

/* #####################################################
	function:
	pre:
	post:
*/
//failout() method that outputs strings to cerr and to fileHandler
void failout(string strIN)
{
	cerr << strIN << endl;
	fileHandler spitFile("Dates.out");
	vector<string> output;
	output.push_back(strIN);
	spitFile.appendFile(output);
}