#include "../AVLTree.h"
#include "../Employee.h"
<<<<<<< HEAD
#include "../Conditions.h"
#include <memory>
=======
>>>>>>> 71e69bfde8a99fce7a5473f8c55bb78aaeab3346
#include <vector>
#include <math.h>
#include <iostream>
#define COUNT 10

<<<<<<< HEAD
using std::shared_ptr;
using std::vector;
using std::cout;

void print2DUtil(AVLTree<Employee*, IdCondition>::Node* root, int space)
=======
using std::vector;
using std::cout;

void print2DUtil(AVLTree<shared_ptr<Employee>, int>::AVLNode root, int space)
>>>>>>> 71e69bfde8a99fce7a5473f8c55bb78aaeab3346
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    cout<<std::endl;
    for (int i = COUNT; i < space; i++)
        cout<<" ";
<<<<<<< HEAD
    cout<<root->data->GetEmployeeId()<<"\n";
=======
    cout<<root->key<<"\n";
>>>>>>> 71e69bfde8a99fce7a5473f8c55bb78aaeab3346
 
    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
<<<<<<< HEAD
void print2D(AVLTree<Employee*, IdCondition>::Node* root)
=======
void print2D(AVLTree<shared_ptr<Employee>, int>::AVLNode root)
>>>>>>> 71e69bfde8a99fce7a5473f8c55bb78aaeab3346
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

<<<<<<< HEAD
void testFunction(bool (*test_func)(const vector<Employee*>&, AVLTree<Employee*, IdCondition>&),
                const vector<Employee*>& employees, AVLTree<Employee*, IdCondition>& tree)
=======
void testFunction(bool (*test_func)(const vector<shared_ptr<Employee>>&, AVLTree<shared_ptr<Employee>, int>&),
                const vector<shared_ptr<Employee>>& employees, AVLTree<shared_ptr<Employee>, int>& tree)
>>>>>>> 71e69bfde8a99fce7a5473f8c55bb78aaeab3346
{
    if(test_func(employees, tree)){
        std::cout << "\033[;32mPASSED\033[0m" << std::endl;
    }
    else{
        std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
    }
}

<<<<<<< HEAD
bool inorderCheckBalance(AVLTree<Employee*, IdCondition>::Node* root)
=======
bool inorderCheckBalance(AVLTree<shared_ptr<Employee>, int>::AVLNode root)
>>>>>>> 71e69bfde8a99fce7a5473f8c55bb78aaeab3346
{
    bool left, right, is_root_balanced = false;
    if(root == nullptr){
        return true;
    }
    left = inorderCheckBalance(root->getLeft());
<<<<<<< HEAD
    if(abs((AVLTree<Employee*, IdCondition>::getHeight(root->getLeft())-AVLTree<Employee*, IdCondition>::getHeight(root->getRight()))) < 2)
=======
    if(abs((root->getLeft()->getHeight()-root->getRight()->getHeight())) < 2)
>>>>>>> 71e69bfde8a99fce7a5473f8c55bb78aaeab3346
        return is_root_balanced = true;
    right = inorderCheckBalance(root->getRight());
    return left && is_root_balanced && right;
}

<<<<<<< HEAD
bool testInsertNode(const vector<Employee*>& employees, AVLTree<Employee*, IdCondition>& tree)
{
    std::cout << "Testing " << __func__ << " ";
    try{
        for (Employee* employee : employees)
        {
            tree.insertNode(employee);
=======
bool testInsertNode(const vector<shared_ptr<Employee>>& employees, AVLTree<shared_ptr<Employee>, int>& tree)
{
    std::cout << "Testing " << __func__ << " ";
    try{
        for (shared_ptr<Employee> employee : employees)
        {
            tree.insertNode(employee->GetEmployeeId(), employee);
>>>>>>> 71e69bfde8a99fce7a5473f8c55bb78aaeab3346
            if(!inorderCheckBalance(tree.getRoot())){
                return false;
            }
        }
    }
    catch(const std::exception& e){
        return false;
    }
    try{
<<<<<<< HEAD
        tree.insertNode(employees[5]);
        return false;
    }
    catch(const AVLTree<Employee*, IdCondition>::ElementAlreadyInTree& e){}
    try{
        tree.insertNode(employees[0]);
        return false;
    }
    catch(const AVLTree<Employee*, IdCondition>::ElementAlreadyInTree& e){}
    return true;
}

bool testFindElement(const vector<Employee*>& employees, AVLTree<Employee*, IdCondition>& tree){
    std::cout << "Testing " << __func__ << " ";
    Employee* dummy_employee(new Employee(0, 0, 0, 0));
    try{
        tree.findElement(dummy_employee, tree.getRoot());
        return false;
    }
    catch(const AVLTree<Employee*, IdCondition>::ElementNotInTree& e){}
    try{
        for (Employee* employee : employees)
        {
            tree.findElement(employee, tree.getRoot());
=======
        tree.insertNode(employees[5]->GetEmployeeId(), employees[5]);
        return false;
    }
    catch(const BinSearchTree<shared_ptr<Employee>, int>::ElementAlreadyInTree& e){}
    try{
        tree.insertNode(employees[0]->GetEmployeeId(), employees[0]);
        return false;
    }
    catch(const BinSearchTree<shared_ptr<Employee>, int>::ElementAlreadyInTree& e){}
    return true;
}

bool testFindElement(const vector<shared_ptr<Employee>>& employees, AVLTree<shared_ptr<Employee>, int>& tree){
    std::cout << "Testing " << __func__ << " ";
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
>>>>>>> 71e69bfde8a99fce7a5473f8c55bb78aaeab3346
        }
    }
    catch(const std::exception& e){
        return false;
    }
<<<<<<< HEAD
    vector<Employee*> to_find {employees[0],
                        employees[7],
                        employees[6],
                        employees[8]};
    for(Employee* employee : to_find){
        Employee* employee_to_find = tree.findElement(employee, tree.getRoot())->getData();
        if(employee_to_find != employee){
            return false;
        }
    }
    delete dummy_employee;
    return true;
}
//doesnt use employees
bool testDeleteEmptyTree(const vector<Employee*>& employees, AVLTree<Employee*, IdCondition>& tree)
{
    std::cout << "Testing " << __func__ << " ";
    Employee* dummy_employee(new Employee(0, 0, 0, 0));
    try{
        tree.deleteNode(dummy_employee);
        return false;
    }catch(const AVLTree<Employee*, IdCondition>::ElementNotInTree& e){}
    if(tree.getRoot() != nullptr){
        return false;
    }
    delete dummy_employee;
    return true;
}
//empty the tree
bool testDeleteNode(const vector<Employee*>& employees, AVLTree<Employee*, IdCondition>& tree)
{
    std::cout << "Testing " << __func__ << " ";
    try{
        for (Employee* employee : employees)
        {
            // print2D(tree.getRoot());
            tree.deleteNode(employee);
=======
    vector<int> to_find {employees[0]->GetEmployeeId(),
                        employees[7]->GetEmployeeId(),
                        employees[6]->GetEmployeeId(),
                        employees[8]->GetEmployeeId()};
    for(int id : to_find){
        shared_ptr<Employee> employee_to_find = tree.findElement(id, tree.getRoot())->getData();
        if(employee_to_find->GetEmployeeId() != id){
            return false;
        }
    }
    return true;
}
//doesnt use employees
bool testDeleteEmptyTree(const vector<shared_ptr<Employee>>& employees, AVLTree<shared_ptr<Employee>, int>& tree)
{
    std::cout << "Testing " << __func__ << " ";
    try{
        tree.deleteNode(5);
        return false;
    }catch(const BinSearchTree<shared_ptr<Employee>, int>::ElementNotInTree& e){}
    if(tree.getRoot() != nullptr){
        return false;
    }
    return true;
}
//empty the tree
bool testDeleteNode(const vector<shared_ptr<Employee>>& employees, AVLTree<shared_ptr<Employee>, int>& tree)
{
    std::cout << "Testing " << __func__ << " ";
    try{
        for (shared_ptr<Employee> employee : employees)
        {
            // print2D(tree.getRoot());
            tree.deleteNode(employee->GetEmployeeId());
>>>>>>> 71e69bfde8a99fce7a5473f8c55bb78aaeab3346
            if(!inorderCheckBalance(tree.getRoot())){
                return false;
            }
        }
<<<<<<< HEAD
    }catch(const AVLTree<Employee*, IdCondition>::ElementNotInTree& e){return false;}
=======
    }catch(const std::exception& e){return false;}
>>>>>>> 71e69bfde8a99fce7a5473f8c55bb78aaeab3346
    if(tree.getRoot() != nullptr){
        return false;
    }
    return true;
}

<<<<<<< HEAD
bool testSingleNode(const vector<Employee*>& employees, AVLTree<Employee*, IdCondition>& tree)
{
    std::cout << "Testing " << __func__ << " ";
    Employee* employee = employees[0];
    tree.insertNode(employee);
=======
bool testSingleNode(const vector<shared_ptr<Employee>>& employees, AVLTree<shared_ptr<Employee>, int>& tree)
{
    std::cout << "Testing " << __func__ << " ";
    shared_ptr<Employee> employee = employees[0];
    tree.insertNode(employee->GetEmployeeId(), employee);
>>>>>>> 71e69bfde8a99fce7a5473f8c55bb78aaeab3346
    if(tree.getRoot()->getData() != employee){
        return false;
    }
    if(!inorderCheckBalance(tree.getRoot())){
        return false;
    }
<<<<<<< HEAD
    tree.deleteNode(employee);
    return tree.getRoot() == nullptr;
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
=======
    tree.deleteNode(employee->GetEmployeeId());
    return tree.getRoot() == nullptr;
}

void fillVector1(vector<shared_ptr<Employee>>& employees)
{
    shared_ptr<Employee> employee(new Employee(5, 1, 1000, 1));
    employees.push_back(employee);
    employee = shared_ptr<Employee>(new Employee(2, 1, 1000, 1));
    employees.push_back(employee);
    employee = shared_ptr<Employee>(new Employee(8, 1, 1000, 1));
    employees.push_back(employee);
    employee = shared_ptr<Employee>(new Employee(1, 1, 1000, 1));
    employees.push_back(employee);
    employee = shared_ptr<Employee>(new Employee(4, 1, 1000, 1));
    employees.push_back(employee);
    employee = shared_ptr<Employee>(new Employee(6, 1, 1000, 1));
    employees.push_back(employee);
    employee = shared_ptr<Employee>(new Employee(10, 1, 1000, 1));
    employees.push_back(employee);
    employee = shared_ptr<Employee>(new Employee(3, 1, 1000, 1));
    employees.push_back(employee);
    employee = shared_ptr<Employee>(new Employee(7, 1, 1000, 1));
    employees.push_back(employee);
    employee = shared_ptr<Employee>(new Employee(9, 1, 1000, 1));
    employees.push_back(employee);
    employee = shared_ptr<Employee>(new Employee(12, 1, 1000, 1));
    employees.push_back(employee);
    employee = shared_ptr<Employee>(new Employee(11, 1, 1000, 1));
    employees.push_back(employee);
}

void fillVector2(vector<shared_ptr<Employee>>& employees)
{
    for (int i = 0; i < 10; i++)
    {
        shared_ptr<Employee> employee(new Employee(i+1, 2, 1000*i, i+5));
>>>>>>> 71e69bfde8a99fce7a5473f8c55bb78aaeab3346
        employees.push_back(employee);
    }
}

<<<<<<< HEAD
void fillVector3(vector<Employee*>& employees)
{
    for (int i = 1; i < 5; i++)
    {
        Employee* employee = new Employee(10*i, 2, 1000*i, i+5);
        employees.push_back(employee);
    }
    Employee* employee = new Employee(35, 2, 1000, 1);
    employees.push_back(employee);
    for (int i = 11; i < 16; i++)
    {
        Employee* employee = new Employee(i, 2, 1000*i, i+5);
=======
void fillVector3(vector<shared_ptr<Employee>>& employees)
{
    for (int i = 1; i < 5; i++)
    {
        shared_ptr<Employee> employee(new Employee(10*i, 2, 1000*i, i+5));
        employees.push_back(employee);
    }
    shared_ptr<Employee> employee(new Employee(35, 2, 1000, 1));
    employees.push_back(employee);
    for (int i = 11; i < 16; i++)
    {
        shared_ptr<Employee> employee(new Employee(i, 2, 1000*i, i+5));
>>>>>>> 71e69bfde8a99fce7a5473f8c55bb78aaeab3346
        employees.push_back(employee);
    }
}

<<<<<<< HEAD
void clearVector(vector<Employee*>& employees)
{
    for (auto p : employees)
    {
        delete p;
    } 
    employees.clear();
}


int main(){
    IdCondition cond;
    AVLTree<Employee*, IdCondition> tree(cond);
    vector<Employee*> employees;
=======

int main(){
    AVLTree<shared_ptr<Employee>, int> tree;
    vector<shared_ptr<Employee>> employees;
>>>>>>> 71e69bfde8a99fce7a5473f8c55bb78aaeab3346
    fillVector1(employees);
    testFunction(testDeleteEmptyTree, employees, tree);
    testFunction(testSingleNode, employees, tree);
    // test fillVector1 tree
    testFunction(testInsertNode, employees, tree);
    testFunction(testFindElement, employees, tree);
    testFunction(testDeleteNode, employees, tree);
     
    // test fillVector2 tree
<<<<<<< HEAD
    clearVector(employees);
=======
    employees.clear();
>>>>>>> 71e69bfde8a99fce7a5473f8c55bb78aaeab3346
    fillVector2(employees);
    testFunction(testInsertNode, employees, tree);
    // print2D(tree.getRoot());
    testFunction(testFindElement, employees, tree);
    // print2D(tree.getRoot());
    testFunction(testDeleteNode, employees, tree);

    // test fillVector3 tree
<<<<<<< HEAD
    clearVector(employees);
=======
    employees.clear();
>>>>>>> 71e69bfde8a99fce7a5473f8c55bb78aaeab3346
    fillVector3(employees);
    testFunction(testInsertNode, employees, tree);
    testFunction(testFindElement, employees, tree);
    testFunction(testDeleteNode, employees, tree);
    
<<<<<<< HEAD
    clearVector(employees);
=======
>>>>>>> 71e69bfde8a99fce7a5473f8c55bb78aaeab3346
    return 0;
}