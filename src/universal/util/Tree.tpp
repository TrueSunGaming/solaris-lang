#include "Tree.hpp"

template <class T> Tree<T>::Tree(T value, std::vector<Tree*> children)
    : value(value),
      children(children) {}