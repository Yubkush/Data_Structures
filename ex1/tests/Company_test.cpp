#include "../Company.h"
#include "../AVLTree.h"
#include "../Employee.h"
#include "../Conditions.h"
#include <memory>
#include <vector>
#include <math.h>
#include <iostream>
#define COUNT 10

using std::shared_ptr;
using std::vector;
using std::cout;

// void print2DUtil(AVLcompany<Employee*, IdCondition>::Node* root, int space)
// {
//     // Base case
//     if (root == NULL)
//         return;
 
//     // Increase distance between levels
//     space += COUNT;
 
//     // Process right child first
//     print2DUtil(root->right, space);
 
//     // Print current node after space
//     // count
//     cout<<std::endl;
//     for (int i = COUNT; i < space; i++)
//         cout<<" ";
//     cout<<root->data->GetEmployeeId()<<"\n";
 
//     // Process left child
//     print2DUtil(root->left, space);
// }
 
// // Wrapper over print2DUtil()
// void print2D(AVLcompany<Employee*, IdCondition>::Node* root)
// {
//     // Pass initial space count as 0
//     print2DUtil(root, 0);
// }

void testFunction(bool (*test_func)(const vector<Employee*>&, Company&),
                const vector<Employee*>& employees, Company& company)
{
    if(test_func(employees, company)){
        std::cout << "\033[;32mPASSED\033[0m" << std::endl;
    }
    else{
        std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
    }
}

bool testAddEmployee(const vector<Employee*>& employees, Company& company)
{
    std::cout << "Testing " << __func__ << " ";
    try{
        for (Employee* employee : employees)
        {
            int num = company.getNumOfEmployees();
            company.AddEmployee(employee);
            if(company.getNumOfEmployees() != num + 1){
                return false;
            }
        }
    }
    catch(const std::exception& e){
        return false;
    }
    try{
        company.AddEmployee(employees[5]);
        return false;
    }
    catch(const Company::EmployeeAlreadyInCompany& e){}
    try{
        company.AddEmployee(employees[0]);
        return false;
    }
    catch(const Company::EmployeeAlreadyInCompany& e){}
    if(company.getHighestEarner() != company.getEmployeeSalaryDict().findMaxNode(company.getEmployeeSalaryDict().getRoot())->getData()){
        return false;
    }
    return true;
}

//doesnt use employees
bool testEmptyCompany(const vector<Employee*>& employees, Company& company)
{
    std::cout << "Testing " << __func__ << " ";
    Employee* dummy_employee(new Employee(0, 0, 0, 0));
    try{
        company.removeEmployee(dummy_employee);
        return false;
    }catch(const Company::EmployeeNotInCompany& e){}
    if(company.getNumOfEmployees() != 0){
        return false;
    }
    delete dummy_employee;
    return true;
}
//empty the company
bool testRemoveEmployee(const vector<Employee*>& employees, Company& company)
{
    std::cout << "Testing " << __func__ << " ";
    try{
        for (Employee* employee : employees)
        {
            company.removeEmployee(employee);
        }
    }catch(const Company::EmployeeNotInCompany& e){return false;}
    if(company.getNumOfEmployees() != 0){
        return false;
    }
    return true;
}

bool testSingleEmployee(const vector<Employee*>& employees, Company& company)
{
    std::cout << "Testing " << __func__ << " ";
    Employee* employee = employees[0];
    company.AddEmployee(employee);
    if(company.getHighestEarner() != employee){
        return false;
    }
    if(company.getNumOfEmployees() != 1){
        return false;
    }
    company.removeEmployee(employee);
    return company.getEmployeeIdDict().getRoot() == nullptr && company.getEmployeeSalaryDict().getRoot() == nullptr;
}

bool finalTest(const vector<Employee*>& employees, Company& company)
{
    std::cout << "Testing " << __func__ << " ";
    for (int i = 0; i < 3; i++)
    {
        try{
            company.AddEmployee(employees[i]);
        }
        catch(const Company::EmployeeAlreadyInCompany& e){return false;}
        if(company.getHighestEarner() != employees[i]){
            return false;
        }
    }
    if(company.getNumOfEmployees() != 3){
        return false;
    }
    try{
        company.removeEmployee(employees[2]);
    }
    catch(const Company::EmployeeNotInCompany& e){return false;}
    if(company.getNumOfEmployees() != 2){
        return false;
    }
    for (int i = 2; i < employees.size(); i++)
    {
        try{
            company.AddEmployee(employees[i]);
        }
        catch(const Company::EmployeeAlreadyInCompany& e){return false;}
    }
    if(company.getHighestEarner() != employees[5]){
        return false;
    }
    try{
        company.removeEmployee(employees[employees.size()-1]);
        company.removeEmployee(employees[employees.size()-2]);
    }
    catch(const Company::EmployeeNotInCompany& e){return false;}
    if(company.getNumOfEmployees() != employees.size()-2){
        return false;
    }
    return true;
}

void fillVector1(vector<Employee*>& employees)
{
    Employee* employee = new Employee(5, 1, 1000, 1);
    employees.push_back(employee);
    employee = new Employee(2, 1, 1000, 1);
    employees.push_back(employee);
    employee = new Employee(8, 1, 1000, 1);
    employees.push_back(employee);
    employee = new Employee(1, 1, 1000, 1);
    employees.push_back(employee);
    employee = new Employee(4, 1, 1000, 1);
    employees.push_back(employee);
    employee = new Employee(6, 1, 1000, 1);
    employees.push_back(employee);
    employee = new Employee(10, 1, 1000, 1);
    employees.push_back(employee);
    employee = new Employee(3, 1, 1000, 1);
    employees.push_back(employee);
    employee = new Employee(7, 1, 1000, 1);
    employees.push_back(employee);
    employee = new Employee(9, 1, 1000, 1);
    employees.push_back(employee);
    employee = new Employee(12, 1, 1000, 1);
    employees.push_back(employee);
    employee = new Employee(11, 1, 1000, 1);
    employees.push_back(employee);
}

void fillVector2(vector<Employee*>& employees)
{
    for (int i = 0; i < 10; i++)
    {
        Employee* employee = new Employee(i+1, 2, 1000*i, i+5);
        employees.push_back(employee);
    }
}

void fillVector3(vector<Employee*>& employees)
{
    for (int i = 1; i < 5; i++)
    {
        Employee* employee = new Employee(101*i, 2, 10*i, i+5);
        employees.push_back(employee);
    }
    Employee* employee = new Employee(35, 2, 1000, 1);
    employees.push_back(employee);
    for (int i = 11; i < 16; i++)
    {
        Employee* employee = new Employee(i, 2, 1000, i+5);
        employees.push_back(employee);
    }
}

void clearVector(vector<Employee*>& employees)
{
    for (auto p : employees)
    {
        delete p;
    } 
    employees.clear();
}


int main(){
    Company company(1, 10000);
    vector<Employee*> employees;
    fillVector1(employees);
    testFunction(testEmptyCompany, employees, company);
    testFunction(testSingleEmployee, employees, company);
    // test fillVector1 company
    testFunction(testAddEmployee, employees, company);
    testFunction(testRemoveEmployee, employees, company);
     
    // test fillVector2 company
    clearVector(employees);
    fillVector2(employees);
    testFunction(testAddEmployee, employees, company);
    // print2D(company.getRoot());
    // print2D(company.getRoot());
    testFunction(testRemoveEmployee, employees, company);

    // test fillVector3 company
    clearVector(employees);
    fillVector3(employees);
    testFunction(testAddEmployee, employees, company);
    testFunction(testRemoveEmployee, employees, company);

    testFunction(finalTest, employees, company);
    
    clearVector(employees);
    return 0;
}