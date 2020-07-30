#ifndef PATRON	//FILE GUARDS REFER: https://www.youtube.com/watch?v=RU5JUHAiR18
#define PATRON

#include <string>
#include <iostream>
#include "Book.h"

using namespace book;
using namespace std;

namespace patron {
	
	class DateOfBirth {
		public:
			int day, month, year;
	};
	char ch;
	string id, firstName, lastName;
	DateOfBirth dob;
	char gender;
	int size;
	
	class Patron {
		public:
			string getID() {
				return this->id;
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
			DateOfBirth getDOB() {
				return this->dob;
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
			void setDOB(DateOfBirth dob) {
				this->dob = dob;
			}
			Patron* linkToNextPatron;
			book::Book * bookList;
		private:
			string id, firstName, lastName;
			DateOfBirth dob;
			char gender;
	};

	int getSize(Patron*& head);
	void promptNewPatron(Patron*&);
	void insertPatron(Patron*& head, Patron * newPatron);

	/*
		PROMPT NEW PATRON
		- A function that prompts the user to input new patron information.
		- Takes a pointer address as a parameter, does not work (update the pointer value) if only passing by pointer.
		- refer: https://stackoverflow.com/questions/22000190/when-passing-head-of-linked-list-to-function-why-do-we-need-to-pass-it-by-refere%5C%5C
	*/
	void promptNewPatron(Patron *& head) {
		Patron* p = new Patron;
		cout << "Enter Patron details" << endl;
		cout << "First name: ";
		cin >> firstName;
		cout << "Last name: ";
		cin >> lastName;
		cout << "Gender (M/F): ";
		cin >> gender;
		cout << "Date of Birth (dd/mm/yyyy): ";
		cin >> dob.day >> dob.month >> dob.year;

		system("CLS");

		cout << "Confirm Patron Details" << endl << endl;
		cout << "Name: " << firstName << " " << lastName << endl;
		cout << "Gender: " << gender << endl;
		cout << "Date of Birth: " << endl;
		cout << endl;
		cout << "Confirm? (Y/N): ";
		cin >> ch;
		switch (ch) {
		case 'Y':
		case 'y':
			p->setFirstname(firstName);
			p->setLastName(lastName);
			p->setGender(gender);
			p->setDOB(dob);
			//p->bookList = NULL;
			p->linkToNextPatron = NULL;
			insertPatron(head, p);
			break;
		case 'N':
		case'n':
			system("CLS");
			promptNewPatron(head);
			break;
		}
	}

	/*
		INSERT PATRON
		- A function that inserts a new patron object to the first node of the linked list.
		- Takes 2 parameters, reference to pointer and pointer to patron object.
		- refer: https://stackoverflow.com/questions/22000190/when-passing-head-of-linked-list-to-function-why-do-we-need-to-pass-it-by-refere%5C%5C
	*/
	void insertPatron(Patron*& head, Patron * newPatron) {
		if (head == NULL) {
			head = newPatron;
		}
		else {
			Patron* current = head;
			newPatron->linkToNextPatron = current;
			head = newPatron;
		}
	}

	void viewPatron(Patron * &head) {
		if (head == NULL) {
			system("CLS");
			cout << "Patron List is empty!" << endl;
			system("PAUSE");
		}
		else {
			system("CLS");
			Patron * current = head;
			cout << "Name\t\tGender\tDate of Birth" << endl;
			while (current != NULL) {
				cout << current->getFirstName() << " " << current->getLastName() << "\t" << current->getGender() << "\t" << current->getDOB().day << "/" << current->getDOB().month << "/" << current->getDOB().year<< endl;
				current = current->linkToNextPatron;
			}
			cout << "\nTotal Patron(s): " << getSize(head) << " Patron(s)." << endl;
			system("PAUSE");
			system("CLS");
		}
	}

	int getSize(Patron * &head) {
		size = 0;
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

	void validateDOB() {
		do {

		} while (dob.day < 0);
	}
}

#endif