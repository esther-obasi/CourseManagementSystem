#include "interface.h"
#include "utility.h"
#include <iostream>
#include <string>
#include "ctype.h"
using namespace std;
Course* StoreCart = nullptr;
int CartCount = 0;
const string StudentInterface::student_menu[MAX_MENU] = {
    "\n===== STUDENT PORTAL =====",
    "\nShow Cart [1]",
    "\nBrowse Departments [2]",
    "\nExit [3]",
    "\nEnter your choice [1, 2, 3]: "
};
const string StudentInterface::cart_menu[MAX_MENU] = {
    "\n===== CART OPTIONS =====",
    "\nList Courses [1]",
    "\nCheckout [2]",
    "\nReturn to Main Menu [3]",
    "\nEnter your choice [1, 2, 3]: "
};
const string StudentInterface::dept_menu[MAX_MENU] = {
    "\n===== DEPARTMENTS HOMEPAGE =====",
    "\nList Courses of a Department [1]",
    "\nGo Back to Main Menu [2]",
    "\nEnter your choice [1, 2]: "
};
const string StudentInterface::course_menu[MAX_MENU] = {
    "\n===== COURSES HOMEPAGE =====",
    "\nAdd to Cart a Course [1]",
    "\nGo Back to Browse Departments Menu [2]",
    "\nEnter your choice [1, 2]: "
};
StudentInterface::StudentInterface() : Interface(){
    if (StoreCart == nullptr) {
        StoreCart = new Course[MAX_ENTRIES];
    }
    Interface::SetList(student_menu, size(student_menu));
}
void StudentInterface::AddToCart(int dept){
    while(true){
        Interface::ListCourses(dept, 2); 
        Interface::SetList(course_menu, size(course_menu));
        Interface::DisplayContent();
        int choice;
        if (!(cin >> choice)) {
            std::cout << "\nInvalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        if (choice == 1) { //add to cart
            int courseChoice;
            cout << "\nEnter the course number to add to your cart: ";
            if (!(cin >> courseChoice) || courseChoice < 1) {
                std::cout << "\nInvalid course number. Please try again." << endl;
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            } else {
                bool courseFound = false;
                for (int i = 0; i < TotalCourses; i++) {
                    if (StoreCourses[i].GetDeptId() == dept && StoreCourses[i].GetCourseId() == courseChoice) {
                        StoreCart[CartCount] = StoreCourses[i];
                        CartCount++;
                        courseFound = true;
                        std::cout << "\nCourse added to cart." << endl;
                        break;
                    }
                }
                if (!courseFound) {
                    std::cout << "\nCourse code not included." << endl;
                }
            }
        }else if (choice == 2) { //back to browse departments menu
            break; // Exit the inner loop to return to the departments menu
        } else {
            cout << "Invalid choice. Please enter 1 or 2." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}
/*void StudentInterface::RemoveFromCart(float key){
   bool found = false;
    for (int i = 0; i < CartCount; i++) {
        if (StoreCart[i].GetCourseId() == key) {
            found = true;
            for (int j = i; j < CartCount - 1; j++) {
                StoreCart[j] = StoreCart[j + 1];
            }
            CartCount--;
            break;
        }
    }
}*/
void StudentInterface::ClearCart(){
    delete[] StoreCart;
    StoreCart = nullptr;
    StoreCart = new Course[MAX_ENTRIES]; // Reallocate the cart for future use
    CartCount = 0; // Clear the cart after checkout
}
void StudentInterface::Checkout(){
    if (CartCount == 0) {
        std::cout << "\nYour cart is empty. Please add courses to your cart before checking out." << endl;
    } else {
        double totalPrice = 0.0;
        std::cout << "\n===== CHECKOUT =====" << endl;
        for (int i = 0; i < CartCount; i++) {
            totalPrice += StoreCart[i].GetCoursePrice();
        }
        std::cout << "\nTotal Price: $" << totalPrice << endl;
        std::cout << "Thank you for your purchase!" << endl;
        ClearCart(); // Clear the cart after checkout
    }
}
void StudentInterface::RunMenu() {
    int choice;
    while (true) {
        Interface::SetList(student_menu, size(student_menu));
        Interface::DisplayContent();
        if (!(cin >> choice)) {
            std::cout << "\nInvalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        if (choice == 1) { //show cart menu
            while(true){
                Interface::SetList(cart_menu, size(cart_menu));
                Interface::DisplayContent();
                int choice;
                if (!(cin >> choice)) {
                    std::cout << "\nInvalid input. Please enter a number." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    continue;
                }
            if (choice == 1) { //list courses in cart
                Interface::ListCourses(0, 0);
                continue; //go back to cart menu
            } else if (choice == 2) { //checkout
                Checkout();
                break; //return to student menu after checkout 
            } else if (choice == 3) { //go back to student menu
                break; // Exit the inner loop to return to the main menu
            } else {
                std::cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        } else if (choice == 2) { //browse departments
            while(true){
                Interface::ListDepartments();
                Interface::SetList(dept_menu, size(dept_menu));
                Interface::DisplayContent();
                if (!(cin >> choice)) {
                    std::cout << "\nInvalid input. Please enter a number." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    continue;
                }
                if (choice == 1) { //list courses of a department
                    int deptChoice;
                    cout << "\nEnter the department number to list its courses: ";
                    if (!(cin >> deptChoice) || deptChoice < 1 || deptChoice > TotalDepartments) {
                        std::cout << "\nInvalid department number. Please try again." << endl;
                        cin.clear();
                        cin.ignore(10000, '\n');
                        continue;
                    }else{
                        AddToCart(deptChoice); // prints course list and facilitates 'add a course to the cart'
                    }
                } else if (choice == 2) { //go back to main menu
                    break; // Exit the inner loop to return to the main menu
                } else {
                    cout << "Invalid choice. Please enter 1 or 2." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            }
        } else if (choice == 3) {
            Interface::ExitProgram();  // exit program
        } else {
            cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}
StudentInterface::~StudentInterface(){
    delete[] StoreCart;
    StoreCart = nullptr;
}