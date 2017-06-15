//Brian Lee
//CS202 - Fant
//Program 3



//Main file for program3 to illustrate what the program can do. When the user
//is presented with a menu, the BST will have already been populated from
//an external text file. 

#include "EBC.h"

using namespace std;

void msg();	//greets user
int menu();	//present user with menu options


int main()
{
	EBC beaverton;
	int total = beaverton.read();
	bool exit = false;	
	int num;
	int size = 31;

		

	cout << total << " names read from file.\n\n\n\n\n" << endl;
	msg();

	do
	{
		num = menu();

		//View List
		if(num == 1)
		{
			cout << "\nTotal: ";
			beaverton.displayList();
		}	


		//Search
		if(num == 2)
		{
			char *first = new char[size];
			char *last = new char[size];


			cout << "Enter first name: ";
			cin.get(first, size, '\n');
			cin.ignore(100, '\n');

			cout << "Enter last name: ";
			cin.get(last, size, '\n');

			beaverton.findPerson(last, first);
			delete []first;
			delete []last;
			first = last = NULL;
			
		}


		//Remove Person
		if(num == 3)
		{
			
			char *first = new char[size];
			char *last = new char[size];


			cout << "Enter first name: ";
			cin.get(first, size, '\n');
			cin.ignore(100, '\n');

			cout << "Enter last name: ";
			cin.get(last, size, '\n');
			
			person to_remove(last, first);

			if(beaverton.removePerson(to_remove))
				cout << "Person was found and removed." << endl;

			else
				cout << "Person was not found." << endl;

			delete []first;
			delete []last;
			first = last = NULL;
		}


		//Add a person
		if(num == 4)
		{
			
			char *first = new char[size];
			char *last = new char[size];
			int r, n;



			cout << "Enter first name: ";
			cin.get(first, size, '\n');
			cin.ignore(100, '\n');

			cout << "Enter last name: ";
			cin.get(last, size, '\n');
			
			person to_add(last, first);
			cout << "How many contact methods to add: ";
			cin >> n;

			if(n > 3)
				cout << "Don't be greedy...You get three!" << endl;


			delete []first;
			delete []last;
            		first = last = NULL;

			for(int i=0; i < n; ++i)
			{
                
			    char *title = new char[size];
			    char *des = new char[size];
            
				cout << "Enter contact title: ";
				cin.get(title, size, '\n');
				cin.ignore(100, '\n');
				
				cout << "Enter Description: ";
				cin.get(des, size, '\n');
				cin.ignore(100, '\n');

				cout << "Enter Priority: ";
				cin >> r;
				cin.ignore(100, '\n');
			
				contact c(title, des, r);
				if(!to_add.addContact(c))
					cout << "Failed to add contact." << endl;

				delete []title;
				delete []des;	

                		des = title = NULL;
			}

            if(!beaverton.addPerson(to_add))
                    cout << "\n\nFailed to add person\n" << endl;
		}



		//exit
		if(num == 5)
			exit = true;

			
		//invalid choice
	    if(num < 1 || num > 5)	
			cout << "\n\n INVALID SELECTION \n\n" << endl;	


	} while(!exit);

    cout << "Good Bye" << endl;
	return 0;
}


// FUNCTION BODIES

//Informs the user about the program.
void msg(void)
{
	cout << "\n";
    cout << "EMERGENCY BROADCAST SYSTEM application. Below you will be\n";
    cout << "presented with a menu of choices.\n\n" << endl;
}


//Displays a menu of choices for the
//user to select from. Returns the
//user's choice.
int menu(void)
{
	int n;

	cout << "\n";
	cout << "Choose from the options below:\n";
	cout << "1 - View List\n";
	cout << "2 - Search\n";
	cout << "3 - Remove A Person\n";
	cout << "4 - Add A Person\n";
	cout << "5 - Exit\n";
	cout << "------------------------\n";
	cout << "Enter Selection: ";
	cin >> n;
	cin.ignore(100,'\n');
	return n;
}
