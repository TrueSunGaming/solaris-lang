#include "LinkedList.hpp"

template <class T> LinkedList<T>::LinkedList(const T& value) : value(value) {}
template <class T> LinkedList<T>::LinkedList(const T& value, LinkedList<T> *next) : value(value), next(next) {}

template <class T> LinkedList<T>::LinkedList(const std::vector<T>& values) {
    if (values.size() < 1) throw std::runtime_error("LinkedList requires a value");
    value = values[0];

    LinkedList<T> *cur = this;
    for (size_t i = 1; i < values.size(); i++) {
        cur->next = new LinkedList(values[i]);
        cur = cur->next;
    }
}

template <class T> LinkedList<T> *LinkedList<T>::getNode(size_t distance) {
    LinkedList<T> *node = this;

    for (size_t i = 0; i < distance; i++) {
        node = node->next;
        if (!node) return nullptr;
    }

    return node;
}

template <class T> std::vector<LinkedList<T> *> LinkedList<T>::getNodes(size_t startDistance, size_t count) {
    if (count < 1) return {};

    std::vector<LinkedList<T> *> nodes = { getNode(startDistance) };
    if (!nodes.back()) return {};

    //nodes.reserve(count);

    for (size_t i = 0; i < count - 1; i++) {
        if (!nodes.back()->next) break;
        nodes.push_back(nodes.back()->next);
    }

    return nodes;
}

template <class T> std::vector<LinkedList<T> *> LinkedList<T>::getNodes(const std::vector<size_t>& distances) {
    std::vector<LinkedList<T> *> nodes = {};

    std::vector<size_t> sortedDistances = distances;
    std::sort(sortedDistances.begin(), sortedDistances.end());

    LinkedList<T> *cur = this;
    size_t idx = 0;
    for (size_t i = 0; cur; i++) {
        if (i == sortedDistances[idx]) {
            nodes.push_back(cur);
            idx++;
        }

        cur = cur->next;
    }

    return nodes;
}

template <class T> std::optional<T> LinkedList<T>::getValue(size_t distance) {
    LinkedList<T> *node = getNode(distance);
    return node ? std::optional(node->value) : std::nullopt;
}

template <class T> std::vector<T> LinkedList<T>::getValues(size_t startDistance, size_t count) {
    std::vector<T> values = {};
    for (const auto node : getNodes(startDistance, count)) values.push_back(node->value);
    return values;
}

template <class T> std::vector<T> LinkedList<T>::getValues(const std::vector<size_t>& distances) {
    std::vector<T> values = {};
    for (const auto node : getNodes(distances)) values.push_back(node->value);
    return values;
}

template <class T> bool LinkedList<T>::setValue(size_t distance, const T& value) {
    LinkedList<T> *node = getNode(distance);
    if (node) node->value = value;
    return !!node;
}

template <class T> std::optional<T> LinkedList<T>::removeNode(size_t distance, bool free) {
    if (distance == 0) throw std::runtime_error("Cannot remove head of linked list");
    
    LinkedList<T> *node = getNode(distance - 1);

    bool success = node && node->next;
    std::optional<T> removedValue = std::nullopt;
    if (success) {
        removedValue = std::move(node->next->value);

        LinkedList<T> *newNext = node->next->next;
        if (free) delete node->next;
        node->next = newNext;
    }

    return std::move(removedValue);
}

template <class T> std::vector<T> LinkedList<T>::removeNodes(size_t distance, size_t count, bool free) {
    if (distance == 0) throw std::runtime_error("Cannot remove head of linked list");

    std::vector<T> removedValues;

    LinkedList<T> *node = getNode(distance - 1);
    if (node) {
        std::vector<LinkedList<T> *> nodes = node->getNodes(1, count);
        LinkedList<T> *newNext = nodes.back()->next;

        for (const auto i : nodes) {
            removedValues.push_back(std::move(i->value));

            if (free) delete i;
        }

        node->next = newNext;
    }

    return std::move(removedValues);
}