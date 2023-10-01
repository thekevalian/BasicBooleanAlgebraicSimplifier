#include <iostream>
#include "dubitmap.hpp"
int main(int argc, char** argv){
    std::string test("01ABBA"); 
    KOS::dubitmap a(test, 'A', 'B');
    KOS::dubitmap b = a;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    return 0;
}