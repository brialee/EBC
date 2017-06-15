//Brian Lee
//CS202 - Fant
//Program3

//Header file for the node class. A node contains a LLL of persons with the same
//last name, as well as pointers to left and right nodes (as the node class is 
//intended to be used as a BST node). Additionally, each node has a last name
//data member that indicates the last name for the duplicates in the LLL pointed
//to by *head.



#include "name.h"


class node
{
	public:
		node();	//default constructor
		node(const node&);	//copy constructor
		~node();	//destructor

		//OVERLOADED OPERATORS

		//POSTCON: The left operand will have data matching the right operand,
		//however only the name and LLL info is copied. The right and left pointers
		//will remain NULL.
		node& operator=(const node&);


		//POSTCON: If the left operand is less than the first operand, in terms of
		//comparing the ASCII values for the *name data, the function will return true.
		bool operator<(const node&);


		//POSTCON: If the right operand less than the first operand, in terms of
		//comparing the ASCII values for the *name data, the function will return true.
		bool operator>(const node&);


		//OUTPUT: Displays the name associated with a node and the number of person
		//nodes pointed to by *head.
		friend ostream& operator << (ostream &, const node&);

		//MANAGING THE LLL	

		
		//INPUT: A person object that will be added to the LLL pointed
		//to by *head.
		//POSTCON: Returns true if the person was added to the LLL...this
		//function will always return true.
		bool addPerson(person &);


		//OUTPUT: Displays the names of all persons in the LLL
		void displayList();


		//INPUT: A pointer to a char array/
		//POSTCON: The passed pointer will pointed to the first char in an array
		//with data matching the name data of the calling node object.
		void retrieveName(char* &);


		//INPUT: The first name of a person to be removed from LLL.
		//OUTPUT: Returns true if the person was found and removed.
		//POSTCON: If found, the person will be removed.
		bool removePerson(char []);


		//INPUT: The first name of a person to be searched for in the LLL.
		//OUTPUT: A message displaying the status of the search, if the person is 
		//found their data will be displayed.
		void findPerson(char []);


		//OUTPUT: Returns true if *head points to NULL
		bool emptyList();


		//INPUT: Pointer to a person object.
		//POSTCON: pointer will point to the head of the LLL. (_PointToHead).
		void _pth(person* &);


		
		bool copyList(person* &);	//copies invoking node's list into the passed node's list


		//INPUT: Pointer to a person object to be added to LLL.
		//POSTCON: Person will be added to the LLL pointed to by *head.
		//This function will always return true.
		bool addPerson(person* &);

		//PERTAINING TO LEFT/RIGHT NODE POINTERS

		//INPUT: pointer to a node object.
		//POSTCON: Passed pointer now points to the arguments *left pointer.
		void moveLeft(node* &);


		//INPUT: pointer to a node object.
		//POSTCON: Passed pointer now points to the arguments *right pointer.
		void moveRight(node* &);


		//OUTPUT: Returns true if the calling node object has a non-NULL left pointer.
		bool hasLeft();


		//OUTPUT: Returns true if the calling node object has a non-NULL right pointer.
		bool hasRight();


		//INPUT: pointer to a node object.
		//OUTPUT: Returns true if the calling object's left pointer and the passed pointer
		//are pointed to the same object.
		bool isLeft(node* &);


		
		//INPUT: pointer to a node object.
		//OUTPUT: Returns true if the calling object's right pointer and the passed pointer
		//are pointed to the same object.
		bool isRight(node* &);


		//INPUT: Pointer to a node class object.
		//POSTCON: Calling node object will have its' *right pointer point to the passed node	
		void setRight(node* &);


		
		//INPUT: Pointer to a node class object.
		//POSTCON: Calling node object will have its' *left pointer point to the passed node	
		void setLeft(node* &);


		//OUTPUT: Returns true if the calling node object has NULL left and right pointers.
		bool isLeaf();

		//Testing
		void test(node &);


	protected:
		char *name;	//last name associated with node
		node *left;	//pointer to left node
		node *right;	//pointer to right node
		person *head;	//points to the head of the LLL of persons with the same last name
		int length;	//how many nodes are in the LLL?
	

	private:

		//INPUT: Pointers to persons "previous", "current", and a "person to add" object.
		//POSTCON: Returns true if the person was added to the LLL
		bool addPerson(person* &, person* &, person &);

		//INPUT: Pointer to a person class object (ideally, head)
		//POSTCON: All nodes in LLL pointed to by passed argument will 
		//be deleted.
		void deallocate(person* &);

		//INPUT: Pointers to a "previous", "current" person objects, and first name of person to be removed.
		//POSTCON: Returns true if the person was found in LLL and successfully removed.
		bool removePerson(person* &, person* &, char []);

		//INPUT: Pointer to "current" person (ideally head on first invocation), and the first name of
		//the person to find.
		//OUTPUT: Displays a message indicating the status of the function call, i.e. Were they found?
		void findPerson(person* &, char []);

}; 
