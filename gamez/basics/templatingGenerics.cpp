// Generics and Templates
#include <iostream>

template <typename T>
class DynamicArray
{
    size_t m_size;
    T* m_arr;
    
public:
    //constructor
    DynamicArray(size_t size)
        : m_size(size)
        , m_arr(new T[size]) //sets the default vals to 0
    {
        std::cout << "Array Constructor Called\n";
    }
    
    //destrctor
    ~DynamicArray() 
    {
        delete [] m_arr;
        std::cout << "Array Destructor Called\n";
    }
    
    
    int get(size_t index) const
    {
        return m_arr[index];
    }
    
    int set(size_t index, T val)
    {
        return m_arr[index] = val;
    }
    
    void print() const
    {
        for (size_t i=0; i<m_size ; i++)
        {
            std::cout << i << " " << m_arr[i] << "\n";
        }
    }
    
    //operator overloading
    const T& operator[](size_t index) const
    {
        return m_arr[index];
    }
    
    T& operator[](size_t index)
    {
        return m_arr[index];
    }
};


int main(int argc, char *argv[]) 
{
    DynamicArray<float> myArray(5); //array of size 5
    
    std::cout<< "The type is : " << typeid(myArray).name() << "\n";
    
    //JAVA way of doing set
    myArray.set(0,7.3);
    myArray.set(3,66.76);
    
    //Operator overloading way
    myArray[1] = 18.69; //calls the operator [] defined in the class, so myArray[1] is a reference to what lives on address of myArray[1]
    myArray.print();
    
    /*
        Const Correctness
        if you set 
        const DynamicArray<float> myArray(10);
        
        and then do:
        std::cout << myArray[2] << "\n";
        
        even if you're not modifying the array, you are
        calling the [] operator on myArray
    */
    
    std::cout << "My Array CONST\n";
    const DynamicArray<float> myArrayConst(5);
    myArrayConst.print();
    // myArrayConst[1] = 10.2;
    // std::cout << "value at index 1 of myArrayConst" << myArrayConst[1];
    return 0;
}

/*
Array Constructor Called
The type is : 12DynamicArrayIfE
0 7.3
1 18.69
2 0
3 66.76
4 0
My Array CONST
Array Constructor Called
0 0
1 0
2 0
3 0
4 0
Array Destructor Called
Array Destructor Called
*/