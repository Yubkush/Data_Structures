#ifndef BIN_TREE_H_
#define BIN_TREE_H_

#include <string>
#include <exception>
using std::string;
using std::exception;

template <class T, class K>
class BinSearchTree
{
    protected:
        class Node
        {
            K key;
            T data;
            Node* left;
            Node* right;
            Node* parent;
            Node(const K& key, const T& data, const Node* parent = nullptr):key(key), data(data), left(nullptr), right(nullptr){
                this->parent = parent;
            }
            ~Node() = default;
        };
        Node* root;

    public:
        class ElementNotInTree: exception{};
        class ElementAlreadyInTree: exception{};
        class MaxElementInTree: exception{};
        BinSearchTree(): root(nullptr)
        {
            
        }

        ~BinSearchTree() = default;

        //O(log(n))
        void insertNode(const K& key, const T& value)
        {
            try{
                this->findElement(key);
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
            else if(key < parent.key){
                parent->left = insert;
            }
            else{
                parent->right = insert;
            }
        }

        //O(log(n))
        const Node* findElement(const K& key, const Node* start)
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

        //O(1)
        bool isEmpty() const
        {
            return root == nullptr;
        }

        //O(1)
        bool isLeaf(const Node* node) const
        {
            return (node->left == nullptr) && (node->right == nullptr);
        }

        //O(1)
        bool isLeftChild(const Node* node) const
        {
            if(node->parent->left == node){
                return true;
            }
            return false;
        }
        
        //O(1)
        void removeLeaf(Node* leaf)
        {
            if(isLeftChild(leaf)){
                leaf->parent->left == nullptr;
            }
            else {
                leaf->parent->right == nullptr;
            }
            delete leaf;
        }

        //O(1)
        void removeNodeWithOneChild(Node* to_delete)
        {
            Node* son = to_delete->left;
            if(to_delete->left == nullptr){
                son = to_delete->right;
            }
            if(isLeftChild(to_delete)){
                to_delete->parent->left = son;
            }
            else {
                to_delete->parent->right = son;
            }
            delete to_delete;
        }

        //O(1)
        void swapNodes(Node* node1, Node* node2)
        {
            Node* temp = new Node(node1);
            node1->right = node2->right;
            node1->left = node2->left;
            node1->parent = node2->parent;
            if(isLeftChild(node2)){
                node2->parent->left = node1;
            }
            else {
                node2->parent->right = node1;
            }
            node2->right = temp->right;
            node2->left = temp->left;
            node2->parent = temp->parent;
            if(isLeftChild(temp)){
                temp->parent->left = node1;
            }
            else {
                temp->parent->right = node1;
            }
            delete temp;
        }
        
        //O(log n)
        void deleteNode(Node* to_delete, const K& key)
        {
            try{
                Node* to_delete = findElement(key, root);
            }
            catch(const ElementNotInTree& e){
                throw ElementNotInTree();
            }
            //is leaf
            if(isLeaf(to_delete)){
                removeLeaf(to_delete);
            }
            //has one child
            else if(to_delete->left == nullptr || to_delete->right == nullptr){
                removeNodeWithOneChild(to_delete);
            }
            //has two childs
            else{
                Node* next = findMinNode(to_delete->right);
                swapNodes(to_delete, next);
                if(isLeaf(to_delete)){
                    removeLeaf(to_delete);
                }
                //has one child
                else{
                    removeNodeWithOneChild(to_delete);
                }
            }
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

#endif /* BIN_TREE_H_ */