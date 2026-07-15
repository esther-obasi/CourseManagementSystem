#include "interface.h"
#include "utility.h"
#include <iostream>
#include <fstream>
#include <string>
#include "ctype.h"
using namespace std;

Department* StoreDepartments = nullptr;
Course* StoreCourses = nullptr;

int TotalDepartments = 0;
const char* csvFile = "Your/Path/To/CSVFile.csv";

const string AdminInterface::admin_menu[MAX_MENU] = {
    "\n===== ADMIN PORTAL =====",
    "\nList Departments [1]",
    "\nAdd Department [2]",
    "\nAdd Course to Department [3]",
    "\nSave Changes to CSV [4]",
    "\nExit [5]",
    "\nEnter your choice [1, 2, 3, 4, 5]: "
};
AdminInterface::AdminInterface(){
    SetList(admin_menu, size(admin_menu));
}
void AdminInterface::RunMenu() {
    int choice;
    if (StoreDepartments == nullptr) {
        StoreDepartments = new Department[MAX_ENTRIES];
    }
    if (StoreCourses == nullptr) {
        StoreCourses = new Course[MAX_ENTRIES];
    }
    
    while (true) {
        SetList(admin_menu, size(admin_menu));
        DisplayContent();
        if (!(cin >> choice)) {
            std::cout << "\nInvalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        if (choice == 1) {
            ListDepartments();
        } else if (choice == 2) {
            // Add department
            AddDepartment();
        } else if (choice == 3) {
            // Add course to department
            ListDepartments();
            if (TotalDepartments > 0) {
                AddCourse();
            }
        } else if (choice == 4) {
            SaveToCSV();
        } else if (choice == 5) {
            ExitProgram();  // Exit the program
        } else {
            std::cout << "\nInvalid choice. Please enter 1, 2, 3, 4, or 5." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}
void AdminInterface::ListDepartments() {
    if (TotalDepartments == 0) {
        cout << "\nNo departments available. Please add a department." << endl;
    } else {
        cout << "\n===== DEPARTMENTS =====" << endl;
        for (int i = 0; i < TotalDepartments; i++) {
            cout << "[" << i + 1 << "] " << StoreDepartments[i].Department::GetDepartmentName() << endl;
        }
    }
}
void AdminInterface::ListCourses(int id, int type) {
    int count = StoreDepartments[id - 1].Department::GetCourseCount();
    if (count == 0) {
        std::cout << "\nNo courses available in this department." << endl;
    } else {
        switch (type) {
        case 1:
            std::cout << "\n===== COURSES IN " << toUpper(StoreDepartments[id - 1].GetDepartmentName()) << " =====" << endl;
            for (int i = 0; i < StoreDepartments[id - 1].GetCourseCount(); i++) {
                std::cout << "[" << StoreCourses[i].GetCourseId() << "] " << StoreCourses[i].GetCourseName() << endl;
            }
            break;
        case 2:
            std::cout << "\n===== DETAILS =====" << endl;
            for (int i = 0; i < StoreDepartments[id - 1].GetCourseCount(); i++) {
                std::cout << "[" << StoreCourses[i].GetCourseId() << "] " << StoreCourses[i].GetCourseName() 
                    << " - $" << StoreCourses[i].GetCoursePrice() << endl;
            }
            break;
        }
    }
}
void AdminInterface::AddDepartment(){
    string name;
    cout << "\nEnter department name: ";
    getline(cin >> ws, name);
    if (name.empty()) {
        cout << "\nDepartment name cannot be empty." << endl;
        return;
    }
    name = Trim(name);
    // Check for duplicates (case-insensitive)
    bool duplicate = false;
    for (int i = 0; i < TotalDepartments; i++) {
        string existing = Trim(toLower(StoreDepartments[i].GetDepartmentName()));
        if (existing.find(Trim(toLower(name))) != string::npos) {
            cout << "\nDepartment '" << name << "' already exists." << endl;
            duplicate = true;
            break;
        }
    }
    if (!duplicate && TotalDepartments < MAX_ENTRIES) {
        StoreDepartments[TotalDepartments] = Department(name);
        TotalDepartments++;
        cout << "\nDepartment '" << name << "' added successfully." << endl;
    } else if (TotalDepartments >= MAX_ENTRIES) {
        cout << "\nCannot add more departments. Maximum limit reached." << endl;
    }
}
void AdminInterface::AddCourse(){
    int dept, course;
    double price;
    string name, schedule;
    do{
        cout << "\nEnter department number [0 to go back]: ";
    }while(!(cin >> dept) || dept < 0 || dept > TotalDepartments);
    if (dept == 0) {
        cout << "\nReturning to previous menu." << endl;
        return;
    }
    ListCourses(dept, 1); // List courses in the selected department
    do{
        cout << "\nEnter course number: ";
    }while(!(cin >> course) || course < 1);
    // Check for duplicates - only in the selected department (case-insensitive)
    bool duplicate = false;
    int count = StoreDepartments[dept - 1].GetCourseCount();
    for (int i = 0; i < count; i++) {
        // Only check courses in the selected department
        if (StoreCourses[i].GetDeptId() == dept) {
            bool existing = StoreCourses[i].GetCourseId() == course ? true : false;
            if (existing) {
                cout << "\nCourse number already exists in " << StoreDepartments[dept - 1].GetDepartmentName() << "." << endl;
                duplicate = true;
                break;
            }
        }
    }
    if (!duplicate && count < MAX_ENTRIES) {
        do{
            cout << "\nEnter course name: ";
        }while(!(cin >> ws, getline(cin, name)) || name.empty());
        do {
            cout << "\nEnter course schedule [M/W, T/R, or W/F]: ";
            if (cin >> ws && getline(cin, schedule) && !schedule.empty()) {
                schedule = toUpper(Trim(schedule));
            if (schedule == "M/W" || schedule == "T/R" || schedule == "W/F") {
                break;  // Valid schedule, exit loop
            }
        }
        cout << "\nInvalid schedule. Please enter M/W, T/R, or W/F." << endl;
        } while (true);
        do{
            cout << "\nEnter course price: ";
        }while(!(cin >> price) || price < 0);

        StoreCourses[count] = Course(dept, course, name, schedule, price);
        StoreDepartments[dept - 1].SetCourseCount(count + 1);
        cout << "\nCourse '" << name << "' added successfully." << endl;
    } else if (count >= MAX_ENTRIES) {
        cout << "\nCannot add more courses. Maximum limit reached." << endl;
    }
}
void AdminInterface::SaveToCSV(){
    ofstream outFile(csvFile);
    if (!outFile) {
        cout << "\nError opening file for writing." << endl;
        return;
    }
    // Write departments
    for (int i = 0; i < TotalDepartments; i++) {
        outFile << "Department," << StoreDepartments[i].GetDepartmentName() << endl;
    }
    // Write courses
    for (int i = 0; i < TotalDepartments; i++) {
        int courseCount = StoreDepartments[i].GetCourseCount();
        for (int j = 0; j < courseCount; j++) {
        outFile << "Course," 
                << StoreCourses[j].GetDeptId() + 1 << "," // Department number
                << StoreCourses[j].GetCourseName() << ","
                << StoreCourses[j].GetCourseSchedule() << ","
                << StoreCourses[j].GetCoursePrice() << endl;
        }
    }
    outFile.close();
    cout << "\nData saved to CSV successfully." << endl;
}
AdminInterface::~AdminInterface(){
    delete[] StoreDepartments;
    delete[] StoreCourses;
}