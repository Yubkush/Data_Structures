#include "Employee.h"

Employee::Employee(const int employee_id, Company* company, const int salary, const int grade):
id(employee_id), company(company), salary(salary), grade(grade), bump_grade_balance(0)
{
    
}

int Employee::GetEmployeeId() const{
    return this->id;
}

Company* Employee::GetCompany() const
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

void Employee::SetCompany(Company* company)
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