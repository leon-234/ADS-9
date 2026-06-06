// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "tree.h"

static void dfsAll(
    Node* node,
    std::vector<char>& current,
    std::vector<std::vector<char>>& result) {
    if (node->value != '\0')
        current.push_back(node->value);

    if (node->children.empty()) {
        result.push_back(current);
    }else {
        for (auto child : node->children)
            dfsAll(child, current, result);
    }
    if (node->value != '\0')
        current.pop_back();
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    dfsAll(tree.getRoot(), current, result);
    return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    auto perms = getAllPerms(tree);
    if (num < 1 || num > perms.size())
        return {};
    return perms[num - 1];
}

static long long fact(int n) {
    long long res = 1;
    for (int i = 2; i <= n; i++)
        res *= i;
    return res;
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    int n = tree.size();
    long long total = fact(n);
    if (num < 1 || num > total)
        return {};
    num--;
    Node* current = tree.getRoot();
    std::vector<char> result;
    int remain = n;
    while (remain > 0) {
        long long block = fact(remain - 1);
        int childIndex = num / block;
        if (childIndex >= current->children.size())
            return {};
        current = current->children[childIndex];
        result.push_back(current->value);
        num %= block;
        remain--;
    }
    return result;
}
