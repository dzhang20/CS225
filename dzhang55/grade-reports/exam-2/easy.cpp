#include "linkedlist.h"
#include <iostream>
using namespace std;

bool pop(LinkedList &mylist)
{
        if(mylist.head==NULL)
                return 0;
        Node*  curr = mylist.head;
        while(curr->next->next!=NULL){
                curr= curr->next;
        }
        delete (curr->next); 
        curr->next = NULL;
	return 1;
}
