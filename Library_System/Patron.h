#ifndef PATRON	//FILE GUARDS REFER: https://www.youtube.com/watch?v=RU5JUHAiR18
#define PATRON

#pragma warning(disable: 4996) //REFER: https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-3-c4996?f1url=https%3A%2F%2Fmsdn.microsoft.com%2Fquery%2Fdev16.query%3FappId%3DDev16IDEF1%26l%3DEN-US%26k%3Dk(C4996)%26rd%3Dtrue&view=vs-2019

#include <string>
#include <iostream>
#include <ctime>
#include "Book.h"
#include "CustomDate.h"

using namespace book;
using namespace std;
using namespace date;

namespace patron {
	Date dob;
	char ch;
	string id, firstName, lastName;
	char gender;
	
	class Patron {
		public:
			Patron* linkToNextPatron;
			char* registeredDate;
			string patronID;
			Date dateOfBirth;
			string getID() {
				return patronID;
			}
			char getGender() {
				return this->gender;
			}
			string getFirstName() {
				return this->firstName;
			}
			string getLastName() {
				return this->lastName;
			}
			Date getDateOfBirth() {
				return this->dateOfBirth;
			}
			void setFirstname(string fn) {
				this->firstName = fn;
			}
			void setLastName(string ln) {
				this->lastName = ln;
			}
			void setGender(char gender) {
				this->gender = gender;
			}
			void setDob(Date dob) {
				this->dateOfBirth = dob;
			}

		private:
			string firstName, lastName;
			char gender;
	};

	//FUNCTION PROTOTYPES
	int getSize(Patron*& head);
	void promptNewPatron(Patron*&);
	void insertPatron(Patron*& head, Patron* newPatron);
	void searchPatron(Patron*& head);
	string generateID(Patron*& patronHead);
	bool printPatronDetails(Patron* patron);
	void viewPatron(Patron*& head);

	/*
		SEARCH PATRON FUNCTION
		- Function that search for a specified patron by name or id
	*/
	void searchPatron(Patron*& head) {
		if (head == NULL) {
			system("CLS");
			cout << "Patron list is empty" << endl;
			system("PAUSE");
		}
		else {
			system("CLS");
			Patron* current = head;
			string patronInfo;
			bool flag = false;
			int ch;
			cout << "Search Patron\n1. ID\n2. Full Name\n" << endl;
			cout << "Menu: ";
			cin >> ch;
			switch (ch) {
			case 1:
				system("CLS");
				cout << "Enter ID to search" << endl;
				cout << "ID: ";
				cin >> patronInfo;
				while (current != NULL) {
					bool res = patronInfo == current->getID() ? printPatronDetails(current) : false;
					if (res) { flag = true; break; }
					else current = current->linkToNextPatron;
				}
				break;
			case 2:
				system("CLS");
				cout << "Enter Name to search" << endl;
				cout << "Full Name: ";
				cin.ignore();
				getline(cin, patronInfo);
				while (current != NULL) {
					string concatenate = current->getFirstName() + " " + current->getLastName();
					bool res = patronInfo == concatenate ? printPatronDetails(current) : false;
					if (res) { flag = true; break; }
					else current = current->linkToNextPatron;
				}
				break;
			}
			if (!flag) {
				cout << "Patron Not found" << endl;
				system("PAUSE");
			}
		}
	}

	/*
		PRINT PATRON DETAILS - SINGLE
		- A function that prints a single patron information, implemented during searching
	*/
	bool printPatronDetails(Patron * patron) {
		system("CLS");
		cout << "Patron Details" << endl;
		cout << "Patron ID\tName\t\tGender\tDate of Birth\tRegistered Date" << endl;
		cout << patron->getID() << "\t\t" << patron->getFirstName() << " " << patron->getLastName() << "\t" << patron->getGender() << "\t" << patron->getDateOfBirth().day << "/" << patron->getDateOfBirth().month << "/" << patron->getDateOfBirth().year << "\t" << patron->registeredDate << endl;
		system("PAUSE");
		return true;
	}

	/*
		PROMPT NEW PATRON
		- A function that prompts the user to input new patron information.
		- Takes a pointer address as a parameter, does not work (update the pointer value) if only passing by pointer.
		- refer: https://stackoverflow.com/questions/22000190/when-passing-head-of-linked-list-to-function-why-do-we-need-to-pass-it-by-refere%5C%5C
	*/
	void promptNewPatron(Patron *& head) {
		system("CLS");
		time_t currentDateTime = time(0);
		Patron* p = new Patron;
		cout << "Enter Patron details" << endl;
		cout << "First name: ";
		cin >> firstName;
		cout << "Last name: ";
		cin >> lastName;
		cout << "Gender (M/F): ";
		cin >> gender;
		do {
			cout << "Date of Birth (dd/mm/yyyy): ";
			cin >> dob.day >> dob.month >> dob.year;
		} while (!checkDate(dob.day, dob.month, dob.year));

		system("CLS");

		cout << "Confirm Patron Details" << endl << endl;
		cout << "Name: " << firstName << " " << lastName << endl;
		cout << "Gender: " << gender << endl;
		cout << "Date of Birth: " << dob.day << "/" << dob.month << "/" << dob.year << endl;
		cout << endl;
		cout << "Confirm? (Y/N): ";
		cin >> ch;
		switch (ch) {
		case 'Y':
		case 'y':
			p->patronID = generateID(head);
			p->setFirstname(firstName);
			p->setLastName(lastName);
			p->setGender(toupper(gender));
			p->setDob(dob);
			p->registeredDate = ctime(&currentDateTime);
			p->linkToNextPatron = NULL;
			insertPatron(head, p);
			break;
		case 'N':
		case'n':
			system("CLS");
			//promptNewPatron(head);
			break;
		}
	}

	/*
		INSERT PATRON
		- A function that inserts a new patron object to the FIRST NODE of the linked list.
		- Takes 2 parameters, reference to pointer and pointer to patron object.
		- refer: https://stackoverflow.com/questions/22000190/when-passing-head-of-linked-list-to-function-why-do-we-need-to-pass-it-by-refere%5C%5C
	*/
	void insertPatron(Patron*& head, Patron * newPatron) {
		if (head == NULL) {
			head = newPatron;
			cout << "Added Patron successfully!" << endl;
			system("PAUSE");
		}
		else {
			Patron* current = head;
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
	void viewPatron(Patron * &head) {
		if (head == NULL) {
			system("CLS");
			cout << "Patron List is empty!" << endl;
			system("PAUSE");
		}
		else {
			system("CLS");
			Patron * current = head;
			cout << "Patron ID\tName\t\tGender\tDate of Birth\tRegistered Date" << endl;
			while (current != NULL) {
				cout << current->getID() << "\t\t" << current->getFirstName() << " " << current->getLastName() << "\t" << current->getGender() << "\t" << current->getDateOfBirth().day << "/" << current->getDateOfBirth().month << "/" << current->getDateOfBirth().year << "\t" << current->registeredDate << endl;
				current = current->linkToNextPatron;
			}
			cout << "\nTotal Patron(s): " << getSize(head) << " Patron(s)." << endl;
			system("PAUSE");
			system("CLS");
		}
	}

	/*
		GET SIZE FUNCTION
		- A function to get the size of Patron Linked List
	*/
	int getSize(Patron * &head) {
		int size = 0;
		if (head == NULL) {
			return 0;
		}
		else {
			Patron* current = head;
			while (current != NULL) {
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
	string generateID(Patron * & patronHead) {
		if (patronHead == NULL) {
			return "PT1";
		}
		else {
			Patron* current = patronHead;
			string tempID = current->getID();
			tempID = tempID.substr(2, 5);
			string id = to_string(stoi(tempID) + 1);
			return "PT" + id;
		}
	}
}

#endif