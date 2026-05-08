#ifndef TREE_AND_FOREST_H
#define TREE_AND_FOREST_H

/*
forest->binary_tree
最大子节点->left
最大弟弟节点->right
*/

/*
binary->tree
断开右节点连到parent上
若无parent就成为root节点
*/

/*
树的遍历
先序遍历:先访问完根节点后再从左到右遍历子树
    root == nullptr return
    else root 递归func(root_child...)
    
后序遍历:左到右遍历完所有子树再访问根
    root == nullptr return
    else func(root_child...) root
*/

#endif //TREE_AND_FOREST_H