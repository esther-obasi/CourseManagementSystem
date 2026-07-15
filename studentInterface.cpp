#include "interface.h"
#include "utility.h"
#include <iostream>
#include <string>
#include "ctype.h"
using namespace std;
const string StudentInterface::student_menu[MAX_MENU] = {
    "\n===== STUDENT PORTAL =====",
    "\nShow Cart [1]",
    "\nBrowse Departments [2]",
    "\nExit [3]",
    "\nEnter your choice [1, 2, 3]: "
};
const string StudentInterface::cart_menu[MAX_MENU] = {
    "\n===== CART =====",
    "\nList Courses [1]",
    "\nCheckout [2]",
    "\nReturn to Main Menu [3]",
    "\nEnter your choice [1, 2, 3]: "
};
StudentInterface::StudentInterface() : Interface(){
    SetList(student_menu, size(student_menu));
}
void StudentInterface::RunMenu() {
    int choice;
    while (true) {
        SetList(student_menu, size(student_menu));
        DisplayContent();
        if (cin >> choice) {
            if (choice == 1) {
                SetList(cart_menu, size(cart_menu));
                // Handle cart
            } else if (choice == 3) {
                Interface::ExitProgram();  // exit program
            } else {
                cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
    }
}
StudentInterface::~StudentInterface(){
}