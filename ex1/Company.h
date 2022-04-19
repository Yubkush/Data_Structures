#ifndef COMPANY_H_
#define COMPANY_H_

#include "Employee.h"
#include "AVLTree.h"
#include <memory>

using std::shared_ptr;

class Company
{
    private:
        int id;
        int value;
        int num_of_employees;
        Employee* highest_earner;
        AVLTree<Employee*, int> EmployeeID_Dict;
        AVLTree<AVLTree<Employee*, int>, int> EmployeeSalary_Dict;

    public:
        Company(int id, int value);
        ~Company() = default;
        //Getters
        int getId() const;
        int getValue() const;
        int getNumOfEmployees() const;
        Employee* getHighestEarner() const;
        AVLTree<Employee*, int>& getEmployeeIdDict();
        AVLTree<AVLTree<Employee*, int>, int>& getEmployeeSalaryDict();
        //setters
        void setValue(int value);
        void setNumOfEmployees(int num_of_employees);
        void setHighestEarner(Employee* highest_earner);
        
        void AddEmployee(Employee* employee);
        void removeEmployee(Employee* employee);
};

#endif /* COMPANY_H_ */