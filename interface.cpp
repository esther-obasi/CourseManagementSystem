#include "interface.h"
#include "utility.h"
#include <iostream>
#include <string>
#include "ctype.h"
using namespace std;
Department* StoreDepartments = nullptr;
Course* StoreCourses = nullptr;
int TotalDepartments = 0;
int TotalCourses = 0;
const string Interface::init_menu[MAX_MENU] = {
    "\n===== WELCOME =====",
    "\nStudent [1]",
    "\nAdmin [2]",
    "\nExit [3]",
    "\nEnter your choice [1, 2, 3]: "
};
Interface::Interface(){
    if (StoreDepartments == nullptr) {
        StoreDepartments = new Department[MAX_ENTRIES];
    }
    if (StoreCourses == nullptr) {
        StoreCourses = new Course[MAX_ENTRIES];
    }
    if (TotalDepartments == 0) {
        StoreDepartments[0] = Department("Computer Science");
        StoreDepartments[1] = Department("Business Administration");
        StoreDepartments[2] = Department("Engineering");

        StoreDepartments[0].SetCourseCount(4);
        StoreDepartments[1].SetCourseCount(4);
        StoreDepartments[2].SetCourseCount(4);

        StoreCourses[0] = Course(1, 101, "Introduction to Programming", "M/W", 1200.00);
        StoreCourses[1] = Course(1, 102, "Data Structures", "T/R", 1350.00);
        StoreCourses[2] = Course(1, 103, "Computer Networks", "W/F", 1400.00);
        StoreCourses[3] = Course(1, 104, "Artificial Intelligence", "M/W", 1600.00);

        StoreCourses[4] = Course(2, 201, "Principles of Marketing", "M/W", 1100.00);
        StoreCourses[5] = Course(2, 202, "Financial Accounting", "T/R", 1250.00);
        StoreCourses[6] = Course(2, 203, "Business Ethics", "W/F", 1000.00);
        StoreCourses[7] = Course(2, 204, "Operations Management", "M/W", 1300.00);

        StoreCourses[8] = Course(3, 301, "Engineering Mathematics", "M/W", 1450.00);
        StoreCourses[9] = Course(3, 302, "Circuit Analysis", "T/R", 1500.00);
        StoreCourses[10] = Course(3, 303, "Thermodynamics", "W/F", 1550.00);
        StoreCourses[11] = Course(3, 304, "Materials Science", "M/W", 1650.00);

        TotalDepartments = 3;
        TotalCourses = 12;
    }
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
void Interface::ListDepartments() {
    if (TotalDepartments == 0) {
        cout << "\nNo departments available. Please add a department." << endl;
    } else {
        cout << "\n===== DEPARTMENTS =====" << endl;
        for (int i = 0; i < TotalDepartments; i++) {
            cout << "[" << i + 1 << "] " << StoreDepartments[i].Department::GetDepartmentName() << endl;
        }
    }
}
void Interface::ListCourses(int id, int type) {
    if (type == 0) { // list cart
        if (CartCount == 0) {
            std::cout << "\nNo courses yet." << endl;
        } else {
            std::cout << "\n===== CART =====" << endl;
            for (int i = 0; i < CartCount; i++) {
                std::cout << "[" << StoreCart[i].GetCourseId() << "] " << StoreCart[i].GetCourseName()
                    << " - " << StoreCart[i].GetCourseSchedule() << " - $" << StoreCart[i].GetCoursePrice() << endl;
            }
        }
    } else { // list courses of a department
        int count = StoreDepartments[id - 1].GetCourseCount();
        if (count == 0) {
            std::cout << "\nNo courses available in this department." << endl;
        } else {
            switch (type) {
            case 1: { // for course identification
                std::cout << "\n===== COURSES IN " << toUpper(StoreDepartments[id - 1].GetDepartmentName()) << " =====" << endl;
                for (int i = 0; i < TotalCourses; i++) {
                    if (StoreCourses[i].GetDeptId() == id) {
                        std::cout << "[" << StoreCourses[i].GetCourseId() << "] " << StoreCourses[i].GetCourseName() << endl;
                    }
                }
                break;
            }
            case 2: { // for course with price
                std::cout << "\n===== COURSES =====" << endl;
                for (int i = 0; i < TotalCourses; i++) {
                    if (StoreCourses[i].GetDeptId() == id) {
                        std::cout << "[" << StoreCourses[i].GetCourseId() << "] " << StoreCourses[i].GetCourseName()
                            << " - $" << StoreCourses[i].GetCoursePrice() << endl;
                    }
                }
                break;
            }
            }
        }
    }
}
void Interface::ExitProgram(){
    cout << "\nExiting the program. Goodbye!" << endl;
    exit(0);
}
Interface::~Interface(){
    delete[] StoreDepartments;
    delete[] StoreCourses;
    StoreDepartments = nullptr;
    StoreCourses = nullptr;
}
