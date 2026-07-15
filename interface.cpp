#include "interface.h"
#include "utility.h"
#include <iostream>
#include <string>
#include "ctype.h"
using namespace std;

const string Interface::init_menu[MAX_MENU] = {
    "\n===== WELCOME =====",
    "\nStudent [1]",
    "\nAdmin [2]",
    "\nExit [3]",
    "\nEnter your choice [1, 2, 3]: "
};
Interface::Interface(){
    SetList(init_menu, size(init_menu));
}
void Interface::RunMenu() {
    int choice;
    while (true) {
        DisplayContent();
        if (cin >> choice) {
            if (choice == 1) {
                StudentInterface student;
                student.RunMenu();
            } else if (choice == 2) {
                AdminInterface admin;
                admin.RunMenu();
            } else if (choice == 3) {
                ExitProgram();  // exit program
            } else {
                cout << "\nInvalid choice. Please enter 1, 2, or 3." << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
    }
}
void Interface::SetList(const string items[], int count) {
    for (int i = 0; i < count && i < MAX_ENTRIES; i++) {
        list[i] = items[i];
    }
}
string Interface::Trim(const string& str) {
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    if (start == string::npos) return "";  // All whitespace
    
    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(start, end - start + 1);
}
void Interface::DisplayContent(){
    for(int i = 0; i < size(list); i++){
        cout << *(list+i);
    }
}
string Interface::toLower(const string& str) {
    static string lowerStr;
    lowerStr = str;
    for (char& c : lowerStr) {
        c = tolower(c);
    }
    return lowerStr;
}
string Interface::toUpper(const string& str) {
    static string upperStr;
    upperStr = str;
    for (char& c : upperStr) {
        c = toupper(c);
    }
    return upperStr;
}
void Interface::ExitProgram(){
    cout << "\nExiting the program. Goodbye!" << endl;
    exit(0);
}
Interface::~Interface(){
}
