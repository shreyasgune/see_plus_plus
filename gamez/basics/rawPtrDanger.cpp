// Online C++ compiler to run C++ program online
#include <iostream>

void print(int &i)
{
    std::cout<< &i << " " << i << " " << sizeof(i) << "\n";
}

int main(int argc, char *argv[]) 
{
    int a = 10;
    int* pa = &a;
    
    int b = 25;
    int* pb = &b;
    
    //*pa = 17; //makes the value of 'a' as 17
    
    // DANGER ZONE
    /*
    if we do arithmetic on pointers, we can basically modify
    value at an unintentional address
    
    Check it out, (as an example)
    a is at address 0x7ffd28376e5c
    b is at address 0x7ffd28376e58
    
    they are 4 bytes apart.
    
    pb is of type: INT
    when we subtract 1 from it, it will subtract
    the number of bytes, of the data type.
    
    Since '1' is a 4 byte long int,
    we are basically subtracting address - 4 bytes 
    in the example below
    */
    *(pb+1) = 17; //address of b minus 4 bytes == address of a
    print(*(pb+1));
    //so the value at a is now changed to 17
    /*
        a is at address 0x7ffd28376e5c with value 17
        b is at address 0x7ffd28376e58 with value 25
    */
    
    
    //print calling
    print(a);
    print(b);
    //
    /*
    print(pa); // fails
    
    initializing argument 1 of 'void print(int&)'
    4 | void print(int &i)
      |            ~~~~~^
    error: cannot bind rvalue '(int)pa' to 'int&'
       
    
    */
    return 0;
}