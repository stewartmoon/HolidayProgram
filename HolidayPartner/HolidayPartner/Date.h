#pragma once
#ifndef Date_H
#define Date_H
#include <iostream>
#include <sstream> 
#include <ctime>
#include <string>
using namespace std;

class Date {
private:
	int month, day, year;
	int days[13];
	void setDays();
public:
	//constructors
	Date(); //constructor for todays date
	Date(int m, int d, int y); //constructor to assign date
	Date(string str); //constructor for todays date as "mm/dd/year
	Date(int gregorian); //constructor to convert a Gregorian date to Date

						 //methods
	int getMonth() const; //returns the private variable month
	int getDay() const; //returns the private variable day
	int getYear() const; //returns the private variable year
	string toString() const; //returns the string mm/dd/yyyy
	bool leapYear() const; //determines if the year is a leap year
	int dayofYear() const; //returns the day of the year: ie 2/1/???? is the 32 day of year
	int julian() const;
	int weekday() const; //returns 0 for Sunday, 1 for Monday, etc.

						 //overloaded operators
	bool operator==(const Date& otherDate); //2 dates are equal if month, day and year are equal
	bool operator<(const Date& otherDate); //a date is < another date if it is earlier
	bool operator>(const Date& otherDate); //a date is > another date if it is later
	Date operator=(const Date& otherDate); //let's you copy one date to another.
	Date operator+(int); //Assign new values to the date after adding the number of days
	friend ostream& operator << (ostream &output, const Date &d);
	friend istream& operator >> (istream &input, Date &d);
	Date thanksgiving(int year); //member function that calculates the date 
};
bool validDate(int m, int d, int y); //test other date
bool leapYear(int y); //let's you test any year, not just the year for the instance
int julian(int m, int d, int y); //convert any date to Julian
void gregorian(int jd, int &mth, int &d, int &y);
static int days2[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
#endif