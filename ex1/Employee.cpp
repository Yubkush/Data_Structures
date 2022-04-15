#include "Employee.h"

Employee::Employee(const int employee_id, const int company_id, const int salary, const int grade):
id(employee_id), company_id(company_id), salary(salary), grade(grade)
{
    
}

int Employee::GetEmployeeId() const{
    return this->id;
}

int Employee::GetCompanyId() const
{
    return company_id;
}

int Employee::GetSalary() const
{
    return salary;
}

int Employee::GetGrade() const
{
    return grade;
}

void Employee::SetCompanyId(const int company_id)
{
    this->company_id = company_id;
}

void Employee::SetSalary(const int salary)
{
    this->salary = salary;
}

void Employee::SetGrade(const int grade)
{
    this->grade = grade;
}

bool Employee::operator<(const Employee& employee) const
{
    return this->id < employee.GetEmployeeId();
}