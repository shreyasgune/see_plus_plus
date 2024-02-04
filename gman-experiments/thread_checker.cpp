#include <iostream>
#include <thread>
#include <vector>

void threadFunction(int id)
{
    std::cout << "-------------\n";
    std::cout << "Thread ID:" << id << std::endl;
    std::cout << "Running on core " << std::this_thread::get_id() << std::endl;
    std::cout << "-------------\n";
}

int main()
{
    // telling the program how many threads to create
    const int numThreads = 4;

    // vector to hold the created threads
    // std::vector<std::thread> threads;

    // create the threads and run the threads function
    for (int i = 0; i < numThreads; ++i)
    {
        /* 
        emplace_back is a C++ function to add an element to the vector.
        creates a new element directly in place within the container, avoiding needless
        copying or moving
        */
        // threads.emplace_back(threadFunction,i);

        // for sequential run
        std::thread myThread(threadFunction, i);
        myThread.join();
    }

    // joining the threads and waiting for their completion
    // for (auto& thread : threads)
    // {
    //     thread.join();
    // }
    return 0;
}

// to compile and run: g++ -std=c++17 -o ./binaries/thread_checker thread_checker.cpp && ./binaries/thread_checker


/*
Output



*/