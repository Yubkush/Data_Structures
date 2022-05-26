#ifndef CONDITIONS_H
#define CONDITIONS_H

#include "Employee.h"

class Employee;

class SalaryCondition
{
    public:
        SalaryCondition() = default;
        ~SalaryCondition() = default;
        bool operator()(const Employee* e1, const Employee* e2) const;
};

#endif /* CONDITIONS_H */