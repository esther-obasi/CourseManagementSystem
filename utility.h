#ifndef UTILITY_H
#define UTILITY_H
#include <string>
using namespace std;
const int MAX_ENTRIES = 50;
class Department{
private:
//data members
    string department_name;
    int total_courses;
public:
//constructors
    Department();
    Department(const string& text);
    ~Department(); //destructor
//member functions
    string GetDepartmentName() const;
    void SetCourseCount(int count);
    int GetCourseCount() const;
};

class Course{
private:
//data members
    int dept_id;
    float course_id;
    string course_name;
    string course_schedule;
    double course_price;
public:
//constructors
    Course();
    Course(int dept, float course, const string& name, const string& schedule, double price);
    ~Course(); //destructor
//member functions
    string GetCourseName() const;
    string GetCourseSchedule() const;
    double GetCoursePrice() const;
    int GetDeptId() const;
    float GetCourseId() const;
};

#endif //UTILITY_H