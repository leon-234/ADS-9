// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <algorithm>

struct Node {
    char value;
    std::vector<Node*> children;
    explicit Node(char v = '\0') : value(v) {}
};

class PMTree {
 private:
    Node* root;
    int alphabetSize;
    void build(Node* parent, std::vector<char> elems) {
        if (elems.empty())
            return;
        for (int i = 0; i < elems.size(); i++) {
            Node* child = new Node(elems[i]);
            parent->children.push_back(child);
            std::vector<char> rest = elems;
            rest.erase(rest.begin() + i);
            build(child, rest);
        }
    }
    void destroy(Node* node) {
        if (!node)
            return;
        for (auto child : node->children)
            destroy(child);
        delete node;
    }

 public:
    explicit PMTree(const std::vector<char>& elems) {
        alphabetSize = elems.size();
        root = new Node();
        build(root, elems);
    }
    ~PMTree() {
        destroy(root);
    }
    Node* getRoot() const { return root; }
    int size() const { return alphabetSize; }
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);
#endif  // INCLUDE_TREE_H_
