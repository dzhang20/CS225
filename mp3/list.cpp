/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
 clear();  /// @todo Graded in MP3.1
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    /// @todo Graded in MP3.1
	if(length==0)
		return;
	ListNode* curr = head;
	ListNode* prev = NULL;
	while(curr!=NULL){
		prev = curr;
		curr = curr->next;
		delete prev;
		prev = curr;
		if(prev == tail){
			delete prev;
			curr = NULL;
			prev = NULL;	
			head = NULL;
			tail = NULL;
			length = 0;
		}
	}
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata)
{
    /// @todo Graded in MP3.1
	ListNode* curr = new ListNode(ndata);
	if(length==0){
		head = curr;
		tail = head;
		length++;
		curr = NULL;
	}else{
		curr->next = head;
		head = curr;
		curr = NULL;
		length++;
	}
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata)
{
    /// @todo Graded in MP3.1
	ListNode* curr = head;
	if(curr == NULL){
		head = new ListNode(ndata);
		tail = head;
		length++;
	}else{
		curr = tail;
		tail = new ListNode(ndata);
		curr->next = tail;
		tail->prev = curr;
		curr = NULL;
		length++;
	}
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint)
{
    /// @todo Graded in MP3.1
	if(endPoint==startPoint||length==0)
		return;
	else{
		ListNode* pre = startPoint->prev;
		ListNode* curr = startPoint;
		ListNode* endP = startPoint;
		ListNode* temp = NULL;
		int step = 1;
		while(endP!=endPoint){
			endP=endP->next;
			step++;		
		}
		for(int i=0;i<step;i++){
			if (i==0){
				temp=endPoint->next;
			}else{
				temp=curr->prev;
			}
			curr->prev=curr->next;
			curr->next=temp;
			curr=curr->prev;
		}
		if(startPoint==head)
			head = endPoint;
		if(endPoint==tail)
			tail=startPoint;
		temp = startPoint;
		startPoint = endPoint;
		endPoint = temp;
		if(endPoint->next!=NULL)
			endPoint->next->prev = endPoint;
		startPoint->prev = pre;
		if(startPoint->prev!=NULL)
			startPoint->prev->next = startPoint;
		temp = NULL;
		curr = NULL;	
	}
}
/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n)
{
	ListNode* curr = head;
	ListNode* temp = curr;
    /// @todo Graded in MP3.1
	if(n>=length)
		reverse();
	while(length>0){
		if(length<=n){
			while(temp!=tail&&temp!=NULL)
				temp=temp->next;
			reverse(curr,temp);
		}
		else{
			for(int i=1;i<n;i++){
				temp=temp->next;	
			}
			reverse(curr,temp);
			curr=temp->next;
			temp=temp->next;
		}
		length-=n;
	}
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
    /// @todo Graded in MP3.1
	ListNode* curr=head->next;
	ListNode* temp=NULL;
	if(length==0)
		return;
	while(curr!=NULL&&curr->next!=NULL){
		temp=curr;
		curr=curr->next->next;
		temp->prev->next=temp->next;
		temp->next->prev=temp->prev;
		tail->next=temp;
		temp->prev=tail;
		tail=temp;
		temp->next=NULL;
	}
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head) {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    } else {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL) {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint)
{
    /// @todo Graded in MP3.2
	for(int i=0;i<splitPoint;i++){
		if(start!=NULL)
			start=start->next;
		else
			return NULL;
	}
	start->prev->next=NULL;
	start->prev=NULL;
	return start; // change me!
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if (tail != NULL) {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second)
{
    /// @todo Graded in MP3.2
	ListNode* start;
	ListNode* temp1 = first;
	ListNode* temp2 = second;
	ListNode* temp = NULL;
	if(first==NULL){
		head=second;
		return second;
	}
	if(second==NULL){
		head=first;
		return first;
	}
	if(temp1->data<temp2->data){
		start=temp1;
		temp1=temp1->next;
	}
	else{
		start=temp2;
		temp2=temp2->next;
	}
	head=start;
	while(temp1!=NULL||temp2!=NULL){
		if(temp1==NULL||(temp2!=NULL&&temp2->data<temp1->data)){
			start->next=temp2;
			temp=start->next;
			temp->prev=start;
			start=start->next;
			temp2=temp2->next;
		}else{
			start->next=temp1;
                        temp=start->next;
                        temp->prev=start;
                        start=start->next;
                        temp1=temp1->next;
		}
	}
	if(first->data<second->data)
		return first;	 
	return second; // change me!
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength)
{
    /// @todo Graded in MP3.2
    if (chainLength==1)
        return start;
    int mid = chainLength/2;
    ListNode* right = split(start,mid);
    ListNode* left = start;
    right = mergesort(right,chainLength-mid);
    start = mergesort(left,mid);
    return merge(right,start);
}
