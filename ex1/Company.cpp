#include "Company.h"

Company::Company(const int id, const int value):
id(id), value(value), num_of_employees(0), id_cond(), salary_cond(), 
highest_earner(nullptr), id_dict(id_cond), salary_dict(salary_cond)
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

int Company::getNumOfEmployees() const
{
    return num_of_employees;
}
Employee* Company::getHighestEarner() const
{
    return highest_earner;
}
AVLTree<Employee*, IdCondition>& Company::getEmployeeIdDict()
{
    return id_dict;
}

AVLTree<Employee*, SalaryCondition>& Company::getEmployeeSalaryDict()
{
    return salary_dict;
}

void Company::setValue(int value)
{
    this->value = value;
}
void Company::setNumOfEmployees(int num_of_employees)
{
    this->num_of_employees = num_of_employees;
}
void Company::setHighestEarner(Employee* highest_earner)
{
    this->highest_earner = highest_earner;
}

void Company::AddEmployee(Employee* employee)
{
    try{
        id_dict.insertNode(employee);
        salary_dict.insertNode(employee);
        //update highest_earner and num_of_employees
        highest_earner = salary_dict.findMaxNode(salary_dict.getRoot())->getData();
        num_of_employees++;
        //update employee company*
        employee->SetCompany(this);
    }
    catch(const AVLTree<Employee*, IdCondition>::ElementAlreadyInTree& e){
        throw EmployeeAlreadyInCompany();
    }
    catch(const AVLTree<Employee*, SalaryCondition>::ElementAlreadyInTree& e){
        throw EmployeeAlreadyInCompany();
    }
}

void Company::removeEmployee(Employee* employee)
{
    try{
        //remove from both tree
        id_dict.deleteNode(employee);
        salary_dict.deleteNode(employee);
        employee->SetCompany(nullptr);
        //update highest_earner and num_of_employees
        if(id_dict.isEmpty()){
            highest_earner = nullptr;
        }
        else{
            highest_earner = salary_dict.findMaxNode(salary_dict.getRoot())->getData();
        }
        num_of_employees--;
    }
    catch(const AVLTree<Employee*, IdCondition>::ElementNotInTree& e){
        throw EmployeeNotInCompany();
    }
    catch(const AVLTree<Employee*, SalaryCondition>::ElementNotInTree& e){
        throw EmployeeNotInCompany();
    }
}