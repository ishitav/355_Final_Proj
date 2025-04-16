
#include "person.h"

Person::Person(){
    // I'm already done! 
    set_person();
}

Person::Person(string f_name, string l_name, string b_date, string emailType, string email, string phoneType, string phone) {
    this->f_name = f_name;
    this->l_name = l_name;
    birthdate = new Date(b_date);
    this->email = new Email(emailType, email);
    this->phone = new Phone(phoneType, phone);
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

    // cout << "Created person " << f_name << l_name << endl; 
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
    ifstream file(filename.c_str());

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string b_date, email_line, phone_line;

    getline(file, f_name);     // Julia Scarlett Elizabeth
    getline(file, l_name);     // Louis-Dreyfus
    getline(file, b_date);     // 1/13/1961
    getline(file, phone_line); // (Home) 310-192-2011
    getline(file, email_line); // (Work) julia@wh.com

    birthdate = new Date(b_date);

    // Parse phone
    string phone_type = "Home", phone_number = "000-000-0000";
    size_t phone_pos = phone_line.find(')');
    if (phone_line.front() == '(' && phone_pos != string::npos) {
        phone_type = phone_line.substr(1, phone_pos - 1);
        phone_number = phone_line.substr(phone_pos + 2); // skip ") "
    }

    // Parse email
    string email_type = "Work", email_address = "invalid@email.com";
    size_t email_pos = email_line.find(')');
    if (email_line.front() == '(' && email_pos != string::npos) {
        email_type = email_line.substr(1, email_pos - 1);
        email_address = email_line.substr(email_pos + 2); // skip ") "
    }

    email = new Email(email_type, email_address);
    phone = new Phone(phone_type, phone_number);

    file.close();
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
	birthdate->print_date();
    
    phone->print();
    email->print();
}
