#ifndef CONDITIONS_H
#define CONDITIONS_H

#include "Employee.h"

class Employee;

class IdCondition
{
    public:
        IdCondition() = default;
        ~IdCondition() = default;
        bool operator()(const Employee* e1, const Employee* e2) const;
};

class SalaryCondition
{
    public:
        SalaryCondition() = default;
        ~SalaryCondition() = default;
        bool operator()(const Employee* e1, const Employee* e2) const;
};

#endif /* CONDITIONS_H */