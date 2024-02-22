#include <iostream>
#include <vector>
// using namespace std;
// if we don't want to prepend all the commands from the std library, we just use the line above and C++ then assumes we're using std library. BUT, as a practice, is better to be more verbose




int main( int argc, char * argv[])
{
    std::cout << "Hello There" << std::endl;
    // we add the endl so that we don't get newline issues between different OS

    std::string first = "general";
    std::string last = "kenobi";
    
    // we can add strings
    std::string name = first + " " + last;

    std::cout<< name << std::endl;

    //vector stuff

    //declare a vector
    std::vector<int> vec;
    vec.push_back(66);
    vec.push_back(10);

    // NOTE: unlike other languages, if you try to access vec[45] or something out of array bounds, you will NOT get an error. You will get whatever value exists in memory for that address location.
    
    // you can access the vector value using vec[0]..etc 

    // using size_t because its safer to use. vec.size() is unsigned. You could run into issues comparing signed and unsigned stuff. siz_t is a long, unsigned int and it will adhere to 32 bits on a x86 and 64 bits on x64 
    for (size_t i=0; i < vec.size(); i++)
    {
        std::cout<< vec[i] << "\n";
    }

    // range based for loop
    // use auto because it will consider the type of whatever the vector data type is
    // warning : if you just use auto a, it will copy everything in the vector to a. To avoid this, use references.
    for (auto& a : vec)
    {
      std::cout<< a <<"\n";   
    }



    return 0;
}