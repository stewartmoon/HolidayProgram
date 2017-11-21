/* Author: Stewart Moon 
Class: CSC 223-100
Professor: Jeffrey Howard
Due Date: 11/21/2017
Description: Holiday program using the class Date to calculate different days of the week for holidays
*/
#include "Date.h"
#include <iostream>
using namespace std;

int main()
{
	//Define Array of 6 holidays
	Date holidays[6];

	//prompt the user for the year
	int year;
	cout << "Please enter a Year: " << endl;
	cin >> year;

	//Define Holidays and their dates
	Date newYears(1, 1, year);
	holidays[0] = newYears;

	Date julyFourth(7, 4, year);
	holidays[1] = julyFourth;

	Date birthday(10, 1, year);
	holidays[2] = birthday;

	Date halloween(10, 31, year);
	holidays[3] = halloween;

	Date christmas(12, 25, year);
	holidays[5] = christmas;
	//Pass the year to the function thanksgiving
	Date giving = giving.thanksgiving(year);
	holidays[4] = giving;

	//Logic to calculate the date for the holiday arrays.
	for (int x = 0; x <= 5; x++)
	{
		int day = holidays[x].weekday();
		cout << "The Holiday " << holidays[x] << " is on a ";
		switch (day)
		{
		case 0:
			cout << "Sunday" << endl;
			break;
		case 1:
			cout << "Monday" << endl;
			break;
		case 2:
			cout << "Tuesday" << endl;
			break;
		case 3:
			cout << "Wednesday" << endl;
			break;
		case 4:
			cout << "Thursday" << endl;
			break;
		case 5:
			cout << "Friday" << endl;
			break;
		case 6:
			cout << "Saturday" << endl;
			break;
		}
	}
	return 0;
}//main