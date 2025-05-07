#include <iostream>
#include "network.h"
#include "person.h"
#include "misc.h"

using namespace std;

int main() {
    Network net;

    // ===== PHASE 1 =====
    cout << "===== PHASE 1: LOAD DATABASE =====" << endl;
    net.loadDB("networkDB.txt");

    cout << "\n===== PHASE 1: PRINT DATABASE =====" << endl;
    net.printDB();

    cout << "\n===== PHASE 1: ADDING PERSON FROM TEMPLATE FILE =====" << endl;
    Person* new_person = new Person("person_template.txt");
    if (net.search(new_person) == nullptr) {
        net.push_back(new_person);
        cout << "Person added successfully.\n";
    } else {
        cout << "Person already exists. Not added.\n";
        delete new_person;
    }

    cout << "\n===== PHASE 1: SAVE TO test_output.txt =====" << endl;
    net.saveDB("test_output.txt");

    cout << "\n===== PHASE 1: SEARCH FOR 'Julia Louis-Dreyfus' =====" << endl;
    Person* julia = net.search("Julia", "Louis-Dreyfus");
    if (julia) {
        cout << "Found:\n";
        julia->print_person();
    } else {
        cout << "Person not found.\n";
    }

    cout << "\n===== PHASE 1: REMOVE 'Julia Louis-Dreyfus' =====" << endl;
    if (net.remove("Julia", "Louis-Dreyfus")) {
        cout << "Remove successful.\n";
    } else {
        cout << "Person not found.\n";
    }

    cout << "\n===== PHASE 1: SAVE FINAL STATE TO test_output_2.txt =====" << endl;
    net.saveDB("test_output_2.txt");

    // ===== PHASE 2 =====
    cout << "\n===== PHASE 2: FRIENDSHIP TEST BETWEEN EXISTING USERS =====" << endl;
    
    // Use only people from your networkDB.txt:
    // Martin Van Nostrand and Truman Burbank
    Person* martin = net.search("Martin", "Van Nostrand");
    Person* truman = net.search("Truman", "Burbank");

    if (martin && truman) {
        cout << "\n>>> Before friendship:\n";
        martin->print_person();
        truman->print_person();

        martin->makeFriend(truman);
        truman->makeFriend(martin);

        cout << "\n>>> After friendship:\n";
        martin->print_person();
        truman->print_person();

        cout << "\n>>> Sorted friend list for Martin:\n";
        martin->print_friends();

        cout << "\n>>> Sorted friend list for Truman:\n";
        truman->print_friends();
    } else {
        cout << "Martin or Truman not found. Check your networkDB.txt.\n";
    }

    return 0;
}