# Make a game



## ECS Programming
ECS = Entities, Components, Systems
ECS is a software design paradigm. It can be used for non-game projects as well.

- Entity : Any object in the game (player, platform, tile, bullet etc)
- Component: properties that can attach to Entities. It's just pure data, no logic involved.
- Systems: Code/logic that drives behaviour.
    - movement
    - rendering
    - sound
    - physics

- Object Oriented Programming uses concepts of Objects and Inheritance to implement specific functionality.
- Object Oriented Design is the process of strictly using OOP in order to design the architecture of the engine and entities.
    - example
        OOP can help us manage data and code. Lets say we have an entity, say obj1 with an (x,y) cooridnate.
        Class Tile or Class Player can inherit from obj1. obj1 can be like a colour/sprite.
        Entity can be static (like colour) or dynamic (like speed). For something that needs
        to inherit from static entities and dynamic entities, now we're talking about multiple inheritance and bunch of classes.
- Same thing, but using ECS :
    - entity needs a position, we just attach position component
    - entity needs a speed, we just attach a speed component
    - Lets say we need to make a entity:Tree >> we need 
        - component:Position(float x, float y), 
        - component:Sprite(image *images[], float times[])
    - Lets say we need to make an entity:Enemy >> we need
        - component:Position(float x, float y), 
        - component:Sprite(image *images[], float times[])
        - component:AI(bool doLeft, bool doRight, bool doJump, bool doShoot)
        - component:Velocity(float x, float y)
        - component:AABB(float width, float height) #collision thru Access Aligned Bounding Box
    - Lets say we need to make a entity:Player >> we need
        - component:Position(float x, float y), 
        - component:Sprite(image *images[], float times[])
        - component:Input(bool keyLeft, bool keyRight, bool keyJump)
        - component:Velocity(float x, float y)
        - component:AABB(float width, float height) #collision thru Access Aligned Bounding Box
- This is called composition based architecture, because you're composing entities, out of shared components.
- System
    - Movement: `for (e: entities) { e.pos += e.velocity; }`
    - Collision
        ```
        for(b: bullets)
            for( e: enemies)
                if(Physics::IsCollision(b,e))
                    e.health -= b.damage
                    b.destroy();
        ```
    - Rendering System `for (e: entities) { window.draw(e.sprite, e.pos)}`

## Engine Architecture
```
Game Engine
    >Scene
        >Systems
        >EntityManager
            >Entity
                >Component
```
Game Engine has a collection of scenes(main menu, overworld map, fighting an enemy). Each scene will have its own system.

EntityManager will be factory design pattern 
- any entity created or destroyed, will be managed via the EntityManager
- entity constructor will be private, so we HAVE to go through the EntityManager
- we will manage memory efficiently, by giving instructions to the EntityManager to manage the assets across different scenes.

## Why C++ ?
- Its very widely used and supported
- Good library support
- Properly written code runs fast
- Code is highly customizable
- It's going to be around for a long time
### Gotchas
- You can end up writing unsafe code
- Gotta manage your own memory
- Syntax can be a bit confusing
- Can be hard to read code if its too customized
- Compiler/Linker error triage

### C++ Compilation Process
1. You have your source code (file.cpp)
2. All of your source code files and header files get run through the pre-processor, where your `include` , `define` etc, get processed. This is where you could get error.
3. After that, all your library pulls or definitions, get added to a massive source-code file.
4. this "pre-processor output" megafile is then run through the compiler. This is where you can get an error.
5. After compilation, you get an object file created (`file.cpp` --> `file.o`)
6. The linker then links the object files together, to create the executable binary (`file`). This is also where you can get, a linker error.

### Some housekeeping note about C++
- you don't want to compile all your files, everyime. You only want to recompile the things that you have changed.
- Linking is much faster than compiling. Generate the new object files `file.o` if there are changes is `file.cpp`
- C++ is separated into header `file.h` (declarations) files and cpp `file.cpp` (definitions) files.
- Example of declaration: `int sum(int x, int y);`
- Example of a definition : `int sum(int x, int y) { return x+y; }`
- Header files contain class declarations or definitions. It gets annoying, defining all your classes in the same file.
- Header file explainer
  - You see the class functionality at a glace, reduces cognitive load.
  - Separates the design from the implementation.
  - Headers don't change that often, so you're reducing the compile time.
  - Something to watch out for, is cyclic dependencies, which could be hard to detect. (Class A depends on Class B and Class B depends on Class A)
  - Example
    ```
    //my_class.h

        namespace N
        {
            class my_class
            {
                //declaring the function
                public:
                    void do_something();

            };
        }
    ```

    and the cpp file for this would be
    ```
    //my_class.cpp

        #include <my_class.h> // header in the local dir
        #include <iostream> // header in standard lib
        
        using namespace N;
        using namespace std;

        //defining the function
        void my_class::do_something()
        {
            cout << "do something!" << endl;
        }
    ```
    and this would be then used by
    ```
    // my_program.cpp

        #include <my_class.h>

        using namespace N;

        int main()
        {
            //create a class object
            my_class mc;

            //call our function
            mc.do_something();

            return 0;
        }
    ```
    and we get the output
    - Class example
    ```
    class Point
    {
        int m_x = 0; // private by default
        int m_y = 0; // private
    public:
        Point(int x, int y);
        int getX();
        int getY();
    };

    ```
    - Class Constructor
    ```
    Point::Point(int x, int y)
    {
        m_x = x;
        m_y = y;
    }
    ```
    This is an inefficient way of doing things, because when you call the constructor, you're assigning the m_x and m_y to 0 by default, and then spending some more time re-assigning value of x to m_x and y to m_y.
    To avoid that, you do :
    
        - // Member Initializer list
        Point::Point(int x, int y)
            : m_x(x)
            , m_y(y)
            {

            }
    You CAN set the value of const var using initializer list
    
    - Class Destructor
    ``` 
    Point::~Point()
    {
        //clean up here
    }
    ```
### C++ Memory
- Two types of memory considerations in C++ :
    - stack memory
    - heap memory
- When a program is launched, OS gives it access to some areas in memory. We can manipulate stack and heap.
- Stack and Heap are both stored on RAM, its just data storage space
- We request an amount of memory from stack or heap, and the OS gives it to the program
- The diff is in
    - size of available memory
    - the way memory is allocated
    - speed at which it is allocated (stack is faster)
    - way we request for the memory
    - stack memory is deallocated when it leaves scope
- example
    ```
    int main()
    {
        //vars
        int val = 5; // stack
        int* hval = new int; // heap
        *hval = 5;

        //arrays
        int a[5]; // stack
        int* ha = new int[5]; // heap
        ha[3] = 10;

        MyClass c(args); // stack
        MyClass *hc = new MyClass(args); //heap
    }

    ```
- Stack Memory
    - has prefefined size
    - very easy to run out of it
    - local vars without new are allocated to stack memory by default
    - program function calls and return addresses are also allocated on stack
    - it's known as static memory
    - all stack memory allocation sizes need to be known at compile time
    - memory allocation which depends on runtime variables (dynamic memory size), like taking an input from user, must be heap allocated
    - compiler knows where your var value is on the stack
    - example
    ```
    int main()
    {
        int i = 6; //goes on stack first; [6]
        int b = 10; // goes next on stack; [10 6]
        Point p(5,4); // goes next on stack; [4 5 10 6]
    } // once you reach here, your stuff gets deallocated

    ```
- Heap Memory
    - much more space available
    - allocation via `new` keyword
        
        `Type *varName = new Type;`
    - `new` under the hood just calls `malloc`
    - OS finds a contiguous chunk of memory and returns a pointer to it
    - `Pt* p = new Pt(5,4)` : on the heap, `5 -> 0x1 address`, `5 -> 0x2 address` but the address `0x1` that `p` is assigned, that's on the stack.
    - When scope ends, stack gets cleared but heap is still allocated. To clear heap, you can `delete p;` . There are other ways as well.
- C++ Pointers
    - pointer stores memory address
    - modifying the pointer var modifies the address it points to
    - to modify the value, we dereference
    - raw pointers are unsafe
    - example
    ```
    int i = 6; // local int var
    int *p; // pointer to int, undefined right now (dangerous, cuz it basically has ANY value at that address)
    p = &i; //p now has address of var i
    *p = 7; //dereference, so now i is 7

    ```
    - Need pointer for inheritance
    
        ` Base *ptr = new Derived();`
    - Pass by value vs pass by reference : modify variable passed into a function
    - Pointing to large data (since large data can't live on stack)
- C++ References
    - Safe pointers, using `&` instead of `*`
    - Its safe because a reference MUST point to existing data. Pointers can point to...anything.
    - That's why its preferred.
- Pass by Value vs Pass by Reference
    - C++ is pass by value, but we wanna use pass by reference cuz copying large data is costly.
    - We also may want to modify the value passed.
    - Passing Large Data Properly
    ```
    void machineLearn(const BigData &d);

    int main()
    {
        BigData data(args);
        machineLearn(data);
    }

    ```
    - Pass by `const` reference : whenever we pass a variable to a function that we don't want to modify, we use `const` - cuz it declares that the var can't be modified inside the function, only used.
    - Pass by reference means we're only sending a 8-byte refernce instead of that large data copy stuff in pass by val.
    - When to use `pass by value` ? when using primitives like int, cuz it faster. You don't have to dereference anything. Also, you can pass stuff like `std::shared_ptr<T>` by value.
    

