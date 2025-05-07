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

    cout << "\n===== PHASE 3: ADDING TEST USERS WITH DIVERSE ATTRIBUTES =====" << endl;

    // Person A: the one we're testing recommendations for
    Person* alice = new Person("Alice", "Smith", "3/14/1995", "alice@usc.edu", "310-123-4567");
    alice->set_attribute("college", "USC");
    alice->set_attribute("major", "Computer Science");
    alice->set_attribute("state", "CA");
    alice->set_attribute("email_provider", "usc");

    // Person B: highly similar to Alice → should be recommended
    Person* bob = new Person("Bob", "Nguyen", "6/22/1994", "bob@usc.edu", "310-222-3333");
    bob->set_attribute("college", "USC");
    bob->set_attribute("major", "Computer Science");
    bob->set_attribute("state", "CA");
    bob->set_attribute("email_provider", "usc");

    // Person C: partly similar → may be recommended
    Person* carol = new Person("Carol", "Lee", "11/5/1996", "carol@gmail.com", "213-444-5555");
    carol->set_attribute("college", "UCLA");
    carol->set_attribute("major", "Computer Science");
    carol->set_attribute("state", "CA");
    carol->set_attribute("email_provider", "gmail");

    // Person D: low similarity → shouldn't be recommended
    Person* daniel = new Person("Daniel", "Rodriguez", "8/9/1995", "daniel@yahoo.com", "415-666-7777");
    daniel->set_attribute("college", "NYU");
    daniel->set_attribute("major", "Philosophy");
    daniel->set_attribute("state", "NY");
    daniel->set_attribute("email_provider", "yahoo");

    // Person E: totally unrelated → shouldn't be recommended
    Person* emma = new Person("Emma", "Khan", "1/1/1997", "emma@harvard.edu", "617-888-9999");
    emma->set_attribute("college", "Harvard");
    emma->set_attribute("major", "Law");
    emma->set_attribute("state", "MA");
    emma->set_attribute("email_provider", "harvard");

    net.push_back(alice);
    net.push_back(bob);
    net.push_back(carol);
    net.push_back(daniel);
    net.push_back(emma);

    // Simulate friendships
    alice->makeFriend(emma);  // test that she’s not re-recommended

    cout << "\n===== PHASE 3: RECOMMENDED FRIENDS FOR ALICE =====" << endl;
    net.recommend_friends(alice);

    return 0;
}