// RAII
#include <iostream>

void print(int &i)
{
    std::cout<< &i << " " << i << " " << sizeof(i) << "\n";
}

class IntArray
{
    size_t m_size;
    int* m_arr;
    
public:
    //constructor
    IntArray(size_t size)
        : m_size(size)
        , m_arr(new int[size]) //sets the default vals to 0
    {
        std::cout << "Array Constructor Called\n";
    }
    
    //destrctor
    ~IntArray() 
    {
        delete [] m_arr;
        std::cout << "Array Destructor Called\n";
    }
    
    
    int get(size_t index) const
    {
        return m_arr[index];
    }
    
    int set(size_t index, int val)
    {
        m_arr[index] = val;
    }
    
    void print() const
    {
        for (size_t i=0; i<m_size ; i++)
        {
            std::cout << i << " " << m_arr[i] << "\n";
        }
    }
};


int main(int argc, char *argv[]) 
{
    IntArray myArray(5); //array of size 5
    
    myArray.set(0,7);
    myArray.set(3,66);
    
    myArray.print();
    return 0;
}

/*
Array Constructor Called
0 7
1 0
2 0
3 66
4 0
Array Destructor Called
*/