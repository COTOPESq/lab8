#include "Header.h"

#include <iostream>
#include <vector>
#include <map>
#include <string>
// #include <memory>

#ifndef SMARTPTR_H
#define SMARTPTR_H

class Point {
    int x, y;

public:
    Point(int x, int y) : x(x), y(y) {}
    void prsize_t_info(std::ostream& out) const {
        out << "(" << x << ", " << y << ")\n";
    }
};

template<class T>
class MyUnique_ptr {
    T* ptr = nullptr;
public:
    MyUnique_ptr(T* ptr) : ptr(ptr) {  }
    MyUnique_ptr(const MyUnique_ptr<T>& other) = delete;
    MyUnique_ptr(MyUnique_ptr<T>&& other) {
        std::swap(ptr, other.ptr);
    }
    ~MyUnique_ptr() {
        // std::cout << "~MyUnique_ptr\n";
        if (ptr) delete ptr;
        ptr = nullptr;
        // std::cout << "~MyUnique_ptr\n";
    }

    T* get() const {
        return ptr;
    }
    T& operator*() {
        /* if (ptr) */ return *ptr;
    }
    T& operator*() const {
        /* if (ptr) */ return *ptr;
    }
    T* operator->() {
        return ptr;
    }
    T* operator->() const {
        return ptr;
    }

    MyUnique_ptr<T> operator = (const MyUnique_ptr<T>&) = delete;
    MyUnique_ptr<T>& operator = (MyUnique_ptr<T>&& other) {
        if (this == other) return *this;
        if (ptr) delete ptr;
        ptr = nullptr;
        std::swap(ptr, other.ptr);
        return *this;
    }
};

template<class T>
std::ostream& operator << (std::ostream& out, const MyUnique_ptr<T>& ptr) {
    return out << *ptr;
}

template <class T>
void create_uniqueqq(std::vector<MyUnique_ptr<T>>& vec, const T& t) {
    vec.push_back(MyUnique_ptr<T>(new T(t)));
}

template <class T>
MyUnique_ptr<T> create_unique(const T& t) {
    return MyUnique_ptr<T>(new T(t));
}

template <class T, class ...Args>
void create_uniqueqq(std::vector<MyUnique_ptr<T>>& vec, const T& t, const Args& ... args) {
    vec.push_back(MyUnique_ptr<T>(new T(t)));
    create_uniqueqq(vec, args ...);
}

template <class T, class ...Args>
std::vector<MyUnique_ptr<T>> create_unique(const T& t, const Args& ... args) {
    std::vector<MyUnique_ptr<T>> vec;
    create_uniqueqq(vec, t, args ...);
    return vec;
}

template<class T>
class MyShared_ptr {
    T* ptr = nullptr;
    size_t* ptr_count = nullptr;
public:
    MyShared_ptr(T* ptr) {
        if (ptr == nullptr) {
            this->ptr = nullptr;
            ptr_count = nullptr;
        }
        else {
            this->ptr = ptr;
            ptr_count = new size_t(1);
        }
        // std::cout << "create shared constructor\n";
    }
    MyShared_ptr(MyShared_ptr& other) {
        ptr = other.ptr;
        ptr_count = other.ptr_count;
        ++(*ptr_count);
        // std::cout << "copy shared constructor\n";
    }
    MyShared_ptr(MyShared_ptr&& other) {
        std::swap(ptr, other.ptr);
        std::swap(ptr_count, other.ptr_count);
        // std::cout << "move shared constructor\n";
    }
    ~MyShared_ptr() {
        // std::cout << "~MyUnique_ptr\n";
        // if (ptr) std::cout << *ptr_count << std::endl;
        if (ptr_count && ptr) {
            if (*ptr_count == 1) {
                delete ptr;
                delete ptr_count;
                ptr = nullptr;
                ptr_count = nullptr;
                std::cout << "delete shared\n";
            }
            else {
                --(*ptr_count);
                std::cout << "increment count " << *ptr_count << '\n';
            }
        }
    }

    size_t get_ptrCount() const {
        if (ptr) return *ptr_count;
        return 0;
    }

    T* get() const {
        return ptr;
    }
    T& operator*() {
        /* if (ptr) */ return *ptr;
    }
    T& operator*() const {
        /* if (ptr) */ return *ptr;
    }
    T* operator->() {
        return ptr;
    }
    T* operator->() const {
        return ptr;
    }

    MyShared_ptr<T> operator = (MyShared_ptr<T>& other) {
        if (this.ptr == other.ptr) return *this;
        if (ptr_count && ptr) {
            if (*ptr_count == 1) {
                delete ptr;
                delete ptr_count;
            }
            else {
                --(*ptr_count);
            }
        }
        ptr = other.ptr;
        ptr_count = other.ptr_count;
        ++(*ptr_count);
        // std::cout << "copy shared\n";
        return *this;
    }
    MyShared_ptr<T>& operator = (MyShared_ptr<T>&& other) {
        if (this.ptr == other.ptr) return *this;
        if (ptr_count && ptr) {
            if (*ptr_count == 1) {
                delete ptr;
                delete ptr_count;
            }
            else {
                --(*ptr_count);
            }
        }
        ptr = nullptr;
        ptr_count = nullptr;
        std::swap(ptr, other.ptr);
        std::swap(ptr_count, other.ptr_count);
        // std::cout << "move shared\n";
        return *this;
    }
};

template<class T>
std::ostream& operator << (std::ostream& out, const MyShared_ptr<T>& ptr) {
    return out << *ptr;
}

template <class T>
void create_sharedqq(std::vector<MyShared_ptr<T>>& vec, const T& t) {
    vec.push_back(MyShared_ptr<T>(new T(t)));
}

template <class T>
MyShared_ptr<T> create_shared(const T& t) {
    return MyShared_ptr<T>(new T(t));
}

template <class T, class ...Args>
void create_sharedqq(std::vector<MyShared_ptr<T>>& vec, const T& t, const Args& ... args) {
    vec.push_back(MyShared_ptr<T>(new T(t)));
    create_sharedqq(vec, args ...);
}

template <class T, class ...Args>
std::vector<MyShared_ptr<T>> create_shared(const T& t, const Args& ... args) {
    std::vector<MyShared_ptr<T>> vec;
    create_sharedqq(vec, t, args ...);
    return vec;
}



#endif