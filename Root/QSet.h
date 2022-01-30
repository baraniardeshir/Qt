#pragma once
#include <set>
#include <iostream>

template<typename T>
class QSet : public std::set<T> {

public:
    using std::set<T>::set;
    bool remove(const T& value);
    bool removeAt(int i) { std::set<T>::erase(std::next(this->begin(), i)); }

    T& at(int i) { return *(std::next(std::set<T>::begin(), i)); }
    const T& at(int i) const { return *(std::next(std::set<T>::cbegin(), i)); }

    void append (const T& item) { std::set<T>::insert(item); }
    inline bool isEmpty() const { return this->empty();}
    bool contains (const T& value) const;
    void reserve(size_t s) {}
    

};

template<typename T>
bool QSet<T>::remove(const T &value) {
    return this->erase(value);
}

template<typename T>
bool QSet<T>::contains(const T &value) const {
    return (std::set<T>::find(value) != std::set<T>::end());
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const QSet<T> &set) {
    for (auto item = set.begin(); item != set.end(); item++) {
        std::cout << "\"" << *item << "\"\r\n";
    }
    return os;
}
