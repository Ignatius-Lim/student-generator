//***This file handles the random selection of a forte language for a student***
#include "student.h"
std::string western();
std::string chinese();
std::string japanese();

std::vector<std::string> others = {"Spanish", "German", "France", "Spanish", "Latin", "Greek", "Irish", "Polish", "Swiss"};

Forte::Forte(StudentName::Ethnic ethnic) //Handles the generation of the dominant language of the student
{
        
    switch(ethnic)
    {
        case StudentName::Ethnic::Chinese:
            language = chinese();
            break;

        case StudentName::Ethnic::Japanese:
            language = japanese();
            break;

        case StudentName::Ethnic::Western:
            language = western();
            break;

        default:
            std::cout << "Invalid ethnicity: Language generation failed!" << std::endl;
            language = "Not available";
    }
}

std::string western()
{    
    std::vector<std::string> west;
    
    for(auto oth: others) //Copy the contents of others to west
    {
        west.push_back(oth);
    }

    west.push_back("English"); 
    west.push_back("Chinese");  
    west.push_back("Japanese");    

    return west[Common::RNG_engine(0, west.size() - 1)]; //Returns a random language
}

std::string chinese()
{    
    int RNG_chance = Common::RNG_engine(0, 100);

    if(RNG_chance >= 0 && RNG_chance <= 59) //Chinese: 60% chance
    {
        return "Chinese";
    }
    else if(RNG_chance >= 60 && RNG_chance <= 79) //English: 20%
    {
        return "English";
    }
    else if(RNG_chance >= 80 && RNG_chance <= 84) //Japanese: 5%
    {
        return "Japanese";
    }
    else //Others: 15%
    {
        return others[Common::RNG_engine(0, others.size()-1)];
    }
}

std::string japanese()
{    
    int RNG_chance = Common::RNG_engine(0, 100);

    if(RNG_chance >= 0 && RNG_chance <= 89) //Japanese: 90% chance
    {
        return "Japanese";
    }
    else if(RNG_chance >= 90 && RNG_chance <= 97) //English: 8% chance
    {
        return "English";
    }
    else  //Others: 2% chance
    {       
        return others[Common::RNG_engine(0, others.size()-1)];
    }
}

std::string Forte::get_language() const
{
    return language;
}