#include <string>
#include <iostream>

using namespace std;

namespace patron {
	int age, day, month, year;
	string id, firstName, lastName;

	class Patron {
		public:
			string getFirstName() {
				return this->firstName;
			}
			string getLastName() {
				return this->lastName;
			}
			void setFirstname(string fn) {
				this->firstName = fn;
			}
			void setLastName(string ln) {
				this->lastName = ln;
			}
		private:
			class DateOfBirth {
				int day, month, year;
			};
			string id, firstName, lastName;
			DateOfBirth dob;
			char gender;
			int age;
	};
	void insertPatron() {
		Patron* p = new Patron;
		cout << "Enter Patron details" << endl;
		cout << "First name: ";

		cout << "Last name: ";

		cout << "Gender (M/F): ";

		cout << "Date of Birth (dd/mm/yyy): ";
		cin >> day >> month >> year;

	}
}