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

void print2DUtil(AVLTree<Employee*, IdCondition>::Node* root, int space)
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
    cout<<root->data<<"\n";
 
    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void print2D(AVLTree<Employee*, IdCondition>::Node* root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

void testFunction(bool (*test_func)(const vector<Employee*>&, AVLTree<Employee*, IdCondition>&),
                const vector<Employee*>& employees, AVLTree<Employee*, IdCondition>& tree)
{
    if(test_func(employees, tree)){
        std::cout << "\033[;32mPASSED\033[0m" << std::endl;
    }
    else{
        std::cout << "\033[1;31mFAILED\033[0m" << std::endl;
    }
}

bool inorderCheckBalance(AVLTree<Employee*, IdCondition>::Node* root)
{
    bool left, right, is_root_balanced = false;
    if(root == nullptr){
        return true;
    }
    left = inorderCheckBalance(root->getLeft());
    if(abs((AVLTree<Employee*, IdCondition>::getHeight(root->getLeft())-AVLTree<Employee*, IdCondition>::getHeight(root->getRight()))) < 2)
        return is_root_balanced = true;
    right = inorderCheckBalance(root->getRight());
    return left && is_root_balanced && right;
}

bool testInsertNode(const vector<Employee*>& employees, AVLTree<Employee*, IdCondition>& tree)
{
    std::cout << "Testing " << __func__ << " ";
    try{
        for (Employee* employee : employees)
        {
            tree.insertNode(employee);
            if(!inorderCheckBalance(tree.getRoot())){
                return false;
            }
        }
    }
    catch(const std::exception& e){
        return false;
    }
    try{
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
        }
    }
    catch(const std::exception& e){
        return false;
    }
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
    return true;
}
//empty the tree
bool testDeleteNode(const vector<Employee*>& employees, AVLTree<Employee*, IdCondition>& tree)
{
    std::cout << "Testing " << __func__ << " ";
    try{
        for (Employee* employee : employees)
        {
            print2D(tree.getRoot());
            tree.deleteNode(employee);
            if(!inorderCheckBalance(tree.getRoot())){
                return false;
            }
        }
    }catch(const AVLTree<Employee*, IdCondition>::ElementNotInTree& e){return false;}
    if(tree.getRoot() != nullptr){
        return false;
    }
    return true;
}

bool testSingleNode(const vector<Employee*>& employees, AVLTree<Employee*, IdCondition>& tree)
{
    std::cout << "Testing " << __func__ << " ";
    Employee* employee = employees[0];
    tree.insertNode(employee);
    if(tree.getRoot()->getData() != employee){
        return false;
    }
    if(!inorderCheckBalance(tree.getRoot())){
        return false;
    }
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
        employees.push_back(employee);
    }
}

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
        employees.push_back(employee);
    }
}


int main(){
    IdCondition cond;
    AVLTree<Employee*, IdCondition> tree(cond);
    vector<Employee*> employees;
    fillVector1(employees);
    testFunction(testDeleteEmptyTree, employees, tree);
    testFunction(testSingleNode, employees, tree);
    // test fillVector1 tree
    testFunction(testInsertNode, employees, tree);
    testFunction(testFindElement, employees, tree);
    testFunction(testDeleteNode, employees, tree);
     
    // test fillVector2 tree
    employees.clear();
    fillVector2(employees);
    testFunction(testInsertNode, employees, tree);
    // print2D(tree.getRoot());
    testFunction(testFindElement, employees, tree);
    // print2D(tree.getRoot());
    testFunction(testDeleteNode, employees, tree);

    // test fillVector3 tree
    employees.clear();
    fillVector3(employees);
    testFunction(testInsertNode, employees, tree);
    testFunction(testFindElement, employees, tree);
    testFunction(testDeleteNode, employees, tree);
    
    return 0;
}