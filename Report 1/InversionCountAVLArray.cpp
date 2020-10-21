#include <vector>
#include <iostream>

using namespace std;

template<typename T> class Tree {
private:
    const static size_t NIL = -1;

    struct Node {
        T key;
        size_t height, size;
        size_t left, right;
        Node(T key) :
            key(key), size(1), height(1),
            left(NIL), right(NIL) {}
    };

    vector<Node> tree;
    size_t root = NIL;

    int64_t height(size_t i) {
        return i == NIL ? 0 : tree[i].height;
    }
    int64_t size(size_t i)   {
        return i == NIL ? 0 : tree[i].size;
    }
    int64_t balancing(size_t i) {
        return i == NIL ? 0 : height(tree[i].left) - height(tree[i].right);
    }
    void recalculate(size_t i) {
        tree[i].height = max(height(tree[i].left), height(tree[i].right)) + 1;
        tree[i].size = size(tree[i].left) + size(tree[i].right) + 1;
    }

    size_t rotateRight(size_t n) {
        size_t t = tree[n].left;
        tree[n].left = tree[t].right;
        tree[t].right = n;
        recalculate(n);
        recalculate(t);
        return t;
    }

    size_t rotateLeft(size_t n) {
        size_t t = tree[n].right;
        tree[n].right = tree[t].left;
        tree[t].left = n;
        recalculate(n);
        recalculate(t);
        return t;
    }

    size_t insert(size_t i, T key, size_t& inversions) {
        if(i == NIL) {
            tree.push_back(Node(key));
            return tree.size()-1;
        } else if(key < tree[i].key) {
            tree[i].left = insert(tree[i].left, key, inversions);
            inversions += size(tree[i].right) + 1;
        } else if(key > tree[i].key)
            tree[i].right = insert(tree[i].right, key, inversions);

        recalculate(i);

        int64_t balance = balancing(i);

        if(balance > 1) {
            if(key >= tree[tree[i].left].key)
                tree[i].left = rotateLeft(tree[i].left);
            return rotateRight(i);
        } else if(balance < -1) {
            if(key <= tree[tree[i].right].key)
                tree[i].right = rotateRight(tree[i].right);
            return rotateLeft(i);
        } else
            return i;
    }
public:
    Tree(size_t n) { tree.reserve(n); }
    void insert(T key, size_t& inversions) {
        root = insert(root, key, inversions);
    }
};

size_t inversion_count(vector<int64_t>& A) {
    Tree<int64_t> tree(A.size());

    size_t count = 0;

    for(const auto &v : A)
        tree.insert(v, count);

    return count;
}
