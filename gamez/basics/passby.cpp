// pass by val vs pass by ref
#include <iostream>

void makeTen(int a)
{
    a = 10;
}

void makeTenPtr(int *a)
{
    /*
    When this function gets called, we are passing the address
    look up the address, then modify the value at it (to 10)
    */
    *a = 10;
    
    /*  but this is unsafe, cuz what if the address you passed is null?
        what if the value at the address is NOT int, but your
        assignement just cast it as int.
    */
}

void makeTenRef(int &a)
{
    a = 10;
}

void print(int i)
{
    std::cout << "i = " << i << std::endl;
}

int main() {
    // Write C++ code here
    int i = 12;
    // OG i
    print(i);
    makeTen(i);
    print(i);
    makeTenPtr(&i);
    print(i);
    i = 13;
    print(i);
    makeTenRef(i);
    print(i);
   
    return 0;
}