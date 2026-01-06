//***This file contains codes to randomly generate student ID***
#include <iomanip>
#include <sstream>
#include "student.h"

StudentIdGen::StudentIdGen() //Constructor
{
    //Generate random year
    year = Common::RNG_engine(15, 26);                                                   
    
    //Generate random code of 3 chars
    std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";    
    int length = 3;
    
    //The 'code' private variable is a string containing alphabets
    for (int i = 0; i < length; ++i) {
        code += chars[Common::RNG_engine(0, chars.size() - 1)]; 
    }

   generate_position();    
   generate_full_id();
}

void StudentIdGen::generate_position()
{
    //Generate random position
    position = Common::RNG_engine(0, 9999);  
}

void StudentIdGen::generate_full_id()
{
    //Below code change the position to String and make it 4 digits long
    std::ostringstream oss;
    oss << std::setw(4) << std::setfill('0') << position; //The position number will always be 4 digits
    std::string post = oss.str(); //'post' is string version of 'position' 
    
    full_id = std::to_string(year) + code + post;
}

int StudentIdGen::get_year() const
{
    return year;
}

int StudentIdGen::get_position() const
{
    return position;
}

std::string StudentIdGen::get_code() const
{
    return code;
}

std::string StudentIdGen::get_full_id() const
{
    return full_id;
}