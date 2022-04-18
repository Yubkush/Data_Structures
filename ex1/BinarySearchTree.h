#ifndef BIN_TREE_H_
#define BIN_TREE_H_

#include <exception>
#include <iostream>
#include <memory>

using std::exception;
using std::shared_ptr;

template <class T, class K>
class BinSearchTree
{
    protected:
        class Node
        {
            public:
                K key;
                T data;
                Node* left;
                Node* right;
                Node* parent;
                int height;
                Node(const K& key, const T& data, Node* parent = nullptr):key(key), data(data), 
                    left(nullptr), right(nullptr), parent(parent), height(0){
                    
                }
                Node(const Node&) = default;
                Node& operator=(const Node&) = default;
                ~Node() = default;
                const T& getData() const{
                    return data;
                }
                Node* getLeft() const{
                    return left;
                }
                Node* getRight() const{
                    return right;
                }
                int getHeight() const{
                    if(this == nullptr)
                        return -1;
                    return this->height;
                }
        };
    public:
        Node* root;

        class ElementNotInTree: exception{};
        class ElementAlreadyInTree: exception{};

        BinSearchTree(): root(nullptr)
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

        virtual ~BinSearchTree()
        {
            destroyRecursive(root);
        }

        virtual Node* getRoot() const
        {
            return root;
        }

        //O(log(n))
        virtual Node* findElement(const K& key, Node* start) const
        {
            if(start == nullptr){
                throw ElementNotInTree();
            }
            else if(start->key == key){
                return start;
            }
            else if(key < start->key){
                return findElement(key, start->left);
            }
            else{
                return findElement(key, start->right);
            }
        }

        //O(log(n))
        virtual void insertNode(const K& key, const T& value)
        {
            try{
                this->findElement(key, root);
                throw ElementAlreadyInTree();
            }
            catch(const ElementNotInTree& e){}
            Node* parent = nullptr;
            Node* temp = root;
            while(temp != nullptr){
                parent = temp;
                if(key < temp->key){
                    temp = temp->left;
                }
                else{
                    temp = temp->right;
                }
            }
            Node* insert = new Node(key, value, parent);
            if(parent == nullptr){
                root = insert;
            }
            else if(key < parent->key){
                parent->left = insert;
            }
            else{
                parent->right = insert;
            }
        }

        //O(1)
        bool isEmpty() const
        {
            return root == nullptr;
        }
        
        virtual Node* deleteNode(Node* root, const K& key)
        {
            if(root == nullptr){
                return root;
            }
            if(this->root == root && root->left == nullptr && root->right == nullptr){
                Node* temp = this->root;
                this->root = nullptr;
                delete temp;
                return this->root;
            }

            // If the key to be deleted is in the left subtree
            if(key < root->key){
                root->left = deleteNode(root->left, key);
                if(root->left != nullptr){
                    root->left->parent = root;
                }
            }

            // If the key to be deleted is in the right subtree
            else if(root->key < key){
                root->right = deleteNode(root->right, key);
                if(root->right != nullptr){
                    root->right->parent = root;
                }
            }
            
            //The root's key is equal to the key we want to delete
            else{

                Node* temp;
                // Two children
                if(root->left != nullptr && root->right != nullptr){
                   temp = findMinNode(root->right);
                   root->key = temp->key;
                   root->data = temp->data;
                   root->right = deleteNode(root->right, temp->key);
                }
                else{
                    temp = root;
                    // Only left child
                    if(root->left != nullptr){
                        root = root->left;
                    }
                    // Only right child
                    else if(root->right != nullptr){
                        root = root->right;
                    }
                    // Leaf
                    else{
                        root = nullptr;
                    }
                    delete(temp);
                }
            }
            return root;
        }

        //O(n)
        virtual void inorder(Node* root) const
        {
            if (root == nullptr) {return;}
            inorder(root->left);
            std::cout << root->key << " ";
            inorder(root->right);
        }

        //O(log n)
        Node* findMinNode(Node* node) const
        {
            Node* current = node;
            while (current->left != nullptr)
            {
                current = current->left;
            }
            return current;
        }

        //O(log n)
        Node* findMaxNode(Node* node) const
        {
            Node* current = node;
            while (current->right != nullptr)
            {
                current = current->right;
            }
            return current;
        }

        //O(log n)
        virtual Node* findNextInorder(Node* start) const
        {
            if(start->right != nullptr){
                return findMinNode(start->right);
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

#endif /* BIN_TREE_H_ */