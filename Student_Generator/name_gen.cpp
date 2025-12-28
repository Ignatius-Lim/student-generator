#include "student.h"

std::string west_name();
std::string japanese_name();
std::string chinese_name();

std::vector<std::string> english_names = {"Mark", "Parker", "Park", "George", "Mate", "Nathan",
"Howard", "Obama", "Water", "Ally", "John", "Abraham"};

std::vector<std::string> japanese_names = {"Kasumi", "Nakasu", "Sakura", "Norihiro", 
    "Takehashi", "Takasaki", "Natsumi", "Tanjiro", "Rengoku", "Sagara", "Yoshihide", "Daiki"};

StudentName::StudentName()
{       
    /*std::random_device rd;                  
    std::mt19937 gen(rd());                  
    std::uniform_int_distribution<> dist(0, static_cast<int>(Ethnic::count) - 1);
    
    race = static_cast<Ethnic>(dist(gen));*/
    race = Ethnic::Western;

    switch(race)
    {
        case Ethnic::Chinese:
            //Do something
            break;
        case Ethnic::Japanese:
            full_name = japanese_name();
            break;
        case Ethnic::Western:
            full_name = west_name();
            break;
        default:
            std::cout << "Failed to generate Western name!" << std::endl;
            full_name = "Failure Name";
            break;
    }
}

std::string west_name()
{
    std::random_device rd;                  
    std::mt19937 gen(rd());                  
    std::uniform_int_distribution<> dist(0, english_names.size() - 1);

    std::string first_name = english_names[dist(gen)];

    std::random_device rd1;                  
    std::mt19937 gen1(rd1());                  
    std::uniform_int_distribution<> dist1(0, english_names.size() - 1);

    std::string last_name = english_names[dist1(gen1)];

    return first_name + " " + last_name;
}

std::string japanese_name()
{
    std::random_device rd;                  
    std::mt19937 gen(rd());                  
    std::uniform_int_distribution<> dist(0, japanese_names.size() - 1);

    std::string first_name = japanese_names[dist(gen)];

    std::random_device rd1;                  
    std::mt19937 gen1(rd1());                  
    std::uniform_int_distribution<> dist1(0, japanese_names.size() - 1);

    std::string last_name = japanese_names[dist1(gen1)];

    return first_name + " " + last_name;
}

StudentName::Ethnic StudentName::get_ethnic() const
{
    return race;
}

std::string StudentName::get_name() const
{
    return full_name;
}