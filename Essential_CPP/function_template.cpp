#include <iostream>
#include <stdlib.h>

template <typename T> void Swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}


int main() {
    int n1 = 100,n2 = 200;
    Swap(n1,n2);
    std::cout << n1 << "/" << n2 <<std::endl;

    float f1 = 3.14,f2 = 12.86;
    Swap(f1,f2);
    std::cout << f1 << "/" << f2 <<std::endl;

    system("pause");
    return 0;
}