#ifndef DATE
#define DATE

#include <iostream>
#include <string>


namespace date {
	class Date {
		public:
			int day, month, year;
	};
	bool checkDate(int day, int month, int year);
	bool checkDate(int day, int month, int year) {
		if (day > 31 || day <= 0 || month > 12 || month <= 0) {
			return false;
		}
		else {
			switch (month) {
			case 2:
				return (day > 0 || day <= 28) ? true : false;
				break;
			//MONTHS WITH 31 DAYS
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				return (day > 0 || day <= 31) ? true : false;
				break;
			//MONTHS WITH 30 DAYS
			case 4:
			case 6:
			case 9:
			case 11:
				return (day > 0 || day <= 30) ? true : false;
				break;
			default:return false; break;
			}
		}
	}
}

#endif