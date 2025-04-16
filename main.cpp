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