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

void Network::connect(){
    if (!p1 || !p2) {
        cout << "Error: One or both persons are NULL.\n";
        return;
    }

    if (p1 == p2) {
        cout << "A person cannot friend themselves.\n";
        return;
    }

    // added friend 2 to friend 1's list
    bool added1 = p1->add_friend(p2);
    // added friend 1 to friend 2's list
    bool added2 = p2->add_friend(p1);

    cout << "\n";
    p1->print_person();
    cout << "\n";
    p2->print_person();
    cout << "\n";

    if (added1 && added2)
        cout << "They are now friends!\n";
    else
        cout << "They were already friends.\n";


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
            // TODO: Complete me!
            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
            // Save the network database into the file with the given name,
            // with each person saved in the format the save as printing out the person info,
            // and people are delimited similar to "networkDB.txt" format
            cout << "Network saved in " << fileName << endl;
        }
        else if (opt==2){
            // TODO: Complete me!
            cout << "Loading network database \n";
            // TODO: print all the files in this same directory that have "networkDB.txt" format
            // print format: one filename one line.
            // This step just shows all the available .txt file to load.
            cout << "Enter the name of the load file: "; 
            // If file with name FILENAME does not exist: 
            cout << "File FILENAME does not exist!" << endl;
            // If file is loaded successfully, also print the count of people in it: 
            cout << "Network loaded from " << fileName << " with " << count << " people \n";
        }
        else if (opt == 3){
            // TODO: Complete me!
            // TODO: use push_front, and not push_back 
            // Add a new Person ONLY if it does not exists!
            cout << "Adding a new person \n";
        }
        else if (opt == 4){
            // TODO: Complete me!
            // if found, cout << "Remove Successful! \n";
            // if not found: cout << "Person not found! \n";
            cout << "Removing a person \n";
            cout << "First name: ";
            cout << "Last name: ";
        }
        else if (opt==5){
            // TODO: Complete me!
            // print the people with the given last name
            // if not found: cout << "Person not found! \n";
            cout << "Print people with last name \n";
            cout << "Last name: ";
        }
        else if (opt==6){
            cout << "Make friends";

            cout << "Person 1"; 
            cout << "First name: ";
            getline(cin, fname);
            cout << "Last name: ";
            getline(cin, lname);
            Person* p1 = search(fname, lname);
            if (!p1) {
                cout << "Person not found\n";
                return;
            }

            cout << "Person 2";
            cout << "First name: ";
            getline(cin, fname);
            cout << "Last name: ";
            getline(cin, lname);
            Person* p2 = search(fname, lname);
            if (!p2) {
                cout << "Person not found\n";
                return;
            }

            connect(p1, p2);
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