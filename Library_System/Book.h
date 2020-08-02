#ifndef BOOK //FILE GUARDS REFER: https://www.youtube.com/watch?v=RU5JUHAiR18
#define BOOK

#include <string>
#include <iostream>
#include "CustomDate.h"

using namespace std;
using namespace date;

namespace book
{
	/*STRING CONSTANTS - NOTHING FANCY*/
	const string simplifiedBookView = "BOOKID\tBOOKTITLE\tBOOKAUTHOR\tGENRE\tCATEGORY\tINVENTORY";
	const string expandedBookView = "BOOKID\tBOOKTITLE\tBOOKAUTHOR\tGENRE\tCATEGORY\tAVAILABILITY";

	/*CLASS PROTOTYPE*/
	class BookInformation;
	class BookTitle;

	/*CLASS*/
	class BookTitle
	{
		public:
			BookTitle() {}
			BookTitle(BookInformation * bookInformation, BookTitle * uniqueTitle) {
				this->bookInfo = bookInformation;
				this->nextBookTitle = uniqueTitle;
			}
			BookTitle *nextBookTitle;
			BookInformation *bookInfo;
	};

	class BookInformation
	{
		public:
			BookInformation() {}
			BookInformation(string bookTitle, string bookAuthor, string genre, string category, bool availability, string bookID, BookInformation * nextBookInvent) {
				this->bookTitle = bookTitle;
				this->bookAuthor = bookAuthor;
				this->genre = genre;
				this->category = category;
				this->bookAvailability = availability;
				this->bookID = bookID;
				this->nextBookInventory = nextBookInvent;
			}
			string category, genre, bookAuthor, bookTitle, bookID;
			bool bookAvailability;
			BookInformation *nextBookInventory;
			Date* returnDate, * borrowedDate;
	};

	/*FUNCTION PROTOTYPE*/
	string generateBookID(BookTitle *&);
	void insertBookDetail(BookTitle *&, BookTitle *);
	void promptNewBook(BookTitle *&);
	void displayAllBooks(BookTitle *&);
	bool checkDuplicateUniqueTitle(BookTitle*&, string, string);
	void addExistingBookTitle(BookTitle*& bookTitleHead, string bookID);
	void addExistingBookTitle(BookTitle*& bookTitleHead, string,string);
	string generateInventoryID(BookTitle*&, string);
	void searchBook(BookTitle*&, int, string);
	void promptSearch(BookTitle*&);

	/*
		PROMPT SEARCH FUNCTION
		- A simple function so prompt user on what to search;
	*/
	void promptSearch(BookTitle*&bookTitleHead) {
		string bookInfo;
		int ch, subOptions;
		system("CLS");
		cout << "Which Field do you want to search the book on\n1. Genre\n2. Category\n3. Book Title\n4. Availability\nMenu: ";
		cin >> ch;
		switch (ch) {
		case 1:
			cout << "\nChoose a Genre: \nFiction\n1. Fantasy\n2. Science\n3. Historical\n4. Realistic\n5. Fan\n\nNon-Fiction\n6. Narrative\n7. Biography\n8. Periodicals\n9. Self-help\n10. Reference\nGenre: ";
			cin >> subOptions;
			switch (subOptions) {
				case 1: bookInfo = "Fantasy"; break;
				case 2: bookInfo = "Science"; break;
				case 3: bookInfo = "Historical"; break;
				case 4: bookInfo = "Realistic"; break;
				case 5: bookInfo = "Fan"; break;
				case 6: bookInfo = "Narrative"; break;
				case 7: bookInfo = "Biography"; break;
				case 8: bookInfo = "Periodicals"; break;
				case 9: bookInfo = "Self-help"; break;
				case 10: bookInfo = "Reference"; break;
			}
			break;
		case 2:
			cout << "\nChoose a Category:\n1. Fiction\n2. Non-Fiction\nCategory: ";
			cin >> subOptions;
			switch (subOptions) {
			case 1:
				bookInfo = "Fiction";
				break;
			case 2:
				bookInfo = "Non-Fiction";
				break;
			}
			break;
		case 3:
			cout << "\nEnter Book Title (Make sure it is correctly spelled and capitalized): ";
			cin >> bookInfo;
			break;
		case 4:
			cout << "Choose Availability:\n1. Available\n2. Unavailable\nAvailability: ";
			cin >> subOptions;
			switch (subOptions) {
			case 1:
				bookInfo = "Available";
				break;
			case 2:
				bookInfo = "Unavailable";
				break;
			}
			break;
		}
		searchBook(bookTitleHead, ch, bookInfo);
	}

	/*
		SEARCH BOOK FUNCTION
		- A function that search for and print the book details to the admin
		- Takes 3 param, BookTitle reference pointer, Int for the chosen search option and String for the data to search for
	*/
	void searchBook(BookTitle *& bookTitleHead, int fieldOption, string bookField) {
		if (bookTitleHead == NULL) {
			cout << "Book List is empty" << endl;
		}
		else {
			BookTitle* currentBookTitlePointer = bookTitleHead;
			BookInformation* currentBookInformationPointer = currentBookTitlePointer->bookInfo;
			switch (fieldOption) {
				case 1:	/*SEARCH ON GENRE*/
					cout << "BOOKID\tBOOKTITLE\tBOOKAUTHOR\tGENRE\tAVAILABILITY" << endl;
					while (currentBookTitlePointer != NULL) {	/*FIRST WHILE LOOP - TRAVERSE VERTICALLY*/
						if (bookField == currentBookInformationPointer->genre) {
							BookInformation* traverseColumn = currentBookInformationPointer;
							if (traverseColumn->nextBookInventory == NULL) {
								string res = traverseColumn->bookAvailability == true ? "Available" : "Unavailable";
								cout << traverseColumn->bookID << "\t" << traverseColumn->bookTitle << "\t" << traverseColumn->bookAuthor << "\t" << traverseColumn->genre << "\t\t" << res << endl;
							}
							else {
								while (traverseColumn != NULL) {	/*SECOND WHILE LOOP - TRAVERSE HORIZONTALLY*/
									string res = traverseColumn->bookAvailability == true ? "Available" : "Unavailable";
									cout << traverseColumn->bookID << "\t" << traverseColumn->bookTitle << "\t" << traverseColumn->bookAuthor << "\t" << traverseColumn->genre << "\t\t" << res << endl;
									traverseColumn = traverseColumn->nextBookInventory;
								}
							}
						}
						currentBookTitlePointer = currentBookTitlePointer->nextBookTitle;
					}
					break;
				case 2:	/*SEARCH ON CATEGORY*/
					break;
				case 3:	/*SEARCH ON BOOK TITLE*/
					break;
				case 4:	/*SEARCH ON AVAILABILITY*/
					bool res = bookField == "Available" ? true : false;
					break;
			}
		}
	}

	/*
		PROMPT NEW BOOK
		- This function just prompts the user to insert new book details.
		- Takes a reference to a pointer parameter.
		- refer: https://stackoverflow.com/questions/22000190/when-passing-head-of-linked-list-to-function-why-do-we-need-to-pass-it-by-refere%5C%5C
	*/
	void promptNewBook(BookTitle *&bookTitleHead)
	{
		BookInformation *newBookInformation = new BookInformation;
		int ch;
		char confirm;

		system("CLS");
		cout << "INSERTING BOOK" << endl;
		cout << "1. Insert New Title\n2. Add Existing Title" << endl;
		cout << "Menu: ";
		cin >> ch;
		switch (ch)
		{
		case 1:
			system("CLS");
			cout << "Enter Book Details" << endl;
			cout << "Category\n1. Fiction\n2. Non-Fiction\nMenu: ";
			cin >> ch;
			switch (ch)
			{
			case 1:
				newBookInformation->category = "Fiction";
				system("CLS");
				cout << "Genre\n1. Fantasy\n2. Science\n3. Historical\n4. Realistic\n5. Fan\n\nMenu: ";
				cin >> ch;
				switch (ch)
				{
				case 1:
					newBookInformation->genre = "Fantasy";
					break;
				case 2:
					newBookInformation->genre = "Science";
					break;
				case 3:
					newBookInformation->genre = "Historical";
					break;
				case 4:
					newBookInformation->genre = "Realistic";
					break;
				case 5:
					newBookInformation->genre = "Fan";
					break;
				}
				break;
			case 2:
				newBookInformation->category = "Non-Fiction";
				system("CLS");
				cout << "Genre\n1. Narrative\n2. Biography\n3. Periodicals\n4. Self-help\n5. Reference\nMenu: ";
				cin >> ch;
				switch (ch)
				{
				case 1:
					newBookInformation->genre = "Narrative";
					break;
				case 2:
					newBookInformation->genre = "Biography";
					break;
				case 3:
					newBookInformation->genre = "Periodicals";
					break;
				case 4:
					newBookInformation->genre = "Self-help";
					break;
				case 5:
					newBookInformation->genre = "Reference";
					break;
				}
			}
			cout << "Book Title: ";
			cin.ignore();								 //refer: https://stackoverflow.com/questions/12691316/getline-does-not-work-if-used-after-some-inputs
			getline(cin, newBookInformation->bookTitle); // ALLOWS THE INPUT OF STRING WITH SPACES || refer: https://stackoverflow.com/questions/30758245/how-to-store-a-complete-sentence-with-white-spaces-in-a-string-in-cpp
			cout << "Book Author: ";
			getline(cin, newBookInformation->bookAuthor);
			if (checkDuplicateUniqueTitle(bookTitleHead, newBookInformation->bookTitle, newBookInformation->bookAuthor)) {
				cout << "A title exist with similar author, would you like to add duplicate instead? (Y/N)";
				cin >> confirm;
				switch (confirm) {
				case 'y':
				case 'Y':
					addExistingBookTitle(bookTitleHead, newBookInformation->bookTitle, newBookInformation->bookAuthor);
					break;
				case 'n':
				case 'N':
					goto next;
					break;
				}
			}
			else {
				next:
				system("CLS");
				cout << "Confirm Book Details\n" << endl;
				cout << "Category: " << newBookInformation->category << endl;
				cout << "Genre: " << newBookInformation->genre << endl;
				cout << "Book Title: " << newBookInformation->bookTitle << endl;
				cout << "Book Author: " << newBookInformation->bookAuthor << endl;
				cout << "Confirm (Y/N): ";
				cin >> confirm;
				switch (confirm)
				{
				case 'y':
				case 'Y':
					/*INITIALIZE ALL VALUES OF NEWBOOKINFORMATION*/
					newBookInformation->bookID = generateBookID(bookTitleHead);
					newBookInformation->bookAvailability = true;
					newBookInformation->nextBookInventory = NULL;
					newBookInformation->returnDate = NULL;
					newBookInformation->borrowedDate = NULL;
					/*CREATES A NEW UNIQUE BOOK TITLE COLUMN*/
					BookTitle* newBookTitle = new BookTitle;
					newBookTitle->bookInfo = newBookInformation;
					newBookTitle->nextBookTitle = NULL;
					insertBookDetail(bookTitleHead, newBookTitle);
				}
			}
			
			break;
		case 2:
			string bookID;
			displayAllBooks(bookTitleHead);
			cout << "Enter Book ID to add inventory" << endl;
			cout << "BOOKID: ";
			cin >> bookID;
			addExistingBookTitle(bookTitleHead, bookID);
			break;
		}
	}

	/*
		ADD EXISTING BOOK TITLE
		- A function that insert to the inventory of the unique book title
	*/
	void addExistingBookTitle(BookTitle *& bookTitleHead, string bookID) {
		BookTitle* currentColumn = bookTitleHead;
		while (currentColumn != NULL) {
			if (bookID == currentColumn->bookInfo->bookID) {
				BookInformation* toAdd = new BookInformation(currentColumn->bookInfo->bookTitle, currentColumn->bookInfo->bookAuthor, currentColumn->bookInfo->genre, currentColumn->bookInfo->category, currentColumn->bookInfo->bookAvailability, currentColumn->bookInfo->bookID, NULL);
				string bookid = toAdd->bookID;	//EX. BK10001, BK10002
				if (currentColumn->bookInfo->nextBookInventory == NULL) {
					toAdd->bookID = generateInventoryID(bookTitleHead, bookid);
					currentColumn->bookInfo->nextBookInventory = toAdd;
				}
				else {
					BookInformation* traverseRow = currentColumn->bookInfo;
					while (traverseRow->nextBookInventory != NULL) {
						traverseRow = traverseRow->nextBookInventory;
					}
					toAdd->bookID = generateInventoryID(bookTitleHead, bookid);
					traverseRow->nextBookInventory = toAdd;
				}
				break;
			}
			currentColumn = currentColumn->nextBookTitle;
		}
	}

	/*FUNCTION OVERLOAD*/
	void addExistingBookTitle(BookTitle*& bookTitleHead, string bookTitle, string bookAuthor) {
		BookTitle* currentColumnPointer = bookTitleHead;
		while (currentColumnPointer != NULL) {
			if (bookTitle == currentColumnPointer->bookInfo->bookTitle && bookAuthor == currentColumnPointer->bookInfo->bookAuthor) {
				addExistingBookTitle(bookTitleHead, currentColumnPointer->bookInfo->bookID);
				break;
			}
			currentColumnPointer = currentColumnPointer->nextBookTitle;
		}
	}

	/*
		CHECK DUPLICATE UNIQUE TITLE
		- This function is to check for duplicate unique titles and author
	*/
	bool checkDuplicateUniqueTitle(BookTitle *& bookTitleHead, string bookTitle, string bookAuthor) {
		if (bookTitleHead != NULL) {
			BookTitle* currentColumnPointer = bookTitleHead;
			while (currentColumnPointer != NULL) {
				if (bookTitle == currentColumnPointer->bookInfo->bookTitle && bookAuthor == currentColumnPointer->bookInfo->bookAuthor) {
					return true;
					break;
				}
				currentColumnPointer = currentColumnPointer->nextBookTitle;
			}
		}
		return false;
	}

	/*
		INSERT BOOK DETAIL
		- This function allows the insertion of UNIQUE BOOK TITLE to the beginning of the multi dimension linked list
	*/
	void insertBookDetail(BookTitle *&bookTitleHead, BookTitle *newBookTitle)
	{
		if (bookTitleHead == NULL)
		{
			bookTitleHead = newBookTitle;
			cout << "Book Added successfully" << endl;
		}
		else
		{
			BookTitle *currentTitleHead = bookTitleHead;
			newBookTitle->nextBookTitle = currentTitleHead;
			bookTitleHead = newBookTitle;

			cout << "Book Added successfully" << endl;
		}
		system("PAUSE");
	}

	/*
		DISPLAY ALL BOOKS
		- A function that displays all current books, duplicate books will be shown as an 'Inventory' instead.
		- Takes a reference to pointer parameter.
		- refer: https://stackoverflow.com/questions/22000190/when-passing-head-of-linked-list-to-function-why-do-we-need-to-pass-it-by-refere%5C%5C
	*/
	void displayAllBooks(BookTitle *&bookTitleHead)
	{
		system("CLS");
		int ch;
		if (bookTitleHead == NULL) {
			cout << "Book List Empty!";
		}
		else {
			BookTitle* currentBookColumn = bookTitleHead;
			cout << "How would you like to view the Book List\n1. Expanded\n2. Simplified" << endl;
			cout << "Menu: ";
			cin >> ch;
			system("CLS");
			
			switch (ch) {
			case 1:
				cout << expandedBookView << endl;
				while (currentBookColumn != NULL) {
					if (currentBookColumn->bookInfo->nextBookInventory != NULL) {
						BookInformation* currentRow = currentBookColumn->bookInfo;
						while (currentRow != NULL) {
							string res = currentRow->bookAvailability ? "Available" : "Unavailable";
							cout << currentRow->bookID << "\t" << currentRow->bookTitle << "\t" << currentRow->bookAuthor << "\t" << currentRow->genre << "\t" << currentRow->category << "\t" << res << endl;
							currentRow = currentRow->nextBookInventory;
						}
					}
					else {
						string res = currentBookColumn->bookInfo->bookAvailability ? "Available" : "Unavailable";
						cout << currentBookColumn->bookInfo->bookID << "\t" << currentBookColumn->bookInfo->bookTitle << "\t" << currentBookColumn->bookInfo->bookAuthor << "\t" << currentBookColumn->bookInfo->genre << "\t" << currentBookColumn->bookInfo->category << "\t\t" << res << endl;
					}
					currentBookColumn = currentBookColumn->nextBookTitle;
				}
				break;
			case 2:
				int inventory;
				cout << simplifiedBookView << endl;
				while (currentBookColumn != NULL) {
					inventory = 1;
					if (currentBookColumn->bookInfo->nextBookInventory != NULL) {
						BookInformation* currentRow = currentBookColumn->bookInfo;
						while (currentRow->nextBookInventory != NULL) {
							inventory += 1;
							currentRow = currentRow->nextBookInventory;
						}
						cout << currentRow->bookID << "\t" << currentRow->bookTitle << "\t" << currentRow->bookAuthor << "\t" << currentRow->genre << "\t" << currentRow->category << "\t" << inventory << endl;
					}
					else {
						cout << currentBookColumn->bookInfo->bookID << "\t" << currentBookColumn->bookInfo->bookTitle << "\t" << currentBookColumn->bookInfo->bookAuthor << "\t" << currentBookColumn->bookInfo->genre << "\t" << currentBookColumn->bookInfo->category << "\t\t" << inventory << endl;
					}
					currentBookColumn = currentBookColumn->nextBookTitle;
				}
				break;
			}
			
		}
	}

	/*
		GENERATE BOOK ID
		- A function that generates a unique book id
	*/
	string generateBookID(BookTitle *&bookTitleHead)
	{
		if (bookTitleHead == NULL)
		{
			return "BK10001";
		}
		else
		{
			BookTitle* current = bookTitleHead;
			string tempID = current->bookInfo->bookID;
			tempID = tempID.substr(2, 5);	//ONLY TAKES THE VALUE 5 CHARACTERS AFTER BK
			string id = to_string(stoi(tempID) + 1);
			return "BK" + id;
		}
	}

	/*
		GENERATE INVENTORY ID
		- A function that generates unique inventory ID
		- ex. BK10001-1
	*/
	string generateInventoryID(BookTitle*& bookTitleHead, string mainID) {
		BookTitle* currentBookTitlePointer = bookTitleHead;
		while (currentBookTitlePointer != NULL) {
			if (mainID == currentBookTitlePointer->bookInfo->bookID) {
				BookInformation* currentBookInformation = currentBookTitlePointer->bookInfo;
				if (currentBookInformation->nextBookInventory == NULL) {
					return mainID + "-1";
					break;
				}
				else {
					string lastID;
					while (currentBookInformation != NULL) {
						lastID = currentBookInformation->bookID;
						currentBookInformation = currentBookInformation->nextBookInventory;
					}
					string inventoryNumber = lastID.substr(8, 5);		//get the value after "-"
					string id = to_string(stoi(inventoryNumber) + 1);
					return mainID + "-" + id;
				}
			}
			currentBookTitlePointer = currentBookTitlePointer->nextBookTitle;
		}
	}
}

#endif
