//Brian Lee
//CS202 - Fant
//Program 3


//Implementation file for the name header. Included in the name header
//are declarations for the following classes: name, person (publicly derived from
//name), and contact (which each person has three of).



#include "name.h"



//---------------- NAME CLASS ---------


//Default constructor
name::name() : first(NULL), last(NULL)
{}



//Copy Constructor, copies only the first and last name
name::name(const name &to_copy)
{
	first = new char[strlen(to_copy.first) +1];
	strcpy(first, to_copy.first);

	last = new char[strlen(to_copy.last) +1];
	strcpy(last, to_copy.last);
}



//Constructor with arguments for the first
//and last names.
name::name(char l[], char f[])
{
	last = new char[strlen(l) +1];
	strcpy(last, l);

	first = new char[strlen(f) +1];
	strcpy(first, f);
}




//Destructor
name::~name()
{
	delete []first;
	delete []last;

	first = last = NULL;
}



//Overloaded assignment operator that copies data into
//a presumably empty name class object.
name& name::operator = (const name &n)
{
	if(this == &n)
		return *this;

	else
	{
		first = new char[strlen(n.first) +1];
		strcpy(first, n.first);

		last = new char[strlen(n.last) +1];
		strcpy(last, n.last);

		return *this;
	}
}




//Overloaded extraction operator that outputs the
//first and last name.
ostream & operator << (ostream &out, const name &n)
{
	out << n.first << " " << n.last;
	return out;
}




//Returns true if both operands have an identical
//first and last name in terms of ASCII values.
bool name::operator == (const name &b)
{
	if(strcmp(first, b.first) == 0
		&& strcmp(last, b.last) == 0)
		return true;

	else
		return false;
}





//Returns true if the first operand has a last
//name that is lower than the second operand's last
//name in terms of ACSII value.
bool name::operator < (const name &n)
{
	if(strcmp(last, n.last) < 0)
		return true;

	else
		return false;
}



//Returns true if the first operand has a last
//name higher than the second operand's, in terms of
//ASCII values.
bool name::operator > (const name &n)
{
	if(strcmp(last, n.last) > 0)
		return true;

	else
		return false;

}



//Returns the boolean opposite of overloaded == operator
bool name::operator != (const name &n)
{
	return !operator==(n);
}




//Compares the first names of two name class
//objects. Basically a wrapper for stcmp between
//two first names. Returns true if comparison 
// == 0.
int name::compareFirst(name &n)
{
	char *f = NULL;
	n.retrieveFirst(f);

	cout << "Comparing:" << first << endl;
	cout << "with...." << n.first << endl;
	//return strcmp(first, n.first);
	return strcmp(first, f);
}



//Retrieves the last name of a person or
//name class object. Takes as an argument
//a pointer to a char. The passed pointer
//will point to an array with the last name
//as a result of calling the function.
void name::retrieveLast(char* &ptr)
{
	ptr = new char[strlen(last) +1];
	strcpy(ptr, last);
}



//Retrieves the first name of a person or
//name class object. Takes as an argument
//a pointer to a char. The passed pointer
//will point to an array with the first name
//as a result of calling the function.
void name::retrieveFirst(char* &ptr)
{
	ptr = new char[strlen(first) +1];
	strcpy(ptr, first);
}






//-------------------- PERSON CLASS ------------

//Default constructor
person::person() : name() , next(NULL)
{
	contactArry = new contact[MAX];
	
}



//Copy Constructor	
person::person(const person &to_copy) : name(to_copy.last, to_copy.first)
{
	contactArry = new contact[MAX];

	for(int i=0; i < MAX; ++i)
		contactArry[i] = to_copy.contactArry[i];

}



//Constructor with arguments for
//first and last name.
person::person(char last[], char first[]) : name(last, first), next(NULL)
{
	contactArry = new contact[MAX];
} 



//Destructor
person::~person()
{
	next = NULL;
	delete []contactArry;	
}



//Overloaded extraction operator that acts
//as a display function. Outputs the first and
//last name of the person.
ostream & operator << (ostream &out, const person &p)
{

	const name &n(p);
	out << n;
	return out;
}




//Sets the *next pointer to point
//to the passed person node. If the
//passed node is NULL, the next pointer
//will be set to NULL.
void person::setNext(person* &ptr)
{
	if(!ptr)
		next = NULL;

	else
		next = ptr;
}



//Returns true if the calling person
//has a non NULL next pointer. Otherwise
//the function will return true.
bool person::hasNext()
{
	if(!next)
		return false;

	else
		return true;

}



//Takes the person node passed as an argument
//and sets it to point to its' next pointer, regardless
//if the next pointer to NULL or not.
void person::moveNext(person* &ptr)
{
	if(ptr -> hasNext())
		ptr = ptr -> next;
	
	else
		ptr = NULL;
}



//Adds a contact to the contactArry, which holds
//a person's three method of contact. When a method
//is added to the array, it will be added in position
//argument - 1, and replace any exisiting contact 
//method already in place.
bool person::addContact(contact &to_add)
{
	int r = to_add.getRank();
	contactArry[r-1] = to_add;
	return true;
}




//Displays all three contact methods for a
//person object. 
void person::contactList()
{
	for(int i=0; i < MAX; ++i)
		cout << contactArry[i] << endl;
}






//-------------- CONTACT CLASS --------

//Default Constructor
contact::contact() : title(NULL), description(NULL), rank(0)
{}



//Copy Constructor
contact::contact(const contact &to_copy)
{
	title = new char[strlen(to_copy.title) +1];
	strcpy(title, to_copy.title);
		
	description = new char[strlen(to_copy.description) +1];
	strcpy(description, to_copy.description);

	rank = to_copy.rank;

}



//Constructor with arguments for a title, decription
//and integer for rank or priority.
contact::contact(char t[], char d[], int r)
{
	title = new char[strlen(t) +1];
	strcpy(title, t);
		
	description = new char[strlen(d) +1];
	strcpy(description, d);

	rank = r;
}



//Destructor
contact::~contact()
{
	delete []title;
	delete []description;

	title = description = NULL;
}


//Overloaded Assignment Operator
contact& contact::operator = (const contact &to_copy)
{
	if(this == &to_copy)
		return *this;

	//When copying an array, if a contact method is empty,
	//then don't perform the copy operation.
	if(to_copy.title == NULL)
		return *this;

	else
	{
		title = new char[strlen(to_copy.title) +1];
		strcpy(title, to_copy.title);
		
		description = new char[strlen(to_copy.description) +1];
		strcpy(description, to_copy.description);

		rank = to_copy.rank;
		return *this;
	}
}



//Overloaded extraction operator, used to display
//a contact's data
ostream & operator << (ostream &out, const contact &con)
{
	if(con.title == NULL)
		out << "Empty Contact Method....";

	else
		out << "Priority: " << con.rank << " --Type: "	<< con.title << "----Details: " << con.description;
	
	return out;

}



//Returns the rank of the contact.
int contact::getRank()
{
	return rank;
}
