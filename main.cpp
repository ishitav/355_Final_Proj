#include <iostream>
#include "network.h"
using namespace std;

int main() {
    Network net;

    cout << "===== PHASE 1: LOAD DATABASE =====" << endl;
    net.loadDB("networkDB.txt");

    cout << "\n===== ENTERING INTERACTIVE MENU =====" << endl;
    net.showMenu();

    return 0;
}