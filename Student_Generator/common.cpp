//***This file contains codes that are common among some source files***

#include "student.h"

//.txt file names, used for file read, write, and delete. 
const std::string Common::database_file = "profiles.txt";
const std::string Common::representative_file = "representative.txt";

// The number of student profile entries to be created
const int Common::entries_amt = 100;


int Common::RNG_engine(int min, int max)
{
    //The static keywords mean that the codes will only be run once, which is when the first time the function is called.

    /*Running those two line of codes below everytime the function is called is resource unwise because 
    std::mt19937 generates [2^(19937) - 1] sequence of random numbers, very long indeed.
    Everytime dist(gen) is called, it returns the next number in the [2^(19937) - 1] sequence.*/

    static std::random_device rd;                   // non-deterministic seed                  
    static std::mt19937 gen(rd());                  // Mersenne Twister RNG

    std::uniform_int_distribution<> dist(min, max); // inclusive range
    return dist(gen);
}

