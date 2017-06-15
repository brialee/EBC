//Brian Lee
//CS202 - Fant
//Program 3




//Implementation file for EBC class, which is basically a
//Tree class for a BST organized by last name and suited for
//use as an emergency broadcast system. Node objects are added
//to the BST in order of last name. For nodes that are added in which
//there is already an existing last name, that person is added to an
//existing node's LLL of persons with the same last name.


#include "EBC.h"



//Constructor
EBC::EBC() : root(NULL)
{}


//Copy Constructor
EBC::EBC(const EBC &to_copy) : root(NULL)
{
	cout << "Don't forget CC" << endl;
}


//Destructor
EBC::~EBC()
{

	//should call deallocate(root);
	//which should use post order traversal
	//to delete the tree.

    	node *current = root;
	deallocate(current);

 	// delete root;
 	root = NULL;
}



//Deallocates the BST pointed to by
//passed node pointer.
void EBC::deallocate(node* &current)
{
	if(current)
	{
		if(current -> hasLeft())
		{
           	 	node *temp = current;
			temp -> moveLeft(temp);
			deallocate(temp);
		}

		if(current -> hasRight())
		{
       			node *temp = current;
			temp -> moveRight(temp);
			deallocate(temp);
		}

		delete current;
	}
}




//Public wrapper function to add a person to
//the EBC tree pointed to by *root. Function will
//first check for a NULL root pointer, and if 
//necessary add the first node to the tree. Otherwise,
//if root wasn't NULL, a private member function is
//invoked. Function returns true if the operation 
//was successful.
bool EBC::addPerson(person &to_add)
{
	//Root was NULL, list was empty to begin with
	if(!root)
	{
		node *temp = new node;
        	root = temp; 
		return root -> addPerson(to_add);
	}


	//Root was not NULL, list was not empty
	else
	{
		node *parent = root;
		node *child = NULL;
		return addNode(parent, child, to_add);
	}	
}




//Adds a node to tree pointed to by *root.
//Nodes are added to the tree by order of last
//name. Function returns true if operation was 
//successful.
bool EBC::addNode(node* &parent, node* &child, person &to_add)
{
	char *nodeName = NULL;
	char *personName = NULL;
	int result;
	
	parent -> retrieveName(nodeName);	//get name associated with node.
	to_add.retrieveLast(personName);	//get last name for person being added.
	result = strcmp(personName, nodeName);	//strcmp the two.

	//Now that we're done comparing char*, might
	//as well delete them here, since now we're really
	//only concerned with the result of the comparison
	delete nodeName;
	delete personName;
	nodeName = personName = NULL;


	//Need to move left.....
	if(result < 0)
	{
		//Check status of parent's left node....

		//Parent has a valid left pointer
		if(parent -> hasLeft())
		{
			parent -> moveLeft(parent);
			return addNode(parent, child, to_add);	
		}

		//Parent's left node is NULL
		else
		{
			child = new node;
			if(child -> addPerson(to_add))
			{
				parent -> setLeft(child);
				return true;
			}

			else
				return false;	
		}
	}

	//Node already created for person that is being
	//added (in terms of last name). So, add the person
	//to the existing node's LLL of persons with the same
	//last name.
	else if(result == 0)
	{
		return parent -> addPerson(to_add);
	}

	
	//Move to the right since < and == have been eliminated.
	else
	{
		if(parent -> hasRight())
		{
			parent -> moveRight(parent);
			return addNode(parent, child, to_add);
		}

		else
		{
			child = new node;
			if(child -> addPerson(to_add))
			{
				parent -> setRight(child);
				return true;
			}
		
			else
				return false;
		}
	}

}


//Displays all people in the tree, in order of A-Z for last name
void EBC::displayList()
{
	node *current = root;
	cout << inOrder(current) << " total nodes in tree." << endl;
}



//Displays the name data for a node while
//performing an in order traversal of the 
//tree. Function returns number of items displayed.
int EBC::inOrder(node* &current)
{
	int total = 0;

	if(!current)
		return 0;

	else
	{
		if(current -> hasLeft())
		{
			node *temp = current;	//without this things fall apart
			temp -> moveLeft(temp);	//...this too.
			total += inOrder(temp);

		}	

		if(current)
		{
			++total;
			cout << *current << ":\n";
			current -> displayList();
			cout << "\n";
		}

		if(current -> hasRight())
		{
			node *temp = current;	//...same thing here.
			temp -> moveRight(temp);	//don't remove this either.
			total += inOrder(temp);
		}

	}

	return total;
}



//Function to read in node data from an external
//file. Returns the number of items read from file
//and added to the EBC tree. Data is read from an 
//external file named "list.txt"
int EBC::read()
{
	ifstream inFile;
	int total = 0;
	int r;
	char last[31];
	char first[31];
	char file[13] = "list.txt";
	char title[21];
	char des[21];
	

	inFile.open(file);
	
	if(!inFile)
		return 0;

	else
	{
		while(!inFile.eof())
		{
			//skip all lines until < is found
			while(inFile.peek() != 60)
				inFile.ignore(100, '\n');

			//once found, skip <
			inFile.ignore(100, '\n');

			//read in data until > is found
			if(inFile.peek() != 62)
			{
				//Read in first and last name
				inFile.get(first, 31, ':');
				inFile.ignore();


				inFile.get(last, 31, '\n');
				inFile.ignore(100, '\n');


				person to_add(last, first);
				
				//Read in data for contact methods.
				//Each person has three contact methods
				for(int i=0; i < 3; ++i)
				{
					inFile.get(title, 21, ':');
					inFile.ignore();
						
					inFile.get(des, 21, ':');		
					inFile.ignore();

					inFile >> r;
					inFile.ignore(100, '\n');

					contact c(title, des, r);

					to_add.addContact(c);

				}

				//Once the person has all their contact
				//methods added, add the person to the BST
				if(addPerson(to_add))
					++total;

			}	
		}

		inFile.close();
		return total;
	}


}





//Public member function to remove a person from
//the BST pointed to by *root. Takes as an argument
//a person object, from which the first and last
//name will be utilizied to help find the person
//to remove. Returns true if person was found and
//removed suceessfully.
bool EBC::removePerson(person &to_remove)
{
	node *parent = root;
	node *child = root;
	return removePerson(parent, child, to_remove);
}



//Private member function that performs the traversal
//and removal of the targeted person object. If the 
//person in question is the sole member of a node then
//the entire node will be removed. However, if the node
//still has other people with the same last name, then
//just the person in question will be removed and the node
//will remain. Returns true if the targeted person was found
//and removed.
bool EBC::removePerson(node* &parent, node* &child, person &to_remove)
{
	if(!child)
		return false;

	char *nName = NULL;
	char *pName = NULL;
	int result;

	//Get the last name associated with the child node	
	child -> retrieveName(nName);

	//Get the last name of the person to be removed
	to_remove.retrieveLast(pName);

	//compare last names. Once the names are compared.
	//there's no longer a need to the nName and pName pointers...
	//might as well get rid of them now since we're only concerened
	//with the result.
	result = strcmp(pName, nName);
	delete nName;
	delete pName;
	nName = pName = NULL;

	//Person's last name matches node name
	if(result == 0)
	{
		node *target = child;
		char *fName = NULL;
		to_remove.retrieveFirst(fName);

		//Remove the person from the LLL in each
		//Node class obj.
		if(!child -> removePerson(fName))
			return false;
		
		delete []fName;
		fName = NULL;

		//If the list is not empty, there are more people
		//with the same last name, however the correct person
		//has still been removed from the list....keep the node.
		if(!child -> emptyList())
			return true;

		//Otherwise, the node does have an empty person LLL, if the
		//list is empty, then no more people with that last name exist.
		//Time to remove the node.

		//Deleting leaf
		if(child -> isLeaf())
		{
			if(parent -> isLeft(child))
			{
				delete target;
				target = NULL;
				parent -> setLeft(target);
			}

			else
			{
				delete target;
				target = NULL;
				parent -> setRight(target);
			}

			return true;	
		}


		//there is only a right child
		else if(child -> hasRight() && !child -> hasLeft())
		{

			if(parent -> isLeft(child))
			{
				child -> moveRight(child);
				parent -> setLeft(child);
				
				delete target;
				target = NULL;
			}

			
			else
			{
				child -> moveRight(child);
				parent -> setRight(child);
	
				delete target;
				target = NULL;
			}

			return true;
		}	

		
		//there is only a left child
		else if(child -> hasLeft() && !child -> hasRight())
		{

			if(parent -> isLeft(child))
			{
				child -> moveLeft(child);
				parent -> setLeft(child);
				
				delete target;
				target = NULL;
			}

			
			else
			{
				child -> moveLeft(child);
				parent -> setRight(child);
	
				delete target;
				target = NULL;
			}

			return true;	
		}

		//child has two children....This is where iosHelper...helps!
		else
		{
		
			node *iosParent = parent;
			node *iosChild = child;
			iosHelper(iosParent, iosChild, child); 
			return true;
		}
	}

	//Need to move left
	if(result < 0)	
	{
		parent = child;
		child -> moveLeft(child);
		return removePerson(parent, child, to_remove);
	}

	//Need to move right
	else
	{
		parent = child;
		child -> moveRight(child);
		return removePerson(parent, child, to_remove);
	}
}





//iosHelper...Child will point to IOS, parent points to parent
//of IOS, ancestor points to the original node targeted for removal. Data
//is to be copied from the child, into the ancestor. then the child is
//either deleted if it is a leaf, or its right subtree is inherited.
void EBC::iosHelper(node* &parent, node* &child, node* &ancestor)
{
	child -> moveRight(child);

	//Move child to the left most node	
	while(child -> hasLeft())
	{
		parent = child;
		child -> moveLeft(child);
	}

	//copy the person list at the left most node

	person *_head = NULL;
	child -> _pth(_head);

	if(!ancestor -> copyList(_head))
		cout << "Error copying list" << endl;




	//delete or replace the left most node

	//there is a right child to the IOS
	if(child -> hasRight())
	{
       		node *temp = child;
        	temp -> moveRight(temp);

        	parent -> setRight(temp);

        	delete child;
        	child = NULL;
	}

	//IOS is leaf
	else
	{
        	delete child;
        	parent -> setLeft(child);
	}
}




//Public wrapper function to find a person by name.
//If the person is found, the person's data will be
//displayed (their name, and contact list). Function
//is void because a message will be displayed (via a
//node class method) regardless of the person being
//found. Takes as an argument a name class object.
void EBC::findPerson(name &to_find)
{
	node *current = root;
	findPerson(current, to_find);
}



//Public wrapper function to find a person by name.
//If the person is found, the person's data will be
//displayed (their name, and contact list). Function
//is void because a message will be displayed (via a
//node class method) regardless of the person being
//found. Takes as an argument a char array for the 
//last and first name of the person to search for.
void EBC::findPerson(char last[], char first[])
{
	node *current = root;
	name to_find(last, first);
	findPerson(current, to_find);
}



//Private member function to find a person in the BST tree
//pointed to by *root. Funciton will output a message even
//if the person is not found, hence the void return type.
void EBC::findPerson(node* &current, name &target)
{
	if(!current)
		cout << "\n\nPerson could not be found!" << endl;

	else
	{
		char *last = NULL;
		char *nLast = NULL;
		int result;

		current -> retrieveName(nLast);	//get name associated with node object.
		target.retrieveLast(last);	//get last name for the person to be located.
		result  = strcmp(last, nLast);	//compare the two.


		//After the comparison, we no longer need the data pointed to by
		//last and nLast....might as well get rid of it since we're only
		//concerned with the result of the comparison.
		delete last;
		delete nLast;
		last = nLast = NULL;

		//Current node has targeted last name
		if(result == 0)
		{
			//search node for person....
			char *first = NULL;
			target.retrieveFirst(first);	//get first name of the target to be located.
			current -> findPerson(first);	//pass the first name to the current node and search.
			
			delete first;
			first = NULL;
		}

		//Targeted last name is less than current node's data
		else if(result < 0)
		{
			current -> moveLeft(current);
			findPerson(current, target);
		}

		//Targeted last name is greater than current node's data
		else
		{
			current -> moveRight(current);
			findPerson(current, target);
		}
	}
}
