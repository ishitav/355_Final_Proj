#include <iostream>
#include "person.h"

int main() {
    // Create a test Person object using hardcoded values
    std::string first_name = "Julia Scarlett Elizabeth";
    std::string last_name = "Louis-Dreyfus";
    std::string birthdate = "1/13/1961";  // Will test date formatting
    std::string email = "veep@wh.gov";
    std::string phone = "310-192-2847";   // Already formatted string

    // Call the full constructor
    Person* p = new Person(first_name, last_name, birthdate, email, phone);

    // Print all info using print_person
    p->print_person();

    // Clean up
    delete p;

    return 0;
}