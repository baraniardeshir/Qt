#pragma once
#include <utility>
#include <iterator>
#include <unordered_map>
#include <iostream>

template<typename KT, typename VT>
class QHash;

template<typename KT, typename VT>
struct QHashIterator {

    friend QHash<KT,VT>;

    using iterator_category = std::random_access_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = VT;
    using pointer           = value_type*;  // or also value_type*
    using reference         = value_type&;  // or also value_type&

    explicit QHashIterator(typename std::unordered_map<KT, VT>::iterator it) : it(move(it)) {}

    const KT& key()  {
        return it->first;
    }

    VT& value()  {
        return it->second;
    }

    void operator++(int) { // it++
        it++;
    }

    void operator++() { // ++it
        ++it;
    }

    bool operator==(const QHashIterator<KT, VT>& other) {
        return it == other.it;
    }

    bool operator!=(const QHashIterator<KT, VT>& other) {
        return it != other.it;
    }

    reference operator*() {
        return it->second;
    }

    pointer operator->() {
        return &it->second;
    }

private:
    typename std::unordered_map<KT, VT>::iterator get_std_iterator(){
        return it;
    }

    typename std::unordered_map<KT, VT>::iterator it;
};

 template<typename KT, typename VT>
 struct QHashConstIterator {

     friend QHash<KT,VT>;

     using iterator_category = std::random_access_iterator_tag;
     using difference_type   = std::ptrdiff_t;
     using value_type        = VT;
     using pointer           = const value_type*;  // or also value_type*
     using reference         = const value_type&;  // or also value_type&

     explicit QHashConstIterator(typename std::unordered_map<KT, VT>::const_iterator it) : it(move(it)) {}


     const KT& key() const {
         return it->first;
     }

     const VT& value() const {
         return it->second;
     }

     void operator++(int) { // it++
         it++;
     }

     void operator++() { // ++it
         ++it;
     }

     bool operator==(const QHashConstIterator<KT, VT>& other)  {
         return it == other.it;
     }

     bool operator!=(const QHashConstIterator<KT, VT>& other)  {
         return it != other.it;
     }

     reference operator*() {
         return it->second;
     }

     pointer operator->() {
         return &it->second;
     }

 private:
     typename std::unordered_map<KT, VT>::const_iterator get_std_iterator(){
         return it;
     }

     typename std::unordered_map<KT, VT>::const_iterator it;
 };

template<typename KT, typename VT>
class QHash : public std::unordered_map<KT, VT>
{
public:
    using std::unordered_map<KT, VT>::unordered_map;

    bool contains(const KT& key) const ;
    void insert(const KT& key, const VT& value);
    const VT value(const KT& key) const;
    const KT key(const VT& value) const;
    int remove(const KT &key);

    const VT& operator[](const KT& key) const {
        return std::unordered_map<KT, VT>::at(key);
    }

     VT& operator[](const KT& key) {
        return std::unordered_map<KT, VT>::operator[](key);
    }
//    const VT& operator[](const KT& key)  {
//        return std::unordered_map<KT, VT>::operator[](key);
//    }






    QHashIterator<KT, VT> begin() {
        return QHashIterator<KT, VT>(std::unordered_map<KT, VT>::begin());
    }
    QHashIterator<KT, VT> end() {
        return QHashIterator<KT, VT>(std::unordered_map<KT, VT>::end());
    }

    const QHashConstIterator<KT, VT> constBegin() const {
        return QHashConstIterator<KT, VT>(std::unordered_map<KT, VT>::cbegin());
    }
    const QHashConstIterator<KT, VT> constEnd() const {
        return QHashConstIterator<KT, VT>(std::unordered_map<KT, VT>::cend());
    }
    
    QHashIterator<KT, VT> erase(QHashIterator<KT, VT> it) {
        auto std_it = std::unordered_map<KT, VT>::erase(it.get_std_iterator());
        return QHashIterator<KT, VT>(std_it);
    }


    QHashIterator<KT, VT> find(const KT& key) {
        return QHashIterator<KT, VT>(std::unordered_map<KT, VT>::find(key));
    }

    QHashConstIterator<KT, VT> find(const KT& key) const {
        return QHashConstIterator<KT, VT>(std::unordered_map<KT, VT>::find(key));
    }

    bool isEmpty() const { return std::unordered_map<KT, VT>::empty(); }


private:


};

template<typename KT, typename VT>
bool QHash<KT, VT>::contains(const KT &key) const{
    return (this->find(key) != this->constEnd());
}
template<typename KT, typename VT>
const VT QHash<KT, VT>::value(const KT& key) const{
    if(contains(key))
        return this->at(key);
    return VT();
}

template<typename KT, typename VT>
const KT QHash<KT, VT>::key(const VT& value) const {
    for(auto it = this->begin(); it != this->end(); ++it){
        if(it.value() == value){
            return  it.key();
        }
    }
    return KT();
}

template<typename KT, typename VT>
void QHash<KT, VT>::insert(const KT& key, const VT& value) {
    /*
    std::unordered_map<KT, VT>* p = this;
    (*p)[key] = value;
     */
    //std::unordered_map<KT, VT>::operator[](key) = value;

    //std::unordered_map<KT, VT>::insert (std::make_pair<KT, VT>(&key, &value));
    std::unordered_map<KT, VT>::insert ({key, value});
}

template<typename KT, typename VT>
int QHash<KT, VT>::remove(const KT &key) {
    int out = 0;
    if(contains(key)) {
        auto hashSizeBeforeErase = this->size();
        QHashIterator<KT, VT> item = erase(find(key));
        hashSizeBeforeErase != this->size() ? out = 1 : out = 0;
    } else
        out = 0;
    return out;
}


template<typename KT, typename VT>
inline std::ostream& operator<<(std::ostream& os, const QHash<KT, VT>& hash) {

    if (hash.empty()){
        std::cout << "empty QHash()\n";
        return os;
    }
    for (auto item = hash.constBegin(); item != hash.constEnd(); item++) {
        std::cout << "\"" << item.key() << "\" : \"" << item.value() << "\"" << std::endl;
    }
    return os;
}







