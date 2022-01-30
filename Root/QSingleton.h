#pragma once

#include <exception>


template <typename T>
class QSingleton
{
protected:
    explicit QSingleton() {}
public:
    virtual ~QSingleton() {
        instance = nullptr;
    }
    static T* getInstance() {
        if (!instance)
            instance = new T;
        return instance;
    }

protected:
    static T* instance;
};



template <typename T>
T* QSingleton<T>::instance = nullptr;

