#ifndef SEQ_TREE_H
#define SEQ_TREE_H

//-1表示相应节点不存在
template <typename T>
class node {
    T data;
    int left;
    int right;
    int parent;

public:
    node(const T& _data = T(), int l = -1, int r = -1, int _parent = -1)
        : data(_data), left(l), right(r), parent(_parent) {}

    friend class seq_tree<T>;
};

//因易于实现,故只做声明
template <typename T>
class seq_tree {
private:
    node<T>* array;
    int capacity;
    int len;

public:
    seq_tree(int size);
    ~seq_tree();

    int size() const noexcept;
    int height() const noexcept;
    int delete_tree(int i);
    void preorder_print() const noexcept;
    void inorder_print() const noexcept;
    void postorder_print() const noexcept;
    void create_tree(const T& stop_flag);
    bool is_empty() const noexcept;
    bool is_full() const noexcept;

private:
    void double_space();

};

#endif //SEQ_TREE_H