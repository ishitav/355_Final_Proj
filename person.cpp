
#include "person.h"
#include <algorithm>

Person::Person(){
    // I'm already done! 
    set_person();
}


Person::~Person(){
    delete birthdate;
    delete phone; 
    delete email; 
    // TODO: complete the method!
}


Person::Person(string f_name, string l_name, string b_date, string email, string phone){
    // TODO: Complete this method!
    // phone and email strings are in full version
    this->f_name = f_name;
    this->l_name = l_name;
    birthdate = new Date(b_date);
    this->email = new Email("Work", email);
    this->phone = new Phone("Home", phone);
}


Person::Person(string filename){
    set_person(filename);
}


void Person::set_person(){
    // prompts for the information of the user from the terminal
    // first/last name can have spaces!
    // date format must be "M/D/YYYY"
    // We are sure user enters info in correct format.
    // TODO: complete this method!
    
    string temp;
    string type;
    string email_type;
    string email_address; 
    string phone_type;
    string phone_number;     

    cout << "First Name: ";
    // pay attention to how we read first name, as it can have spaces!
    std::getline(std::cin,f_name);

	cout << "Last Name: ";
    std::getline(std::cin,l_name);

    cout << "Birthdate (M/D/YYYY): ";
    std::getline(std::cin,temp);
    // pay attention to how we passed argument to the constructor of a new object created dynamically using new command
    birthdate = new Date(temp); 

    cout << "Type of email address: ";
    std::getline(std::cin, email_type);  
    cout << "Email address: ";
    // code here
    std::getline(std::cin, email_address);       
    
    cout << "Type of phone number: ";
    // code here
    std::getline(std::cin, phone_type);
    cout << "Phone number: ";
    // code here
    // code here
    std::getline(std::cin, phone_number);
    
    email = new Email(email_type, email_address); 
    phone = new Phone(phone_type, phone_number);
}


void Person::set_person(string filename){
    // reads a Person from a file
    // Look at person_template files as examples.     
    // Phone number in files can have '-' or not.
    // TODO: Complete this method!

    ifstream file(filename.c_str());

    string b_date, email_type, email_address, phone_type, phone_number;

    getline(file, f_name);
    getline(file, l_name);
    getline(file, b_date);
    getline(file, email_type);
    getline(file, email_address);
    getline(file, phone_type);
    getline(file, phone_number);

    birthdate = new Date(b_date);
    email = new Email(email_type, email_address);
    phone = new Phone(phone_type, phone_number);

    file.close();
    
}

bool Person::add_friend(Person* p) {
    if (p == this) return false;  // cannot friend self

    // if already friends
    if (std::find(friends.begin(), friends.end(), p) != friends.end()) {
        return false;  // already friends
    }

    friends.push_back(p); // add friend to vector
    return true;
}


bool Person::operator==(const Person& rhs){
    // TODO: Complete this method!
    // Note: you should check first name, last name and birthday between two persons
    // refer to bool Date::operator==(const Date& rhs)

    if (f_name != rhs.f_name) {
        return false; 
    }
    if (l_name != rhs.l_name) {
        return false;
    }
    if (!(*birthdate == *rhs.birthdate)) {
        return false;
    }
    return true;
}

bool Person::operator!=(const Person& rhs){ 
    // TODO: Complete this method!
    if (*this == rhs) {
        return false;
    }
    return true;
}


void Person::print_person(){
    // Already implemented for you! Do not change!
	cout << l_name <<", " << f_name << endl;
	birthdate->print_date("Month D, YYYY");
    phone->print();
    email->print();
}
