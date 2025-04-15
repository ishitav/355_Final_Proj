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
        if(*current == searchEntry){    // overloaded ==
            return current;
        }
        current = current->next;
    }
    return NULL;    // catch-all
}


Person* Network::search(string fname, string lname){
    // New == for Person, only based on fname and lname
    // if found, returns a pointer to it, else returns NULL
    // Note: two ways to implement this, 1st making a new Person with fname and lname and and using search(Person*), 2nd using fname and lname directly.

    Person* current = head; 
    while(current != NULL){
        if(current->f_name == fname && current->l_name == lname){
            return current;
        }
        current = current->next;
    }
    return NULL;
}




void Network::loadDB(string filename){
    ifstream infile(filename);
    if(!infile){
        cout << "File could not be opened" << endl;
        return;
    }

    // clear the existing list
    Person* current = head;
    while(current != NULL){
        Person* temp = current;
        current = current->next;
        delete temp;
    }
    head = NULL;
    tail = NULL;
    count = 0; 

    string first, last, bday;
    string emailType, email, phoneType, phone;

    // parse file line by line
    while(getline(infile, first)) {
        getline(infile, last);
        getline(infile, bday);

        getline(infile, emailType);
        emailType = emailType.substr(1, emailType.length()-2);  // remove parenthesis
        getline(infile, email);

        getline(infile, phoneType);
        phoneType = phoneType.substr(1, phoneType.length()-2);  // remove parenthesis
        getline(infile, phone);

        getline(infile, bday);  // read the separator line

        // construct each person object
        Person* p = new Person(first, last, bday);
        p->add_contact(new Email(emailType, email));
        p->add_contact(new Phone(phoneType, phone));

        // add it with push_back
        push_back(p);
    }
}

// TODO: can we change person::print_person() to return a string
// or be sendable to an output file (not cout) to simplify this?
void Network::saveDB(string filename){
    ofstream outfile(filename);
    if(!outfile) {
        cout << "File could not be opened" << endl;
        return;
    }

    Person* current = head;
    while(current != NULL){
        outfile << current->f_name << " " << current->l_name << endl;
        outfile << current->birthdate->get_date("MM/DD/YYYY") << endl; // Or another format you prefer

        // print email in format: (Type) email_address
        outfile << "(" << current->email->type << ")" << endl;
        outfile << current->email->get_contact("full") << endl;

        // print phone in format: (Type) phone_number
        outfile << "(" << current->phone->type << ")" << endl;
        outfile << current->phone->get_contact("full") << endl;

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
