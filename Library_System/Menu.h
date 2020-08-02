#ifndef MENU
#define MENU

#include <iostream>
#include "Patron.h"
#include "Book.h"

using namespace std;
using namespace patron;
using namespace book;

namespace menu {
	/*INITIALIZE EMPTY HEADER / LIST*/
	BookTitle* bookTitleHead = NULL;
	Patron* patronHead = NULL;

	/*SOME PREDEFINED BOOKS TO TEST OUT AS THIS PROGRAM IS NOT USING FILES OR DATABASE*/
	BookTitle* bookTitle1 = new BookTitle(new BookInformation("Big Bang Theory", "John Wick", "Fantasy", "Fiction", true, "BK10001", NULL), NULL);
	BookTitle* bookTitle2 = new BookTitle(new BookInformation("Bang Bang", "Door Door", "Science", "Fiction", true, "BK10002", NULL), bookTitle1);
	BookTitle* bookTitle3 = new BookTitle(new BookInformation("Harry Potter", "JK Rowling", "Fantasy", "Fiction", false, "BK10003", new BookInformation("Harry Potter", "JK Rowling", "Fantasy", "Fiction", true, "BK10003-1000", NULL)), bookTitle2);
	
	/*LOGIN CREDENTIALS*/
	const string username = "lmsadmin", password = "12345";
	/*USER INPUT TO MATCH LOGIN CREDENTIALS*/
	string* uname, * pass;
	class Menu {
		public:
			Menu(int menuOption) {
				bookTitleHead = bookTitle3;	/*REMOVE OR COMMENT THIS IF YOU WANT TO START WITH AN EMPTY HEADER OR LIST*/
				/*
					As switch statement in C++ does not support comparing strings, int value is used instead.
					reference:
					1 - To show the login menu; Start of the program;
					2 - To show the dashboard for patron and menu functions;
				*/
				switch (menuOption) {
					int choice;
					case 1:
						do {
							cout << "Welcome to LMS\nLogin to access features\n\n1. Login\n0. Exit\n\nMenu: ";
							cin >> choice;
							switch (choice) {
								case 1:
									uname = new string;
									pass = new string;
									do {
										system("CLS");
										cout << "Username: ";
										cin >> *uname;
										cout << "Password: ";
										cin >> *pass;
									} while (*uname != username || *pass != password);
									delete uname, pass;
									system("CLS");
									Menu(2);
									break;
								case 0: break;
							}
						} while (choice != 0);
						break;
					case 2:
						do {
							cout << "Welcome to the dashboard, what would you like to do?" << endl;
							cout << "1. Book Functions\n2. Patron Functions\n\n0. Logout" << endl;
							cout << "Menu: ";
							cin >> choice;
							switch (choice) {
								case 0: system("CLS");  break;
								case 1:
									do {
										system("CLS");
										cout << "Book Functionalities" << endl;
										cout << "\n1. Insert Book Information\n2. Display Books\n3. Search Books\n4. Update Book Information\n\n0. Back" << endl;
										cout << "Menu: ";
										cin >> choice;
										switch (choice) {
										case 1:
											promptNewBook(bookTitleHead);
											system("CLS");
											break;
										case 2:
											displayAllBooks(bookTitleHead);
											system("PAUSE");
											system("CLS");
											break;
										case 3:
											promptSearch(bookTitleHead);
											system("PAUSE");
											system("CLS");
											break;
										case 4:
											break;
										case 0:
											system("CLS");
											Menu(2);
											break;
										}
									} while (choice != 0);
									break;
								case 2:
									/*PATRON FUNCTIONALITY HERE*/
									do {
										system("CLS");
										cout << "Patron Functionalities" << endl;
										cout << "\n1. View Patron\n2. Search Patron\n3. Insert Patron\n4. Update Patron\n5. Delete Patron\n\n6. Borrow Book\n7. Return Book\n8. Patron Book History\n9. View All Patron with Active Books\n\n0. Back" << endl;
										cout << "Menu: ";
										cin >> choice;
										switch (choice) {
										case 1:
											viewPatron(patronHead);
											system("CLS");
											break;
										case 2:
											searchPatron(patronHead);
											system("CLS");
											break;
										case 3:
											promptNewPatron(patronHead);
											system("CLS");
											break;
										case 0:
											system("CLS");
											Menu(2);
											break;
										}
									} while (choice != 0);
							}
						} while (choice != 0);
						break;
				}
			}
	};
}

#endif