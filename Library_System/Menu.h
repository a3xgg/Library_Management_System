#include <iostream>
#include "Patron.h"

using namespace std;

namespace menu {
	const string username = "lmsadmin", password = "12345";
	string* uname, * pass;
	class Menu {
		public:
			Menu(int menuOption) {
				/*
					As switch statement in C++ does not support comparing strings, int value is used instead.
					reference:
					1 - To show the login menu; Start of the program;
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
							}
						} while (choice != 0);
						break;
					case 2:
						do {
							cout << "Welcome to the dashboard, what would you like to do?" << endl;
							cout << "1. Book Functions\n2. Patron Functions\n\n0. Logout" << endl;
							cin >> choice;
							switch (choice) {
								case 0:
									system("CLS");
									Menu(1);
									break;
								case 1:
									
									break;
							}
						} while (choice != 0);
						break;
				}
			}
	};
}