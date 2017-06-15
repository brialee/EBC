//Brian Lee
//CS202 - Fant
//Program 3

//Header file for the name class. Included in this header file are the 
//declarations for the name, person and contact classes. A person is publicly
//derived from a name class (since each person has a name, plus more!). Each
//person also has three contact methods.


#include <cstring>
#include <iostream>
using namespace std;

const int MAX = 3;	//size of the contact array that each person has



//The name class manages only the first and last name for a person.
class name
{
	public:
		name();	//default constructor
		name(const name&);	//copy constructor
		name(char [], char []);	//constructor with arguments for last, first name.
		~name();	//destructor


		//Overloaded Operators

		//POSTCON: calling name object will have data matching right operand
		name& operator = (const name&);	

		//OUTPUT: displays a person's first and last name
		friend ostream& operator << (ostream &, const name &);

		//INPUT: A name class object that will be compared with the left operand
		//OUTPUT: Returns true if both the first and last name are equal in ASCII values
		bool operator==(const name&);


		//INPUT: A name class object that will be compared with the left operand.
		//OUTPUT: Returns true if the left operand is less than the right operand,
		//in terms of ASCII values.
		bool operator<(const name&);


				
		//INPUT: A name class object that will be compared with the left operand.
		//OUTPUT: Returns true if the left operand is greater than the right operand,
		//in terms of ASCII values.
		bool operator>(const name&);


		
		//INPUT: A name class object that will be compared with the left operand.
		//OUTPUT: Returns true if the left operand is not equal to the right operand,
		//in terms of ASCII values.
		bool operator !=(const name&);


		//INPUT: A name object that will be compared with the calling name object.
		//OUTPUT: Returns the value of strcmp(calling first name, argument first name).
		int compareFirst(name&);

		
		//INPUT: Pointer to a char (array).
		//POSTCON: Passsed pointer will point to the first item in a char array
		//that has matching data as the last name for the object that called the function.	
		void retrieveLast(char* &);

	
		
		//INPUT: Pointer to a char (array).
		//POSTCON: Passsed pointer will point to the first item in a char array
		//that has matching data as the first name for the object that called the function.	
		void retrieveFirst(char* &);


	protected:
		char *first;	//first name
		char *last;	//last name


};


//The person class is derived from the name class since all
//people have names (except for that time Prince changed his name to a symbol).
//Each person has a contact tree that stores a tree of contact methods organized
//by priority of a contact method.
class person : public name
{
	public:
		person();	//default constructor
		person(const person &);	//copy constructor
		person(char [], char []); //constructor with arguments for last, first name
		~person();	//destructor

		//OVERLOADED OPERATORS 


		//POSTCON: Displays the first and last name of the person
		friend ostream& operator << (ostream&, const person&);


		//person& operator = (const person&);	//Should only copy name data and contact list
							//but not copy the data pointed to by *next


		//PERTAINING TO THE PERSON

		//INPUT: Pointer to a person class object
		//POSTCON: Calling person object will have next pointer set to point
		//to passed person object. 
		void setNext(person* &);

	
		//POSTCON: Returns true if the calling person object has non-NULL
		//next pointer.
		bool hasNext(void);

		
		//INPUT:A person class object.
		//POSTCON: The passed person object will end up being a reference to its'
		//next person object.
		void moveNext(person* &);

	

		//MANAGING THE CONTACT LIST

		//INPUT: A contact class object and an integer for the rank of the contact method.
		//POSTCON: Returns true if the contact method was added to the array for a person
		bool addContact(class contact &);


		//OUTPUT: Displays all contact methods for a given person
		void contactList();


	protected:
		person *next;	//pointer to next person 
		class contact *contactArry;	//pointer to array of contact methods with array size MAX

};





//Contact class manages data for an single method of contact.
//An single method of contact can be ranked by priority with the
//use of the int rank data member. 1 being first method of contact.
//To discourage the creation of contact specific classes (phone, cell, email, etc.)
//a contact class is able to accommodate any contact method (for storage purposes)
//by simply proving a title and description of the contact method.
class contact
{
	public:
		contact();	//default constructor
		contact(const contact &);	//copy constructor
		contact(char [], char [], int);	//constructor with arguments for title, description, rank
		~contact();	//destructor

		//OVERLOADED OPERATORS

		//INPUT: Contact object to be copied into left operand
		//POSTCON: Left operand will have data matching right operand
		contact& operator = (const contact&);


		//OUTPUT: Displays a method of contact
		friend ostream& operator << (ostream&, const contact&);

		

		//PERTAINING TO THE CONTACT ITSELF

		int getRank(void);



	protected:
		char *title;	//title for a contact method
		char *description;	//description of contact method
		int rank;	//rank of method

};
