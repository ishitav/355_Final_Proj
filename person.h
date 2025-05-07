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
#include <map>         // for attribute map

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
    vector<Person*> myfriends;

    map<string, string> attributes;   // key-value attribute metadata

public:
    Person();
    ~Person();
    Person(string filename);
    Person(string f_name, string l_name, string b_date, string email, string phone);
    Person(string f_name, string l_name, string b_date, string emailType, string email, string phoneType, string phone);

    void set_person();
    void set_person(string filename);

    void print_person();
    void print_friends();
    void makeFriend(Person* p);

    string get_code_name();

    // Phase 3 metadata support
    void set_attribute(string key, string value);
    string get_attribute(string key);
    map<string, string>& get_attributes();

    bool operator==(const Person& rhs);
    bool operator!=(const Person& rhs);
};

#endif