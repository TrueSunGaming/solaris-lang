#pragma once

#include "../../universal/util/LinkedList.hpp"
#include "../data/Object.hpp"
#include <set>

class TempStack {
    private:
        LinkedList<Object *> *head = nullptr;
        std::map<Object *, std::unique_ptr<Object>> ownedObjects;
    
    public:
        void push(Object *value);
        void move(Object *value);
        void move(std::unique_ptr<Object> value);
        void pop(size_t count = 1, size_t start = 0);
        Object *get(size_t index);
        std::vector<Object *> get(const std::vector<size_t>& indices);
};