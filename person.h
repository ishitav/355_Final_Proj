#ifndef PERSON_H
#define PERSON_H

#include "date.h"
#include "contact.h"
#include "fstream"
#include <vector>

class Person{
    friend class Network;

private:
	string f_name;
	string l_name;
	Date *birthdate;
    Email *email;
    Phone *phone;
    // the following to attributes are used in the linked list.
    Person* next;
    Person* prev;
    vector<Person*> friends;    // list of pointers to friends

public: 
    Person();
    ~Person();
    Person(string filename);
    Person(string f_name, string l_name, string b_date, string email, string phone);
    Person(string f_name, string l_name, string b_date, string emailType, string email, string phoneType, string phone);
	
    void print_person();
	void set_person();
	void set_person(string filename);

    void add_friend(Person* p);
    void print_friends();   // utility

    bool operator==(const Person& rhs);
    bool operator!=(const Person& rhs);
};


#endif