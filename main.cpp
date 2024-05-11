#include <iostream>
#include <string>
#include "math.h"
using namespace std;

class Base
{
protected:
    int dat;
public:
    Base() : dat(1) {}
    Base(int d) : dat(d) {}
};

class D1 : protected Base
{
protected:
    int d1;
public:
    D1() : d1(1) {}
    D1(int d) : d1(d) {}
    D1(int d, int dt) : Base(dt), d1(d) {}
};



class D2 : protected Base, protected D1
{
protected:
    int d2;
public:
    D2() : d2(1) {}
    D2(int d) : d2(d) {}
    D2(int d, int dt, int a, int b) : Base(dt), D1(a,b), d2(d) {}
};


class D3 : protected Base, protected D1
{
protected:
    int d3;
public:
    D3() : d3(1) {}
    D3(int d) : d3(d) {}
    D3(int d, int dt, int a, int b) : Base(dt), D1(a, b), d3(d) {}
};


class D23 : protected D2, protected D3
{

protected:
    double d23;
public:
    D23() : d23(1){}
    D23(int d) : d23(d){}
    D23(int d1, int d2, int d3, int d4, int d5, int d6, int d7, int d8, double d9) :
                                                                                     D2(d1, d2, d3, d4),
                                                                                     D3(d5, d6, d7, d8), d23(d9){}
};




class D1V : virtual protected Base
{
protected:
    int d1;
public:
    D1V() : d1(1) {}
    D1V(int d) : d1(d) {}
    D1V(int d, int dt) : Base(dt), d1(d) {}
};



class D2V : virtual protected Base, virtual protected D1V
{
protected:
    int d2;
public:
    D2V() : d2(1) {}
    D2V(int d) : d2(d) {}
    D2V(int d, int dt, int a, int b) : Base(dt), D1V(a, b), d2(d) {}
};


class D3V : virtual protected Base, virtual protected D1V
{
protected:
    int d3;
public:
    D3V() : d3(1) {}
    D3V(int d) : d3(d) {}
    D3V(int d, int dt, int a, int b) : Base(dt), D1V(a, b), d3(d) {}
};


class D23V : virtual protected D2V, virtual protected D3V
{

protected:
    double d23;
public:
    D23V() : d23(1) {}
    D23V(int d) : d23(d) {}
    D23V(int d1, int d2, int d3, int d4, int d5, int d6, int d7, int d8, double d9) :
                                                                                      D2V(d1, d2, d3, d4),
                                                                                      D3V(d5, d6, d7, d8), d23(d9) {}
};

void firstTask(){
    D23 obj(1, 2, 3, 4, 5, 6, 7, 8, 9.5);
    D23V objV(1, 2, 3, 4, 5, 6, 7, 8, 9.5);
    cout << "Size of Base: " << sizeof(Base) << " bytes" << endl;
    cout << "Size of D1: " << sizeof(D1) << " bytes" << endl;
    cout << "Size of D2: " << sizeof(D2) << " bytes" << endl;
    cout << "Size of D3: " << sizeof(D3) << " bytes" << endl;
    cout << "Size of D23: " << sizeof(D23) << " bytes" << endl;
    cout << endl;
    cout << "Size of D1V: " << sizeof(D1V) << " bytes" << endl;
    cout << "Size of D2V: " << sizeof(D2V) << " bytes" << endl;
    cout << "Size of D3V: " << sizeof(D3V) << " bytes" << endl;
    cout << "Size of D23V: " << sizeof(D23V) << " bytes" << endl;
}



class Function
{
protected:
    double x;
public:
    Function() : x(0) {}
    Function(double _x) : x(_x) {}
    virtual double Funk() = 0;
};
class Line: public Function
{
    double a;
    double b;
public:
    Line(double _x, double _a, double _b) : Function(_x), a(_a), b(_b) {}
    virtual double Funk() override {
        return a * x + b;
    }
};

class Ellipse: public Function{
    double a, b;

public:
    Ellipse(double a, double b) : a(a), b(b) {}

    virtual double Funk() override {
        return sqrt(1 - (x * x) / (a * a)) * b;
    }
};

class Hyperbola : public Function {
    double a, b;

public:
    Hyperbola(double a, double b) : a(a), b(b) {}

    virtual double Funk() override {
        return sqrt(1 + (x * x) / (a * a)) * b;
    }
};

void secondTask(){
    double x = 2.0;
    Line line(2, 3, 4);
    Ellipse ellipse(5, 4);
    Hyperbola hyperbola(3, 2);

    cout << "Value of line at x = " << x << ": " << line.Funk() << endl;
    cout << "Value of ellipse at x = " << x << ": " << ellipse.Funk() << endl;
    cout << "Value of hyperbola at x = " << x << ": " << hyperbola.Funk() << endl;
}

class Person {
protected:
    string name;
    int age;

public:
    Person(const string& _name, int _age) : name(_name), age(_age) {}
    virtual ~Person() {}

    virtual void display() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }

    friend istream& operator>>(istream& in, Person& person) {
        in >> person.name;
        in >> person.age;
        return in;
    }

    friend ostream& operator<<(ostream& out, const Person& person) {
        out << "Name: " << person.name << ", Age: " << person.age;
        return out;
    }
};

class Employee : public Person {
protected:
    string position;
    double salary;

public:
    Employee(const string& _name, int _age, const string& _position, double _salary)
        : Person(_name, _age), position(_position), salary(_salary) {}

    void display() const override {
        Person::display();
        cout << "Position: " << position << ", Salary: " << salary << endl;
    }

    friend istream& operator>>(istream& in, Employee& employee) {
        in >> employee.name;
        in >> employee.age;
        in >> employee.position;
        in >> employee.salary;
        return in;
    }

    friend ostream& operator<<(ostream& out, const Employee& employee) {
        out << static_cast<const Person&>(employee) << ", Position: " << employee.position << ", Salary: " << employee.salary;
        return out;
    }
};

class Family {
protected:
    string familyRole;

public:
    Family(const string& _role) : familyRole(_role) {}
    virtual ~Family() {}

    virtual void display() const {
        cout << "Family Role: " << familyRole << endl;
    }

    friend istream& operator>>(istream& in, Family& family) {
        in >> family.familyRole;
        return in;
    }

    friend ostream& operator<<(ostream& out, const Family& family) {
        out << "Family Role: " << family.familyRole;
        return out;
    }
};

class EmployeeFamily : public Employee, public Family, public Person {
public:
    EmployeeFamily(const string& _name, int _age, const string& _position, double _salary, const string& _role)
        : Person(_name, _age), Employee(_name, _age, _position, _salary), Family(_role) {}

    void display() const override {
        Employee::display();
        Family::display();
    }
};

void thirdTask(){
    EmployeeFamily empFam("John Doe", 35, "Manager", 5000, "Father");
    empFam.display();
}

int main() {
   firstTask();
//   secondTask();
//   thirdTask();
    return 0;
}
