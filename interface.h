#ifndef INTERFACE_H
#define INTERFACE_H
#include "utility.h"
#include <string>
using namespace std;
extern Department* StoreDepartments;
extern Course* StoreCourses;
extern Course* StoreCart;

const int MAX_MENU = 7;
extern int TotalDepartments;
extern int TotalCourses;
extern int CartCount;
class Interface{
private:
//data members
    static const string init_menu[MAX_MENU];
    string list[MAX_ENTRIES];
protected:
//helper method for derived classes
    void SetList(const string items[], int count);
public:
//constructor
    Interface();
    ~Interface(); //destructor
//member functions
    virtual void RunMenu();  // Each class implements its own menu loop
    string Trim(const string& str);
    string toLower(const string& str);
    string toUpper(const string& str);
    void DisplayContent();
    void ListDepartments();
    void ListCourses(int id, int type);
    void ExitProgram();
};
class AdminInterface : public Interface{
private:
    static const string admin_menu[MAX_MENU];
public:
//constructor
    AdminInterface();
    ~AdminInterface(); //destructor
//member functions
    void RunMenu() override;
    void AddDepartment();
    void AddCourse();
    void SaveToCSV();
};
class StudentInterface : public Interface{
private:
    static const string student_menu[MAX_MENU];
    static const string cart_menu[MAX_MENU];
    static const string dept_menu[MAX_MENU];
    static const string course_menu[MAX_MENU];
public:
//constructor
    StudentInterface();
    ~StudentInterface(); //destructor
//member functions
    void RunMenu() override;
    void AddToCart(int dept);
    void ClearCart();
    void Checkout();
};
#endif //INTERFACE_H