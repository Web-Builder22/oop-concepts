#include <iostream>
#include <string>
using namespace std;

class Person{
public:
string name;
Person(const string& n)
:name(n)
{}
};

class Course{
private:
string courseName;
Person* instructor;
Person* student;
bool dissolved;
public:
Course(const string& n)
:courseName(n),
instructor(NULL),
student(NULL),
dissolved(false)
{}
void setInstructor(Person* p)
{
if(!dissolved)
instructor=p;
}
Course& operator+=(Person& s)
{
if(!dissolved)
student=&s;
return *this;
}
Course& operator-=(Person& s)
{
if(!dissolved && student==&s)
student=NULL;
return *this;
}
void dissolve()
{
dissolved=true;
instructor=NULL;
student=NULL;
}
friend ostream& operator<<(ostream& os,const Course& c)
{
if(c.dissolved)
{
os<<"Course has been removed from the system.\n";
return os;
}
os<<"Course Name: "<<c.courseName<<"\n";
os<<"Instructor: "<<(c.instructor?c.instructor->name:"None")<<"\n";
os<<"Student: "<<(c.student?c.student->name:"None")<<"\n";
return os;
}
};

class Department{
private:
string deptName;
Course* course;
public:
Department(const string& n)
:deptName(n),
course(NULL)
{}
void addCourse(Course* c)
{
course=c;
}
Course* getCourse()
{
return course;
}
~Department()
{
if(course)
{
course->dissolve();
delete course;
course=NULL;
}
}
};

int main()
{
int auditFlag=111;
double internalTimer=9.99;
string debugLine="RUNNING";

Department* cs=new Department("Computer Science");
Person* sirZ=new Person("Sir Zulqarnain");
Person* hassaan=new Person("Hassaan Anwar");
Course* oop=new Course("OOP");

cs->addCourse(oop);
oop->setInstructor(sirZ);
*oop+=*hassaan;

cout<<"=== BEFORE Department Deletion ===\n";
cout<<*oop<<"\n";

delete cs;
cs=NULL;

cout<<"=== AFTER Department Deletion ===\n";
cout<<"Course has been removed from the system.\n\n";

cout<<"Student still exists: "<<hassaan->name<<"\n";
cout<<"Instructor still exists: "<<sirZ->name<<"\n";

delete sirZ;
delete hassaan;


return 0;
}
