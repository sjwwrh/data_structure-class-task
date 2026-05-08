#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

template <typename T>
struct huffman_node {
    double weight;
    int parent;
    int left;
    int right;
    T val;

    huffman_node(double w = 1, int p = -1, int l = -1, int r = -1, T _val = T())
        : weight(w), parent(p), left(l), right(r), val(_val) {}
};

//注意两边都是开的
template <typename T>
int min_index(huffman_node<T>* arr, int start, int end) {
    int min_i = start;
    for (int i = end - 1; i > start; i++) {
        if ((arr[i].parent == 0) && (arr[i].weight < arr[min_i].weight)) {
            min_i = i;
        }
    }
    return min_i;
}

template <typename T>
huffman_node<T>* best_binary_tree(T value[], double w[], int n) {
    huffman_node<T>* BB_tree = new huffman_node<T>[2 * n];
    for (int leaf_index = 0; leaf_index < n; leaf_index++) {
        int node_index = 2 * n - 1 - leaf_index;
        BB_tree[node_index].val = value[leaf_index];
        BB_tree[node_index].weight = w[leaf_index];
        BB_tree[node_index].parent = 0;
        BB_tree[node_index].left = 0;
        BB_tree[node_index].right = 0;
    }

    int left_node = n - 1;
    while (left_node != 0) {
        int first_min = min_index(BB_tree, left_node, 2 * n);
        BB_tree[first_min].parent = left_node;
        int second_min = min_index(BB_tree, left_node, 2 * n);
        BB_tree[second_min].parent = left_node;
        
        BB_tree[left_node].weight = BB_tree[first_min].weight + BB_tree[second_min].weight;
        BB_tree[left_node].parent = 0;
        BB_tree[left_node].left = first_min;
        BB_tree[left_node].right = second_min;
        left_node--;
    }

    return BB_tree;
}

template <typename T>
char** huffman_code(huffman_node<T> BB_tree[], int n);

#endif //HUFFMAN_TREE_H