#include "Employee.h"

Employee::Employee(const long int employee_id, Company* company, const long int salary, const long int grade):
id(employee_id), company(company), salary(salary), grade(grade)
{
    
}

long int Employee::GetEmployeeId() const{
    return this->id;
}

Company* Employee::GetCompany() const
{
    return company;
}

long int Employee::GetSalary() const
{
    return salary;
}

long int Employee::GetGrade() const
{
    return grade;
}

void Employee::SetCompany(Company* company)
{
    this->company = company;
}

void Employee::SetSalary(const long int salary)
{
    this->salary = salary;
}

void Employee::SetGrade(const long int grade)
{
    this->grade = grade;
}