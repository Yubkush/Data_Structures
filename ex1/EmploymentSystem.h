#ifndef EMPLOYMENT_SYSTEM_H
#define EMPLOYMENT_SYSTEM_H

#include "AVLTree.h"
#include "Employee.h"
#include "Company.h"
#include "Conditions.h"
#include <exception>

class CompanyCondition
{
    public:
        bool operator()(const Company* c1, const Company* c2)
        {
            return c1->getId() < c2->getId();
        }
};

class EmploymentSystem
{
    private:
        IdCondition id_cond;
        SalaryCondition salary_cond;
        CompanyCondition company_cond;
        
        Employee* highest_earner;
        AVLTree<Employee*, IdCondition> employees_id_dict;
        AVLTree<Employee*, SalaryCondition> employees_salary_dict;
        AVLTree<Company*, CompanyCondition> all_companies;
        AVLTree<Company*, CompanyCondition> companies_with_employees;

        //Exceptions
        class CompanyAlreadyExists: std::exception{};
        class CompanyNotInSystem: std::exception{};
        class EmployeeAlreadyExists: std::exception{};
        class EmployeeNotInSystem: std::exception{};
        class CompanyContainsEmployees: std::exception{};
        class NoEmployeesInSystem: std::exception{};
        class AcquireFailed: std::exception{};
    
        //private helpers
        void removeCompanyIfEmpty(Company* company);

    public:
        EmploymentSystem();
        ~EmploymentSystem();

        void AddCompany(int CompanyID, int Value);
        void AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade);
        void RemoveEmployee(int EmployeeID);
        void RemoveCompany(int CompanyID);

        Company* GetCompanyInfo(int CompanyID);
        Employee* GetEmployeeInfo(int EmployeeID);

        void IncreaseCompanyValue(int CompanyID, int ValueIncrease);
        void PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade);
        void HireEmployee(int EmployeeID, int NewCompanyID);

        Employee* GetHighestEarner(int CompanyID, int EmployeeID);
        void AcquireCompany(int AcquirerID, int TargetID, double Factor);
};

#endif /* EMPLOYMENT_SYSTEM_H */