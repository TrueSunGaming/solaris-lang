#pragma once

#include <vector>

template <class T, class C = Tree<T>> class Tree {
    public:
        T value;
        std::vector<C&> children;

        Tree() = default;
        Tree(T value, std::vector<C&> children = {});
        ~Tree() = default;
};

#include "Tree.tpp"