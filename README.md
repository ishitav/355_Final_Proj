Team:

Ishita Vasishtha (<ishitavas@usc.edu>)

Caitlin Sullivan (<ccsulliv@usc.edu>)

Gerson Estrada (<gdestrad@usc.edu>)

# Final Project Phase 2

This submission includes: 
- contact.cpp/h
- person.cpp/h
- date.cpp/h
- network.cpp/h
- misc.cpp/h
- Added functionality for friend connections between Person objects (changes in person, network, and misc primarily)

## Compilation Instructions

To run `main.cpp` or the file that starts the network and calls functions, we must compile ALL the other files and link them to each other in the outfile: 

`g++ -std=c++11 contact.cpp person.cpp date.cpp network.cpp misc.cpp main.cpp -o proj.out`

We need c++11 for our implementation (overriding virtual functions and iterators)

## Implementation Notes

`Network` creates a DLL of Person type objects and implements the essential DLL functions with the ability to search by and return values associated with class Person. 

Any time values are accessed for class Person, the function get_"value"() is called instead of directly referencing the value with person->value because those variables are private to the Person class. 

## Testing Methodology

in `main.cpp`, we test the pipeline and some edge cases (like attempting to add a duplicate user).

<details>

<summary>Test C++ Code</summary>

```
#include <iostream>
#include "network.h"
using namespace std;

int main() {
    Network net;

    cout << "===== PHASE 1: LOAD DEMO DATABASE =====" << endl;
    // Loads from the demo networkDB.txt file
    net.loadDB("networkDB.txt");

    // Print the current database
    cout << "\n===== PRINTING NETWORK =====" << endl;
    net.printDB();

    cout << "\n===== ADDING PERSON FROM TEMPLATE FILE =====" << endl;
    // Create new person from person_template.txt
    Person* new_person = new Person("person_template.txt");

    // Check if person exists
    if (net.search(new_person) == nullptr) {
        net.push_back(new_person);
        cout << "Person added successfully.\n";
    } else {
        cout << "Person already exists. Not added.\n";
        delete new_person; // Avoid memory leak
    }

    // Print updated database
    cout << "\n===== PRINTING UPDATED NETWORK =====" << endl;
    net.printDB();

    cout << "\n===== SAVING DATABASE TO test_output.txt =====" << endl;
    net.saveDB("test_output.txt");

    cout << "\n===== SEARCHING BY NAME (Julia Louis-Dreyfus) =====" << endl;
    Person* found = net.search("Julia", "Louis-Dreyfus");
    if (found != nullptr) {
        cout << "Person found:\n";
        found->print_person();
    } else {
        cout << "Person not found.\n";
    }

    cout << "\n===== REMOVING PERSON (Julia Louis-Dreyfus) =====" << endl;
    net.remove("Julia", "Louis-Dreyfus");

    cout << "\n===== PRINTING FINAL NETWORK STATE =====" << endl;
    net.printDB();

    cout << "\n===== SAVING FINAL STATE TO test_output_2.txt =====" << endl;
    net.saveDB("test_output_2.txt");

    return 0;
}
```

</details>

<details>

<summary>Test Output</summary>

```
===== PHASE 1: LOAD DEMO DATABASE =====

===== PRINTING NETWORK =====
Number of people: 3
------------------------------
Louis-Dreyfus, Julia Scarlett Elizabeth
January 13, 1961
(Office) 310-291-7482
Email (Gmail): something@email.com
------------------------------
Van Nostrand, Martin
July 24, 1949
(Home) 224-432-5809
Email (Yahoo): myemail@yahoo.com
------------------------------
Burbank, Truman
January 17, 1962
(Work) 213-517-9989
Email (Official): document@info.edu
------------------------------

===== ADDING PERSON FROM TEMPLATE FILE =====
Person already exists. Not added.

===== PRINTING UPDATED NETWORK =====
Number of people: 3
------------------------------
Louis-Dreyfus, Julia Scarlett Elizabeth
January 13, 1961
(Office) 310-291-7482
Email (Gmail): something@email.com
------------------------------
Van Nostrand, Martin
July 24, 1949
(Home) 224-432-5809
Email (Yahoo): myemail@yahoo.com
------------------------------
Burbank, Truman
January 17, 1962
(Work) 213-517-9989
Email (Official): document@info.edu
------------------------------

===== SAVING DATABASE TO test_output.txt =====

===== SEARCHING BY NAME (Julia Louis-Dreyfus) =====
Person found:
Louis-Dreyfus, Julia Scarlett Elizabeth
January 13, 1961
(Office) 310-291-7482
Email (Gmail): something@email.com

===== REMOVING PERSON (Julia Louis-Dreyfus) =====

===== PRINTING FINAL NETWORK STATE =====
Number of people: 2
------------------------------
Van Nostrand, Martin
July 24, 1949
(Home) 224-432-5809
Email (Yahoo): myemail@yahoo.com
------------------------------
Burbank, Truman
January 17, 1962
(Work) 213-517-9989
Email (Official): document@info.edu
------------------------------

===== SAVING FINAL STATE TO test_output_2.txt =====
```

</details>

## Unsure Parts/Questions

- error checking for inputs is not implemented - should it be?
- Do we want to limit the type that contact can be set to? Home Work Office
- "Update the print function "print_person", so it will print the person's last name, first name, birth date, phone number, and email address, in new lines"; Should we update it or not?
