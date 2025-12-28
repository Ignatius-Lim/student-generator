#include "student.h"
#define DEBUG //Comment this out when not debugging

void StudentProfile::add_student_id()
{
     id_gen.push_back(StudentIdGen()); //Constructor creates a temp obj of the class 

    //To prove that the vector is working
    /*std::cout << id_gen[0].get_year() << std::endl;
    std::cout << id_gen[0].get_code() << std::endl;
    std::cout << id_gen[0].get_position() << std::endl;*/    
}

void StudentProfile::add_forte(StudentName::Ethnic ethnic)
{
    forte.push_back(Forte(ethnic));
}

void StudentProfile::add_name()
{
    name.push_back(StudentName());
}

StudentProfile::StudentProfile() //Constructor
{        
    add_name();
    add_forte(name[0].get_ethnic());
    add_student_id();
    
    #ifdef DEBUG
    std::cout << name[0].get_name() << std::endl;
    std::cout << forte[0].get_language() << std::endl;
    std::cout << id_gen[0].get_full_id() << std::endl << std::endl;    
    #endif //DEBUG
}

//TODO: Handles the writing of all data to database.txt file,
//either in the student_profile class, or a seperate class