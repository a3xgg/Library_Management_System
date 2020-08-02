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
	const string availabilityView = "BOOKID\tBOOKTITLE\tBOOKAUTHOR\tGENRE\tCATEGORY";

	/*CLASS PROTOTYPE*/
	class BookInformation;
	class BookTitle;

	/*CLASS*/
	class BookTitle
	{
	public:
		BookTitle() {}
		BookTitle(BookInformation *bookInformation, BookTitle *uniqueTitle)
		{
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
		BookInformation(string bookTitle, string bookAuthor, string genre, string category, bool availability, string bookID, BookInformation *nextBookInvent)
		{
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
		Date returnDate, borrowedDate;
	};

	/*FUNCTION PROTOTYPE*/
	string generateBookID(BookTitle *&);
	void insertBookDetail(BookTitle *&, BookTitle *);
	void promptNewBook(BookTitle *&);
	void displayAllBooks(BookTitle *&);
	bool checkDuplicateUniqueTitle(BookTitle *&, string, string);
	void addExistingBookTitle(BookTitle *&, string);
	void addExistingBookTitle(BookTitle *&, string, string);
	string generateInventoryID(BookTitle *&, string);
	void searchBook(BookTitle *&, int, string);
	void promptSearch(BookTitle *&);
	void promptUpdate(BookTitle *&);
	void updateBookInformation(BookTitle *&, string);

	/*
		PROMPT UPDATE
		- A function that prompts the user on the BOOK ID that the user wants to update
	*/
	void promptUpdate(BookTitle *&bookTitleHead)
	{
		if (bookTitleHead == NULL)
		{
			cout << "Book List is empty!" << endl;
		}
		else
		{
			string bookInfo;
			system("CLS");
			displayAllBooks(bookTitleHead);
			cout << "\nEnter the Book ID to edit: ";
			cin >> bookInfo;
			updateBookInformation(bookTitleHead, bookInfo);
		}
	}

	void updateBookInformation(BookTitle *&bookTitleHead, string bookID)
	{
		if (bookTitleHead == NULL)
		{
			cout << "Book List is empty!" << endl;
		}
		else
		{
			BookTitle *currentBookTitle = bookTitleHead;
			string mainID = bookID.substr(0, 7); // GETS THE MAIN ID ex. BK10001 without -X where X is inventory number
			while (currentBookTitle != NULL)
			{ /*FIRST WHILE LOOP - LOOPS THROUGH VERTICALLY TO FIND OUT THE MAIN ID EX. BK10001*/
				if (mainID == currentBookTitle->bookInfo->bookID)
				{
					BookInformation *currentBookColumn = currentBookTitle->bookInfo;
					while (currentBookColumn != NULL)
					{
						if (bookID == currentBookColumn->bookID)
						{
							BookInformation *toUpdate = currentBookColumn;
							int ch;
							system("CLS");
							cout << "EDITING BOOK ID: " << toUpdate->bookID << endl
								 << endl;
							cout << "New Title: ";
							cin.ignore();
							getline(cin, toUpdate->bookTitle);
							cout << "New Author: ";
							getline(cin, toUpdate->bookAuthor);
							cout << "New Category: \n1. Fiction\n2. Non-Fiction" << endl;
							cin >> ch;
							switch (ch)
							{
							case 1:
								toUpdate->category = "Fiction";
								cout << "New Genre: \n1. Fantasy\n2. Science\n3. Historical\n4. Realistic\n5. Fan\n\nMenu: ";
								cin >> ch;
								switch (ch)
								{
								case 1:
									toUpdate->genre = "Fantasy";
									break;
								case 2:
									toUpdate->genre = "Science";
									break;
								case 3:
									toUpdate->genre = "Historical";
									break;
								case 4:
									toUpdate->genre = "Realistic";
									break;
								case 5:
									toUpdate->genre = "Fan";
									break;
								}
								break;
							case 2:
								toUpdate->category = "Non-Fiction";
								cout << "New Genre: \n1. Narrative\n2. Biography\n3. Periodicals\n4. Self-help\n5. Reference\nMenu: ";
								cin >> ch;
								switch (ch)
								{
								case 1:
									toUpdate->genre = "Narrative";
									break;
								case 2:
									toUpdate->genre = "Biography";
									break;
								case 3:
									toUpdate->genre = "Periodical";
									break;
								case 4:
									toUpdate->genre = "Self-help";
									break;
								case 5:
									toUpdate->genre = "Reference";
									break;
								}
								break;
							}
							cout << "\nBOOK ID: " << toUpdate->bookID << " has been updated with following details: " << endl;
							cout << "Book Title: " << toUpdate->bookTitle << endl;
							cout << "Book Author: " << toUpdate->bookAuthor << endl;
							cout << "Category: " << toUpdate->category << endl;
							cout << "Genre: " << toUpdate->genre << endl;
							system("PAUSE");
							break;
						}
						currentBookColumn = currentBookColumn->nextBookInventory;
					}
					break;
				}
				currentBookTitle = currentBookTitle->nextBookTitle;
			}
		}
	}

	/*
		PROMPT SEARCH FUNCTION
		- A function that prompts the admin on what field to search the book on
	*/
	void promptSearch(BookTitle *&bookTitleHead)
	{
		string bookInfo;
		int ch, subOptions;
		system("CLS");
		cout << "Which Field do you want to search the book on\n1. Genre\n2. Category\n3. Book Title\n4. Availability\n5. Book ID\nMenu: ";
		cin >> ch;
		switch (ch)
		{
		case 1:
			cout << "\nChoose a Genre: \nFiction\n1. Fantasy\n2. Science\n3. Historical\n4. Realistic\n5. Fan\n\nNon-Fiction\n6. Narrative\n7. Biography\n8. Periodicals\n9. Self-help\n10. Reference\nGenre: ";
			cin >> subOptions;
			switch (subOptions)
			{
			case 1:
				bookInfo = "Fantasy";
				break;
			case 2:
				bookInfo = "Science";
				break;
			case 3:
				bookInfo = "Historical";
				break;
			case 4:
				bookInfo = "Realistic";
				break;
			case 5:
				bookInfo = "Fan";
				break;
			case 6:
				bookInfo = "Narrative";
				break;
			case 7:
				bookInfo = "Biography";
				break;
			case 8:
				bookInfo = "Periodicals";
				break;
			case 9:
				bookInfo = "Self-help";
				break;
			case 10:
				bookInfo = "Reference";
				break;
			}
			break;
		case 2:
			cout << "\nChoose a Category:\n1. Fiction\n2. Non-Fiction\nCategory: ";
			cin >> subOptions;
			switch (subOptions)
			{
			case 1:
				bookInfo = "Fiction";
				break;
			case 2:
				bookInfo = "Non-Fiction";
				break;
			}
			break;
		case 3:
			cout << "\nEnter Book Title (Ensure correct spelling and capitalization): ";
			cin.ignore();
			getline(cin, bookInfo);
			break;
		case 4:
			cout << "\nChoose Availability:\n1. Available\n2. Unavailable\nAvailability: ";
			cin >> subOptions;
			switch (subOptions)
			{
			case 1:
				bookInfo = "Available";
				break;
			case 2:
				bookInfo = "Unavailable";
				break;
			}
			break;
		case 5:
			cout << "\nEnter Book ID to search (ex. BK10001): ";
			cin >> bookInfo;
			break;
		}
		searchBook(bookTitleHead, ch, bookInfo);
	}

	/*
		SEARCH BOOK FUNCTION
		- A function that search for the specified field the admin entered and prints the book information
		- Takes 3 param, BookTitle reference pointer, Int for the chosen search option and String for the data to search for
	*/
	void searchBook(BookTitle *&bookTitleHead, int fieldOption, string bookField)
	{
		if (bookTitleHead == NULL)
		{
			cout << "Book List is empty" << endl;
		}
		else
		{
			BookTitle *currentBookTitlePointer = bookTitleHead;
			system("CLS");
			switch (fieldOption)
			{
			case 1: /*SEARCH ON GENRE*/
				cout << "SEARCH RESULT(S) BASED ON GENRE: " << bookField << endl
					 << endl;
				cout << "BOOKID\tBOOKTITLE\tBOOKAUTHOR\tGENRE\tAVAILABILITY" << endl;
				while (currentBookTitlePointer != NULL)
				{ /*FIRST WHILE LOOP - TRAVERSE VERTICALLY*/
					if (bookField == currentBookTitlePointer->bookInfo->genre)
					{
						BookInformation *traverseColumn = currentBookTitlePointer->bookInfo;
						if (traverseColumn->nextBookInventory == NULL)
						{
							string res = traverseColumn->bookAvailability == true ? "Available" : "Unavailable";
							cout << traverseColumn->bookID << "\t" << traverseColumn->bookTitle << "\t" << traverseColumn->bookAuthor << "\t" << traverseColumn->genre << "\t\t" << res << endl;
						}
						else
						{
							while (traverseColumn != NULL)
							{ /*SECOND WHILE LOOP - TRAVERSE HORIZONTALLY*/
								string res = traverseColumn->bookAvailability == true ? "Available" : "Unavailable";
								cout << traverseColumn->bookID << "\t" << traverseColumn->bookTitle << "\t" << traverseColumn->bookAuthor << "\t" << traverseColumn->genre << "\t\t" << res << endl;
								traverseColumn = traverseColumn->nextBookInventory;
							}
						}
					}
					currentBookTitlePointer = currentBookTitlePointer->nextBookTitle;
				}
				break;
			case 2: /*SEARCH ON CATEGORY*/
				cout << "SEARCH RESULT(S) BASED ON CATEGORY: " << bookField << endl
					 << endl;
				cout << "BOOKID\tBOOKTITLE\tBOOKAUTHOR\tCATEGORY\tAVAILABILITY" << endl;
				while (currentBookTitlePointer != NULL)
				{
					if (bookField == currentBookTitlePointer->bookInfo->category)
					{
						BookInformation *currentBookColumn = currentBookTitlePointer->bookInfo;
						while (currentBookColumn != NULL)
						{
							string res = currentBookColumn->bookAvailability == true ? "Available" : "Unavailable";
							cout << currentBookColumn->bookID << "\t" << currentBookColumn->bookTitle << "\t" << currentBookColumn->bookAuthor << "\t" << currentBookColumn->genre << "\t\t" << res << endl;
							currentBookColumn = currentBookColumn->nextBookInventory;
						}
					}
					currentBookTitlePointer = currentBookTitlePointer->nextBookTitle;
				}
				break;
			case 3: /*SEARCH ON BOOK TITLE*/
				cout << "SEARCH RESULT(S) FOR " << bookField << endl
					 << endl;
				while (currentBookTitlePointer != NULL)
				{ /*FIRST WHILE LOOP - LOOPS THROUGH THE VERTICAL LIST*/
					if (bookField == currentBookTitlePointer->bookInfo->bookTitle)
					{
						BookInformation *currentColumnBook = currentBookTitlePointer->bookInfo;
						cout << expandedBookView << endl;
						if (currentColumnBook->nextBookInventory != NULL)
						{
							while (currentColumnBook != NULL)
							{ /*SECOND WHILE LOOP - LOOPS THROUGHT THE BOOK INVENTORY (HORIZONTALLY)*/
								string res = currentColumnBook->bookAvailability == true ? "Available" : "Unavailable";
								cout << currentColumnBook->bookID << "\t" << currentColumnBook->bookTitle << "\t" << currentColumnBook->bookAuthor << "\t" << currentColumnBook->genre << "\t\t" << currentColumnBook->category << "\t" << res << endl;
								currentColumnBook = currentColumnBook->nextBookInventory;
							}
						}
						else
						{
							string res = currentColumnBook->bookAvailability == true ? "Available" : "Unavailable";
							cout << currentColumnBook->bookID << "\t" << currentColumnBook->bookTitle << "\t" << currentColumnBook->bookAuthor << "\t" << currentColumnBook->genre << "\t\t" << currentColumnBook->category << "\t" << res << endl;
						}
						break;
					}
					currentBookTitlePointer = currentBookTitlePointer->nextBookTitle;
				}
				break;
			case 4:
			{ /*SEARCH ON AVAILABILITY*/
				bool res = bookField == "Available" ? true : false;
				if (res)
				{
					cout << "CURRENTLY AVAILABLE BOOK(S)\n"
						 << endl;
					cout << availabilityView << endl;
				}
				else
				{
					cout << "CURRENTLY UNAVAILABLE BOOK(S)\n"
						 << endl;
					cout << availabilityView << endl;
				}
				while (currentBookTitlePointer != NULL)
				{ /*FIRST WHILE LOOP - LOOPS THROUGH THE LIST VERTICALLY*/
					BookInformation *currentBookColumn = currentBookTitlePointer->bookInfo;
					while (currentBookColumn != NULL)
					{ /*SECOND WHILE LOOP - LOOPS THROUGH THE LIST HORIZONTALLY*/
						if (res == currentBookColumn->bookAvailability)
						{
							cout << currentBookColumn->bookID << "\t" << currentBookColumn->bookTitle << "\t" << currentBookColumn->bookAuthor << "\t" << currentBookColumn->genre << "\t\t" << currentBookColumn->category << endl;
						}
						currentBookColumn = currentBookColumn->nextBookInventory;
					}
					currentBookTitlePointer = currentBookTitlePointer->nextBookTitle;
				}
			}
			break;
			case 5:
			{
				string mainID = bookField.substr(0, 7);
				cout << "SEARCH RESULT(S) BASED ON BOOK ID: " << bookField << endl
					 << endl;
				cout << expandedBookView << endl;
				while (currentBookTitlePointer != NULL)
				{
					if (mainID == currentBookTitlePointer->bookInfo->bookID)
					{
						BookInformation *currentBookColumn = currentBookTitlePointer->bookInfo;
						while (currentBookColumn != NULL)
						{
							if (bookField == currentBookColumn->bookID)
							{
								string res = currentBookColumn->bookAvailability == true ? "Available" : "Unavailable";
								cout << currentBookColumn->bookID << "\t" << currentBookColumn->bookTitle << "\t" << currentBookColumn->bookAuthor << "\t" << currentBookColumn->genre << "\t\t" << currentBookColumn->category << "\t" << res << endl;
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
			if (checkDuplicateUniqueTitle(bookTitleHead, newBookInformation->bookTitle, newBookInformation->bookAuthor))
			{
				cout << "A title exist with similar author, would you like to add duplicate instead? (Y/N)";
				cin >> confirm;
				switch (confirm)
				{
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
			else
			{
			next:
				system("CLS");
				cout << "Confirm Book Details\n"
					 << endl;
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
					/*CREATES A NEW UNIQUE BOOK TITLE COLUMN*/
					BookTitle *newBookTitle = new BookTitle;
					newBookTitle->bookInfo = newBookInformation;
					newBookTitle->nextBookTitle = NULL;
					insertBookDetail(bookTitleHead, newBookTitle);
				}
			}

			break;
		case 2:
			string bookID;
			displayAllBooks(bookTitleHead);
			cout << "\nEnter Book ID to add inventory (ex. BK10001 without -X)" << endl;
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
	void addExistingBookTitle(BookTitle *&bookTitleHead, string bookID)
	{
		BookTitle *currentUniqueTitlePointer = bookTitleHead;
		while (currentUniqueTitlePointer != NULL)
		{
			if (bookID == currentUniqueTitlePointer->bookInfo->bookID)
			{
				BookInformation *toAdd = new BookInformation(currentUniqueTitlePointer->bookInfo->bookTitle, currentUniqueTitlePointer->bookInfo->bookAuthor, currentUniqueTitlePointer->bookInfo->genre, currentUniqueTitlePointer->bookInfo->category, currentUniqueTitlePointer->bookInfo->bookAvailability, currentUniqueTitlePointer->bookInfo->bookID, NULL);
				string bookid = toAdd->bookID; //EX. BK10001, BK10002
				if (currentUniqueTitlePointer->bookInfo->nextBookInventory == NULL)
				{
					toAdd->bookID = generateInventoryID(bookTitleHead, bookid);
					toAdd->bookAvailability = true;
					currentUniqueTitlePointer->bookInfo->nextBookInventory = toAdd;
				}
				else
				{
					BookInformation *traverseColumnPointer = currentUniqueTitlePointer->bookInfo;
					while (traverseColumnPointer->nextBookInventory != NULL)
					{
						traverseColumnPointer = traverseColumnPointer->nextBookInventory;
					}
					toAdd->bookID = generateInventoryID(bookTitleHead, bookid);
					toAdd->bookAvailability = true;
					traverseColumnPointer->nextBookInventory = toAdd;
				}
				cout << "Book Added successfully" << endl;
				system("PAUSE");
				break;
			}
			currentUniqueTitlePointer = currentUniqueTitlePointer->nextBookTitle;
		}
	}

	/* ADD EXISTING BOOK TITLE FUNCTION OVERLOAD */
	void addExistingBookTitle(BookTitle *&bookTitleHead, string bookTitle, string bookAuthor)
	{
		BookTitle *currentColumnPointer = bookTitleHead;
		while (currentColumnPointer != NULL)
		{
			if (bookTitle == currentColumnPointer->bookInfo->bookTitle && bookAuthor == currentColumnPointer->bookInfo->bookAuthor)
			{
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
	bool checkDuplicateUniqueTitle(BookTitle *&bookTitleHead, string bookTitle, string bookAuthor)
	{
		if (bookTitleHead != NULL)
		{
			BookTitle *currentUniqueTitlePointer = bookTitleHead;
			while (currentUniqueTitlePointer != NULL) /* TRAVERS THE LIST VERTICALLY */
			{
				if (bookTitle == currentUniqueTitlePointer->bookInfo->bookTitle && bookAuthor == currentUniqueTitlePointer->bookInfo->bookAuthor)
				{
					return true;
					break;
				}
				currentUniqueTitlePointer = currentUniqueTitlePointer->nextBookTitle;
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
		if (bookTitleHead == NULL)
		{
			cout << "Book List Empty!";
		}
		else
		{
			BookTitle *currentBookTitlePointer = bookTitleHead;
			cout << "How would you like to view the Book List\n1. Expanded\n2. Simplified" << endl;
			cout << "Menu: ";
			cin >> ch;
			system("CLS");

			switch (ch)
			{
			case 1:
				cout << expandedBookView << endl;
				while (currentBookTitlePointer != NULL)
				{
					if (currentBookTitlePointer->bookInfo->nextBookInventory != NULL)
					{
						BookInformation *currentColumnBook = currentBookTitlePointer->bookInfo;
						while (currentColumnBook != NULL)
						{
							string res = currentColumnBook->bookAvailability ? "Available" : "Unavailable";
							cout << currentColumnBook->bookID << "\t" << currentColumnBook->bookTitle << "\t" << currentColumnBook->bookAuthor << "\t" << currentColumnBook->genre << "\t" << currentColumnBook->category << "\t" << res << endl;
							currentColumnBook = currentColumnBook->nextBookInventory;
						}
					}
					else
					{
						string res = currentBookTitlePointer->bookInfo->bookAvailability ? "Available" : "Unavailable";
						cout << currentBookTitlePointer->bookInfo->bookID << "\t" << currentBookTitlePointer->bookInfo->bookTitle << "\t" << currentBookTitlePointer->bookInfo->bookAuthor << "\t" << currentBookTitlePointer->bookInfo->genre << "\t" << currentBookTitlePointer->bookInfo->category << "\t\t" << res << endl;
					}
					currentBookTitlePointer = currentBookTitlePointer->nextBookTitle;
				}
				break;
			case 2:
				int inventory;
				cout << simplifiedBookView << endl;
				while (currentBookTitlePointer != NULL)
				{
					inventory = 1;
					if (currentBookTitlePointer->bookInfo->nextBookInventory != NULL)
					{
						BookInformation *currentColumnBook = currentBookTitlePointer->bookInfo;
						while (currentColumnBook->nextBookInventory != NULL)
						{
							inventory += 1;
							currentColumnBook = currentColumnBook->nextBookInventory;
						}
						cout << currentBookTitlePointer->bookInfo->bookID << "\t" << currentColumnBook->bookTitle << "\t" << currentColumnBook->bookAuthor << "\t" << currentColumnBook->genre << "\t" << currentColumnBook->category << "\t" << inventory << endl;
					}
					else
					{
						cout << currentBookTitlePointer->bookInfo->bookID << "\t" << currentBookTitlePointer->bookInfo->bookTitle << "\t" << currentBookTitlePointer->bookInfo->bookAuthor << "\t" << currentBookTitlePointer->bookInfo->genre << "\t" << currentBookTitlePointer->bookInfo->category << "\t\t" << inventory << endl;
					}
					currentBookTitlePointer = currentBookTitlePointer->nextBookTitle;
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
			BookTitle *current = bookTitleHead;
			string tempID = current->bookInfo->bookID;
			tempID = tempID.substr(2, 5); //ONLY TAKES THE VALUE 5 CHARACTERS AFTER BK
			string id = to_string(stoi(tempID) + 1);
			return "BK" + id;
		}
	}

	/*
		GENERATE INVENTORY ID
		- A function that generates unique inventory ID
		- ex. BK10001-1
	*/
	string generateInventoryID(BookTitle *&bookTitleHead, string mainID)
	{
		BookTitle *currentBookTitlePointer = bookTitleHead;
		while (currentBookTitlePointer != NULL)
		{
			if (mainID == currentBookTitlePointer->bookInfo->bookID)
			{
				BookInformation *currentBookInformation = currentBookTitlePointer->bookInfo;
				if (currentBookInformation->nextBookInventory == NULL)
				{
					return mainID + "-1";
					break;
				}
				else
				{
					string lastID;
					while (currentBookInformation != NULL)
					{
						lastID = currentBookInformation->bookID;
						currentBookInformation = currentBookInformation->nextBookInventory;
					}
					string inventoryNumber = lastID.substr(8, 5); //get the value after "-"
					string id = to_string(stoi(inventoryNumber) + 1);
					return mainID + "-" + id;
				}
			}
			currentBookTitlePointer = currentBookTitlePointer->nextBookTitle;
		}
	}
} // namespace book

#endif