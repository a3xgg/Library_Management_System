#ifndef PATRON //FILE GUARDS REFER: https://www.youtube.com/watch?v=RU5JUHAiR18
#define PATRON

#pragma warning(disable : 4996) //REFER: https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-3-c4996?f1url=https%3A%2F%2Fmsdn.microsoft.com%2Fquery%2Fdev16.query%3FappId%3DDev16IDEF1%26l%3DEN-US%26k%3Dk(C4996)%26rd%3Dtrue&view=vs-2019

#include <string>
#include <iostream>
#include <ctime>
#include "Book.h"
#include "CustomDate.h"

using namespace book;
using namespace std;
using namespace date;

namespace patron
{
	class Patron
	{
	public:
		Date *dateOfBirth;
		BookInformation *patronBookList;
		Patron *linkToNextPatron;
		char *registeredDate;
		string patronID, firstName, lastName;
		char gender;
		Patron() {}
		Patron(string patronID, string firstName, string lastName, char gender, Date *dob, Patron *linkToNextPatron, BookInformation *patronBookList)
		{
			this->patronID = patronID;
			this->firstName = firstName;
			this->lastName = lastName;
			this->gender = gender;
			this->dateOfBirth = dob;
			this->linkToNextPatron = linkToNextPatron;
			this->patronBookList = patronBookList;
			time_t currentDateTime = time(0);
			this->registeredDate = (ctime(&currentDateTime));
		}
	};

	//FUNCTION PROTOTYPES
	int getSize(Patron *&head);
	void promptNewPatron(Patron *&);
	void promptUpdate(Patron *&);
	void insertPatron(Patron *&head, Patron *newPatron);
	void searchPatron(Patron *&head);
	void updatePatron(Patron *&, string, int);
	string generateID(Patron *&patronHead);
	bool printPatronDetails(Patron *patron);
	void viewPatron(Patron *&head);
	void viewPatronBookList(Patron *&);
	bool checkBookLimit(Patron *);
	void borrowBook(Patron *&, BookTitle *&);
	void viewPatronWithActiveBook(Patron *&);
	void returnBook(Patron *&, BookTitle *&);

	/*
		RETURN BOOK FUNCTION
		- A function that allows an admin to return a book when a patron request for it.
		- If an admin tries to return a book but the patron does not have any active book, it will just print an error message
		- Takes two parameters, patron head and library books head
		- The patron head is to find the specified patron while the book head is to locate the borrowed book (comparing to patron book list)
	*/
	void returnBook(Patron *&patronHead, BookTitle *&libraryBooks)
	{
		system("CLS");
		if (patronHead == NULL || libraryBooks == NULL)
		{
			cout << "Patron or Library List is empty" << endl;
		}
		else
		{
			string patronInfo, bookID;
			viewPatron(patronHead);
			cout << "Enter Patron ID or Full Name to return book: ";
			cin.ignore();
			getline(cin, patronInfo);

			Patron *pointerToPatronHead = patronHead;
			while (pointerToPatronHead != NULL)
			{ /* Loops through the Patron Linked List to find the specified Patron*/
				string concat = pointerToPatronHead->firstName + " " + pointerToPatronHead->lastName;
				if (patronInfo == pointerToPatronHead->patronID || patronInfo == concat)
				{ /* Checks whether the Patron exist - If exist it will break the while loop - Else continue loop*/
					Patron *foundPatron = pointerToPatronHead;
					if (foundPatron->patronBookList == NULL)
					{
						cout << "\n"
							 << foundPatron->firstName << " " << foundPatron->lastName << " does not have any book(s) borrowed yet!\n"
							 << endl;
					}
					else
					{
						system("CLS");
						/* Get Local PC Date and Time*/
						time_t localComputerTimeInSeconds = time(0);

						int counter = 0;
						BookInformation *foundPatronBookList = foundPatron->patronBookList;
						cout << foundPatron->firstName << " " << foundPatron->lastName << " borrowed book(s)\n"
							 << endl;
						cout << "Book ID\t\tBook Title\t\tBorrowed Date\t\tReturn Date" << endl;
						/* Checks the top 3 Nodes of the patron book list to check for active books */
						while (foundPatronBookList != NULL)
						{
							if (counter > 3)
							{
								break;
							}
							/* Set book returnDate into timestamp - https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm */
							tm *bookReturnDateToTimestamp = localtime(&localComputerTimeInSeconds);
							bookReturnDateToTimestamp->tm_year = foundPatronBookList->returnDate->year - 1900;
							bookReturnDateToTimestamp->tm_mon = foundPatronBookList->returnDate->month - 1;
							bookReturnDateToTimestamp->tm_mday = foundPatronBookList->returnDate->day;
							/* Convert into timestamp */
							time_t convertedReturnDate = mktime(bookReturnDateToTimestamp);
							/* Compares the current PC time with converted returnDate*/
							if (localComputerTimeInSeconds < convertedReturnDate)
							{
								cout << foundPatronBookList->bookID << "\t\t" << foundPatronBookList->bookTitle << "\t\t" << foundPatronBookList->borrowedDate->day << "/" << foundPatronBookList->borrowedDate->month << "/" << foundPatronBookList->borrowedDate->year << "\t\t" << foundPatronBookList->returnDate->day << "/" << foundPatronBookList->returnDate->month << "/" << foundPatronBookList->returnDate->year << endl;
								counter += 1;
							}
							else
							{
								counter += 1;
							}
							foundPatronBookList = foundPatronBookList->nextBookInventory;
						}

						/* Prompt book to return */
						cout << "\nWhich book does " << foundPatron->firstName << " " << foundPatron->lastName << " want to return?: " << endl;
						cout << "\nBook ID: ";
						cin >> bookID;

						/* Loop through the Patron's book list to find specified book id*/
						BookInformation *bookList = foundPatron->patronBookList;
						while (bookList != NULL)
						{
							if (bookID == bookList->bookID)
							{
								BookInformation *toReturn = bookList;
								/* Get current local PC time*/
								tm *ltime = localtime(&localComputerTimeInSeconds);
								/* new Date class created - to be inserted into toReturn */
								Date *returnedDate = new Date(ltime->tm_mday, ltime->tm_mon + 1, ltime->tm_year + 1900);
								/* Changes made to Patron Book List */
								/* Set the returnDate field to when the Patron returned the book */
								toReturn->returnDate = returnedDate;
								/* No longer available to the user */
								toReturn->bookAvailability = false;
								/*move to last node - depending on the position*/
								if (foundPatron->patronBookList->nextBookInventory != NULL)
								{

									int position = 0; /* Get the position of the toReturn Node to be used to move the node to the last position of the book list */
									BookInformation *bookPointer = foundPatron->patronBookList;
									while (bookPointer != NULL)
									{
										if (position > 3)
										{
											break;
										}
										if (bookPointer->bookID == toReturn->bookID)
										{
											position += 1;
											break;
										}
										position += 1;
										bookPointer = bookPointer->nextBookInventory;
									}

									/* Switch case - to move the return book node to last node position depending on the position */
									switch (position)
									{
									case 1:
									{
										foundPatron->patronBookList = toReturn->nextBookInventory; /* Pointing to the next book of the first node */
										toReturn->nextBookInventory = NULL;
										BookInformation *traverse = foundPatron->patronBookList;
										while (traverse->nextBookInventory != NULL)
										{
											traverse = traverse->nextBookInventory;
										}
										traverse->nextBookInventory = toReturn;
									}
									break;
									case 2:
									{
										foundPatron->patronBookList->nextBookInventory = toReturn->nextBookInventory;
										toReturn->nextBookInventory = NULL;
										BookInformation *traverse = foundPatron->patronBookList;
										while (traverse->nextBookInventory != NULL)
										{
											traverse = traverse->nextBookInventory;
										}
										traverse->nextBookInventory = toReturn;
									}
									break;
									case 3:
									{
										foundPatron->patronBookList->nextBookInventory->nextBookInventory = toReturn->nextBookInventory;
										toReturn->nextBookInventory = NULL;
										BookInformation *traverse = foundPatron->patronBookList;
										while (traverse->nextBookInventory != NULL)
										{
											traverse = traverse->nextBookInventory;
										}
										traverse->nextBookInventory = toReturn;
									}
									break;
									}
								}

								/* Changes made to Books Library */
								BookTitle *currentRowPointer = libraryBooks;
								string mainID = bookID.substr(0, 7); //GETS THE VALUE BK10001
								while (currentRowPointer != NULL)	 /* First While Loop - traverse the Vertical Book List*/
								{
									if (mainID == currentRowPointer->bookInfo->bookID) /* Checks whether the main id (BK1000X) is equal to the current row pointer ID */
									{
										BookInformation *currentBookColumn = currentRowPointer->bookInfo;
										while (currentBookColumn != NULL) /* Second While Loop - traverse the Horizontal Book List */
										{
											if ((bookID == currentBookColumn->bookID)) /* This compares the USER INPUT to the current column book ID */
											{
												BookInformation *toEdit = currentBookColumn;
												toEdit->bookAvailability = true;
												cout << "Book " << toEdit->bookTitle << " with Book ID " << toEdit->bookID << " has been returned!" << endl;
												break;
											}
											currentBookColumn = currentBookColumn->nextBookInventory;
										}
										break;
									}
									currentRowPointer = currentRowPointer->nextBookTitle;
								}
								break;
							}
							bookList = bookList->nextBookInventory;
						}
					}
					break;
				}
				pointerToPatronHead = pointerToPatronHead->linkToNextPatron;
			}
		}
	}

	/*
		VIEW PATRON WITH ACTIVE BOOK
		- This function check the top 3 node of a patron's book list
		- If any of this books are active, it will print the patron details and latest borrowed book (top node)
	*/
	void viewPatronWithActiveBook(Patron *&patronHead)
	{
		system("CLS");
		/* GET CURRENT LOCAL PC DATE AND TIME - USE TO COMPARE THE RETURN DATE OF A BOOK */
		time_t localTimeInSeconds = time(0);

		int counter = 0;
		if (patronHead == NULL)
		{
			cout << "Patron list is empty!";
		}
		else
		{
			Patron *currentPatron = patronHead; //Points to the First Node of the Patron's list
			cout << "PATRON WITH ACTIVE BOOKS" << endl;
			cout << "\nPatron ID\tFull Name\tLatest Book Borrowed\tBook ID\tReturn Date" << endl;
			while (currentPatron != NULL) /* First While Loop - traverse throught the patron linked list */
			{
				if (currentPatron->patronBookList != NULL) /* If a patron's book list is not empty, it will proceed to printing, else it will continue the while loop*/
				{
					BookInformation *patronBookList = currentPatron->patronBookList;
					while (patronBookList != NULL) /* Second While Loop - traverse throught the Patron's book list */
					{
						if (counter > 3) /* A counter is used as only the top 3 Node is considered to be the active books */
						{
							break;
						}
						else
						{
							tm *bookReturnDateTime = localtime(&localTimeInSeconds);
							/* Sets bookReturnDateTime to returnDate values */
							bookReturnDateTime->tm_year = patronBookList->returnDate->year - 1900;
							bookReturnDateTime->tm_mon = patronBookList->returnDate->month - 1;
							bookReturnDateTime->tm_mday = patronBookList->returnDate->day;
							/* changes the date stored in bookReturnDateTime to seconds */
							time_t bookReturnDateTimeToSeconds = mktime(bookReturnDateTime);
							/* Comparing date in seconds is much more convenient */
							if (localTimeInSeconds <= bookReturnDateTimeToSeconds)
							{
								cout << currentPatron->patronID << "\t\t" << currentPatron->firstName << " " << currentPatron->lastName << "\t" << patronBookList->bookTitle << "\t\t" << patronBookList->bookID << "\t" << patronBookList->returnDate->day << "/" << patronBookList->returnDate->month << "/" << patronBookList->returnDate->year << endl;
								break;
							}
							else
							{
								counter += 1;
							}
						}
						patronBookList = patronBookList->nextBookInventory;
					}
				}
				currentPatron = currentPatron->linkToNextPatron;
			}
		}
	}

	/*
		BORROW BOOK FUNCTION
		- This function allow the admin to borrow book for the patron.
		- Once a book is borrowed, the bookAvailability field within the BookTitle of the borrowed book will be set to false.
		- The borrowed book will then be copied over to the specified patron's book list, and the admin must specify the borrow date, the return will be appended by the function.
	*/
	void borrowBook(Patron *&patronHead, BookTitle *&libraryBooks)
	{
		if (patronHead == NULL)
		{
			cout << "Patron List is empty!" << endl;
		}
		else
		{
			string patronInfo;
			viewPatron(patronHead);
			cout << "Enter Patron ID or Full Name to borrow book: ";
			cin.ignore();
			getline(cin, patronInfo);
			Patron *current = patronHead;
			while (current != NULL)
			{
				string concat = current->firstName + " " + current->lastName;
				if (patronInfo == current->patronID || patronInfo == concat)
				{
					if (checkBookLimit(current))
					{ /* CHECKS THE PATRON'S BOOK LIST TO CHECK WHETHER THE PATRON CAN BORROW ANOTHER BOOK OR NOT */
						cout << "Patron " << current->firstName << " " << current->lastName << " is not allowed to borrow more books (active books = 3)" << endl;
					}
					else
					{
						bool flag = false;
						string bookID;
						displayAllBooks(libraryBooks);
						cout << "\nEnter a specific Book Information ID to borrow (ex. BK10001-1 or BK10001): ";
						cin >> bookID;
						BookTitle *currentBookTitlePointer = libraryBooks;
						string mainID = bookID.substr(0, 7); //GETS THE VALUE BK10001
						while (currentBookTitlePointer != NULL)
						{
							if (mainID == currentBookTitlePointer->bookInfo->bookID)
							{
								BookInformation *currentBookColumn = currentBookTitlePointer->bookInfo;
								while (currentBookColumn != NULL)
								{
									if ((bookID == currentBookColumn->bookID) && currentBookColumn->bookAvailability == true)
									{
										BookInformation *found = currentBookColumn;
										/*Local PC Time variables*/
										time_t currDateTime = time(0);
										tm *currTime = localtime(&currDateTime); //REFER: https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
										currTime->tm_year = 1900 + currTime->tm_year;
										currTime->tm_mon = 1 + currTime->tm_mon;
										/*Set the book borrowed date (depend on pc time) and return date (add 15 days to borrowed date)*/
										Date *borrowDate = new Date(currTime->tm_mday, currTime->tm_mon, currTime->tm_year);

										currDateTime = time(0) + (86400 * 15); //1 day = 86400 seconds, 15 days = 15 * 86400
										currTime = localtime(&currDateTime);
										currTime->tm_year = 1900 + currTime->tm_year;
										currTime->tm_mon = 1 + currTime->tm_mon;
										Date *returnDate = new Date(currTime->tm_mday, currTime->tm_mon, currTime->tm_year);

										/*Here I created a new book information so that it does not override the current books and inventory*/
										BookInformation *toBorrow = new BookInformation(found->bookTitle, found->bookAuthor, found->genre, found->category, found->bookAvailability, found->bookID, NULL, returnDate, borrowDate);

										/*Sets the book availability in book library to false or unavailable*/
										currentBookColumn->bookAvailability = false;

										/*Inserts the borrowed book to the FIRST NODE of the patron book list*/
										if (current->patronBookList == NULL)
										{
											current->patronBookList = toBorrow;
										}
										else
										{
											BookInformation *previousBookInList = current->patronBookList;
											toBorrow->nextBookInventory = previousBookInList;
											current->patronBookList = toBorrow;
										}
										/* Prints out borrowed details and dates*/
										cout << endl;
										cout << "Patron " << current->firstName << " " << current->lastName << " has borrowed " << currentBookColumn->bookTitle << " with BookID: " << currentBookColumn->bookID << endl;
										cout << "Date borrowed: " << toBorrow->borrowedDate->day << "/" << toBorrow->borrowedDate->month << "/" << toBorrow->borrowedDate->year << endl;
										cout << "Return date: " << toBorrow->returnDate->day << "/" << toBorrow->returnDate->month << "/" << toBorrow->returnDate->year << endl;
										break;
									}
									currentBookColumn = currentBookColumn->nextBookInventory;
								}
								break;
							}
							currentBookTitlePointer = currentBookTitlePointer->nextBookTitle;
						}
					}
					break;
				}
				current = current->linkToNextPatron;
			}
		}
	}

	/*
		CHECK BOOK LIMIT FUNCTION
		- A function to check the Top 3 Book List of a Patron, if it has 3 active books (by comparing current PC time with book return date field), returns true;
	*/
	bool checkBookLimit(Patron *toCheckPatron)
	{
		int counter = 0;
		if (toCheckPatron->patronBookList == NULL)
		{
			return false;
		}
		else
		{
			time_t currDateTime = time(0);
			tm *currentDateTime = localtime(&currDateTime); //REFER: https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm

			BookInformation *current = toCheckPatron->patronBookList;
			while (current != NULL)
			{
				if (counter > 3)
				{
					break;
				}
				else
				{
					if (!((current->returnDate->day == currentDateTime->tm_mday) && (current->returnDate->month == (1 + currentDateTime->tm_mon)) && (current->returnDate->year == (1900 + currentDateTime->tm_year))))
					{
						counter += 1;
					}
				}
				current = current->nextBookInventory;
			}
		}
		return counter >= 3 ? true : false;
	}

	/*
		VIEW PATRON BOOK LIST FUNCTION
		- This function allows the admin to view a patron's book history/list.
		- The function prompts the admin to enter Patron's ID or Full Name to view its book list.
	*/
	void viewPatronBookList(Patron *&patronHead)
	{
		if (patronHead == NULL)
		{
			cout << "Patron List is empty";
		}
		else
		{
			string patronInfo;
			system("CLS");
			viewPatron(patronHead);
			cout << "\nEnter Patron ID or Full Name to check book history: ";
			cin.ignore();
			getline(cin, patronInfo);
			Patron *current = patronHead;
			while (current != NULL)
			{
				string concat = current->firstName + " " + current->lastName;
				if (patronInfo == current->patronID || patronInfo == concat)
				{
					Patron *toViewBookList = current;
					if (toViewBookList->patronBookList == NULL)
					{
						cout << toViewBookList->firstName << " " << toViewBookList->lastName << " have yet to borrow a book!" << endl;
					}
					else
					{
						int counter = 1;
						cout << toViewBookList->firstName << " " << toViewBookList->lastName << " latest book(s) borrowed" << endl;
						cout << "#\tBook ID\tBook Title\tBorrowed Date\tReturn Date" << endl;
						BookInformation *currentBookList = toViewBookList->patronBookList;
						while (currentBookList != NULL)
						{
							if (counter > 10)
							{
								break;
							}
							cout << counter << "\t" << currentBookList->bookID << "\t" << currentBookList->bookTitle << "\t" << currentBookList->borrowedDate->day << "/" << currentBookList->borrowedDate->month << "/" << currentBookList->borrowedDate->year << "\t" << currentBookList->returnDate->day << "/" << currentBookList->returnDate->month << "/" << currentBookList->returnDate->year << endl;
							counter += 1;
							currentBookList = currentBookList->nextBookInventory;
						}
					}
					break;
				}
				current = current->linkToNextPatron;
			}
		}
	}

	/*
		PROMPT UPDATE FUNCTION
		- A function that prompts the admin on which patron to update based on ID or Name
	*/
	void promptUpdate(Patron *&patronHead)
	{
		if (patronHead == NULL)
		{
			cout << "Patron List is empty!" << endl;
		}
		else
		{
			system("CLS");
			int ch;
			string patronInfo;
			viewPatron(patronHead);
			cout << "Enter Patron's Full Name or ID to update: ";
			cin.ignore();
			getline(cin, patronInfo);
			cout << "\nWhat information do you want to update\n1. All\n2. First Name\n3. Last Name\n4. Gender\n5. Date of Birth\nMenu: ";
			cin >> ch;
			updatePatron(patronHead, patronInfo, ch);
		}
	}

	/*
		UPDATE PATRON FUNCTION
		- This function updates the patron information by getting the patron to update from the promptUpdate() function
	*/
	void updatePatron(Patron *&patronHead, string patronInfo, int choice)
	{
		system("CLS");
		if (patronHead == NULL)
		{
			cout << "Patron List is empty!" << endl;
		}
		else
		{
			Patron *current = patronHead;
			Patron *found = NULL;
			while (current != NULL)
			{
				string concat = current->firstName + " " + current->lastName;
				if (patronInfo == concat || patronInfo == current->patronID)
				{
					found = current;
					cout << "UPDATING PATRON " << patronInfo << endl;
					switch (choice)
					{
					case 1:
						cout << "First Name: ";
						cin >> found->firstName;
						cout << "Last Name: ";
						cin >> found->lastName;
						cout << "Gender (M/F): ";
						cin >> found->gender;
						found->gender = toupper(found->gender);
						cout << "Date of Birth (dd/mm/yyyy): ";
						cin >> found->dateOfBirth->day >> found->dateOfBirth->month >> found->dateOfBirth->year;

						cout << "\nPatron " << patronInfo << " has been updated with the following details: " << endl;
						cout << "First name: " << found->firstName << endl;
						cout << "Last name: " << found->lastName << endl;
						cout << "Gender: " << found->gender << endl;
						cout << "Date of Birth: " << found->dateOfBirth->day << "/" << found->dateOfBirth->month << "/" << found->dateOfBirth->year << endl;
						break;
					case 2:
						cout << "First Name: ";
						cin >> found->firstName;

						cout << "\nPatron " << patronInfo << " has been updated with following details: " << endl;
						cout << "First Name: " << found->firstName << endl;
						break;
					case 3:
						cout << "Last Name: ";
						cin >> found->lastName;

						cout << "\nPatron " << patronInfo << " has been updated with following details: " << endl;
						cout << "Last Name: " << found->lastName << endl;
						break;
					case 4:
						cout << "Gender (M/F): ";
						cin >> found->gender;
						found->gender = toupper(found->gender);
						cout << "\nPatron " << patronInfo << " has been updated with following details: " << endl;
						cout << "Gender: " << found->gender << endl;
						break;
					case 5:
						cout << "Date of Birth (dd/mm/yyyy): ";
						cin >> found->dateOfBirth->day >> found->dateOfBirth->month >> found->dateOfBirth->year;

						cout << "\nPatron " << patronInfo << " has been updated with following details: " << endl;
						cout << "Date of Birth: " << found->dateOfBirth->day << "/" << found->dateOfBirth->month << "/" << found->dateOfBirth->year << endl;
						break;
					}
					system("PAUSE");
					break;
				}
				current = current->linkToNextPatron;
			}
		}
	}

	/*
		SEARCH PATRON FUNCTION
		- Function that search for a specified patron by name or id
	*/
	void searchPatron(Patron *&head)
	{
		if (head == NULL)
		{
			system("CLS");
			cout << "Patron list is empty" << endl;
			system("PAUSE");
		}
		else
		{
			system("CLS");
			Patron *current = head;
			string patronInfo;
			bool flag = false;
			int ch;
			cout << "Search Patron\n1. ID\n2. Full Name\n\n0. Back\n"
				 << endl;
			cout << "Menu: ";
			cin >> ch;
			switch (ch)
			{
			case 0:
				break;
			case 1:
				system("CLS");
				cout << "Enter Patron ID to search" << endl;
				cout << "ID: ";
				cin >> patronInfo;
				while (current != NULL)
				{
					bool res = patronInfo == current->patronID ? printPatronDetails(current) : false;
					if (res)
					{
						flag = true;
						break;
					}
					else
						current = current->linkToNextPatron;
				}
				break;
			case 2:
				system("CLS");
				cout << "Enter Name to search" << endl;
				cout << "Full Name: ";
				cin.ignore();
				getline(cin, patronInfo);
				while (current != NULL)
				{
					string concatenate = current->firstName + " " + current->lastName;
					bool res = patronInfo == concatenate ? printPatronDetails(current) : false;
					if (res)
					{
						flag = true;
						break;
					}
					else
						current = current->linkToNextPatron;
				}
				break;
			}
			if (!flag)
			{
				cout << "Patron Not found" << endl;
				system("PAUSE");
			}
		}
	}

	/*
		PRINT PATRON DETAILS - SINGLE
		- A function that prints a single patron information, implemented during searching
	*/
	bool printPatronDetails(Patron *patron)
	{
		system("CLS");
		cout << "Patron Details" << endl;
		cout << "Patron ID\tName\t\tGender\tDate of Birth\tRegistered Date" << endl;
		cout << patron->patronID << "\t\t" << patron->firstName << " " << patron->lastName << "\t" << patron->gender << "\t" << patron->dateOfBirth->day << "/" << patron->dateOfBirth->month << "/" << patron->dateOfBirth->year << "\t" << patron->registeredDate << endl;
		system("PAUSE");
		return true;
	}

	/*
		PROMPT NEW PATRON
		- A function that prompts the user to input new patron information.
		- Takes a pointer address as a parameter, does not work (update the pointer value) if only passing by pointer.
		- refer: https://stackoverflow.com/questions/22000190/when-passing-head-of-linked-list-to-function-why-do-we-need-to-pass-it-by-refere%5C%5C
	*/
	void promptNewPatron(Patron *&head)
	{
		char ch;
		system("CLS");
		time_t currentDateTime = time(0);
		Patron *newPatron = new Patron;
		Date *dateOfBirth = new Date;
		cout << "Enter Patron details" << endl;
		cout << "First name: ";
		cin >> newPatron->firstName;
		cout << "Last name: ";
		cin >> newPatron->lastName;
		cout << "Gender (M/F): ";
		cin >> newPatron->gender;
		do
		{
			cout << "Date of Birth (dd/mm/yyyy): ";
			cin >> dateOfBirth->day >> dateOfBirth->month >> dateOfBirth->year;
		} while (!checkDate(dateOfBirth->day, dateOfBirth->month, dateOfBirth->year));

		system("CLS");

		cout << "Confirm Patron Details" << endl
			 << endl;
		cout << "Name: " << newPatron->firstName << " " << newPatron->lastName << endl;
		cout << "Gender: " << newPatron->gender << endl;
		cout << "Date of Birth: " << dateOfBirth->day << "/" << dateOfBirth->month << "/" << dateOfBirth->year << endl;
		cout << endl;
		cout << "Confirm? (Y/N): ";
		cin >> ch;
		switch (ch)
		{
		case 'Y':
		case 'y':
			newPatron->gender = toupper(newPatron->gender);
			newPatron->dateOfBirth = dateOfBirth;
			newPatron->patronID = generateID(head);
			newPatron->registeredDate = ctime(&currentDateTime);
			newPatron->linkToNextPatron = NULL;
			newPatron->patronBookList = NULL;
			insertPatron(head, newPatron);
			break;
		case 'N':
		case 'n':
			system("CLS");
			promptNewPatron(head);
			break;
		}
	}

	/*
		INSERT PATRON
		- A function that inserts a new patron object to the FIRST NODE of the linked list.
		- Takes 2 parameters, reference to pointer and pointer to patron object.
		- refer: https://stackoverflow.com/questions/22000190/when-passing-head-of-linked-list-to-function-why-do-we-need-to-pass-it-by-refere%5C%5C
	*/
	void insertPatron(Patron *&head, Patron *newPatron)
	{
		if (head == NULL)
		{
			head = newPatron;
			cout << "Added Patron successfully!" << endl;
			system("PAUSE");
		}
		else
		{
			Patron *current = head;
			newPatron->linkToNextPatron = current;
			head = newPatron;
			cout << "Added Patron successfully!" << endl;
			system("PAUSE");
		}
	}

	/*
		VIEW PATRON - ALL
		- A function that prints all patron
		- Takes a reference to pointer parameter
	*/
	void viewPatron(Patron *&head)
	{
		if (head == NULL)
		{
			system("CLS");
			cout << "Patron List is empty!" << endl;
			system("PAUSE");
		}
		else
		{
			system("CLS");
			Patron *current = head;
			cout << "Patron ID\tName\t\tGender\tDate of Birth\tRegistered Date" << endl;
			while (current != NULL)
			{
				bool res = current->registeredDate == NULL ? true : false;
				string emptyDate = res == true ? "Empty Date" : current->registeredDate;
				cout << current->patronID << "\t\t" << current->firstName << " " << current->lastName << "\t" << current->gender << "\t" << current->dateOfBirth->day << "/" << current->dateOfBirth->month << "/" << current->dateOfBirth->year << "\t" << emptyDate << endl;
				current = current->linkToNextPatron;
			}
			cout << "\nTotal Patron(s): " << getSize(head) << " Patron(s)." << endl;
		}
	}

	/*
		GET SIZE FUNCTION
		- A function to get the size of Patron Linked List
	*/
	int getSize(Patron *&head)
	{
		int size = 0;
		if (head == NULL)
		{
			return 0;
		}
		else
		{
			Patron *current = head;
			while (current != NULL)
			{
				current = current->linkToNextPatron;
				size += 1;
			}
		}
		return size;
	}

	/*
		GENERATE PATRON ID
		- A function to generate ID for a patron
		- Take reference to pointer as param
		- Note: As new patron is inserted to the first Node, traversing is not needed
	*/
	string generateID(Patron *&patronHead)
	{
		if (patronHead == NULL)
		{
			return "PT10001";
		}
		else
		{
			Patron *current = patronHead;
			string tempID = current->patronID;
			tempID = tempID.substr(2, 5);
			string id = to_string(stoi(tempID) + 1);
			return "PT" + id;
		}
	}
} // namespace patron

#endif