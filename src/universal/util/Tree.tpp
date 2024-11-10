#include "Tree.hpp"

template <class T, class C> Tree<T, C>::Tree(T value, std::vector<C&> children)
    : value(value),
      children(children) {}