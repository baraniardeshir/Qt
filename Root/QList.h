#pragma once
#include <list>

template <class T>
class QList: public std::list<T>{

public:
    using std::list<T>::list;
    void append(const T& item);
    const T& at(const size_t& idx) const;
    T& at(const size_t& idx) ;
    void removeAt(const size_t& idx);
    const T& operator[](size_t i) const {
        return this->at(i);
    }
    T& operator[](size_t i) {
        return this->at(i);
    }

    void reserve (size_t s) {}

};

template<class T>
void QList<T>::append(const T &item) {
    std::list<T>::push_back(item);
}

template<class T>
const T &QList<T>::at(const size_t &idx) const {
    return *(std::next(list<T>::cbegin(), idx));
}
template<class T>
T &QList<T>::at(const size_t &idx)  {
    return *(std::next(list<T>::begin(), idx));
}

template<class T>
void QList<T>::removeAt(const size_t &idx) {
    std::list<T>::erase(next(this->begin(), idx));
}

template<class T>
std::ostream &operator<<(std::ostream &os, const QList<T> &list) {
    for (auto item = list.begin(); item != list.end(); item++) {
        std::cout << "\"" << *item << "\"\r\n";
    }
    return os;
}
