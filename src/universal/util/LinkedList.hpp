#pragma once

#include <optional>
#include <vector>
#include <cstdint>

template <class T>
class LinkedList {
    public:
        LinkedList *next = nullptr;
        T value;

        LinkedList(T value);
        LinkedList(T value, LinkedList<T> *next);
        
        LinkedList<T> *getNode(size_t distance);
        std::vector<LinkedList<T> *> getNodes(size_t startDistance = 0, size_t count = SIZE_MAX);
        std::vector<LinkedList<T> *> getNodes(const std::vector<size_t>& distances);
        std::optional<T> getValue(size_t distance);
        std::vector<T> getValues(size_t startDistance = 0, size_t count = SIZE_MAX);
        std::vector<T> getValues(const std::vector<size_t>& distances);
        void removeNode(size_t distance);
};