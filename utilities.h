#ifndef UTILITIES_H
#define UTILITIES_H
#include <string>
class Department{
private:
//data members
    int dept_id;
    string dept_name;
    int num_of_courses;
public:
//constructors
    Department();
    ~Department(); //destructor
//member functions
    void ListDepartments();
    void AddDepartment();
};

class Course{
private:
//data members
    int course_id;
    string course_name;
    string course_schedule[3];
    double course_price;
public:
//constructors
    Course();
    ~Course(); //destructor
//member functions
    void ListCourses();
    void AddCourse();
};

class Cart{
private:
//data members
public:
//constructors
    Cart();
    ~Cart(); //destructor
//member functions
    void AddToCart();
    void Checkout();
};
#endif