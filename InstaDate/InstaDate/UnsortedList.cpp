#include "stdafx.h"
#include "Client.h"
#include "UnsortedList.h"


struct Node
{
    Client client;
    Node* next;
};

UnsortedList::UnsortedList()  // Class constructor
{
  length = 0;
  listData = NULL;
}
bool UnsortedList::IsFull() const
// Returns true if there is no room for another Client 
//  on the free store; false otherwise.
{
  Node* location;
  try
  {
    location = new Node;
    delete location;
    return false;
  }
  catch(std::bad_alloc exception)
  {
    return true;
  }
}

int UnsortedList::GetLength() const
// Post: Number of items in the list is returned.
{
  return length;
}

void UnsortedList::MakeEmpty()
// Post: List is empty; all items have been deallocated.
{
  Node* tempPtr;

    while (listData != NULL)
    {
      tempPtr = listData;
      listData = listData->next;
      delete tempPtr;
  }
  length = 0;
}
void UnsortedList::PutItem(Client item)
// item is in the list; length has been incremented.
{
  Node* location;			// Declare a pointer to a node

  location = new Node;		// Get a new node 
  location->client = item;		// Store the item in the node
  location->next = listData;	// Store address of first node 
						//   in next field of new node
  listData = location;		// Store address of new node into
						//   external pointer
  length++;				// Increment length of the list
}

Client UnsortedList::GetItem(Client& item, bool& found)
// Pre:  Key member(s) of item is initialized.
// Post: If found, item's key matches an element's key in the 
//       list and a copy of that element has been stored in item;
//       otherwise, item is unchanged. 
{
  bool moreToSearch;
  Node* location;

  location = listData;
  found = false;
  moreToSearch = (location != NULL);

  while (moreToSearch && !found) 
  {
    switch (item.ComparedTo(location->client))
    {
      case LESS    : 
      case GREATER : location = location->next;
                     moreToSearch = (location != NULL);
                     break;
      case EQUAL   : found = true;
                     item = location->client;
                     break;
    }
  }
  return item;
}

 void UnsortedList::DeleteItem(Client item)
// Pre:  item's key has been initialized.
//       An element in the list has a key that matches item's.
// Post: No element in the list has a key that matches item's.
{
  Node* location = listData;
  Node* tempLocation;

  // Locate node to be deleted.
  if (item.ComparedTo(listData->client) == EQUAL)
  {
    tempLocation = location;
    listData = listData->next;		// Delete first node.
  }
  else
  {
    while (item.ComparedTo((location->next)->client) != EQUAL)
      location = location->next;

    // Delete node at location->next
    tempLocation = location->next;
    location->next = (location->next)->next;
  }
  delete tempLocation;
  length--;
}

void UnsortedList::ResetList()
// Post: Current position has been initialized.
{
  currentPos = NULL;
}
 
Client UnsortedList::GetNextItem()
// Post:  A copy of the next item in the list is returned.
//        When the end of the list is reached, currentPos
//        is reset to begin again.
{
  Client item;
  if (currentPos == NULL)
    currentPos = listData;
  else
    currentPos = currentPos->next;
  item = currentPos->client;
  return item;
}

UnsortedList::~UnsortedList()
// Post: List is empty; all items have been deallocated.
{
  Node* tempPtr;

  while (listData != NULL)
  {
    tempPtr = listData;
    listData = listData->next;
    delete tempPtr;
  }
}





