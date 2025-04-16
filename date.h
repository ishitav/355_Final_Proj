#ifndef DATE_H
#define DATE_H

#include <string>
using namespace std;

class Date {
private:
    int month;
    int day;
    int year;

public:
    Date(string raw_date);
    void print_date(string format = "full");
    string get_formatted_date(string format = "full");
    bool operator==(const Date& rhs);
};

#endif