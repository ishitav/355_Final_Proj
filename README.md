Team:

Ishita V (<ishitavas@usc.edu>)

Caitlin Sullivan (<ccsulliv@usc.edu>)

Gerston (<name@usc.edu>)

# Final Project Phase 1: Classes and Methods

This submission includes: 
- contact.cpp/h completed
- person.cpp/h completed
- date.cpp/h completed
- network.cpp/h completed
- misc.cpp/h (only has the banner print statement in it?)

## Compilation Instructions

To run `main.cpp` or the file that starts the network and calls functions, we must compile ALL the other files and link them to each other in the outfile: 

`g++ -std=c++11 contact.cpp person.cpp date.cpp network.cpp misc.cpp main.cpp -o proj.out`

We need c++11 for our implementation (overriding virtual functions)

## Implementation Notes

`Network` creates a DLL of Person type objects and implements the essential DLL functions with the ability to search by and return values associated with class Person. 

Any time values are accessed for class Person, the function get_"value"() is called instead of directly referencing the value with person->value because those variables are private to the Person class. 

## Test Cases and Results 

## Unsure Parts/Questions
- error checking for inputs is not implemented - should it be?
- Do we want to limit the type that contact can be set to? Home Work Office
- "Update the print function "print_person", so it will print the person's last name, first name, birth date, phone number, and email address, in new lines"; Should we update it or not?
