#ifndef PERSON_H
#define PERSON_H

#include "date.h"
#include "contact.h"
#include "misc.h"      // for codeName helper
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

class Person {
    friend class Network;

private:
    string f_name;
    string l_name;
    Date* birthdate;
    Email* email;
    Phone* phone;
    Person* next;
    Person* prev;
    vector<Person*> myfriends;  // <-- should be myfriends, not 'friends'

public:
    Person();
    ~Person();
    Person(string filename);
    Person(string f_name, string l_name, string b_date, string email, string phone);
    Person(string f_name, string l_name, string b_date, string emailType, string email, string phoneType, string phone);

    void set_person();
    void set_person(string filename);

    void print_person();           // Prints person info and friend codes
    void print_friends();          // Prints sorted friend names

    void makeFriend(Person* p);    // Bidirectional friendship logic

    string get_code_name();        // Returns codeName(f_name, l_name)

    bool operator==(const Person& rhs);
    bool operator!=(const Person& rhs);
};

#endif