#include <iostream>
#include <cmath>
#include <utility>

// Класс квадратного уравнения
class QuadraticEquation {
private:
    double a, b, c;

public:
    QuadraticEquation(double a_, double b_, double c_) : a(a_), b(b_), c(c_) {}

    double discriminant() const {
        return b * b - 4 * a * c;
    }

    void printParameters() const {
        std::cout << "a: " << a << ", b: " << b << ", c: " << c << std::endl;
    }

    bool hasRealRoots() const {
        return discriminant() >= 0;
    }
};

// Шаблон "умного" указателя, аналогичный std::unique_ptr
template<class T>
class MyUnique {
    T* p = nullptr;

public:
    MyUnique(T* p_) : p(p_) {}

    ~MyUnique() {
        delete p;
    }

    T* get() const {
        return p;
    }

    T& operator*() {
        return *p;
    }

    T* operator->() {
        return p;
    }

    MyUnique(const MyUnique&) = delete; // Запрещаем копирование
    MyUnique& operator=(const MyUnique&) = delete; // Запрещаем присваивание копированием

    MyUnique(MyUnique&& other) noexcept : p(other.p) {
        other.p = nullptr;
    }

    MyUnique& operator=(MyUnique&& other) noexcept {
        if (this != &other) {
            delete p;
            p = other.p;
            other.p = nullptr;
        }
        return *this;
    }
};

// Глобальная шаблонная функция Make_MyUnique
template<typename T, typename... Args>
MyUnique<T> Make_MyUnique(Args&&... args) {
    return MyUnique<T>(new T(std::forward<Args>(args)...));
}

// Шаблон "умного" указателя, аналогичный std::shared_ptr
template<class T>
class MyShared {
    T* p = nullptr;
    size_t* refCount = nullptr;

public:
    MyShared(T* p_) : p(p_), refCount(new size_t(1)) {}

    ~MyShared() {
        decreaseRefCount();
    }

    T* get() const {
        return p;
    }

    T& operator*() {
        return *p;
    }

    T* operator->() {
        return p;
    }

    MyShared(const MyShared& other) : p(other.p), refCount(other.refCount) {
        (*refCount)++;
    }

    MyShared& operator=(const MyShared& other) {
        if (this != &other) {
            decreaseRefCount();
            p = other.p;
            refCount = other.refCount;
            (*refCount)++;
        }
        return *this;
    }

    MyShared(MyShared&& other) noexcept : p(other.p), refCount(other.refCount) {
        other.p = nullptr;
        other.refCount = nullptr;
    }

    MyShared& operator=(MyShared&& other) noexcept {
        if (this != &other) {
            decreaseRefCount();
            p = other.p;
            refCount = other.refCount;
            other.p = nullptr;
            other.refCount = nullptr;
        }
        return *this;
    }

private:
    void decreaseRefCount() {
        if (refCount) {
            (*refCount)--;
            if (*refCount == 0) {
                delete p;
                delete refCount;
            }
        }
    }
};

// Глобальная шаблонная функция Make_MyShared
template<typename T, typename... Args>
MyShared<T> Make_MyShared(Args&&... args) {
    return MyShared<T>(new T(std::forward<Args>(args)...));
}

int main() {
    // Демонстрация работы с классом QuadraticEquation
    QuadraticEquation equation1(1, -3, 2);
    QuadraticEquation equation2(1, 2, 1);

    std::cout << "Equation 1 parameters: ";
    equation1.printParameters();
    std::cout << "Has real roots? " << (equation1.hasRealRoots() ? "Yes" : "No") << std::endl;

    std::cout << "Equation 2 parameters: ";
    equation2.printParameters();
    std::cout << "Has real roots? " << (equation2.hasRealRoots() ? "Yes" : "No") << std::endl;

    // Создание объекта MyPoint и "умного" указателя на него с помощью Make_MyShared
    class MyPoint {
    private:
        int x, y;

    public:
        MyPoint(int x_, int y_) : x(x_), y(y_) {}

        void printCoordinates() const {
            std::cout << "Point coordinates: (" << x << ", " << y << ")" << std::endl;
        }
    };

    auto mySharedPointPtr = Make_MyShared<MyPoint>(5, 10);
    auto mySharedPointPtr2 = mySharedPointPtr; // Копирование
    mySharedPointPtr->printCoordinates();
    mySharedPointPtr2->printCoordinates();

    return 0;
}
