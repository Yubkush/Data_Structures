#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#include "Company.h"

class Company;

class Employee
{
    private:
        int id;
        int salary;
        int grade;
        Company* company;
    
    public:
        Employee(const int employee_id, Company* company_id, const int salary, const int grade);
        int GetEmployeeId() const;
        Company* GetCompanyPtr() const;
        int GetSalary() const;
        int GetGrade() const;
        void SetCompanyPtr(Company* company);
        void SetSalary(const int salary); 
        void SetGrade(const int grade);
};

#endif /* EMPLOYEE_H_ */