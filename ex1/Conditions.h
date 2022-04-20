#ifndef CONDITIONS_H
#define CONDITIONS_H

#include "Employee.h"
#include "AVLTree.h"

class IdCondition
{
    public:
        bool operator()(const Employee* e1, const Employee* e2)
        {
            return e1->GetEmployeeId() < e2->GetEmployeeId();
        }
};

class SalaryCondition
{
    public:
        bool operator()(const Employee* e1, const Employee* e2)
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
};

#endif /* CONDITIONS_H */