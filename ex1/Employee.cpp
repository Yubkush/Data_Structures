#include "Employee.h"

Employee::Employee(const int employee_id, Company* company, const int salary, const int grade):
id(employee_id), company(company), salary(salary), grade(grade)
{
    
}

int Employee::GetEmployeeId() const{
    return this->id;
}

Company* Employee::GetCompanyPtr() const
{
    return company;
}

int Employee::GetSalary() const
{
    return salary;
}

int Employee::GetGrade() const
{
    return grade;
}

void Employee::SetCompanyPtr(Company* company)
{
    this->company = company;
}

void Employee::SetSalary(const int salary)
{
    this->salary = salary;
}

void Employee::SetGrade(const int grade)
{
    this->grade = grade;
}