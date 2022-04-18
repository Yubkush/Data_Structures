#ifndef AVL_TREE_H
#define AVL_TREE_H
#define LEAF_CHILD -1

#include "BinarySearchTree.h"
#include <math.h>

template <class T, class K>
class AVLTree : BinSearchTree<T,K>
{
    public:
        typedef typename BinSearchTree<T,K>::Node* AVLNode;
        AVLTree() : BinSearchTree<T,K>() {}
        ~AVLTree() = default;
        
        AVLNode getRoot() const override
        {
            return this->root;
        }

        void inorder(AVLNode root) const override
        {
            BinSearchTree<T, K>::inorder(root);
        }

        AVLNode findElement(const K& key, AVLNode start) const override
        {
            try{
                AVLNode to_find = BinSearchTree<T, K>::findElement(key, start);
                return to_find;
            }
            catch(const typename BinSearchTree<T, K>::ElementNotInTree& e){
                throw e;
            }
        }

        int getHeight(const AVLNode node) const
        {
            if(node == nullptr)
                return LEAF_CHILD;
            return node->height;
        }

        int getBalanceFactor(const AVLNode node) const
        {
            if(node == nullptr){
                return 0;
            }
            return getHeight(node->left) - getHeight(node->right);
        }

        void fixHeight(AVLNode root)
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

        void LLR(AVLNode root)
        {
            AVLNode left_of_root = root->left;
            //move left_of_root right subtree to be root's left subtree
            root->left = left_of_root->right;
            if(left_of_root->right != nullptr){
                left_of_root->right->parent = root;
            }
            //move root under left_of_root
            left_of_root->parent = root->parent;
            if(root->parent == nullptr){
                this->root = left_of_root;
            }
            left_of_root->right = root;
            root->parent = left_of_root;
            //update left_of_root parent left/right to left_of_root
            if (left_of_root->parent != NULL && root->key < left_of_root->parent->key) {
                left_of_root->parent->left = left_of_root;
            }
            else {
                if (left_of_root->parent != NULL)
                    left_of_root->parent->right = left_of_root;
            }
            //update heights
            fixHeight(root);
            fixHeight(left_of_root);
        }
        
        void RRR(AVLNode root)
        {
            AVLNode right_of_root = root->right;
            //move right_of_root left subtree to be root's right subtree
            root->right = right_of_root->left;
            if(right_of_root->left != nullptr){
                right_of_root->left->parent = root;
            }
            //move root under right_of_root
            right_of_root->parent = root->parent;
            if(root->parent == nullptr){
                this->root = right_of_root;
            }
            right_of_root->left = root;
            root->parent = right_of_root;
            //update left_of_root parent left/right to left_of_root
            if (right_of_root->parent != NULL && root->key < right_of_root->parent->key) {
                right_of_root->parent->left = right_of_root;
            }
            else {
                if (right_of_root->parent != NULL)
                    right_of_root->parent->right = right_of_root;
            }
            //update heights
            fixHeight(root);
            fixHeight(right_of_root);
        }

        void rebalance(AVLNode node)
        {
            if(getBalanceFactor(node) >= 2){
                //LR_rotation
                if(getBalanceFactor(node->left) < 0){
                    LLR(node->left);
                    RRR(node);
                }
                //LL rotation
                else{
                    LLR(node);
                }
            }
            else if(getBalanceFactor(node) <= -2){
                //RL rotation
                if(getBalanceFactor(node->right) > 0){
                    RRR(node->right);
                    LLR(node);
                }
                //RR rotation
                else{
                    RRR(node);
                }
            }
        }

        void insertNode(const K& key, const T& value) override
        {
            BinSearchTree<T,K>::insertNode(key, value);
            AVLNode node = findElement(key, this->root);
            node->height = 0;
            //update height and rebalance moving up on the tree
            while (node != this->root)
            {
                AVLNode parent = node->parent;
                //update height
                if(getHeight(parent) >= getHeight(node) + 1){
                    break;
                }
                parent->height = getHeight(node) + 1;
                //rebalance if height has changed
                if(abs(getBalanceFactor(parent)) >= 2){
                    rebalance(parent);
                    break;
                }
                node = parent;
            }
        }

        void deleteNode(const K& key)
        {
            AVLNode to_delete_parent, to_delete;
            try{
                to_delete = this->findElement(key, this->root);
            }
            catch(const typename BinSearchTree<T, K>::ElementNotInTree& e){
                throw e;
            }
            /*
                If the node to delete has two children, because of the swap we need to get the
                parent of the swap target, which will be the parent of the node we want to delete
                after the swap.
            */
            if(to_delete->left != nullptr && to_delete->right != nullptr){
                to_delete_parent = (BinSearchTree<T,K>::findNextInorder(to_delete))->parent;
            }
            // If it is a leaf or has only one child, get his parent regularly
            else{
                to_delete_parent = (findElement(key, this->root))->parent;
            }
            //delete node
            BinSearchTree<T,K>::deleteNode(this->root, key);
            //fix the unbalanced tree, lecture algorithm
            while (to_delete_parent != nullptr)
            {
                //fixHeight(to_delete_parent);
                int height_after, height_before = to_delete_parent->height;
                fixHeight(to_delete_parent);
                if(abs(getBalanceFactor(to_delete_parent)) >= 2){
                    rebalance(to_delete_parent);
                    height_after = getHeight(to_delete_parent->parent);
                }
                else{
                    height_after = getHeight(to_delete_parent);
                }
                // if(height_before == height_after){
                //     break;
                // }
                to_delete_parent = to_delete_parent->parent;
            }
        }
};

#endif /* AVL_TREE_H */