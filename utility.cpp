#include "utility.h"
#include <iostream>
#include <string>
using namespace std;
Department::Department() {
    department_name = "";
    total_courses = 0;
}
Department::Department(const string& text) {
    department_name = text;
    total_courses = 0;
}
Department::~Department() {
}
Course::Course() {
    dept_id = 0;
    course_id = 0;
    course_name = "";
    course_schedule = "";
    course_price = 0.0;
}
Course::Course(int dept, int course, const string& name, const string& schedule, double price) {
    dept_id = dept;
    course_id = course;
    course_name = name;
    course_price = price;
    course_schedule = schedule;
}
string Course::GetCourseName() const {
    return course_name;
}
string Course::GetCourseSchedule() const {
    return course_schedule;
}
double Course::GetCoursePrice() const {
    return course_price;
}
int Course::GetDeptId() const {
    return dept_id;
}
int Course::GetCourseId() const {
    return course_id;
}
string Department::GetDepartmentName() const {
    return department_name;
}
int Department::GetCourseCount() const {
    return total_courses;
}
void Department::SetCourseCount(int count) {
    total_courses = count;
}
Course::~Course() {
}