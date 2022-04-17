#ifndef AVL_TREE_H
#define AVL_TREE_H
#define LEAF_CHILD -1

#include "BinarySearchTree.h"
#include <math.h>

template <class T, class K>
class AVLTree : BinSearchTree<T,K>
{
    typedef typename BinSearchTree<T,K>::Node* AVLNode;

    AVLTree() : BinSearchTree<T,K>() {}
    ~AVLTree() = default;
    
    int getHeight(const AVLNode node)
    {
        if(node == nullptr)
            return LEAF_CHILD;
        return node->height;
    }

    int getBalanceFactor(AVLNode node) const
    {
        if(node == nullptr){
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    void fixHeight(AVLNode root)
    {
        if(root != nullptr){
            int height_of_node = 1;

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
            this->root = root;
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
        root->right = right_of_root->right;
        if(right_of_root->right != nullptr){
            right_of_root->right->parent = root;
        }
        //move root under right_of_root
        right_of_root->parent = root->parent;
        if(root->parent == nullptr){
            this->root = root;
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
        if(getBalanceFactor(node) > 0){
            //LR_rotation
            if(getBalanceFactor(node->left) < 0){
                LLR(node->left);
                RRL(node);
            }
            //LL rotation
            else{
                LLR(node);
            }
        }
        else if(getBalanceFactor(node) < 0){
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
        while (node != this->root)
        {
            AVLNode parent = node->parent;
            if(getHeight(parent) >= getHeight(node) + 1){
                break;
            }
            parent->height = getHeight(node) + 1;
            if(abs(getBalanceFactor(parent)) >= 2){
                rebalance(parent);
                break;
            }
            node = parent;
        }
    }

    void deleteNode(const K& key) override
    {
        AVLNode to_delete_parent = (findElement(key, this->root))->parent;
        BinSearchTree<T,K>::deleteNode(this->root, key);
        
        
    }
    
};

#endif /* AVL_TREE_H */