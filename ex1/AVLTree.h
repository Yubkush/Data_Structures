#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include <string>
#include <exception>
#include <math.h>
#include <functional>
#include "Conditions.h"
#include "Employee.h"
using std::string;
using std::exception;

template <class T, class Cond>
class AVLTree
{
    public:

        class Node
        {
            public:
                T data;
                Node* left;
                Node* right;
                int height;
                Node(const T& data): data(data), left(nullptr), right(nullptr), height(0){}
                ~Node() = default;

                Node* getLeft(){
                    return left;
                }
                Node* getRight(){
                    return right;
                }
                T& getData()
                {
                    return data;
                }
        };
    
    private:
        void destroyRecursive(Node* node)
        {
            if(node != nullptr){
                destroyRecursive(node->left);
                destroyRecursive(node->right);
                delete node;
            }
        }

        int getHeight(const Node* node)
        {
            if(node == nullptr)
                return -1;
            return node->height;
        }

        int getBalanceFactor(const Node* node)
        {
            if(node == nullptr){
                return 0;
            }
            return getHeight(node->left) - getHeight(node->right);
        }
        
        void fixHeight(Node* root)
        {
            if(root != nullptr){
                int height_of_node = 0;

                if(root->left != nullptr){
                    height_of_node = root->left->height + 1;
                }

                if(root->right != nullptr){
                    height_of_node = (height_of_node > root->right->height +1) ?
                                    height_of_node : root->right->height +1;
                }
                root->height = height_of_node;
            }
        }

        //right rotation
        Node* LLR(Node* root)
        {
            Node* left_of_root = root->left;
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
            return left_of_root;
        }
        //left rotation
        Node* RRR(Node* root)
        {
            Node* right_of_root = root->right;
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
            return right_of_root;
        }

        Node* rebalance(Node* node)
        {
            if(getBalanceFactor(node) >= 2){
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

        Node* insertNodeHelper(const T& value, Node* start)
        {
            if(start == nullptr){
                start = new Node(value);
            }
            else if(condition(value, start->data)){
                start->left = insertNodeHelper(value, start->left);
                start = rebalance(start);
            }
            else if(condition(start->data, value)){
                start->right = insertNodeHelper(value, start->right);
                start = rebalance(start);
            }
            start->height = ((getHeight((start->left)) > getHeight(start->right)) ? 
                            getHeight((start->left)) : getHeight(start->right)) + 1;
            return start;
        }

        //O(log n)
        Node* deleteNodeHelper(const T& data ,Node* to_delete)
        {
            Node* temp;
            //element not found
            if(to_delete == nullptr){
                return nullptr;
            }

            // Searching for the element
            else if(condition(data, to_delete->data)){
                to_delete->left = deleteNodeHelper(data, to_delete->left);
            }
            else if(condition(to_delete->data, data)){
                to_delete->right = deleteNodeHelper(data, to_delete->right);
            }

            //Element is in to_delete
            //has two childs
            else if(to_delete->left != nullptr && to_delete->right != nullptr){
                temp = findMinNode(to_delete->right);
                to_delete->data = temp->data;
                to_delete->right = deleteNodeHelper(to_delete->data, to_delete->right);
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
            to_delete->height = ((getHeight((to_delete->left)) > getHeight(to_delete->right)) ? 
                            getHeight((to_delete->left)) : getHeight(to_delete->right)) + 1;
            to_delete = rebalance(to_delete);
            return to_delete;
        }

        void treeToSortedArray(Node* root ,T arr[], int index = 0)
        {
            if(root != nullptr){
                treeToSortedArray(root->left, arr, index);
                arr[index] = root->data;
                index++;
                treeToSortedArray(root->right, arr, index);
            }
        }

        void mergeArrays(T merged[], T arr1[], T arr2[], int len1, int len2)
        {
            int i = 0, j = 0, p = 0;
            while(i<len1 && j<len2){
                if(condition(arr1[i], arr2[j])){
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

        Node* sortedArrayToAVLTree(T merged, int start, int end)
        {
            if(start > end){
                return nullptr;
            }
            
            int mid = (start+end)/2;
            Node* root = new Node(merged[mid]);
            root->left = sortedArrayToAVLTree(merged, start, mid - 1);
            root->right = sortedArrayToAVLTree(merged, mid + 1, end);

            return root;
        }

        int countElements(Node* root)
        {
            if(root == nullptr)
                return 0;
            return 1 + countElements(root->left) + countElements(root->right);
        }

    public:
        Node* root;
        Cond condition;
        class ElementNotInTree: exception{};
        class ElementAlreadyInTree: exception{};
        class MaxElementInTree: exception{};
        AVLTree(const Cond& condition): root(nullptr), condition(condition)
        {
            
        }

        virtual ~AVLTree()
        {
            destroyRecursive(root);
        }

        Node* getRoot()
        {
            return this->root;
        }

        //O(log(n))
        Node* findElement(const T& data, Node* start)
        {
            if(start == nullptr){
                throw ElementNotInTree();
            }
            else if(!condition(start->data, data) && !condition(data, start->data)){
                return start;
            }
            else if(condition(data, start->data)){
                return findElement(data, start->left);
            }
            else{
                return findElement(data, start->right);
            }
        }

        //O(log(n))
        void insertNode(const T& value)
        {
            try{
                this->findElement(value, this->root);
                throw ElementAlreadyInTree();
            }
            catch(const ElementNotInTree& e){}
            this->root = insertNodeHelper(value, this->root);
        }

        //O(1)
        bool isEmpty() const
        {
            return root == nullptr;
        }

        void deleteNode(const T& data)
        {
            try{
                this->findElement(data, this->root);
            }
            catch(const ElementNotInTree& e){
                throw ElementNotInTree();
            }
            this->root = deleteNodeHelper(data, this->root);
        }

        //O(log n)
        Node* findMinNode(Node* node)
        {
            Node* current = node;
            while (current->left != nullptr)
            {
                current = current->left;
            }
            return current;
        }

        //O(log n)
        Node* findMaxNode(Node* node)
        {
            Node* current = node;
            while (current->right != nullptr)
            {
                current = current->right;
            }
            return current;
        }

        //O(h+m) where m is number of elements in range and h is the height of the tree
        template <class EX>
        int elementsInRange(Node* root, const T& low, const T& high, EX extra_condition)
        {
            if(root == nullptr){
                return 0;
            }
            //root is in range of data
            if(!condition(root->data, low) && !condition(high, root->data)){
                if(extra_condition(root->data)){
                    return 1 + elementsInRange(root->left, low, high, extra_condition) 
                        + elementsInRange(root->right, low, high, extra_condition);
                }
                else{
                    return elementsInRange(root->left, low, high, extra_condition) + 
                        elementsInRange(root->right, low, high, extra_condition);
                }   
            }
            //out of range
            else if(condition(root->data, low)){
                return elementsInRange(root->right, low, high, extra_condition);
            }

            else{
                return elementsInRange(root->left, low, high, extra_condition);
            }
        }
        
        // O(m+n) where m is number of elements in this and n in number of elements in tree
        void absorbTree(AVLTree tree)
        {
            int len1 = countElements(this->root);
            int len2 = countElements(tree.getRoot());
            T *arr1 = new T[len1];
            T *arr2 = new T[len2];
            T *merged = new T[len1 + len2];
            treeToSortedArray(this->root, arr1);
            treeToSortedArray(this->root, arr2);
            mergeArrays(merged, arr1, arr2, len1, len2);
            Node* temp = this->root;
            this->root = sortedArrayToAVLTree(merged, 0, len1 + len2 - 1);
            //destroy arrays and old tree
            destroyRecursive(temp);
            delete [] arr1;
            delete [] arr2;
            delete [] merged;
        }

        void destroyRecursiveData(Node* node)
        {
            if(node != nullptr){
                destroyRecursive(node->left);
                destroyRecursive(node->right);
                delete node->data;
            }
        }

        template <class Action>
        void inorder(Node* root, const Action& action) {
            if (root == NULL) {return;}
            inorder(root->left);
            action(root->data);
            inorder(root->right);
        }

        template <class K>
        void inorder(Node* root, std::function<void(T,K)> visit) const
        {
            if (root == nullptr) {return;}
            inorder(root->left, visit);
            visit(root->data);
            inorder(root->right, visit);
        }
};

#endif /* AVL_TREE_H_ */