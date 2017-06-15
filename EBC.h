//Brian Lee
//CS202 - Fant
//Program 3


//Electronic Broadcast System class header file. A EBC object has a BST that
//stores all the nodes (an object that holds persons with the same last name)
//for a given EBC class. The intent of the EBC class is that a client application
//could have an emergency broadcast system for a particular zipcode, city,
//neighborhood, etc. 


#include "node.h"
#include "fstream"

class EBC
{
	public:
		EBC();	//default constructor
		EBC(const EBC&);	//copy constructor
		~EBC();	//destructor


		//INPUT: A person class object to be added to the BST
		//POSTCON: Returns true if the passed person object was
		//successfully added to the BST pointed to by *root
		bool addPerson(person &);


		//INPUT:A person class object to be removed from BST
		//POSTCON: Returns true if the passed person was found in the
		//BST and successfully removed from the tree.
		bool removePerson(person &);

		
		//INPUT: The last and first name of a person to be searched for.
		//OUTOUT: If the person is found, their data will be displayed,
		//otherwise a message indicating the person could not be found
		//is displayed.
		void findPerson(char [], char []);

		//INPUT: Name class object.
		//OUTPUT: Same as the above function.
		void findPerson(name &);

		//OUTPUT: Displays the tree data alphabetically from A-Z
		//....(in order traversal)
		void displayList();



		//OUTPUT: The number of items read from an external text file which
		//were subsequently added to the BST pointed to by *root.
		//POSTCON: *root will point to a BST populated with data from
		//an external text file.		
		int read();

	private:
		node *root;	//points to BST

		
		//INPUT: Pointers to nodes "previous", "current", and a person
		//class object to be added to the BST.
		//POSTCON: Returns true if the person was added to the tree.
		bool addNode(node* &, node* &, person &);


		//INPUT: Node object that points to *root of a BST.
		//OUTPUT: Returns the total number of nodes that were displayed
		//during in order traversal.
		int inOrder(node* &);


		//INPUT: Pointers to nodes "previous". "current", and a person
		//object with data matching the person to be removed.
		//POSTCON: Returns true if the person to be removed was found in the
		//BST and was successfully removed.
		bool removePerson(node* &, node* &, person &);

		
		//INPUT: A pointer to the root of a BST, and the name of the person to be
		//searched for.
		//POSTCON: If the person is found, their data will be displayed. Otherwise a
		//message indicating the person could not be found will be displayed.
		void findPerson(node* &, name &);


		//INPUT: A pointer to nodes "previous", "current", and "ancestor"
		void iosHelper(node* &, node* &, node* &); 	

        void deallocate(node* &);

};

