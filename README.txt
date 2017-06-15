README


System & Compiler:
	- Linux, C++ standard 98 using GNU GCC C++ (g++) compiler


Program abstract:
	- Create an emergency broadcast system application. The application will
	build a contact tree that has the top three methods that each individual
	can be contacted by (home phone, cell, work, twitter, etc.).

	- The contact tree will be implimented as a binary search tree organized
	by last name where each node in the tree is a linear linked list of everyone
	with the same last name, sorted by first name. 

	- The program will support operations to insert, remove, display individuals
	to the contact tree.

	- The primary purpose of the program is to illustrate the use of operator
	overloading in inheritance hierarchies. The program does not use dynamic
	binding.


	For a more detailed explanation of the structure of the program, see the Program3_design.pdf document.


Running the program:
	To run the program simply type "make", then ./ebcApp. Once you're done,
	you can delete the object files and the executable by running "make clean"

