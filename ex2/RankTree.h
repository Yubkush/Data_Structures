#ifndef RANK_TREE_H_
#define RANK_TREE_H_

#include "Employee.h"
#include <exception>

using std::exception;

class RankNode
{
    public:
        Employee* data;
        RankNode* left;
        RankNode* right;
        int height;
        int num_employees_sub_tree;
        int sum_grades_sub_tree;
        RankNode(Employee* data): data(data), left(nullptr), right(nullptr), height(0),
                                num_employees_sub_tree(1), sum_grades_sub_tree(data->GetGrade()){};
        ~RankNode() = default;

        int getNumEmployees(){
            return num_employees_sub_tree;
        }
        int getSumGrades(){
            return sum_grades_sub_tree;
        }
        RankNode* getLeft(){
            return left;
        }
        RankNode* getRight(){
            return right;
        }
        Employee* getData()
        {
            return data;
        }
};

class RankTree
{
    private:
        RankNode* root;

        int getHeight(RankNode* node)
        {
            if(node == nullptr)
                return -1;
            return node->height;
        }

        int getBalanceFactor(const RankNode* node)
        {
            if(node == nullptr){
                return 0;
            }
            return getHeight(node->left) - getHeight(node->right);
        }

        void fixHeight(RankNode* root)
        {
            if(root != nullptr){
                int height_of_AVLNode = 0;

                if(root->left != nullptr){
                    height_of_AVLNode = root->left->height + 1;
                }

                if(root->right != nullptr){
                    height_of_AVLNode = (height_of_AVLNode > root->right->height +1) ?
                                    height_of_AVLNode : root->right->height +1;
                }
                root->height = height_of_AVLNode;
            }
        }

        void fixRank(RankNode* root)
        {
            if(root != nullptr){
                root->num_employees_sub_tree = 1;
                root->sum_grades_sub_tree = root->data->GetGrade();

                if(root->left != nullptr){
                    root->num_employees_sub_tree += root->left->num_employees_sub_tree;
                    root->sum_grades_sub_tree += root->left->sum_grades_sub_tree;
                }

                if(root->right != nullptr){
                    root->num_employees_sub_tree += root->right->num_employees_sub_tree;
                    root->sum_grades_sub_tree += root->right->sum_grades_sub_tree;
                }
            }
        }

        //right rotation
        RankNode* LLR(RankNode* root)
        {
            RankNode* left_of_root = root->left;
            //move left_of_root right subtree to be root's left subtree
            root->left = left_of_root->right;
            
            //move root under left_of_root
            left_of_root->right = root;
            if(left_of_root->right == this->root){
                this->root = left_of_root;
            }
            //update heights
            fixHeight(root);
            fixHeight(left_of_root);
            //update ranks
            fixRank(left_of_root->right);
            fixRank(left_of_root);
            return left_of_root;
        }

        //left rotation
        RankNode* RRR(RankNode* root)
        {
            RankNode* right_of_root = root->right;
            //move right_of_root left subtree to be root's right subtree
            root->right = right_of_root->left;
            
            //move root under right_of_root
            right_of_root->left = root;
            if(right_of_root->left == this->root){
                this->root = right_of_root;
            }
            //update heights
            fixHeight(root);
            fixHeight(right_of_root);
            //update ranks
            fixRank(right_of_root->left);
            fixRank(right_of_root);
            return right_of_root;
        }

        RankNode* rebalance(RankNode* node)
        {
            if (getBalanceFactor(node) >= 2)
            {
                //LR_rotation
                if(getBalanceFactor(node->left) < 0){
                    node->left = RRR(node->left);
                    return LLR(node);
                }
                //LL rotation
                else{
                    return LLR(node);
                }
            }
            else if(getBalanceFactor(node) <= -2){
                //RL rotation
                if(getBalanceFactor(node->right) > 0){
                    node->right = LLR(node->right);
                    return RRR(node);
                }
                //RR rotation
                else{
                    return RRR(node);
                }
            }
            return node;
        }

        bool SalaryCondition(const Employee* e1, const Employee* e2)
        {
            if(e1->GetSalary() < e2->GetSalary()){
                return true;
            }
            else if(e1->GetSalary() > e2->GetSalary()){
                return false;
            }
            else{
                return e1->GetEmployeeId() < e2->GetEmployeeId();
            }
        }

        RankNode* insertHelper(Employee* value, RankNode* start)
        {
            if(start == nullptr){
                start = new RankNode(value);
            }
            else if(SalaryCondition(value, start->data)){
                start->left = insertHelper(value, start->left);
                start = rebalance(start);
            }
            else if(SalaryCondition(start->data, value)){
                start->right = insertHelper(value, start->right);
                start = rebalance(start);
            }
            fixHeight(start);
            fixRank(start);
            return start;
        }

        RankNode* removeHelper(const Employee* data ,RankNode* to_delete)
        {
            RankNode* temp;
            //element not found
            if(to_delete == nullptr){
                return nullptr;
            }

            // Searching for the element
            else if(SalaryCondition(data, to_delete->data)){
                to_delete->left = removeHelper(data, to_delete->left);
            }
            else if(SalaryCondition(to_delete->data, data)){
                to_delete->right = removeHelper(data, to_delete->right);
            }

            //Element is in to_delete
            //has two childs
            else if(to_delete->left != nullptr && to_delete->right != nullptr){
                temp = findMinNode(to_delete->right);
                to_delete->data = temp->data;
                to_delete->right = removeHelper(to_delete->data, to_delete->right);
            }
            // One child or leaf
            else{
                temp = to_delete;
                if(to_delete->left == nullptr){
                    to_delete = to_delete->right;
                }
                else if(to_delete->right == nullptr){
                    to_delete = to_delete->left;
                }
                delete temp;
            }
            //we erased to_delete so we dont need to fix heights or balance
            if(to_delete == nullptr){
                return to_delete;
            }
            fixHeight(to_delete);
            fixRank(to_delete);
            to_delete = rebalance(to_delete);
            return to_delete;
        }

        int treeToSortedArray(RankNode* root ,Employee* arr[], int index = 0)
        {
            if(root != nullptr){
                index = treeToSortedArray(root->left, arr, index);
                arr[index] = root->data;
                index++;
                index = treeToSortedArray(root->right, arr, index);
            }
            return index;
        }

        void mergeArrays(Employee* merged[], Employee* arr1[], Employee* arr2[], int len1, int len2)
        {
            int i = 0, j = 0, p = 0;
            while(i<len1 && j<len2){
                if(SalaryCondition(arr1[i], arr2[j])){
                    merged[p] = arr1[i];
                    i++;
                }
                else{
                    merged[p] = arr2[j];
                    j++;
                }
                p++;
            }
            for(;i<len1;i++, p++){merged[p] = arr1[i];}
            for(;j<len2;j++, p++){merged[p] = arr2[j];}
        }

        RankNode* sortedArrayToRankTree(Employee* merged[], int start, int end)
        {
            if(start > end){
                return nullptr;
            }
            
            int mid = (start+end)/2;
            RankNode* root = new RankNode(merged[mid]);
            root->left = sortedArrayToRankTree(merged, start, mid - 1);
            root->right = sortedArrayToRankTree(merged, mid + 1, end);

            return root;
        }

        void RankTreeFixHeightAndRank(RankNode* root)
        {
            if(root!=nullptr){
                RankTreeFixHeightAndRank(root->left);
                RankTreeFixHeightAndRank(root->right);
                fixHeight(root);
                fixRank(root);
            }
        }

        int countElements(RankNode* root)
        {
            if(root == nullptr)
                return 0;
            return 1 + countElements(root->left) + countElements(root->right);
        }

    public:
        class ElementNotInTree: exception{};
        class ElementAlreadyInTree: exception{};
        class MaxElementInTree: exception{};

        RankTree();
        ~RankTree();

        RankNode* getRoot();
        RankNode* findElement(Employee* data, RankNode* start);
        void insert(Employee* value);
        bool isEmpty() const;
        void remove(Employee* data);
        RankNode* findMinNode(RankNode* start);
        RankNode* findMaxNode(RankNode* start);
        double averageGradesInSalaryRange(RankNode* root, int lower, int higher);
        void absorbTree(RankTree& tree);
        void destroyRecursiveData(RankNode* node);
};

#endif /* RANK_TREE_H_ */