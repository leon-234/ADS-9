// Copyright 2022 NNTU-CS
#include <iostream>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <random>
#include <vector>
#include "tree.h"

int64_t fact(int n) {
    int64_t r = 1;
    for (int i = 2; i <= n; i++)
        r *= i;

    return r;
}

void experiment() {
    std::ofstream out("data.txt");
    out << "n all perm1 perm2\n";
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int n = 3; n <= 10; n++) {
        std::cout << "n = " << n << std::endl;
        std::vector<char> alphabet;
        for (int i = 0; i < n; i++)
            alphabet.push_back('A' + i);
        PMTree tree(alphabet);
        std::uniform_int_distribution<int64_t>
            dist(1, fact(n));
        int num = dist(gen);
        double tAll;
        double tPerm1;
        double tPerm2 = 0;
        auto start =
            std::chrono::high_resolution_clock::now();
        auto perms = getAllPerms(tree);
        auto finish =
            std::chrono::high_resolution_clock::now();
        tAll =
            std::chrono::duration<double, std::milli>
            (finish - start).count();
        start =
            std::chrono::high_resolution_clock::now();
        auto p1 = getPerm1(tree, num);
        finish =
            std::chrono::high_resolution_clock::now();
        tPerm1 =
            std::chrono::duration<double, std::milli>
            (finish - start).count();
        const int TESTS = 1000;
        for (int k = 0; k < TESTS; k++) {
            num = dist(gen);
            start =
                std::chrono::high_resolution_clock::now();
            auto p2 = getPerm2(tree, num);
            finish =
                std::chrono::high_resolution_clock::now();
            tPerm2 +=
                std::chrono::duration<double, std::nano>
                (finish - start).count();
        }
        tPerm2 /= TESTS;
        tPerm2 /= 1000000.0; 
        out << n << " "
            << tAll << " "
            << tPerm1 << " "
            << tPerm2 << "\n";
        std::cout
            << "all=" << tAll
            << " ms, perm1=" << tPerm1
            << " ms, perm2=" << tPerm2
            << " ms\n";
    }
    out.close();
}

int main() {
    experiment();
    return 0;
}
