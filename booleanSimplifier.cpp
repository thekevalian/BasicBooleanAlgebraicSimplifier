#include <iostream>
#include "dubitmap.hpp"
int main(int argc, char** argv){
    std::string test("01XX--"); 
    KOS::dubitmap a(test);
    std::cout << a(5);
    KOS::dubitmap b = a;
    b.push_back_dubit(0);
    b.push_back_dubit(0);
    KOS::dubitmap c;
    std::cout << c << std::endl;
    c += a;
    c.change_dubit(0, 0);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    c.push_back_dubit(0);
    c.push_back_dubit(2);
    std::cout << c << " With Length "<< c.length() <<std::endl;
    std::cout << (a==c) << std::endl;
    return 0;
}