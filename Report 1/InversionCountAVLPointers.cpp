#include <vector>
#include <iostream>

using namespace std;

template<typename T> class Tree {
    struct Node {
        T key;
        Node *left, *right;
        int64_t height, size;

        Node(T key) :
            key(key), size(1), height(1),
            left(nullptr), right(nullptr) {}
        ~Node() {
            delete left;
            delete right;
        }
    };

    Node *root = nullptr;

    int64_t height(Node *n) {
        return n == nullptr ? 0 : n->height;
    }
    int64_t size(Node *n)   {
        return n == nullptr ? 0 : n->size;
    }
    int64_t balancing(Node *n) {
        return n == nullptr ? 0 : height(n->left) - height(n->right);
    }
    void recalculate(Node *n) {
        n->height = max(height(n->left), height(n->right)) + 1;
        n->size = size(n->left) + size(n->right) + 1;
    }

    Node *rotateRight(Node *n) {
        Node *t = n->left;
        n->left = t->right;
        t->right = n;
        recalculate(n);
        recalculate(t);
        return t;
    }

    Node *rotateLeft(Node *n) {
        Node *t = n->right;
        n->right = t->left;
        t->left = n;
        recalculate(n);
        recalculate(t);
        return t;
    }

    Node *insert(Node *node, T key, size_t& inversions) {
        if(node == nullptr)
            return new Node(key);
        else if(key < node->key) {
            node->left = insert(node->left, key, inversions);
            inversions += size(node->right) + 1;
        } else if(key > node->key)
            node->right = insert(node->right, key, inversions);

        recalculate(node);

        int64_t balance = balancing(node);

        if(balance > 1) {
            if(key >= node->left->key)
                node->left = rotateLeft(node->left);
            return rotateRight(node);
        } else if(balance < -1) {
            if(key <= node->right->key)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        } else
            return node;
    }
public:
    Tree() { }
    ~Tree() { delete root; }
    void insert(T key, size_t& inversions) {
        root = insert(root, key, inversions);
    }
};

size_t inversion_count(vector<int64_t>& A) {
    Tree<int64_t> tree;

    size_t count = 0;

    for(const auto &v : A)
        tree.insert(v, count);

    return count;
}
