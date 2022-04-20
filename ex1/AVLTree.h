#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include <string>
#include <exception>
#include <math.h>
#include "Conditions.h"
#include "Employee.h"
using std::string;
using std::exception;

// class Condition
// {
//     public:
//         virtual bool operator()(const Employee* e1, const Employee* e2) = 0;
// };

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

        Node* root;
        Cond condition;
        class ElementNotInTree: exception{};
        class ElementAlreadyInTree: exception{};
        class MaxElementInTree: exception{};
        AVLTree(const Cond& condition): root(nullptr), condition(condition)
        {
            
        }

        void destroyRecursive(Node* node)
        {
            if(node != nullptr){
                destroyRecursive(node->left);
                destroyRecursive(node->right);
                delete node;
            }
        }

        virtual ~AVLTree()
        {
            destroyRecursive(root);
        }

        Node* getRoot()
        {
            return this->root;
        }

        static int getHeight(const Node* node)
        {
            if(node == nullptr)
                return -1;
            return node->height;
        }

        static int getBalanceFactor(const Node* node)
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
        void LLR(Node* root)
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
        }
        //left rotation
        void RRR(Node* root)
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
        }

        void rebalance(Node* node)
        {
            if(getBalanceFactor(node) >= 2){
                //LR_rotation
                if(getBalanceFactor(node->left) < 0){
                    RRR(node->left);
                    LLR(node);
                }
                //LL rotation
                else{
                    LLR(node);
                }
            }
            else if(getBalanceFactor(node) <= -2){
                //RL rotation
                if(getBalanceFactor(node->right) > 0){
                    LLR(node->right);
                    RRR(node);
                }
                //RR rotation
                else{
                    RRR(node);
                }
            }
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

        Node* insertNodeHelper(const T& value, Node* start)
        {
            if(start == nullptr){
                start = new Node(value);
            }
            else if(condition(value, start->data)){
                start->left = insertNodeHelper(value, start->left);
                rebalance(start);
            }
            else if(condition(start->data, value)){
                start->right = insertNodeHelper(value, start->right);
                rebalance(start);
            }
            start->height = ((getHeight((start->left)) > getHeight(start->right)) ? 
                            getHeight((start->left)) : getHeight(start->right)) + 1;
            return start;
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
            rebalance(to_delete);
            return to_delete;
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
        template <class Action>
        void inorder(Node* root, const Action& action) {
            if (root == NULL) {return;}
            inorder(root->left);
            action(root->data);
            inorder(root->right);
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

        //O(log n)
        Node* findNextInorder(Node* start)
        {
            if(start->right != nullptr){
                return findMinNode(start->right);
            }
            if(start == findMaxNode(root)){
                throw MaxElementInTree();
            }
            Node* temp = start;
            Node* next = start->parent;
            while (next != nullptr && temp == next->right)
            {
                temp = next;
                next = next->parent;
            }
            return next;
        }
};

#endif /* AVL_TREE_H_ */