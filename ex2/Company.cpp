#include "Company.h"

Company::Company(const int id, const int value): id(id), value(value), num_of_interns(0), sum_of_interns_grades(0),
                                    all_employees(), employees_with_salary()
{
    
}

int Company::getId() const
{
    return id;
}

int Company::getValue() const
{
    return value;
}

int Company::getNumOfInterns() const
{
    return num_of_interns;
}

int Company::getSumOfInternsGrades() const
{
    return sum_of_interns_grades;
}

RankTree& Company::getEmployeesWithSalaryTree()
{
    return employees_with_salary;
}

HashTable& Company::getEmployeesHash()
{
    return all_employees;
}

void Company::setValue(int value)
{
    this->value = value;
}

void Company::increaseNumOfInterns(int num_of_interns)
{
    if(this->num_of_interns + num_of_interns < 0){
        throw EmployeesUnderZero();
    }
    this->num_of_interns += num_of_interns;
}

void Company::increaseSumOfInternsGrades(int sum_of_interns_grades)
{
    if(this->sum_of_interns_grades + sum_of_interns_grades < 0){
        throw EmployeesUnderZero();
    }
    this->sum_of_interns_grades += sum_of_interns_grades;
}

void Company::AddEmployee(Employee* employee)
{
    //update num_of_interns and sum_of_interns_grades
    num_of_interns++;
    sum_of_interns_grades += employee->GetGrade();
    all_employees.insert(employee);
    //update employee company*
    employee->SetCompany(this);
}

void Company::removeEmployee(Employee* employee)
{
    try{
        all_employees.remove(employee->GetEmployeeId());
        //remove from tree
        if(employee->GetSalary() > 0){
            employees_with_salary.remove(employee);
        }
        else{
            //update num_of_interns and sum_of_interns_grades
            increaseNumOfInterns(-1);
            increaseSumOfInternsGrades(-(employee->GetGrade()));
        }
        employee->SetCompany(nullptr);
    }
    catch(const RankTree::ElementNotInTree& e){
        throw EmployeeNotInCompany();
    }
    catch(const HashTable::ElementNotInTable& e){
        throw EmployeeNotInCompany();
    }
    catch(const EmployeesUnderZero& e){
        throw e;
    }
}