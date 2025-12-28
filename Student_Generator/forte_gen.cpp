#include "student.h"
std::string western();
std::string chinese();
std::string japanese();

std::vector<std::string> others = {"Spanish", 
"German", "France", "Spanish", "Latin", "Greek", "Irish", "Polish", "Swiss"};

std::string Forte::get_language() const
{
    return language;
}

Forte::Forte(StudentName::Ethnic ethnic)
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

/*Forte::Forte()
{
    int race = 2; //Play around with this number to test
    
    switch(race)
    {
        case 0:
            language = chinese();
            break;

        case 1:
            language = japanese();
            break;

        case 2:
            language = western();
            break;

        default:
            std::cout << "Invalid ethnicity: Language generation failed!" << std::endl;
            language = "Not available";
    }    
}*/

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
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, west.size() - 1);

    return west[dist(gen)]; //Returns a random language
}

std::string chinese()
{    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 100);

    if(dist(gen) >= 0 && dist(gen) <= 59) //Chinese: 60% chance
    {
        return "Chinese";
    }
    else if(dist(gen) >= 60 && dist(gen) <= 79) //English: 20%
    {
        return "English";
    }
    else if(dist(gen) >= 80 && dist(gen) <= 84) //Japanese: 5%
    {
        return "Japanese";
    }
    else //Others: 15%
    {
        std::uniform_int_distribution<> dist(0, others.size()-1);
        return others[dist(gen)];
    }
}

std::string japanese()
{    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 100);

    if(dist(gen) >= 0 && dist(gen) <= 89) //Japanese: 90% chance
    {
        return "Japanese";
    }
    else if(dist(gen) >= 90 && dist(gen) <= 97) //English: 8% chance
    {
        return "English";
    }
    else  //Others: 2% chance
    {
        std::uniform_int_distribution<> dist(0, others.size()-1);
        return others[dist(gen)];
    }

}