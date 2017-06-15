//Brian Lee
//CS202 - Fant
//Program3


//Implementation file for the node class. The node class is representative
//of a BST node, however each node in the BST has a LLL for persons with
//the same last name (as each node is for a particular last name). 

#include "node.h"



// ------------------- NODE CLASS ----------------



//Default contstructor
node::node() : name(NULL), left(NULL), right(NULL), head(NULL), length(0)
{}



//Copy constructor
node::node(const node &to_copy) : left(NULL), right(NULL), length(0)
{
	name = new char[strlen(to_copy.name) +1];
	strcpy(name, to_copy.name);

	//if the source data has a non-NULL head
	//pointer then copy the data in LLL
	if(to_copy.head)
	{
		person *current = to_copy.head;

		while(current)
		{
			if(!addPerson(*current))
				cout << "Error..." << endl;

			current -> moveNext(current);
		}	

	}

}



//Destructor
node::~node()
{
	delete []name;
	name = NULL;

	left = right = NULL;
		
	//Deallocates entire LLL pointed
	//to by *head
	deallocate(head);
}



//Deallocate function should go here
void node::deallocate(person* &current)
{
	if(current)
	{
		person *to_remove = current;
		current -> moveNext(current);

		delete to_remove;
		to_remove = NULL;
		deallocate(current);
	}
}




//Overloaded assignment operator, The assignment 
//operator will only copy the last name the node
//represents as well as the LLL of persons with
//the same last name. The left and right pointers
//are not copied from a source node.
node& node::operator=(const node &to_copy)
{
	if(this == &to_copy)
		return *this;

	else
	{
		name = new char[strlen(to_copy.name) +1];
		strcpy(name, to_copy.name);

		//if there are existing entires in the LLL,
		//clear it so a new list can take its place.
		if(head)
		{
			deallocate(head);
		}

		person *current = to_copy.head;

		//copy the source LLL
		while(current)
		{
			addPerson(current);
			current -> moveNext(current);	
		}	
	
		return *this;
	}	

}


//Returns true if the left operand is less than
//the right operand in terms of comparing the
//ASCII values for associated last names.
bool node::operator < (const node &n)
{
	return (strcmp(name, n.name) < 0);
}




//Returns true if the right operand is greater
//than the left operand in terms of the ASCII
//values for the associated names.
bool node::operator > (const node &n)
{
	return (strcmp(name, n.name) > 0);
}




//Public wrapper function to call the private
//method that adds a new person to the LLL
//pointed to by *head. Returns true if the
//operation was successful.
bool node::addPerson(person &to_add)
{
	person *previous = NULL;
	person *current = head;	
		
	++length;

	return addPerson(previous, current, to_add);
}


//Performs the same operation as the above function
//however it takes as an argument a pointer to a 
//person object. This was originally implemented for
//debugging purposes, however it has survived a code
//purge.
bool node::addPerson(person* &to_add)
{
	person ta(*to_add);
	person *previous = NULL;
	person *current = head;
	
	++length;

	return addPerson(previous, current, ta);

}




//Adds a person to the LLL pointed to by
//*head. LLL is sorted by first name of the
//persons being added. Returns true if the 
//operation was successful.
bool node::addPerson(person* &previous, person* &current, person &to_add)
{

	//head is NULL, first entry in the list. If the list
	//empty, then this is the first person to populate this
	//node class object. So, set node's name data member also.
	if(!head)
	{
		head = new person(to_add);
	
		//set node class name to last name
		//of first person added to the list	
		head -> retrieveLast(name);
	
		return true;
	}


	//Adding at the end of the list
	else if(!current)
	{
		person *temp = new person(to_add);
		previous -> setNext(temp);
		return true;
	}


	//The person being added comes before the person
	//pointed to by current. Ex. to_add "A", current "B"
	if(to_add.compareFirst(*current) < 0)
	{
		//Adding before head
		if(!previous)
		{
			person *temp = new person(to_add);
			temp -> setNext(head);
			head = temp;
			return true;
		}


		//adding inbetween
		else
		{
			person *temp = new person(to_add);
			previous -> setNext(temp);
			temp -> setNext(current);
			return true;
		}
	}	


	//Move on to next node and compore
	else
	{
		previous = current;
		current -> moveNext(current);
		return addPerson(previous, current, to_add);
	}

}






//Displays the list of persons pointed to by
// *head. 
void node::displayList()
{
	person *current = head;

	while(current)
	{
		cout << *current << endl;
		current -> moveNext(current);
	}
}


//Overloaded extraction operator that 
//displays the last name associated
//with the node.
ostream& operator << (ostream &out, const node &n)
{
	out << "Name: " << n.name << endl;
	out << "Num of persons: " << n.length;
	return out;
}




//After the function call the char * passed
//as an argument will point to a char array
//that matches the data that is in node's name
//char array.
void node::retrieveName(char* &ptr)
{
	ptr = new char[strlen(name) +1];
	strcpy(ptr, name);
}




//The node passed as an argument will
//be changed to point to its' left node
//regardless if it is NULL or not.
void node::moveLeft(node* &ptr)
{
	if(!ptr -> left)
		ptr = NULL;

	else
		ptr = ptr -> left;
}





//The node passed as an argument will
//be changed to point to its' right node
//regardless if it is NULL or not.
void node::moveRight(node* &ptr)
{
	if(!ptr -> right)
		ptr = NULL;
	
	else
		ptr = ptr -> right;
}



//Returns true if the left node
//is not pointing to NULL. Otherwise
//it returns false.
bool node::hasLeft()
{
	if(!left)
		return false;

	else
		return true;
}




//Returns true if the right node
//is not pointing to NULL. Otherwise
//it returns false.
bool node::hasRight()
{
	if(!right)
		return false;

	else
		return true;
}



//Sets a node's Left pointer to point to
//the passed argument, even if the passed node
//is NULL.
void node::setLeft(node* &ptr)
{
	left = ptr;
}




//Sets a node's Right pointer to point to
//the passed argument, even if the passed node
//is NULL.
void node::setRight(node* &ptr)
{
	right = ptr;
}




//Public wrapper function to remove a person. Takes
//as an argument a first name. (The last name isn't needed
//because all persons in the list have the same last name)
//Returns true if the person was found and removed.
bool node::removePerson(char lName[])
{
	person *previous;
	person *current = head;
	if(removePerson(previous, current, lName))
	{
		--length;
		if(length == 0)
		{
			char msg[11] = "Empty Data";
			delete name;
			strcpy(name, msg);	
		}
		return true;
	}

	else
		return false;
}




//Private member function to remove a person from the LLL
//pointed to *head. Function will return true if the
//person was found and removed.
bool node::removePerson(person* &previous, person* &current, char target[])
{
	if(!current)
		return false;


	char *cName = NULL;
	current -> retrieveFirst(cName);

	//Match in last name is found
	if(strcmp(cName, target) == 0)
	{
		delete cName;
		cName = NULL;

		//removing head node
		if(current == head)
		{
			current -> moveNext(current);
			delete head;
			head = current;			
			return true;
		}


		//removing at end of list
		if(!current -> hasNext())
		{
			delete current;
			current = NULL;

			previous -> setNext(current);
			return true;
		}
		
		//removing between two nodes
		else
		{
			person *to_remove = current;
	
			current -> moveNext(current);
			previous -> setNext(current);
			
			delete to_remove;
			to_remove = NULL;

			return true;
		}

	}

	else
	{
		delete cName;
		cName = NULL;

		previous = current;
		current -> moveNext(current);

		return removePerson(previous, current, target);
	}

}



//Public wrapper function to find a person. If a
//person is found, their data will be displayed.
//Otherwise a message will display that the person
//could not be found. Takes as an argument the first
//name of the person to be found, since all persons
//in a node will have the same last name.
void node::findPerson(char target[])
{
	person *current = head;
	return findPerson(current, target);
}



//Private member function to find a person. A message
//will be displayed regardless of if the person is 
//found or not. Takes as an argument a pointer to the LLL of
//people pointed to by *head (ideally) and the first name
//of the person to be found.
void node::findPerson(person* &current, char target[])
{
	if(!current)
		cout << "The Person Could Not Be Found!" << endl;

	else
	{
		char *cName = NULL;
		current -> retrieveFirst(cName);

		if(strcmp(cName, target) == 0)
		{
			delete cName;
			cName = NULL;

			cout << "Match Found...Data Below:" << endl;
			cout << "Name: " << *current << endl;	//displays persons name
			cout << "Emergency Contact Methods:" << endl;
			current -> contactList();	//displays their contact methods
		}

		else
		{
			delete cName;
			cName = NULL;

			current -> moveNext(current);
			return findPerson(current, target);
		}
	}

}



//Returns true if both left and right
//nodes pointers for the calling node
//are NULL. 
bool node::isLeaf()
{
	return(!left && !right);
}




//Returns true if the passed node is
//pointing to the same address as the
//calling function's *left node pointer.
bool node::isLeft(node* &ptr)
{
	return (left == ptr);
}




//Returns true if the passed node is
//pointing to the same address as the
//calling function's *right node pointer.
bool node::isRight(node* &ptr)
{
	return (right == ptr);
}



//Returns true if *head is NULL.
bool node::emptyList()
{
	return !head;
}



//Passed person pointer will point to
//head to LLL in the calling node.
void node::_pth(person* &ptr)
{
	ptr = head;	
}



//Copies a list from the source (the node object
//invoking the call) to the destination node.
//Ideally, this function is only called when a 
//destination node has an empty list. (For example,
//as part of the iosHelper method).
bool node::copyList(person* &source)
{
	//If the destination list is not empty
	if(head)	
		return false;

	else
	{
		while(source)
		{
			if(!addPerson(source))
				return false;

			source -> moveNext(source);
		}

		return true;
	}	
}


