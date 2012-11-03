#include "Client.h"

struct node
{
    Client data;
    node *nextLink;
    node *previousLink;
};