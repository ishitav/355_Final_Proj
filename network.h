#ifndef NETWORK_H
#define NETWORK_H

#include "person.h"
#include "date.h"
// You may need to add more libraries 
#include <stdlib.h>
class Network{

    private:
        Person* head;
        Person* tail;
        int count; 
        

    public:
        Network();
        Network(string fileName);
        ~Network();

        Person* search(Person* searchEntry);
        Person* search(string fname, string lname);
        
        void printDB();
        void push_front(Person* newEntry);
        void push_back(Person* newEntry);
        bool remove(string fname, string lname);
        void showMenu();
        void loadDB(string fileName);
        void saveDB(string fileName);

        void connect_friends();
};

#endif