#include "common.h"
#include <iostream>

using namespace std;

void updateSum(Node<int> *&root)
{
	// YOUR CODE HERE!
	if(root==NULL)
		return;
	else if(root->left==NULL&&root->right==NULL)
		return;
	else if(root->left!=NULL&&root->right==NULL){
		updateSum(root->left);
		root->data=root->left->data+root->data;
	}
	else if(root->left==NULL&&root->right!=NULL){
		updateSum(root->right);
		root->data=root->right->data+root->data;
	}else{
		updateSum(root->left);
		updateSum(root->right);
		root->data=root->left->data+root->right->data+root->data;
	}		
}
