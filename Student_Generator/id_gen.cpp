#include <iomanip>
#include <sstream>
#include "student.h"

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

StudentIdGen::StudentIdGen() //Constructor
{
    //Generate random year
    std::random_device rd1;                  // non-deterministic seed
    std::mt19937 gen1(rd1());                  // Mersenne Twister RNG
    std::uniform_int_distribution<> dist1(15, 26); // inclusive range

    year = dist1(gen1);
    std::string year_str = std::to_string(year); //The 'year' private variable converted to string                                                 
    
    //Generate random code of 3 chars
    std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";    
    int length = 3;

    std::random_device rd2;
    std::mt19937 gen2(rd2());
    std::uniform_int_distribution<> dist2(0, chars.size() - 1);
    
    for (int i = 0; i < length; ++i) {
        code += chars[dist2(gen2)]; //The 'code' private variable is the string containing alphabets
    }

    //Generate random position
    std::random_device rd3;                  
    std::mt19937 gen3(rd3());                  
    std::uniform_int_distribution<> dist3(0, 9999); 

    position = dist3(gen3); //The 'post' private variable contains the position number 

    std::ostringstream oss;
    oss << std::setw(4) << std::setfill('0') << position;
    std::string post = oss.str(); //'post' is string version of 'position'

    //Concatinate all
    full_id = year_str + code + post;    
}