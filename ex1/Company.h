#ifndef COMPANY_H_
#define COMPANY_H_

#include "Employee.h"
#include "Conditions.h"
#include "AVLTree.h"
#include <exception>

class Company
{
    private:
        int id;
        int value;
        int num_of_employees;
        IdCondition id_cond;
        SalaryCondition salary_cond;
        Employee* highest_earner;

        AVLTree<Employee*, IdCondition> id_dict;
        AVLTree<Employee*, SalaryCondition> salary_dict;

    public:
        class EmployeeAlreadyInCompany: public std::exception{};
        class EmployeeNotInCompany: public std::exception{};
        Company(const int id, const int value);
        ~Company() = default;

        //Getters
        int getId() const;
        int getValue() const;
        int getNumOfEmployees() const;
        Employee* getHighestEarner() const;
        AVLTree<Employee*, IdCondition>& getEmployeeIdDict();
        AVLTree<Employee*, SalaryCondition>& getEmployeeSalaryDict();
        //setters
        void setValue(int value);
        void setNumOfEmployees(int num_of_employees);
        void setHighestEarner(Employee* highest_earner);
        
        void AddEmployee(Employee* employee);
        void removeEmployee(Employee* employee);
};

#endif /* COMPANY_H_ */