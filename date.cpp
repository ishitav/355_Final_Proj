#include "date.h"
#include <iostream>
#include <sstream>
using namespace std;

static const string month_names[13] = {
    "", "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

Date::Date(string raw_date) {
    char slash;
    stringstream ss(raw_date);
    ss >> month >> slash >> day >> slash >> year;
}

void Date::print_date(string format) {
    
        cout << month_names[month] << " " << day << ", " << year << endl;
    
}

string Date::get_formatted_date(string format) {
    return month_names[month] + " " + to_string(day) + ", " + to_string(year);
}

bool Date::operator==(const Date& rhs) {
    return month == rhs.month && day == rhs.day && year == rhs.year;
}