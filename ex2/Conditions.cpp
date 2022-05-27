#include "Conditions.h"

bool IdCondition::operator()(const Employee* e1, const Employee* e2) const
{
    return e1->GetEmployeeId() < e2->GetEmployeeId();
}

bool SalaryCondition::operator()(const Employee* e1, const Employee* e2) const
{
    if(e1->GetSalary() < e2->GetSalary()){
        return true;
    }
    else if(e1->GetSalary() > e2->GetSalary()){
        return false;
    }
    else{
        return e1->GetEmployeeId() > e2->GetEmployeeId();
    }
}