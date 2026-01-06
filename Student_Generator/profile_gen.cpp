//***This file handles the random generation of student profiles***

#include "student.h"
//#define DEBUG //Comment this out when not debugging


StudentProfile::StudentProfile() //Constructor
{        
    std::ofstream outFile;

    outFile.open(Common::database_file);

    if (outFile.fail())
        std::cout << std::endl << "Couldn't write to file!" << std::endl;
    else
    {
        //Generates pre-defined amount of random entries of student profiles and write them to file
        for(int i = 0; i<Common::entries_amt; i++)
        {
            add_name();
            add_forte(name[i].get_ethnic());
            add_student_id();

            //Saves student profile info to file
            outFile << name[i].get_full_name() << std::endl;
            outFile << forte[i].get_language() << std::endl;
            outFile << id_gen[i].get_full_id() << std::endl << std::endl;
            
            #ifdef DEBUG
            std::cout << name[i].get_full_name() << std::endl;
            std::cout << forte[i].get_language() << std::endl;
            std::cout << id_gen[i].get_full_id() << std::endl << std::endl;    
            #endif //DEBUG
        }  
        outFile.close();
        std::cout << "Database created & written successfully!" << std::endl;
    }
}

//Detects duplicate Student ID
bool StudentProfile::id_exists(const std::string& fullID) const
{
    for (const auto& idg : id_gen)
        if (idg.get_full_id() == fullID) //loop through id_gen[i].get_full_id() to check for duplicate
            return true;
    return false;
}

void StudentProfile::add_student_id()
{
    StudentIdGen newID; //This will generate the full ID once.
    
    //Below code will keep regenerating position value until no duplicate when compared to the id_gen vector
    while (id_exists(newID.get_full_id()))
    {
        newID.generate_position();
        newID.generate_full_id();
    } 

    id_gen.push_back(newID);   
}

void StudentProfile::add_forte(StudentName::Ethnic ethnic)
{
    //Calls the Forte class constructor which will create a temporary new Forte object.
    //Then push the Forte object to the forte vector.
    forte.push_back(Forte(ethnic)); 
}

//Detects duplicate Student Name
bool StudentProfile::name_exists(const std::string& fullName) const
{
    for (const auto& n : name)
        if (n.get_full_name() == fullName)
            return true;
    return false;
}

void StudentProfile::add_name()
{
    StudentName newName;

    while (name_exists(newName.get_full_name()))
    {
        newName.generate_name(newName.get_ethnic()); //Reuse the generated ethnicity to generate a new full name
    }
    
    name.push_back(newName);
}

