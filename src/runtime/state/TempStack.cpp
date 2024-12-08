#include "TempStack.hpp"
#include <iostream>

void TempStack::push(Object *value) {
    LinkedList<Object *> *oldHead = head;
    head = new LinkedList<Object *>(value);
    head->next = oldHead;
}

void TempStack::move(Object *value) {
    move(std::unique_ptr<Object>(value));
}

void TempStack::move(std::unique_ptr<Object> value) {
    push(value.get());
    ownedObjects[value.get()] = std::move(value);
}

void TempStack::pop(size_t count, size_t start) {
    if (start == 0) {
        LinkedList<Object *> *next = head->next;

        ownedObjects.erase(head->value);
        delete head;
        head = next;
        return;
    }

    for (const auto i : head->removeNodes(start, count)) {
        ownedObjects.erase(i);
    }
}

Object *TempStack::get(size_t index) {
    std::optional<Object *> obj = head ? head->getValue(index) : std::nullopt;
    return obj ? *obj : nullptr;
}

std::vector<Object *> TempStack::get(const std::vector<size_t>& indices) {
    return head->getValues(indices);
}

std::string TempStack::toString() const {
    std::string res = "";

    size_t count = 0;
    for (const auto i : head->getValues()) {
        if (i != head->value) res += "\n";
        res += "%tmp" + std::to_string(count++) + ": ";
        res += i->toString();
    }

    return res;
}