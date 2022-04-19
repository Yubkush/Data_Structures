#include "Company.h"

Company::Company(const int id, const int value):
id(id), value(value)
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
AVLTree<Employee*, int>& Company::getEmployeeIdDict()
{
    return EmployeeID_Dict;
}

AVLTree<AVLTree<Employee*, int>, int>& Company::getEmployeeSalaryDict()
{
    return EmployeeSalary_Dict;
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
    this->EmployeeID_Dict.insertNode((*employee).GetEmployeeId(), employee);
    try{
        this->EmployeeSalary_Dict.findElement((*employee).GetSalary(), EmployeeSalary_Dict.getRoot());
    }
    //If salary doesn't exist in tree build avl tree for salary
    catch(const BinSearchTree<BinSearchTree<Employee*, int>, int>::ElementNotInTree& e){
        this->EmployeeSalary_Dict.insertNode((*employee).GetSalary(), AVLTree<Employee*, int>());
    }
    //insert employee to salary tree
    ((this->EmployeeSalary_Dict.findElement((*employee).GetSalary(), EmployeeSalary_Dict.getRoot()))->getData()).
                                            insertNode((*employee).GetEmployeeId(), employee);
    //update highest_earner and num_of_employees
    if(employee->GetSalary() > highest_earner->GetSalary()){
        highest_earner = employee;
    }
    else if(employee->GetSalary() == highest_earner->GetSalary() && 
            employee->GetEmployeeId() < highest_earner->GetEmployeeId()){
        highest_earner = employee;
    }
    num_of_employees += 1;
}

void Company::removeEmployee(Employee* employee)
{
    try{
        //remove from both tree
        EmployeeID_Dict.deleteNode(employee->GetEmployeeId());
        AVLTree<Employee*, int>& mini_tree = EmployeeSalary_Dict.findElement(employee->GetSalary(), EmployeeSalary_Dict.getRoot())->getData();
        mini_tree.deleteNode(employee->GetEmployeeId());
        if(mini_tree.getRoot() == nullptr){
            EmployeeSalary_Dict.deleteNode(employee->GetSalary());
        }
        //update highest_earner and num_of_employees
        AVLTree<Employee*, int>& max_tree_node = EmployeeSalary_Dict.findMaxNode(EmployeeSalary_Dict.getRoot())->getData();
        highest_earner = max_tree_node.findMaxNode(max_tree_node.getRoot())->getData();
        num_of_employees -= 1;
    }
    catch(const typename BinSearchTree<BinSearchTree<Employee*, int>, int>::ElementNotInTree& e){
        throw e;
    }
    catch(const typename BinSearchTree<Employee*, int>::ElementNotInTree& e){
        throw e;
    }
}