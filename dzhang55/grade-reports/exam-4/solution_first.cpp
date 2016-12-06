#include "common.h"
#include <iostream>
#include <algorithm>

/*
	The algorithm library is included if needed, for the function:
	max: returns the largest of the values passed as arguments.
*/

using namespace std;

Node<int>* deleteNode(Node<int> *&root, int target)
{
	// YOUR CODE HERE!
	if(root==NULL)
		return NULL;
	else if(root->data<target)
		return deleteNode(root->right,target);
	else if(root->data>target)
		return deleteNode(root->left,target);
	else{
		if(root->left==NULL||root->right==NULL){
			Node<int>* temp=(root->left==NULL)?(root->right):(root->left);
			delete root;
			root=temp;
		}else{
			Node<int>* temp=root->right;
			while(temp->left)
				temp=temp->left;
			root->data=temp->data;
			delete temp;
			temp=NULL;
		}
		return root;
	}
}
