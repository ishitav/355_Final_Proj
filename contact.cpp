
#include "contact.h"
#include <iostream>
#include <string>
// TODO: Add needed libraries! 
using namespace std; 

Email::Email(string type, string email_addr){
    // TODO: Complete me!
    this->type = type; 
    this->email_addr = email_addr; 
    //assigning the function parameters to the class variables 
}


void Email::set_contact(){
    // TODO: Do not change the prompts!
    string type; 
    string email_addr; 
	
    cout << "Enter the type of email address: ";
    // some code here
    cin >> type; 
    cout << "Enter email address: ";
    // some code here
    cin >> email_addr; 

    this->type = type; 
    this->email_addr = email_addr; 
}


string Email::get_contact(string style) {
    if (style == "full")
        return "Email (" + type + "): " + email_addr;
    else
        return email_addr;
}

void Email::print() {
    cout << get_contact() << endl;
}


Phone::Phone(string type, string num){
    // TODO: It is possible that num includes "-" or not, manage it!
    // TODO: Complete this method!
    // Note: We don't want to use C++11! stol is not valid!

    this->type = type; 

    //filtering out the - 
    int string_size = num.size();
    for(int i = 0; i <string_size; i++) {
        if (num[i] == '-') {
            //delete the - and move all the other numbers up 
            for(int j = i; j <(string_size-1); j++) {
                num[j] = num[j+1];
            }

            num.resize(string_size-1);
            string_size--; 
            i--; 

        }
    } 

    //manual string to int conversion
    long result = 0; 
    for(int i = 0; i <string_size; i++) {
        char digit = num[i];
        if (digit >= '0' && digit <= '9') {
            result = result * 10 + (digit - '0');
        }
    }

    phone_num = (long) result; 

}


void Phone::set_contact(){
    // TODO: Complete this method
    // Use the same prompts as given!
    string type; 
    string num; 
	cout <<"Enter the type of phone number: ";
    cin >>type; 
	cout << "Enter the phone number: ";
    cin >> num; 

    this->type = type; 
    
    //filtering out the - 
    int string_size = num.size();
    for(int i = 0; i <string_size; i++) {
        if (num[i] == '-') {
            //delete the - and move all the other numbers up 
            for(int j = i; j <(string_size-1); j++) {
                num[j] = num[j+1];
            }

            num.resize(string_size-1);
            string_size--; 
            i--; 

        }
    } 

    //manual string to int conversion
    long result = 0; 
    for(int i = 0; i <string_size; i++) {
        char digit = num[i];
        if (digit >= '0' && digit <= '9') {
            result = result * 10 + (digit - '0');
        }
    }

    phone_num = (long) result; 

}

string Phone::get_contact(string style) {
    string num_str = to_string(phone_num);  
    string formatted = num_str;

    if (num_str.length() == 10)
        formatted = num_str.substr(0, 3) + "-" + num_str.substr(3, 3) + "-" + num_str.substr(6, 4);

    if (style == "full")
        return "(" + type + ") " + formatted;
    else
        return formatted;
}

void Phone::print() {
    cout << this->get_contact() << endl;
}

