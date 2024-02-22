#include <iostream>
#include <vector>
#include <fstream>

class Student
{
    std::string m_first = "First";
    std::string m_last  = "Last";
    int         m_id    = 0;
    float       m_avg   = 0;

public:
    //default constructor
    Student() {}

    //non-default constructor
    Student(std::string first, std::string last, int id, float avg)
        : m_first(first)
        , m_last(last)
        , m_id(id)
        , m_avg(avg)
    {}

    //public functions
    int getAvg() const
    {
        return m_avg;
    }

    int getID() const
    {
        return m_id;
    }

    std::string getFirst() const
    {
        return m_first;
    }

    std::string getLast() const
    {
        return m_last;
    }

    void print() const
    {
        std::cout << m_first << " " << m_last << " ";
        std::cout << m_id << " " << m_avg << std::endl;
    }
};

class Course
{
    std::string m_name = "Course";
    std::vector<Student> m_student;
public:
        Course() {}
        Course(const std::string& name)
            : m_name(name)
        {}

        void addStudent(const Student& s)
        {
            m_student.push_back(s);
        }

        // since c++ is pass by value, to avoid copying the whole vector, we use a reference
        // const at beginning means whatever we're returning, cannot be changed, say m_student
        // const at the end means that the function getStudents() will NOT change the class.
        const std::vector<Student>& getStudents() const
        {
            return m_student;
        }

        
        //load student info from a file
        void loadFromFile(const std::string& filename)
        {
            std::ifstream fin(filename);
            //read all string tokens from file and print them on the screen
            std::string first, last;
            int id;
            float avg;
            while(fin >> first) //while I have a valid first line character
            {
                fin >> last >> id >> avg; //next line adds it, next line, auto converts to int , next line, auto converts to float

                addStudent
                (
                    Student(first, last, id, avg)
                );
            }

        }

        void print() const
        {
            for (const auto& s : m_student)
            {
                s.print();
            }
        }

};

int main(int argc, char * argv[])
{
    // create object 
    Student s1;
    const Student s2("General", "Kenobi", 1, 6.66);
    Student s3("General", "Grevious", 2, 3.14);

    // if you have a const object [say, const Student s4("x","y",17,34.1)], you NEED to declare the calling function as const as well, to ensure that the calling function is not changing anything, [say, void print() const {}]. Its called const correctness: any place where you have a function that is not changing the internals of a class, make it const.
    
    Course jedi101("JEDI 101");
    jedi101.addStudent(s2);
    jedi101.addStudent(s3);
    jedi101.addStudent
    (
        Student("Qui-Gon", "Jinn", 13, 8.65)
    );
    jedi101.print();

    //from File
    std::cout<< "\nFROM FILE" << std::endl;
    Course jedi102("JEDI 102");
    jedi102.loadFromFile("studentfile.txt");
    jedi102.print();

    return 0;
}