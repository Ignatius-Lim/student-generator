#include <thread>   // for sleep_for
#include <chrono>   // for milliseconds, seconds
#include <filesystem> //For deleting file and detecting the presence of a file
#include <cctype> //For detection of valid digits
#include "student.h"

//============================== Display functions =============================
void clear_screen();
//Add default values in show_screen declaration here to avoid "too few argumants" error
void show_screen(const std::string& content, bool waitForEnter = true, bool clear_display = true, 
    std::string next_action = "return to main menu...");

//=============================== Prompt functions =========
void prompt_generate_database();
bool prompt_delete_record();

//============================= Read and pick functions =========================
bool read_profiles();
void display_representative(std::string, std::string, std::string, int, bool);
bool pick_representative();
bool read_representative();
char read_single_char(const std::string&);

//======================================= Misc ===================================
void initiate_generator(int);
void delete_file(std::string, std::filesystem::path);


//================================== Global variables =============================
int const DEFAULT_AMT = 100; //The default amount of profiles to generate


int main()
{     
    while(true)
    {  
        // Show main menu
        show_screen
        (
            "=== Main Menu ===\n"
            "1. Generate a database of student profiles\n"
            "2. Read from database\n"
            "3. Pick a school representative\n"
            "4. Delete database\n"
            "5. Exit\n"
            "Choose an option: ", 
            false
        );

        int choice;              
        
        //If cin failbit is set, due to user inputting non-numerical character
        if(!(std::cin >> choice))
        {
            std::cin.clear(); // reset fail state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Clears the stream

            show_screen("Please provide valid input!");
            continue; // restart menu loop
        }

        std::cin.ignore(); // remove leftover newline  

        switch(choice)
        {
            //Generates a list of student profiles
            case 1:
                {
                    if (std::filesystem::exists(Common::database_file))
                    {                        
                        show_screen("There is an existing database.\n"
                            "Are you sure you want to generate a new database?\n"
                            "Existing database will be overwritten.(Y/N):\n", false);                        
                        
                        bool is_invalid_input;

                        do
                        {                   
                            is_invalid_input = false;                            

                            char regen = std::tolower(static_cast<unsigned char>(read_single_char("Enter Y or N: ")));                            

                            switch(regen)
                            {
                                case 'y':
                                show_screen("You have chosen to regenerate the database.\n"
                                    "Existing database will be overwritten.", true, true, "continue...");
                                prompt_generate_database();
                                break; 

                                case 'n':
                                    show_screen("You have chosen not to regenerate the database.");
                                    break;

                                default:
                                    std::cout << "INVALID INPUT! Please enter Y or N only!" << std::endl;
                                    is_invalid_input = true;
                                    break;
                            }
                        } while (is_invalid_input);                      

                    }
                    else
                    {
                        prompt_generate_database();
                    }                  
                
                    break;
                }

            //Reads and displays student profiles from database
            case 2:
                {
                    show_screen("Reading from database...\n", false);
                    //Throughout this .cpp file, delays are added to make the user interface feels more natural
                    // Delay 0.5 second                    
                    std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
                    
                    if (std::filesystem::exists(Common::database_file))
                    {
                        if(!read_profiles())
                            show_screen("Error opening database file. Please debug program!", true, false);
                        else
                            show_screen("Student profiles loaded succesfully!", true, false);
                    } 
                    else
                    {
                        show_screen("No student profiles found! Please generate student profiles first!", true, false);
                    }                 

                    break;
                }

            //Pick a school representative from the student profiles database
            case 3:
                {
                    show_screen("Picking a new school representative...", false);
                    std::this_thread::sleep_for(std::chrono::milliseconds(500)); 

                    if (std::filesystem::exists(Common::representative_file)) 
                    {
                        if(!read_representative())
                            show_screen("Error opening representative record file. Please debug program!", true, false);
                        else
                        {                                                        
                            show_screen("Let's all congratulate the new school representative!", true, false, "continue...");
                                                        
                            clear_screen();

                            while(prompt_delete_record())
                            {
                                //This while-loop body is intentionally left blank.
                                //The while condition will be true as long as the user input is invalid.
                            }
                                                       
                        }
                    } 
                    else 
                    {
                        if(!pick_representative())
                            show_screen("No student profiles found! "
                                "Please generate student profiles first!", true, false);
                        else
                            show_screen("Let's all congratulate the new school representative!", true, false);
                    }                 

                    break;
                }

                
            //Deletes student profiles database
            case 4:
                {
                    delete_file("Deleting database file...", Common::database_file);
                    break;
                }

            //Exits the program
            case 5:
                clear_screen();
                std::cout << "Exiting..." << std::endl;                        
                return 0;

            default:
                show_screen("Please provide valid input!");
                break;
        }
    }  
        
    return 0;
}

// Clears the terminal 
void clear_screen() 
{
    //std::cout << "\033[2J\033[1;1H"; // Hide previous contents & move cursor to top-left.
    system("clear"); //Compared to the above, this actually clears the screen.
}

//From the function declaration at the top of main.cpp, by default waitForEnter and clear_display are true.
void show_screen(const std::string& content, bool waitForEnter, bool clear_display, std::string next_action) 
{
    if(clear_display)
    {
        clear_screen();  
    }    
                 
    std::cout << content << std::endl;
    if (waitForEnter) 
    {
        // Delay 1 second
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        
        std::cout << "\nPress ENTER to " << next_action << std::endl;
        
        //Clear everything the user has typed up to pressing Enter (which is actually a \n).
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

char read_single_char(const std::string& literal) 
{
    while (true) 
    {
        if(!literal.empty())
            std::cout << literal << std::endl;
        
        std::string line;
        std::getline(std::cin, line);

        std::cout << std::endl;

        if (line.size() == 1) //If single character, return that character
            return line[0];

        std::cout << "Invalid input. Please enter exactly one character! " << std::endl;

        if(literal.empty())
            std::cout << "Try again: " << std::endl;

    }
}

void prompt_generate_database()
{    
    show_screen
    (
        "Do you want to change the number of student profiles to generate?\n"
        "(Default is 100 student profiles)\n\n"
        "Yes(Y): Set a custom number of student profiles to generate\n"
        "No(N): Use the default setting\n",
        false
    ); 

    bool is_invalid_input;

    do
    {
        is_invalid_input = false;        

        char option = std::tolower(static_cast<unsigned char>(read_single_char("Enter Y or N: ")));        

        switch(option)
        {
            //Custom setting
            case 'y':            
                {                
                    show_screen("Please input the number of student profiles you would like to generate:", false);

                    int input;

                    while (true)
                    {                       

                        if(!(std::cin >> input))
                        {
                            std::cin.clear(); // reset fail state
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Clears the stream
                            std::cout << std::endl;

                            std::cout << "Invalid input. Digits only!" << std::endl;
                            std::cout << "Enter digits only: ";
                            continue; // restart menu loop
                        }
                        else
                        {
                            std::cin.ignore(); // remove leftover newline
                            std::cout << std::endl;
                            break;
                        }
                        
                    }

                    Common::entries_amt = input;                

                    initiate_generator(Common::entries_amt);
                    break;
                }

            //Default setting
            case 'n':
                {
                    Common::entries_amt = DEFAULT_AMT;
                    initiate_generator(Common::entries_amt);
                    break;
                }

            default:
                std::cout << "INVALID INPUT! Please enter Y or N only!" << std::endl;
                is_invalid_input = true;
                break;           
        }
    } while (is_invalid_input); 
}

//Starts the generation of student profiles
void initiate_generator(int amt)
{
    show_screen("Generating " + std::to_string(amt) + " student profiles...\n", false); 
    std::this_thread::sleep_for(std::chrono::seconds(1));  

    //The constructor of StudentProfile class calls the various random generators.
    StudentProfile profile;

    std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
    show_screen(std::to_string(amt) + " profiles generated successfully!", true, false);
}

//Read student profiles from the database
bool read_profiles()
{
    std::string str;
    std::ifstream inFile;

    inFile.open(Common::database_file);

    if(inFile.fail())
    {
        std::cout << std::endl << "Couldn't access database!" << std::endl;
        return false;
    }

    else
    {
        //"while (!inFile.eof())" becomes false only after a read fail, not at read fail, 
        //so it is not a good one to use for controling read loop. 
        //Use the below one instead. It becomes false at read fail due to EOF.
        while (std::getline(inFile, str)) 
        {           
            std::cout << "Name:              " << str << std::endl;

            getline(inFile, str);
            std::cout << "Dominant language: " << str << std::endl;

            getline(inFile, str);
            std::cout << "Student ID:        " << str << std::endl;

            getline(inFile, str);
            std::cout << str << std::endl;
        }
        inFile.close();
        std::cout << "File read successfully!" << std::endl;
        return true;
    }
}

void display_representative(std::string name, std::string lang, std::string id, int yr, bool no_record = true)
{
    if(!no_record)
    {
        std::cout << "\nYou have previously picked a school representative." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }     
    
    std::cout << "The school representative chosen is ";
        if (no_record)
            std::this_thread::sleep_for(std::chrono::seconds(1)); 
        
        std::cout << name << "!\n" << std::endl;

        if (no_record)
            std::this_thread::sleep_for(std::chrono::seconds(2)); 
        
        std::cout << "Congratulation to " << name << " for being selected!" << std::endl;

        std::cout << "Enrolled in this school in the year " << yr << ", " << name
        << "'s student ID is " << id << "." << std::endl;

        std::cout << "The language " << name << " is best at is " << lang << "." << std::endl;

        std::cout << name << " is very passionate about " << lang << " language.\n" << std::endl;
}

bool pick_representative()
{
    std::vector<std::string> stu_name, dominant_lang, stu_ID;
    std::string str; 

    std::ifstream inFile;
    inFile.open(Common::database_file);

    if(inFile.fail())
    {
        std::cout << std::endl << "Couldn't access database!" << std::endl;
        return false;
    }
    else
    {
        while(std::getline(inFile, str))
        {            
            stu_name.push_back(str);

            std::getline(inFile, str);
            dominant_lang.push_back(str);

            std::getline(inFile, str);
            stu_ID.push_back(str);

            std::getline(inFile, str); //Consumes blank space
        }

        inFile.close();

        //Randomly choose a student representative
        int picker = Common::RNG_engine(0, stu_name.size() - 1);
        
        //Extract first 2 chars as substring, convert to int, and add 2000 to it
        int year = 2000 + stoi(stu_ID[picker].substr(0,2)); 

        //Save result to file
        std::ofstream outFile;
        outFile.open(Common::representative_file);

        if(outFile.fail())
        {
            std::cout << std::endl << "Couldn't write representative info to file!" << std::endl;
        }
        else
        {
            outFile << stu_name[picker] << std::endl;
            outFile << dominant_lang[picker] << std::endl;
            outFile << stu_ID[picker] << std::endl;
            outFile << year << std::endl;
        }
        outFile.close();

        display_representative(stu_name[picker], dominant_lang[picker], stu_ID[picker], year);

        return true;
    }    
}

bool read_representative()
{
    std::string stu_name, dominant_lang, stu_ID, str; 
    int year;
    
    std::ifstream inFile;
    inFile.open(Common::representative_file);
    
    if(inFile.fail())
    {
        std::cout << std::endl << "Couldn't access saved representative data!" << std::endl;
        return false;
    }
    else
    {
        std::getline(inFile, str);
        stu_name = str;

        std::getline(inFile, str);
        dominant_lang = str;

        std::getline(inFile, str);
        stu_ID = str;

        std::getline(inFile, str);
        year = stoi(str);

        inFile.close();

        display_representative(stu_name, dominant_lang, stu_ID, year, false);

        return true;
    }

}

bool prompt_delete_record()
{    
    std::cout << "Do you want to delete existing school representative record? (Y/N):" << std::endl;

    char option = std::tolower(static_cast<unsigned char>(read_single_char("")));

    switch(option)
    {
        case 'y':
            delete_file("Deleting school representative record...", Common::representative_file);
            break;

        case 'n':
            show_screen("You have chosen not to delete the record.", true, false);
            break;

        default:
            std::cout << "INVALID INPUT! Please enter Y or N only!" << std::endl;
            return true;            
    }
    return false;
}

void delete_file(std::string literal, std::filesystem::path file)
{
    show_screen(literal, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
        
    try 
    {
        if (std::filesystem::remove(file)) 
        {                            
            show_screen("File deleted successfully.", true, false);
        } 
        else 
        {                            
            show_screen("File does not exist.", true, false);
        }
    } 
    catch (const std::filesystem::filesystem_error& e)                     
    {
        
        //string literal [const char*] and e.what() [const char*] can't concatinate.
        //Therefore, need to convert "Error: " string literal to std::string object.
        //Because string object can concatinate with const char*
        std::string str = std::string("Error: ") + e.what();

        show_screen(str, true, false);
    }
}

