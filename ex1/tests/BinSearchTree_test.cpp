#include "../BinarySearchTree.h"
#include "../Employee.h"
#include <vector>
#include <math.h>
#include <iostream>

using std::vector;

void testFunction(bool (*test_func)(const vector<shared_ptr<Employee>>&, BinSearchTree<shared_ptr<Employee>, int>&),
                const vector<shared_ptr<Employee>>& employees, BinSearchTree<shared_ptr<Employee>, int>& tree)
{
    if(test_func(employees, tree)){
        std::cout << "PASSED" << std::endl;
    }
    else{
        std::cout << "FAILED" << std::endl;
    }
}

bool testInsertNode(const vector<shared_ptr<Employee>>& employees, BinSearchTree<shared_ptr<Employee>, int>& tree)
{
    try{
        for (shared_ptr<Employee> employee : employees)
        {
            tree.insertNode(employee->GetEmployeeId(), employee);
        }
    }
    catch(const std::exception& e){
        return false;
    }
    try{
        tree.insertNode(employees[5]->GetEmployeeId(), employees[5]);
        return false;
    }
    catch(const BinSearchTree<shared_ptr<Employee>, int>::ElementAlreadyInTree& e){}
    return true;
}

bool testFindElement(const vector<shared_ptr<Employee>>& employees, BinSearchTree<shared_ptr<Employee>, int>& tree){
    shared_ptr<Employee> dummy_employee(new Employee(0, 0, 0, 0));
    try{
        tree.findElement(dummy_employee->GetEmployeeId(), tree.getRoot());
        return false;
    }
    catch(const BinSearchTree<shared_ptr<Employee>, int>::ElementNotInTree& e){}
    try{
        for (shared_ptr<Employee> employee : employees)
        {
            tree.findElement(employee->GetEmployeeId(), tree.getRoot());
        }
    }
    catch(const std::exception& e){
        return false;
    }
    for (int i = 0; i < 10; i++)
    {
        shared_ptr<Employee> employee_to_find = tree.findElement(employees[i]->GetEmployeeId(), tree.getRoot())->getData();
        if(employee_to_find->GetEmployeeId() != 10+i*pow(-1,i)){
            return false;
        }
    }
    return true;
}

bool testDeleteNode(const vector<shared_ptr<Employee>>& employees, BinSearchTree<shared_ptr<Employee>, int>& tree)
{
    try{
        for (shared_ptr<Employee> employee : employees)
        {
            auto node = tree.deleteNode(tree.getRoot() ,employee->GetEmployeeId());
        }
    }catch(const std::exception& e){return false;}
    if(tree.getRoot() != nullptr){
        return false;
    }
    return true;
}

void fillVector(vector<shared_ptr<Employee>>& employees)
{
    for (int i = 0; i < 10; i++)
    {
        shared_ptr<Employee> employee(new Employee(10+i*pow(-1,i), 2, 1000*i, i+5));
        employees.push_back(employee);
    }
    for (int i = 1; i < 10; i++)
    {
        shared_ptr<Employee> employee(new Employee(10+i*pow(-1,i+1), 2, 1000*i, i+5));
        employees.push_back(employee);
    }
}

int main(){
    BinSearchTree<shared_ptr<Employee>, int> tree;
    vector<shared_ptr<Employee>> employees;
    fillVector(employees);
    testFunction(testInsertNode, employees, tree);
    testFunction(testFindElement, employees, tree);
    testFunction(testDeleteNode, employees, tree);
    return 0;
}