#ifndef BOOK //FILE GUARDS REFER: https://www.youtube.com/watch?v=RU5JUHAiR18
#define BOOK

#include <string>
#include <iostream>
#include "CustomDate.h"

using namespace std;
using namespace date;

namespace book
{

	//CLASS PROTOTYPES
	class BookInformation;
	class BookTitle;

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
	};

	//FUNCTION PROTOTYPES
	string generateBookID(BookTitle *&);
	void insertBookDetail(BookTitle *&, BookTitle *);
	void promptNewBook(BookTitle *&);
	void displayAllBooks(BookTitle *&);

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
			cin.ignore();							 //refer: https://stackoverflow.com/questions/12691316/getline-does-not-work-if-used-after-some-inputs
			getline(cin, newBookInformation->bookTitle); // ALLOWS THE INPUT OF STRING WITH SPACES || refer: https://stackoverflow.com/questions/30758245/how-to-store-a-complete-sentence-with-white-spaces-in-a-string-in-cpp
			cout << "Book Author: ";
			getline(cin, newBookInformation->bookAuthor);
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

				newBookInformation->bookID = generateBookID(bookTitleHead);
				newBookInformation->bookAvailability = true;
				newBookInformation->nextBookInventory = NULL;

				BookTitle *newBookTitle = new BookTitle;
				newBookTitle->bookInfo = newBookInformation;
				newBookTitle->nextBookTitle = NULL;
				insertBookDetail(bookTitleHead, newBookTitle);
			}
			system("PAUSE");
			break;
		case 2:
			string bookID;
			cout << "Enter Book ID to add inventory" << endl;
			cout << "BOOKID: ";
			cin >> bookID;
			BookTitle* currentColumn = bookTitleHead;
			while (currentColumn != NULL) {
				if (bookID == currentColumn->bookInfo->bookID) {
					BookInformation* toAdd = new BookInformation(currentColumn->bookInfo->bookTitle, currentColumn->bookInfo->bookAuthor, currentColumn->bookInfo->genre, currentColumn->bookInfo->category, currentColumn->bookInfo->bookAvailability, currentColumn->bookInfo->bookID, NULL);
					if (currentColumn->bookInfo->nextBookInventory == NULL) {
						currentColumn->bookInfo->nextBookInventory = toAdd;
					}
					else {
						BookInformation* traverseRow = currentColumn->bookInfo;
						while (traverseRow->nextBookInventory != NULL) {
							traverseRow = traverseRow->nextBookInventory;
						}
						traverseRow->nextBookInventory = toAdd;
					}
					break;
				}
				currentColumn = currentColumn->nextBookTitle;
			}
			break;
		}
		system("PAUSE");
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
				cout << "BOOKID\tBOOKTITLE\tBOOKAUTHOR\tGENRE\tCATEGORY\tAVAILABILITY" << endl;
				while (currentBookColumn != NULL) {
					if (currentBookColumn->bookInfo->nextBookInventory != NULL) {
						BookInformation* currentRow = currentBookColumn->bookInfo;
						while (currentRow != NULL) {
							string res = currentRow->bookAvailability ? "Available" : "Unavailable";
							cout << currentRow->bookID << "\t" << currentRow->bookTitle << "\t" << currentRow->bookAuthor << "\t" << currentRow->genre << "\t" << currentRow->category << "\t" << res << endl;
							currentRow = currentRow->nextBookInventory;
						}
					}
					currentBookColumn = currentBookColumn->nextBookTitle;
				}
				break;
			case 2:
				int inventory;
				cout << "BOOKID\tBOOKTITLE\tBOOKAUTHOR\tGENRE\tCATEGORY\tINVENTORY" << endl;
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
			return "BK1";
		}
		else
		{
			return "BK2";
		}
	}
} // namespace book

#endif
