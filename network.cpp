#include "network.h"
#include <limits>
#include "misc.h"
#include <fstream>

Network::Network(){
    head = NULL;
    tail = NULL;
    count = 0;
}


Network::Network(string fileName){
    // TODO: complete this method!
    // Implement it in one single line!
    // You may need to implement the load method before this!
    loadDB(fileName);
}

Network::~Network(){ 
    Person* current = head; // pointer 
    while (current != NULL){ // while not at the end
        Person* temp = current; // pointer to current
        current = current->next; // point to next element
        delete temp; // deallocate
    }
    // reinitialize
    head = NULL;
    tail = NULL;
    count = 0;
}

Person* Network::search(Person* searchEntry){
    // Searches the Network for searchEntry
    // if found, returns a pointer to it, else returns NULL
    
    Person* current = head;
    while(current != NULL){
        if(*current == *searchEntry){    // overloaded ==
            return current;
        }
        current = current->next;
    }
    return NULL;    // catch-all
}


Person* Network::search(string fname, string lname) {
    Person* current = head; 
    while (current != NULL) {
        bool lastMatch = (current->l_name == lname);

        // Case-sensitive partial match for first name
        bool firstMatch = (current->f_name.find(fname) != string::npos);

        if (firstMatch && lastMatch) {
            return current;
        }

        current = current->next;
    }
    return NULL;
}

void Network::loadDB(string filename){
    ifstream infile(filename);
    if (!infile) {
        cout << "File could not be opened" << endl;
        return;
    }

    // Clear existing list
    Person* current = head;
    while (current != NULL) {
        Person* temp = current;
        current = current->next;
        delete temp;
    }
    head = NULL;
    tail = NULL;
    count = 0;

    string fname, lname, bday;
    string emailLine, phoneLine;

    while (getline(infile, fname)) {
        getline(infile, lname);
        getline(infile, bday);         // EX: "1/13/1961"
        getline(infile, emailLine);    // EX: "(Work) julia@wh.com"
        getline(infile, phoneLine);    // EX: "(Home) 310-192-2011"
        string separator;
        getline(infile, separator);    // --------------------

        // Parse email
        string emailType, email;
        size_t ep = emailLine.find(')');
        if (emailLine.front() == '(' && ep != string::npos) {
            emailType = emailLine.substr(1, ep - 1);
            email = emailLine.substr(ep + 2);
        } else {
            emailType = "Work";
            email = "invalid@email.com";
        }

        // Parse phone
        string phoneType, phone;
        size_t pp = phoneLine.find(')');
        if (phoneLine.front() == '(' && pp != string::npos) {
            phoneType = phoneLine.substr(1, pp - 1);
            phone = phoneLine.substr(pp + 2);
        } else {
            phoneType = "Home";
            phone = "0000000000";
        }

        // Create person and push
        Person* p = new Person(fname, lname, bday, emailType, email, phoneType, phone);
        push_back(p);
    }
}

// TODO: can we change person::print_person() to return a string
// or be sendable to an output file (not cout) to simplify this?
void Network::saveDB(string filename) {
    ofstream outfile(filename);
    if (!outfile) {
        cout << "File could not be opened" << endl;
        return;
    }

    Person* current = head;
    while (current != NULL) {
        outfile << current->f_name << endl;
        outfile << current->l_name << endl;

        // Print raw date string (M/D/YYYY) that loadDB expects
        outfile << current->birthdate->get_formatted_date() << endl;

        // Email
        outfile << "(" << current->email->get_type() << ") "
                << current->email->get_contact("short") << endl;

        // Phone
        outfile << "(" << current->phone->get_type() << ") "
                << current->phone->get_contact("short") << endl;

        outfile << "--------------------" << endl;

        current = current->next;
    }

    outfile.close();
}


void Network::printDB(){
    // Leave me alone! I know how to print! 
    // Note: Notice that we don't need to update this even after adding to Personattributes
    // This is a feature of OOP, classes are supposed to take care of themselves!
    cout << "Number of people: " << count << endl;
    cout << "------------------------------" << endl;
    Person* ptr = head;
    while(ptr != NULL){
        ptr->print_person();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}


// completed: add person to front of LL
void Network::push_front(Person* newEntry){
    newEntry->prev = NULL;
    newEntry->next = head;

    if (head != NULL)
        head->prev = newEntry;
    else
        tail = newEntry;
    
    head = newEntry;
    count++;
}


void Network::push_back(Person* newEntry){
    // Adds a new Person (newEntry) to the back of LL
    newEntry->next = NULL;
    newEntry->prev = tail;

    if(tail != NULL){
        tail->next = newEntry;
    }else{
        head = newEntry;
    }

    tail = newEntry;
    count++;
}


// removes a person from the DLL by name
bool Network::remove(string fname, string lname){
    Person* target = search(fname, lname);
    if(!target){
        return false;
    }

    // found case 1: element has a previous value
    // link next to previous to skip target
    if(target->prev){
        target->prev->next = target->next;
    }else{
        head = target->next;
    }

    // found case 2: element has a next value
    // link previous to next to skip target
    if(target->next){
        target->next->prev = target->prev;
    }else{

        tail = target->prev;
        

    }

    //
    delete target;
    count--;    // denote removal of an element
    return true;    
 
}


void Network::showMenu(){
    // TODO: Complete this method!
    // All the prompts are given to you, 
    // You should add code before, between and after prompts!

    int opt;
    while(1){
        cout << "\033[2J\033[1;1H";
        printMe("banner"); // from misc library

        cout << "Select from below: \n";
        cout << "1. Save network database \n";
        cout << "2. Load network database \n";
        cout << "3. Add a new person \n";
        cout << "4. Remove a person \n";
        cout << "5. Print people with last name  \n";
        cout << "6. Connect two friends\n";
        cout << "7. Test Friend Reccomendation System\n";
        cout << "\nSelect an option ... ";
        
        
        if (cin >> opt) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Wrong option! " << endl;
            return;
        }
        
        // You may need these variables! Add more if you want!
        string fname, lname, fileName, bdate;
        cout << "\033[2J\033[1;1H";

        if (opt==1){
            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
            getline(cin, fileName);
            saveDB(fileName);
            cout << "Network saved in " << fileName << endl;
        }
        else if (opt==2){
            cout << "Loading network database \n";
            cout << "Enter the name of the load file: ";
            getline(cin, fileName);
        
            ifstream infile(fileName);
            if (!infile) {
                cout << "File " << fileName << " does not exist!\n";
            } else {
                infile.close(); // optional
                loadDB(fileName);
                cout << "Network loaded from " << fileName << " with " << count << " people \n";
            }
        }

        else if (opt == 3){
            cout << "Adding a new person \n";
            Person* newPerson = new Person();  // prompts user for details

            if (search(newPerson) == nullptr) {
                push_front(newPerson);  // use push_front per spec
                cout << "Person added successfully.\n";
            } else {
                delete newPerson;
                cout << "Person already exists. Not added.\n";
            }
        }
        else if (opt == 4){
            cout << "Removing a person \n";
            cout << "First name: ";
            getline(cin, fname);
            cout << "Last name: ";
            getline(cin, lname);

            if (remove(fname, lname)) {
                cout << "Remove Successful!\n";
            } else {
                cout << "Person not found!\n";
            }
        }
        else if (opt==5){
            cout << "Print people with last name \n";
            cout << "Last name: ";
            getline(cin, lname);

            bool found = false;
            for (Person* curr = head; curr != nullptr; curr = curr->next) {
                if (curr->l_name == lname) {
                    curr->print_person();
                    found = true;
                }
            }

            if (!found) {
                cout << "Person not found! \n";
            }
        }else if (opt == 6) {
            cout << "Make friends\n";
        
            string fname1, lname1, fname2, lname2;
        
            cout << "Person 1\nFirst Name: ";
            getline(cin, fname1);
            cout << "Last Name: ";
            getline(cin, lname1);
        
            Person* p1 = search(fname1, lname1);
            if (!p1) {
                cout << "Person not found!\n";
                continue;
            }
        
            cout << "Person 2\nFirst Name: ";
            getline(cin, fname2);
            cout << "Last Name: ";
            getline(cin, lname2);
        
            Person* p2 = search(fname2, lname2);
            if (!p2) {
                cout << "Person not found!\n";
                continue;
            }
        
            cout << "\n" << fname1 << " " << lname1 << ":\n";
            p1->print_person();
            cout << "\n" << fname2 << " " << lname2 << ":\n";
            p2->print_person();
        
            p1->makeFriend(p2);
            p2->makeFriend(p1);
        
            cout << "\nFriendship created!\n";
        } else if (opt == 7) {
            cout << "\n===== PHASE 3: INTELLIGENT FRIEND RECOMMENDATION DEMO =====\n";
        
            // 1. Create test users
            Person* alice = new Person("Alice", "Smith", "3/14/1995", "alice@usc.edu", "310-123-4567");
            Person* bob = new Person("Bob", "Nguyen", "6/22/1994", "bob@usc.edu", "310-222-3333");
            Person* carol = new Person("Carol", "Lee", "11/5/1996", "carol@gmail.com", "213-444-5555");
            Person* daniel = new Person("Daniel", "Rodriguez", "8/9/1995", "daniel@yahoo.com", "415-666-7777");
            Person* emma = new Person("Emma", "Khan", "1/1/1997", "emma@harvard.edu", "617-888-9999");
        
            // 2. Set attributes
            alice->set_attribute("college", "USC");
            alice->set_attribute("major", "CS");
            alice->set_attribute("state", "CA");
            alice->set_attribute("email_provider", "usc");
        
            bob->set_attribute("college", "USC");
            bob->set_attribute("major", "CS");
            bob->set_attribute("state", "CA");
            bob->set_attribute("email_provider", "usc");
        
            carol->set_attribute("college", "UCLA");
            carol->set_attribute("major", "CS");
            carol->set_attribute("state", "CA");
            carol->set_attribute("email_provider", "gmail");
        
            daniel->set_attribute("college", "NYU");
            daniel->set_attribute("major", "Philosophy");
            daniel->set_attribute("state", "NY");
            daniel->set_attribute("email_provider", "yahoo");
        
            emma->set_attribute("college", "Harvard");
            emma->set_attribute("major", "Law");
            emma->set_attribute("state", "MA");
            emma->set_attribute("email_provider", "harvard");
        
            // 3. Add to network
            push_back(alice);
            push_back(bob);
            push_back(carol);
            push_back(daniel);
            push_back(emma);
        
            // Group into vector for looping
            vector<Person*> testUsers = {alice, bob, carol, daniel, emma};
        
            // 4. Show user details
            cout << "\n--- TEST USERS AND THEIR ATTRIBUTES ---\n";
            for (Person* p : testUsers) {
                cout << p->get_code_name() << " (" << p->f_name << " " << p->l_name << ")\n";
                cout << "  College: " << p->get_attribute("college") << "\n";
                cout << "  Major: " << p->get_attribute("major") << "\n";
                cout << "  State: " << p->get_attribute("state") << "\n";
                cout << "  Email Provider: " << p->get_attribute("email_provider") << "\n\n";
            }
        
            // 5. Pre-define a friendship
            alice->makeFriend(emma);
            cout << "--- Friendship Created: Alice is already friends with Emma ---\n\n";
        
            // 6. Mini interactive loop: pick who to recommend for
            while (true) {
                cout << "\nSelect a user to run friend recommendation (or type 'exit'):\n";
                for (size_t i = 0; i < testUsers.size(); ++i) {
                    cout << "  " << (i + 1) << ". " << testUsers[i]->f_name << " " << testUsers[i]->l_name << "\n";
                }
                cout << "> ";
        
                string input;
                getline(cin, input);
                if (input == "exit") break;
        
                int choice = -1;
                try {
                    choice = stoi(input);
                } catch (...) {
                    cout << "Invalid input. Try again.\n";
                    continue;
                }
        
                if (choice < 1 || choice > testUsers.size()) {
                    cout << "Invalid selection. Try again.\n";
                    continue;
                }
        
                Person* selected = testUsers[choice - 1];
                cout << "\n>>> Recommending friends for " << selected->f_name << " " << selected->l_name << "...\n";
                recommend_friends(selected);
            }
        
            // 7. Cleanup test users
            for (Person* p : testUsers) {
                remove(p->f_name, p->l_name);
            }
        
            cout << "\n>>> Test complete. Returning to main menu.\n";
        }
        
        else
            cout << "Nothing matched!\n";
        
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\nPress Enter key to go back to main menu ... ";
        string temp;
        std::getline (std::cin, temp);
        cout << "\033[2J\033[1;1H";
    }
}

double compute_similarity(Person* a, Person* b) {
    double score = 0.0;

    if (a->get_attribute("college") == b->get_attribute("college"))
        score += 0.4;
    if (a->get_attribute("major") == b->get_attribute("major"))
        score += 0.3;
    if (a->get_attribute("state") == b->get_attribute("state"))
        score += 0.1;
    if (a->get_attribute("email_provider") == b->get_attribute("email_provider"))
        score += 0.2;

    return score;
}

void Network::recommend_friends(Person* p) {
    std::vector<std::pair<double, Person*>> candidates;

    for (Person* current = head; current != nullptr; current = current->next) {
        if (current == p) continue;

        // Skip if already friends
        bool already_friend = false;
        for (auto f : p->myfriends) {
            if (f == current) {
                already_friend = true;
                break;
            }
        }
        if (already_friend) continue;

        double sim = compute_similarity(p, current);
        if (sim > 0.0)
            candidates.push_back({sim, current});
    }

    std::sort(candidates.begin(), candidates.end(),
        [](const std::pair<double, Person*>& a, const std::pair<double, Person*>& b) {
            return a.first > b.first;
        });

    std::cout << "Recommended friends for " << p->f_name << " " << p->l_name << ":\n";
    for (size_t i = 0; i < std::min(candidates.size(), size_t(3)); ++i) {
        Person* rec = candidates[i].second;
        std::cout << rec->get_code_name() << " (" << rec->f_name << " " << rec->l_name << ") — score: " << candidates[i].first << "\n";
    }
}