#include "RankTree.h"

RankTree::RankTree() : root(nullptr)
{
    
}

static void destroyRecursive(RankNode* node)
{
    if(node != nullptr){
        destroyRecursive(node->left);
        destroyRecursive(node->right);
        delete node;
    }
}

RankTree::~RankTree()
{
    destroyRecursive(root);
}

RankNode* RankTree::getRoot()
{
    return this->root;
}

RankNode* RankTree::findElement(Employee* data, RankNode* start)
{
    if(start == nullptr){
        throw ElementNotInTree();
    }
    else if(!SalaryCondition(start->data, data) && !SalaryCondition(data, start->data)){
        return start;
    }
    else if(SalaryCondition(data, start->data)){
        return findElement(data, start->left);
    }
    else{
        return findElement(data, start->right);
    }
}

void RankTree::insert(Employee* value)
{
    try{
        this->findElement(value, this->root);
        throw ElementAlreadyInTree();
    }
    catch(const ElementNotInTree& e){}
    this->root = insertHelper(value, this->root);
}

bool RankTree::isEmpty() const
{
    return root == nullptr;
}

void RankTree::remove(Employee* data)
{
    try{
        this->findElement(data, this->root);
    }
    catch(const ElementNotInTree& e){
        throw ElementNotInTree();
    }
    this->root = removeHelper(data, this->root);
}

RankNode* RankTree::findMinNode(RankNode* start)
{
    RankNode* current = start;
    while (current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}

RankNode* RankTree::findMaxNode(RankNode* start)
{
    RankNode* current = start;
    while (current->right != nullptr)
    {
        current = current->right;
    }
    return current;
}

double RankTree::averageGradesInSalaryRange(RankNode* root, int lower, int higher)
{
    int num_employees_in_range = root->getNumEmployees();
    int sum_grades_in_range = root->getSumGrades();
    RankNode* temp = root;
    //run to lower bound
    while(temp != nullptr){
        if(lower <= temp->getData()->GetSalary()){
            temp = temp->getLeft();
        }
        else{
            num_employees_in_range -= 1;
            sum_grades_in_range -= temp->data->GetGrade();
            if(temp->left != nullptr){
                num_employees_in_range -= temp->left->getNumEmployees();
                sum_grades_in_range -= temp->left->getSumGrades();
            }
            temp = temp->getRight();
        }
    }
    temp = root;
    //run to higher bound
    while(temp != nullptr){
        if(temp->getData()->GetSalary() <= higher){
            temp = temp->getRight();
        }
        else{
            num_employees_in_range -= 1;
            sum_grades_in_range -= temp->data->GetGrade();
            if(temp->right != nullptr){
                num_employees_in_range -= temp->right->getNumEmployees();
                sum_grades_in_range -= temp->right->getSumGrades();
            }
            temp = temp->getLeft();
        }
    }
    return (double)sum_grades_in_range / (double)num_employees_in_range;
}

void RankTree::absorbTree(RankTree& tree)
{
    int len1 = countElements(this->root);
    int len2 = countElements(tree.getRoot());
    Employee** arr1 = new Employee*[len1];
    Employee** arr2 = new Employee*[len2];
    Employee** merged = new Employee*[len1 + len2];
    treeToSortedArray(this->root, arr1);
    treeToSortedArray(tree.root, arr2);
    mergeArrays(merged, arr1, arr2, len1, len2);
    RankNode* temp = this->root;
    this->root = sortedArrayToRankTree(merged, 0, len1 + len2 - 1);
    RankTreeFixHeightAndRank(this->root);
    //destroy arrays and old tree
    destroyRecursive(temp);
    delete [] arr1;
    delete [] arr2;
    delete [] merged;
}

void RankTree::destroyRecursiveData(RankNode* node)
{
    if(node != nullptr){
        destroyRecursiveData(node->left);
        destroyRecursiveData(node->right);
        delete node->data;
    }
}