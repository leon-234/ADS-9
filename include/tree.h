// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>

struct Node {
    char value;
    std::vector<Node*> children;
    explicit Node(char v = '\0');
};

class PMTree {
 private:
    Node* root;
    int alphabetSize;
    void build(Node* parent, std::vector<char> elems);
    void destroy(Node* node);

 public:
    PMTree(const std::vector<char>& elems);
    ~PMTree();
    Node* getRoot() const { return root; }
    int size() const { return alphabetSize; }
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);
#endif  // INCLUDE_TREE_H_
