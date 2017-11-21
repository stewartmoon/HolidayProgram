#include "Date.h"

/*Date::Date() {
time_t t = time(0);   // get time now
struct tm * now = localtime(&t);
month = now->tm_mon + 1;
day = now->tm_mday;
year = now->tm_year + 1900;
setDays();
}//constructor for today: cross platform
*/

Date::Date() {
	struct tm newtime;
	__time64_t long_time;
	char timebuf[26];
	errno_t err;
	// Get time as 64-bit integer.
	_time64(&long_time);
	// Convert to local time.
	err = _localtime64_s(&newtime, &long_time);
	month = newtime.tm_mon + 1;
	day = newtime.tm_mday;
	year = newtime.tm_year + 1900;
	setDays();
}//constructor for today for Visual Studio


bool validDate(int m, int d, int y) {
	int days2[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	bool valid = true; //assume it is valid until found to be invalid
	if (y<1000) valid = false;
	if (m<1 || m>12) valid = false;
	if (valid) {
		if (leapYear(y)) days2[2] = 29;
		if (d<1 || d>days2[m]) valid = false;
	}
	return valid;
}//validDate
void Date::setDays(void) {
	int days2[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	for (int m = 0; m < 13; m++) days[m] = days2[m];
	if (leapYear()) days[2] = 29;
}
Date::Date(int m, int d, int y) {
	//constructor to assign values to month day and year 
	if (validDate(m, d, y)) {
		month = m;
		day = d;
		year = y;
	}
	else {
		month = day = 1;
		year = 1970; //Unix time starting point
	} //not valid: set to default valid date
	for (int m = 0; m<13; m++) days[m] = days2[m];
} //constructor with assigned values

Date::Date(int julian) {
	//Fliegel-Van Flandern algorithm to convert Julian date to Gregorian number month, day, and year
	gregorian(julian, month, day, year);
	setDays();
}//Date Julian 

Date::Date(string str) { //constructor for todays date as "mm/dd/year
						 //Parse str by adding one char at a s time to the token until a "/" is encounter.
						 //When "/" is encountered start the next token
						 //int p=0;
	int count = 0;
	int num[3];
	string token[3];
	int len = str.length();
	for (int p = 0; p<len; p++) {
		if (str.substr(p, 1) == "/") count++;
		else token[count] += str.substr(p, 1);
	}//parse str to create array of tokens
	bool error = false;
	for (int p = 0; p<3; p++) {
		try {
			num[p] = stoi(token[p]);
		}//try to convert to int
		catch (invalid_argument&) {
			num[p] = -1;
			error = true;
		} //catch
	}//each of the 3 tokens
	if (!error && validDate(num[0], num[1], num[2])) {
		month = num[0];
		day = num[1];
		year = num[2];
	} //no error
	else {
		month = day = 1;
		year = 1970; //Unix time starting point
	}  //not valid: set to default valid date 
	for (int m = 0; m<13; m++) days[m] = days2[m];
}//constructor with string such as "10/31/2016"

Date Date::operator=(const Date& otherDate) {
	//assigns another instance of the date class to this.
	month = otherDate.month;
	day = otherDate.day;
	year = otherDate.year;
	return *this;  //allows date1=date=date3;
}//overloaded operator =

Date Date::operator+(int numDays) {
	//Adds the number of days to the Julian date.
	Date other(month, day, year); //make copy of the date
	int jd = other.julian();  //find the Julian date
	jd += numDays; //add the number of days to the Julian date
	gregorian(jd, other.month, other.day, other.year); //Convert the Julian date back to Gregorian
	if (other.leapYear()) days2[2] = 29; else days2[2] = 28;
	for (int m = 0; m<13; m++) other.days[m] = days2[m];
	return other;
} //operator +

int Date::dayofYear() const {
	//returns the day of the year, ie 2/1/???? is the 32 day of the year
	int total = day;
	for (int m = 1; m<month; m++) total += days[m];
	return total;
}//dayofYear


static void gregorian(int julian, int &mth, int &d, int &y) {
	//Fliegel-Van Flandern algorithm to convert Julian date to Gregorian month, day, and year
	int p, q, r, s, t, u, v;
	p = julian + 68569;
	q = 4 * p / 146097;
	r = p - (146097 * q + 3) / 4;
	s = 4000 * (r + 1) / 1461001;
	t = r - 1461 * s / 4 + 31;
	u = 80 * t / 2447;
	v = u / 11;
	y = 100 * (q - 49) + s + v;
	mth = u + 2 - 12 * v;
	d = t - 2447 * u / 80;
} //Gregorian

int Date::julian() const {
	int jd = day - 32075 + 1461 * (year + 4800 + (month - 14) / 12) / 4 +
		367 * (month - 2 - (month - 14) / 12 * 12) / 12 - 3 * ((year + 4900 + (month - 14) / 12) / 100) / 4;
	return jd;
}//julian

bool Date::leapYear() const {
	bool leap = false;
	if (year % 4 == 0) leap = true;
	if (year % 100 == 0 && year % 400 != 0) leap = false;
	return leap;
}//leapYear

static bool leapYear(int yr) {
	bool leap = false;
	if (yr % 4 == 0) leap = true;
	if (yr % 100 == 0 && yr % 400 != 0) leap = false;
	return leap;
}//leapYear

int Date::weekday() const {
	//returns 0 for Sunday, 1 for Monday, etc.
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	int y = year;
	y -= month < 3;
	return (y + y / 4 - y / 100 + y / 400 + t[month - 1] + day) % 7;
}//weekday

int Date::getMonth() const {
	//private variables cannot be accessed directly but require "getter" functions
	return month;
}//getMonth

int Date::getDay() const {
	return day;
}//

int Date::getYear() const {
	return year;
}//getYear

string Date::toString() const {
	stringstream oss;  //a stream to append the values
	oss << month << "/" << day << "/" << year;
	return oss.str();
}//toString

bool Date::operator==(const Date& otherDate) {
	return (month == otherDate.month && day == otherDate.day && year == otherDate.year);
}//operator ==

bool Date::operator<(const Date& otherDate) {
	//A date is less than another date if is earlier
	bool result = false; //assume false until proven true
	if (year<otherDate.year) result = true;
	else if (year == otherDate.year && month<otherDate.month) result = true;
	else if (year == otherDate.year && month == otherDate.month && day<otherDate.day) result = true;
	return result;
}//operator<

bool Date::operator>(const Date& otherDate) {
	//Convert both dates to Julian and compare the Julian dates
	int jd1 = julian();
	int jd2 = otherDate.julian();
	return jd1>jd2;
}//operator>

ostream& operator << (ostream &output, const Date &d) {
	output << d.toString();
	return output;
} // operator <<

istream& operator >> (istream &input, Date &d) {
	string s;
	input >> s;
	Date other(s); //create a new Date
	d = other; //assign the new Date to d
	return input;
} // operator >>
Date Date::thanksgiving(int year)
{
	Date thanks(11, 1, year);
	while (thanks.weekday() != 4)
	{
		thanks = thanks + 1;
	}
	thanks = thanks + 21;
	return thanks;
}