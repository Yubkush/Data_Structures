#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include <string>
#include <exception>
#include <math.h>
#include <functional>
using std::string;
using std::exception;

template<class T>
class AVLNode
{
    public:
        T data;
        AVLNode* left;
        AVLNode* right;
        int height;
        AVLNode(const T& data): data(data), left(nullptr), right(nullptr), height(0){}
        virtual ~AVLNode() = default;

        AVLNode* getLeft(){
            return left;
        }
        AVLNode* getRight(){
            return right;
        }
        T& getData()
        {
            return data;
        }
};

template <class T, class Cond>
class AVLTree
{   
    private:
        void destroyRecursive(AVLNode<T>* AVLNode)
        {
            if(AVLNode != nullptr){
                destroyRecursive(AVLNode->left);
                destroyRecursive(AVLNode->right);
                delete AVLNode;
            }
        }

        int getHeight(const AVLNode<T>* AVLNode)
        {
            if(AVLNode == nullptr)
                return -1;
            return AVLNode->height;
        }

        int getBalanceFactor(const AVLNode<T>* AVLNode)
        {
            if(AVLNode == nullptr){
                return 0;
            }
            return getHeight(AVLNode->left) - getHeight(AVLNode->right);
        }
        
        void fixHeight(AVLNode<T>* root)
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

        //right rotation
        AVLNode<T>* LLR(AVLNode<T>* root)
        {
            AVLNode<T>* left_of_root = root->left;
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
        AVLNode<T>* RRR(AVLNode<T>* root)
        {
            AVLNode<T>* right_of_root = root->right;
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

        AVLNode<T>* rebalance(AVLNode<T>* AVLNode)
        {
            if(getBalanceFactor(AVLNode) >= 2){
                //LR_rotation
                if(getBalanceFactor(AVLNode->left) < 0){
                    AVLNode->left = RRR(AVLNode->left);
                    return LLR(AVLNode);
                }
                //LL rotation
                else{
                    return LLR(AVLNode);
                }
            }
            else if(getBalanceFactor(AVLNode) <= -2){
                //RL rotation
                if(getBalanceFactor(AVLNode->right) > 0){
                    AVLNode->right = LLR(AVLNode->right);
                    return RRR(AVLNode);
                }
                //RR rotation
                else{
                    return RRR(AVLNode);
                }
            }
            return AVLNode;
        }

        AVLNode<T>* insertAVLNodeHelper(const T& value, AVLNode<T>* start)
        {
            if(start == nullptr){
                start = new AVLNode<T>(value);
            }
            else if(condition(value, start->data)){
                start->left = insertAVLNodeHelper(value, start->left);
                start = rebalance(start);
            }
            else if(condition(start->data, value)){
                start->right = insertAVLNodeHelper(value, start->right);
                start = rebalance(start);
            }
            start->height = ((getHeight((start->left)) > getHeight(start->right)) ? 
                            getHeight((start->left)) : getHeight(start->right)) + 1;
            return start;
        }

        //O(log n)
        AVLNode<T>* deleteAVLNodeHelper(const T& data ,AVLNode<T>* to_delete)
        {
            AVLNode<T>* temp;
            //element not found
            if(to_delete == nullptr){
                return nullptr;
            }

            // Searching for the element
            else if(condition(data, to_delete->data)){
                to_delete->left = deleteAVLNodeHelper(data, to_delete->left);
            }
            else if(condition(to_delete->data, data)){
                to_delete->right = deleteAVLNodeHelper(data, to_delete->right);
            }

            //Element is in to_delete
            //has two childs
            else if(to_delete->left != nullptr && to_delete->right != nullptr){
                temp = findMinAVLNode(to_delete->right);
                to_delete->data = temp->data;
                to_delete->right = deleteAVLNodeHelper(to_delete->data, to_delete->right);
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

        int treeToSortedArray(AVLNode<T>* root ,T arr[], int index = 0)
        {
            if(root != nullptr){
                index = treeToSortedArray(root->left, arr, index);
                arr[index] = root->data;
                index++;
                index = treeToSortedArray(root->right, arr, index);
            }
            return index;
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

        AVLNode<T>* sortedArrayToAVLTree(T merged[], int start, int end)
        {
            if(start > end){
                return nullptr;
            }
            
            int mid = (start+end)/2;
            AVLNode<T>* root = new AVLNode<T>(merged[mid]);
            root->left = sortedArrayToAVLTree(merged, start, mid - 1);
            root->right = sortedArrayToAVLTree(merged, mid + 1, end);

            return root;
        }

        void AVLTreeFixHeight(AVLNode<T>* root)
        {
            if(root!=nullptr){
                AVLTreeFixHeight(root->left);
                AVLTreeFixHeight(root->right);
                fixHeight(root);
            }
        }

        int countElements(AVLNode<T>* root)
        {
            if(root == nullptr)
                return 0;
            return 1 + countElements(root->left) + countElements(root->right);
        }

    public:
        AVLNode<T>* root;
        Cond condition;
        class ElementNotInTree: exception{};
        class ElementAlreadyInTree: exception{};
        class MaxElementInTree: exception{};
        AVLTree(const Cond& condition): root(nullptr), condition(condition)
        {
            
        }

        ~AVLTree()
        {
            destroyRecursive(root);
        }

        AVLNode<T>* getRoot()
        {
            return this->root;
        }

        //O(log(n))
        AVLNode<T>* findElement(const T& data, AVLNode<T>* start)
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
        void insertAVLNode(const T& value)
        {
            try{
                this->findElement(value, this->root);
                throw ElementAlreadyInTree();
            }
            catch(const ElementNotInTree& e){}
            this->root = insertAVLNodeHelper(value, this->root);
        }

        //O(1)
        bool isEmpty() const
        {
            return root == nullptr;
        }

        void deleteAVLNode(const T& data)
        {
            try{
                this->findElement(data, this->root);
            }
            catch(const ElementNotInTree& e){
                throw ElementNotInTree();
            }
            this->root = deleteAVLNodeHelper(data, this->root);
        }

        //O(log n)
        AVLNode<T>* findMinAVLNode(AVLNode<T>* start)
        {
            AVLNode<T>* current = start;
            while (current->left != nullptr)
            {
                current = current->left;
            }
            return current;
        }

        //O(log n)
        AVLNode<T>* findMaxAVLNode(AVLNode<T>* start)
        {
            AVLNode<T>* current = start;
            while (current->right != nullptr)
            {
                current = current->right;
            }
            return current;
        }

        //O(h+m) where m is number of elements in range and h is the height of the tree
        template <class EX>
        int elementsInRange(AVLNode<T>* root, const T& low, const T& high, EX extra_condition)
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
        void absorbTree(AVLTree& tree)
        {
            int len1 = countElements(this->root);
            int len2 = countElements(tree.getRoot());
            T *arr1 = new T[len1];
            T *arr2 = new T[len2];
            T *merged = new T[len1 + len2];
            treeToSortedArray(this->root, arr1);
            treeToSortedArray(tree.root, arr2);
            mergeArrays(merged, arr1, arr2, len1, len2);
            AVLNode<T>* temp = this->root;
            this->root = sortedArrayToAVLTree(merged, 0, len1 + len2 - 1);
            AVLTreeFixHeight(this->root);
            //destroy arrays and old tree
            destroyRecursive(temp);
            delete [] arr1;
            delete [] arr2;
            delete [] merged;
        }

        void destroyRecursiveData(AVLNode<T>* AVLNode)
        {
            if(AVLNode != nullptr){
                destroyRecursiveData(AVLNode->left);
                destroyRecursiveData(AVLNode->right);
                delete AVLNode->data;
            }
        }
};

#endif /* AVL_TREE_H_ */
