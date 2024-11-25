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

    nodes.reserve(count);

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
    return node ? node->value : std::nullopt;
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

template <class T> bool LinkedList<T>::removeNode(size_t distance) {
    LinkedList<T> *node = getNode(distance - 1);

    bool success = node && node->next;
    if (success) node->next = node->next->next;

    return success;
}

template <class T> void LinkedList<T>::removeNodes(size_t distance, size_t count) {
    LinkedList<T> *node = getNode(distance - 1);
    if (node) node->next = node->getNode(count + 1);
}