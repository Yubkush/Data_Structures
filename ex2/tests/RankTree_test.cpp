#include "../RankTree.h"
#include "gtest/gtest.h"

#include <vector>
#include <math.h>

using std::vector;

RankTree createFullTree()
{
    vector<Employee*> employee_vector;
    Employee* temp = new Employee(4,nullptr, 50,10);
    employee_vector.push_back(temp);
    temp = new Employee(2,nullptr, 20,16);
    employee_vector.push_back(temp);
    temp = new Employee(45,nullptr, 56,16);
    employee_vector.push_back(temp);
    temp = new Employee(1,nullptr, 10,5);
    employee_vector.push_back(temp);
    temp = new Employee(68,nullptr, 33,6);
    employee_vector.push_back(temp);
    temp = new Employee(44,nullptr, 51,2);
    employee_vector.push_back(temp);
    temp = new Employee(10,nullptr, 100,460);
    employee_vector.push_back(temp);
    RankTree tree;
    for (int i = 0; i < employee_vector.size(); i++)
    {
        tree.insert(employee_vector[i]);
    }
    return tree;
}

RankTree createSmallTree()
{
    vector<Employee*> employee_vector;
    Employee* temp = new Employee(50,nullptr, 50,50);
    employee_vector.push_back(temp);
    temp = new Employee(51,nullptr, 44,2);
    employee_vector.push_back(temp);
    temp = new Employee(54,nullptr, 50,22);
    employee_vector.push_back(temp);
    temp = new Employee(52,nullptr, 44,5);
    employee_vector.push_back(temp);
    RankTree tree;
    for (int i = 0; i < employee_vector.size(); i++)
    {
        tree.insert(employee_vector[i]);
    }
    return tree;
}

bool postorderCheckHeight(RankNode* root)
{
    bool flag = true;
    if(root!=nullptr){
        flag = flag && postorderCheckHeight(root->left);
        flag = flag && postorderCheckHeight(root->right);
        if(root->left == nullptr){
            if(root->right == nullptr){
                flag = flag && root->height == 0;
            }
            else{
                flag = flag && (root->height == root->right->height + 1);
            }
        }
        else{
            if(root->right == nullptr){
                flag = flag && (root->height == root->left->height + 1);
            }
            else{
                flag = flag && (root->height == root->left->height + 1);
            }
        }
    }
    return flag;
}

TEST(FullTree, CheckInsert)
{
    RankTree tree = createFullTree();
    RankNode* root = tree.getRoot();
    EXPECT_TRUE(postorderCheckHeight(root));
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_EQ(root->getNumEmployees(), 7);
    EXPECT_EQ(root->getSumGrades(), 515);
    EXPECT_EQ(root->getData()->GetSalary(), 50);
    EXPECT_EQ(root->getLeft()->getNumEmployees(), 3);
    EXPECT_EQ(root->getLeft()->getSumGrades(), 27);
    EXPECT_EQ(root->getRight()->getNumEmployees(), 3);
    EXPECT_EQ(root->getRight()->getSumGrades(), 478);
    RankNode* min = tree.findMinNode(root);
    EXPECT_EQ(min->getData()->GetSalary(), 10);
    EXPECT_EQ(min->getNumEmployees(), 1);
    EXPECT_EQ(min->getSumGrades(), 5);
    RankNode* max = tree.findMaxNode(root);
    EXPECT_EQ(max->getData()->GetSalary(), 100);
    EXPECT_EQ(max->getNumEmployees(), 1);
    EXPECT_EQ(max->getSumGrades(), 460);
    tree.destroyRecursiveData(root);
}

TEST(FullTree, CheckHeightValidity)
{
    RankTree tree = createFullTree();
    EXPECT_EQ(postorderCheckHeight(tree.getRoot()), true);
    tree.destroyRecursiveData(tree.getRoot());
}

TEST(FullTree, CheckRemoveLLR)
{
    RankTree tree = createFullTree();
    Employee to_remove(44,nullptr, 51,2);
    tree.remove(&to_remove);
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getNumEmployees(), 6);
    EXPECT_EQ(tree.getRoot()->getSumGrades(), 513);
    EXPECT_EQ(tree.getRoot()->getData()->GetSalary(), 50);
    EXPECT_EQ(tree.getRoot()->getRight()->getNumEmployees(), 2);
    EXPECT_EQ(tree.getRoot()->getRight()->getSumGrades(), 476);
    to_remove = Employee(45,nullptr, 56,16);
    tree.remove(&to_remove);
    EXPECT_EQ(tree.getRoot()->getNumEmployees(), 5);
    EXPECT_EQ(tree.getRoot()->getSumGrades(), 497);
    EXPECT_EQ(tree.getRoot()->getData()->GetSalary(), 50);
    EXPECT_EQ(tree.getRoot()->getRight()->getNumEmployees(), 1);
    EXPECT_EQ(tree.getRoot()->getRight()->getSumGrades(), 460);
    to_remove = Employee(10,nullptr, 100,460);
    tree.remove(&to_remove);
    EXPECT_EQ(tree.getRoot()->getNumEmployees(), 4);
    EXPECT_EQ(tree.getRoot()->getSumGrades(), 37);
    EXPECT_EQ(tree.getRoot()->getData()->GetSalary(), 20);
    EXPECT_EQ(tree.getRoot()->getRight()->getNumEmployees(), 2);
    EXPECT_EQ(tree.getRoot()->getRight()->getData()->GetSalary(), 50);
    EXPECT_EQ(tree.getRoot()->getRight()->getSumGrades(), 16);
    tree.destroyRecursiveData(tree.getRoot());
}

TEST(FullTree, CheckRemoveRRR)
{
    RankTree tree = createFullTree();
    Employee to_remove(68,nullptr, 33,6);
    tree.remove(&to_remove);
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->getNumEmployees(), 6);
    EXPECT_EQ(tree.getRoot()->getSumGrades(), 509);
    EXPECT_EQ(tree.getRoot()->getData()->GetSalary(), 50);
    EXPECT_EQ(tree.getRoot()->getLeft()->getNumEmployees(), 2);
    EXPECT_EQ(tree.getRoot()->getLeft()->getSumGrades(), 21);
    to_remove = Employee(2,nullptr, 20,16);
    tree.remove(&to_remove);
    EXPECT_EQ(tree.getRoot()->getNumEmployees(), 5);
    EXPECT_EQ(tree.getRoot()->getSumGrades(), 493);
    EXPECT_EQ(tree.getRoot()->getData()->GetSalary(), 50);
    EXPECT_EQ(tree.getRoot()->getLeft()->getNumEmployees(), 1);
    EXPECT_EQ(tree.getRoot()->getLeft()->getSumGrades(), 5);
    to_remove = Employee(1,nullptr, 10,5);
    tree.remove(&to_remove);
    EXPECT_EQ(tree.getRoot()->getNumEmployees(), 4);
    EXPECT_EQ(tree.getRoot()->getSumGrades(), 488);
    EXPECT_EQ(tree.getRoot()->getData()->GetSalary(), 56);
    EXPECT_EQ(tree.getRoot()->getLeft()->getNumEmployees(), 2);
    EXPECT_EQ(tree.getRoot()->getLeft()->getData()->GetSalary(), 50);
    EXPECT_EQ(tree.getRoot()->getLeft()->getSumGrades(), 12);
    tree.destroyRecursiveData(tree.getRoot());
}

TEST(FullTree, CheckAverageGradesInSalaryRange)
{
    RankTree tree = createFullTree();
    RankNode* root = tree.getRoot();
    int num_employees_in_range, sum_grades_in_range;
    tree.averageGradesInSalaryRange(root,0,101, &num_employees_in_range, &sum_grades_in_range);
    EXPECT_EQ(((double)sum_grades_in_range)/(num_employees_in_range), 515.0/7);
    tree.averageGradesInSalaryRange(root,0,50, &num_employees_in_range, &sum_grades_in_range);
    EXPECT_EQ(((double)sum_grades_in_range)/(num_employees_in_range), ((double)37)/4);
    tree.averageGradesInSalaryRange(root,0,51, &num_employees_in_range, &sum_grades_in_range);
    EXPECT_EQ(((double)sum_grades_in_range)/(num_employees_in_range), ((double)39)/5);
    tree.averageGradesInSalaryRange(root,0,55, &num_employees_in_range, &sum_grades_in_range);
    EXPECT_EQ(((double)sum_grades_in_range)/(num_employees_in_range), ((double)39)/5);
    tree.averageGradesInSalaryRange(root,0,21, &num_employees_in_range, &sum_grades_in_range);
    EXPECT_EQ(((double)sum_grades_in_range)/(num_employees_in_range), ((double)21)/2);
    tree.averageGradesInSalaryRange(root,11,22, &num_employees_in_range, &sum_grades_in_range);
    EXPECT_EQ(((double)sum_grades_in_range)/(num_employees_in_range), 16);
    tree.averageGradesInSalaryRange(root,33,33, &num_employees_in_range, &sum_grades_in_range);
    EXPECT_EQ(((double)sum_grades_in_range)/(num_employees_in_range), 6);
    tree.averageGradesInSalaryRange(root,111,122, &num_employees_in_range, &sum_grades_in_range);
    EXPECT_EQ((num_employees_in_range), 0);
    tree.averageGradesInSalaryRange(root,49,50, &num_employees_in_range, &sum_grades_in_range);
    EXPECT_EQ(((double)sum_grades_in_range)/(num_employees_in_range), 10);
    tree.averageGradesInSalaryRange(root,32,52, &num_employees_in_range, &sum_grades_in_range);
    EXPECT_EQ(((double)sum_grades_in_range)/(num_employees_in_range), ((double)18)/3);
    tree.averageGradesInSalaryRange(root,32,99, &num_employees_in_range, &sum_grades_in_range);
    EXPECT_EQ(((double)sum_grades_in_range)/(num_employees_in_range), ((double)34)/4);
    tree.averageGradesInSalaryRange(root,0,0, &num_employees_in_range, &sum_grades_in_range);
    EXPECT_EQ((num_employees_in_range), 0);
    tree.destroyRecursiveData(tree.getRoot());
}

TEST(FullTree, CheckGetElementByReverseRank)
{
    RankTree tree = createFullTree();
    RankNode* root = tree.getRoot();
    Employee* e = tree.getElementByReverseRank(3);
    EXPECT_EQ(e->GetEmployeeId(), 44);
    e = tree.getElementByReverseRank(4);
    EXPECT_EQ(e->GetEmployeeId(), 4);
    e = tree.getElementByReverseRank(1);
    EXPECT_EQ(e->GetEmployeeId(), 10);
    e = tree.getElementByReverseRank(2);
    EXPECT_EQ(e->GetEmployeeId(), 45);
    e = tree.getElementByReverseRank(5);
    EXPECT_EQ(e->GetEmployeeId(), 68);
    e = tree.getElementByReverseRank(6);
    EXPECT_EQ(e->GetEmployeeId(), 2);
    e = tree.getElementByReverseRank(7);
    EXPECT_EQ(e->GetEmployeeId(), 1);
    EXPECT_THROW(tree.getElementByReverseRank(8), RankTree::RankNotFound);
    tree.destroyRecursiveData(root);
}

TEST(FullTree, CheckSumOfGradeTopWorkers)
{
    RankTree tree = createFullTree();
    RankNode* root = tree.getRoot();
    EXPECT_EQ(tree.sumOfGradeTopWorkers(1), 460);
    EXPECT_EQ(tree.sumOfGradeTopWorkers(2), 476);
    EXPECT_EQ(tree.sumOfGradeTopWorkers(3), 478);
    EXPECT_EQ(tree.sumOfGradeTopWorkers(4), 488);
    EXPECT_EQ(tree.sumOfGradeTopWorkers(5), 494);
    EXPECT_EQ(tree.sumOfGradeTopWorkers(6), 510);
    EXPECT_EQ(tree.sumOfGradeTopWorkers(7), 515);
    EXPECT_THROW(tree.sumOfGradeTopWorkers(8), RankTree::NotEnoughEmployees);
    tree.destroyRecursiveData(root);
}

TEST(FullTree, CheckAbsorbTree)
{
    RankTree tree = createFullTree();
    RankTree small_tree = createSmallTree();
    tree.absorbTree(small_tree);
    RankNode* root = tree.getRoot();
    EXPECT_TRUE(postorderCheckHeight(root));
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_EQ(root->getNumEmployees(), 11);
    EXPECT_EQ(root->getSumGrades(), 594);
    EXPECT_EQ(root->getData()->GetSalary(), 50);
    EXPECT_EQ(root->getLeft()->getNumEmployees(), 5);
    EXPECT_EQ(root->getLeft()->getSumGrades(), 34);
    EXPECT_EQ(root->getRight()->getNumEmployees(), 5);
    EXPECT_EQ(root->getRight()->getSumGrades(), 550);
    RankNode* min = tree.findMinNode(root);
    EXPECT_EQ(min->getData()->GetSalary(), 10);
    EXPECT_EQ(min->getNumEmployees(), 2);
    EXPECT_EQ(min->getSumGrades(), 21);
    RankNode* max = tree.findMaxNode(root);
    EXPECT_EQ(max->getData()->GetSalary(), 100);
    EXPECT_EQ(max->getNumEmployees(), 1);
    EXPECT_EQ(max->getSumGrades(), 460);
    tree.destroyRecursiveData(root);
}

TEST(SmallTree, CheckInsert)
{
    RankTree tree = createSmallTree();
    RankNode* root = tree.getRoot();
    EXPECT_TRUE(postorderCheckHeight(root));
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_EQ(root->getNumEmployees(), 4);
    EXPECT_EQ(root->getSumGrades(), 79);
    EXPECT_EQ(root->getData()->GetSalary(), 50);
    EXPECT_EQ(root->getLeft()->getNumEmployees(), 2);
    EXPECT_EQ(root->getLeft()->getSumGrades(), 7);
    EXPECT_EQ(root->getRight()->getNumEmployees(), 1);
    EXPECT_EQ(root->getRight()->getSumGrades(), 22);
    EXPECT_EQ(root->getLeft()->getRight()->getNumEmployees(), 1);
    EXPECT_EQ(root->getLeft()->getRight()->getSumGrades(), 5);
    EXPECT_EQ(root->getLeft()->getRight()->getData()->GetSalary(), 44);
    tree.destroyRecursiveData(root);
}

TEST(SmallTree, CheckInsertRLR)
{
    RankTree tree = createSmallTree();
    RankNode* root = tree.getRoot();
    EXPECT_TRUE(postorderCheckHeight(root));
    EXPECT_FALSE(tree.isEmpty());
    Employee* e = new Employee(55, nullptr, 52, 22);
    EXPECT_NO_THROW(tree.insert(e));
    e = new Employee(56, nullptr, 51, 22);
    EXPECT_NO_THROW(tree.insert(e));
    EXPECT_EQ(tree.getRoot()->getRight()->getNumEmployees(), 3);
    EXPECT_EQ(tree.getRoot()->getRight()->getSumGrades(), 66);
    EXPECT_EQ(tree.getRoot()->getRight()->getData()->GetEmployeeId(), 56);
    EXPECT_EQ(tree.getRoot()->getRight()->getData()->GetSalary(), 51);
    tree.destroyRecursiveData(root);
}

TEST(SmallTree, CheckRemoveLR)
{
    RankTree tree = createSmallTree();
    RankNode* root = tree.getRoot();
    Employee temp = Employee(50,nullptr, 50,50);
    EXPECT_NO_THROW(tree.remove(&temp));
    EXPECT_EQ(tree.getRoot()->getRight()->getNumEmployees(), 1);
    EXPECT_EQ(tree.getRoot()->getRight()->getSumGrades(), 22);
    EXPECT_EQ(tree.getRoot()->getRight()->getData()->GetEmployeeId(), 54);
    EXPECT_EQ(tree.getRoot()->getLeft()->getData()->GetSalary(), 44);
    EXPECT_EQ(tree.getRoot()->getLeft()->getData()->GetEmployeeId(), 51);
    EXPECT_EQ(tree.getRoot()->getNumEmployees(), 3);
    EXPECT_EQ(tree.getRoot()->getSumGrades(), 29);
    EXPECT_EQ(tree.getRoot()->getData()->GetEmployeeId(), 52);
    EXPECT_TRUE(postorderCheckHeight(root));
    tree.destroyRecursiveData(root);
}

TEST(SmallTree, CheckGetElementByReverseRank)
{
    RankTree tree = createSmallTree();
    RankNode* root = tree.getRoot();
    Employee* e = tree.getElementByReverseRank(3);
    EXPECT_EQ(e->GetEmployeeId(), 52);
    e = tree.getElementByReverseRank(4);
    EXPECT_EQ(e->GetEmployeeId(), 51);
    e = tree.getElementByReverseRank(1);
    EXPECT_EQ(e->GetEmployeeId(), 54);
    e = tree.getElementByReverseRank(2);
    EXPECT_EQ(e->GetEmployeeId(), 50);
    EXPECT_THROW(tree.getElementByReverseRank(8), RankTree::RankNotFound);
    tree.destroyRecursiveData(root);
}

TEST(SmallTree, CheckSumOfGradeTopWorkers)
{
    RankTree tree = createSmallTree();
    RankNode* root = tree.getRoot();
    EXPECT_EQ(tree.sumOfGradeTopWorkers(1), 22);
    EXPECT_EQ(tree.sumOfGradeTopWorkers(2), 72);
    EXPECT_EQ(tree.sumOfGradeTopWorkers(3), 77);
    EXPECT_EQ(tree.sumOfGradeTopWorkers(4), 79);
    EXPECT_THROW(tree.sumOfGradeTopWorkers(8), RankTree::NotEnoughEmployees);
    EXPECT_THROW(tree.sumOfGradeTopWorkers(0), RankTree::RankNotFound);
    EXPECT_THROW(tree.sumOfGradeTopWorkers(5), RankTree::NotEnoughEmployees);
    tree.destroyRecursiveData(root);
}

TEST(SmallTree, CheckAbsorbTree)
{
    RankTree tree = createFullTree();
    RankTree small_tree = createSmallTree();
    small_tree.absorbTree(tree);
    RankNode* root = small_tree.getRoot();
    EXPECT_TRUE(postorderCheckHeight(root));
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_EQ(root->getNumEmployees(), 11);
    EXPECT_EQ(root->getSumGrades(), 594);
    EXPECT_EQ(root->getData()->GetSalary(), 50);
    EXPECT_EQ(root->getLeft()->getNumEmployees(), 5);
    EXPECT_EQ(root->getLeft()->getSumGrades(), 34);
    EXPECT_EQ(root->getRight()->getNumEmployees(), 5);
    EXPECT_EQ(root->getRight()->getSumGrades(), 550);
    RankNode* min = tree.findMinNode(root);
    EXPECT_EQ(min->getData()->GetSalary(), 10);
    EXPECT_EQ(min->getNumEmployees(), 2);
    EXPECT_EQ(min->getSumGrades(), 21);
    RankNode* max = tree.findMaxNode(root);
    EXPECT_EQ(max->getData()->GetSalary(), 100);
    EXPECT_EQ(max->getNumEmployees(), 1);
    EXPECT_EQ(max->getSumGrades(), 460);
    small_tree.destroyRecursiveData(root);
}
