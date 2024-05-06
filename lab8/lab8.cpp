#include "Header.h"
#include "smartPtr.h"

#include <iostream>
#include <list>
#include <memory>
// g++ source/lab8/lab8.cpp source/lab8/Hardware_and_software_protection.cpp -o build/lab8

// template<class T> std::list<MyUnique_ptr<T>> lst;
int main() {

    // MyShared_ptr<kvad> my_ptr1(new kvad("aaa", 1));
    // // // std::cout << my_ptr1->get_protection_class_number() << std::endl;
    // std::cout << my_ptr1;
    // auto ptr_container1 = create_unique<kvad>(kvad(), kvad("aaa", 1),
    //                               kvad("bbb", 2), kvad("ccc", 3), kvad("ccc", 4));
    auto ptr_container2 = create_shared<kvad>(kvad(), kvad(3., -5.1, 1.),
        kvad(3.,22., -1.), kvad(1.,-2.,5.), kvad(1., 5.1, -4));
    // for (const auto& el : ptr_container1) {
    //   std::cout << el;
    // }
    // std::cout << std::endl;
    // for (const auto& el : ptr_container2) {
    //   std::cout << el;
    // }
    /*kvad* kvad10 = new kvad();
    MyUnique_ptr<kvad> p1(kvad10), p2(kvad10);*/ // Так делвть нельзя, на совести пользователя
    kvad* kvad1 = new kvad();
    kvad* kvad2 = new kvad();
    MyShared_ptr<kvad> shared1(kvad1);
    MyShared_ptr<kvad> shared2(shared1);
    MyShared_ptr<kvad> shared3 = MyShared_ptr<kvad>(MyShared_ptr<kvad>(kvad2));
    std::cout << shared1.get_ptrCount() << std::endl;
    std::cout << shared2.get_ptrCount() << std::endl;
    std::cout << shared3.get_ptrCount() << std::endl;
    
    // MyUnique_ptr<int> my_ptr2(new int(4));
    // std::cout << *my_ptr2 << std::endl;
    // Make_MyUnique(kvad("sss", 2), Point(1, 2), kvad("ddd", 3));
    return 0;
}