#pragma once

#include <vector>

template <class T> class Tree {
    public:
        T value;
        std::vector<Tree*> children;

        Tree() = default;
        Tree(T value, std::vector<Tree*> children = {});
        ~Tree() = default;
};

#include "Tree.tpp"