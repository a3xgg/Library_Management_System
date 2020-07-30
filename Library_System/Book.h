#ifndef BOOK	//FILE GUARDS REFER: https://www.youtube.com/watch?v=RU5JUHAiR18
#define BOOK

#include <string>
#include <iostream>

using namespace std;

namespace book {
	class Book {
		public:
			string getBookID() {
				return this->bookID;
			}
			string getBookAvailability() {
				return this->bookAvailability;
			}
			string getBookTitle() {
				return this->bookTitle;
			}
			string getBookAuthor() {
				return this->bookAuthor;
			}
			string getCategory() {
				return this->category;
			}
			string getGenre() {
				return this->genre;
			}
			//Patron getBorrowedBy() {
			//	return this->borrowedBy;
			//}
			void setBookAvailability(string availability) {
				this->bookAvailability = availability;
			}
			void setBookTitle(string newTitle) {
				this->bookTitle = newTitle;
			}
			void setCategory(string newCategory) {
				this->category = newCategory;
			}
			void setGenre(string newGenre) {
				this->genre = newGenre;
			}
			//void setBorrowedBy(Patron newBorrowed) {
			//	this->borrowedBy = newBorrowed;
			//}
			Book* nextBookTitle, * nextInventoryTitle;

		private:
			string bookID, bookAvailability, bookTitle, bookAuthor, category, genre;
			//Patron borrowedBy;
			//date::Date borrowedDate, returnDate;
	};

	/*
		PROMPT NEW BOOK
		- This function just prompts the user to insert new book details.
		- Takes a reference to a pointer parameter.
		- refer: https://stackoverflow.com/questions/22000190/when-passing-head-of-linked-list-to-function-why-do-we-need-to-pass-it-by-refere%5C%5C
	*/
	void promptNewBook(Book*& bookHead) {
		int ch;

		cout << "INSERTING BOOK" << endl;
		cout << "1. Insert New Title\n2. Add Existing Title";
		cout << "Menu: ";
		cin >> ch;
		switch (ch) {
		case 1:
			break;
		case 2:
			break;
		}
	}

	void search(Book*& bookHead, int ch) {
		if (bookHead == NULL) {

		}
	}

	/*
		DISPLAY ALL BOOKS
		- A function that displays all current books, duplicate books will be shown as an 'Inventory' instead.
		- Takes a reference to pointer parameter.
		- refer: https://stackoverflow.com/questions/22000190/when-passing-head-of-linked-list-to-function-why-do-we-need-to-pass-it-by-refere%5C%5C
	*/
	void displayAllBooks(Book*& bookHead) {
		system("CLS");
		int inventory = 0;
		if (bookHead == NULL) {
			cout << "Book List is empty!" << endl;
		}
		else {
			Book* bookTitle = bookHead;
			Book* bookInventory = NULL;
			while (bookTitle->nextBookTitle != NULL) {
				cout << "Book Title\tAuthor\tGenre\tCategory\Inventory" << endl;
				if (bookTitle->nextInventoryTitle != NULL) {
					bookInventory = bookTitle;
					while (bookInventory->nextInventoryTitle != NULL) {
						inventory += 1;
						bookInventory = bookInventory->nextInventoryTitle;
					}
				}
				cout << bookTitle->getBookTitle() << "\t" << bookTitle->getBookAuthor() << endl;
			}
		}
		system("PAUSE");
	}

	void generateBookID() {

	}
}

#endif
