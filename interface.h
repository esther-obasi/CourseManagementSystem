#ifndef INTERFACE_H
#define INTERFACE_H
class Interface{
private:
public:
//constructor
    Interface();
    ~Interface(); //destructor
};
class AdminInterface : public Interface{
private:
public:
//constructor
    AdminInterface();
    ~AdminInterface(); //destructor
//member function
    void SaveToCSV();
};
class StudentInterface : public Interface{
private:
public:
//constructor
    StudentInterface();
    ~StudentInterface(); //destructor
};
#endif