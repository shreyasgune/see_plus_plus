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
    ```
    
    ```