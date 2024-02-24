#include <iostream>


void print(int &var)
{
    // if we pass var directly, it's going to be a different var
    // that's why we pass the address of a and b in main down below
    std::cout << "Variable val is: "<< var << std::endl;
    std::cout << "at address: "<< &var << std::endl;
    std::cout << "Size of which is: "<< sizeof(var) << std::endl;
    std::cout << "-----" << std::endl;
}

int main(int argc, char *argv[])
{
    int a = 10;
    int b = 25;
    
    print(a);
    print(b);
    
    // doin this for array
    int arr[5] = {} ;//this means values are 0 by default, so we don't just print out stuff that's in memory
    int *harr = new int[5];
    for (size_t i=0; i<5; i++)
    {
        print(arr[i]); //when you see the output, the addresses will be contiguously, 4 bytes apart from each other
    }
    
    // heap array output
    for (size_t i=0; i<5; i++)
    {
        print(harr[i]); //when you see the output, the addresses will be contiguously, 4 bytes apart from each other
    }

    return 0;
}