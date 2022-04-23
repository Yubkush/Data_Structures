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

class ExtraPlaceholder
{
    virtual bool operator()(Employee* employee) const
    {
        return true;
    }
};

class ExtraEmployeeConditions
{
    private:
        int min_salary;
        int min_grade;
    public:
        ExtraEmployeeConditions(int min_salary, int min_grade) : min_salary(min_salary), min_grade(min_grade){}
        bool operator()(Employee* employee) const
        {
            return (employee->GetSalary() >= min_salary) && (employee->GetGrade() >= min_grade);
        }
};

class EmploymentSystem
{
    private:
        IdCondition id_cond;
        SalaryCondition salary_cond;
        CompanyCondition company_cond;
        
        Employee* highest_earner;
        int num_of_employees;
        int num_companies_with_employees;
        AVLTree<Employee*, IdCondition> employees_id_dict;
        AVLTree<Employee*, SalaryCondition> employees_salary_dict;
        AVLTree<Company*, CompanyCondition> all_companies;
        AVLTree<Company*, CompanyCondition> companies_with_employees;
    
        //private helpers
        void removeCompanyIfEmpty(Company* company);

    public:
        //Exceptions
        class CompanyAlreadyExists: std::exception{};
        class CompanyNotInSystem: std::exception{};
        class EmployeeAlreadyExists: std::exception{};
        class EmployeeNotInSystem: std::exception{};
        class CompanyContainsEmployees: std::exception{};
        class NoEmployeesInSystem: std::exception{};
        class AcquireFailed: std::exception{};
        class NotEnoughCompanies: std::exception{};
        class NoEmployeesInCompany: std::exception{};

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

        Employee* GetHighestEarner(int CompanyID);
        void AcquireCompany(int AcquirerID, int TargetID, double Factor);
        void GetAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees);
        void GetHighestEarnerInEachCompany(int NumOfCompanies, int **Employees);
        void GetNumEmployeesMatching(int CompanyID, int MinEmployeeID, int MaxEmployeeId,
                        int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees);
};

#endif /* EMPLOYMENT_SYSTEM_H */