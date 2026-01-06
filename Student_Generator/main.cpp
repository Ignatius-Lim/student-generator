#include <thread>   // for sleep_for
#include <chrono>   // for milliseconds, seconds
#include <filesystem> //For deleting file and detecting the presence of a file
#include "student.h"

void clear_screen();

//Add default values in show_screen declaration here to avoid "too few argumants" error
void show_screen(const std::string& content, bool waitForEnter = true, bool clear_display = true, 
    std::string next_action = "return to main menu...");

bool read_profiles();
void display_representative(std::string, std::string, std::string, int, bool);
bool pick_representative();
bool read_representative();
void delete_file(std::string, std::filesystem::path);
bool prompt_delete_record();

int main()
{   
    std::string stu_amount = std::to_string(Common::entries_amt);
    
    while(true)
    {  
        // Show main menu
        show_screen
        (
            "=== Main Menu ===\n"
            "1. Generate a database of " + stu_amount + " student profiles\n"
            "2. Read from database\n"
            "3. Pick a school representative\n"
            "4. Delete database\n"
            "5. Exit\n"
            "Choose an option: ", 
            false
        );

        int choice;
        std::cin >> choice;
        std::cin.ignore(); // remove leftover newline

        switch(choice)
        {
            //Generates a list of student profiles
            case 1:
                {
                    show_screen("Generating " + stu_amount + " student profiles...\n", false); 
                    //Throughout this .cpp file, delays are added to make the user interface feels more natural
                    // Delay 1 second
                    std::this_thread::sleep_for(std::chrono::seconds(1));  

                    //The constructor of StudentProfile class calls the various random generators.
                    StudentProfile profile;

                    std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
                    show_screen("Profiles generated successfully!", true, false); 
                    break;
                }

            //Reads and displays student profiles from database
            case 2:
                {
                    show_screen("Reading from database...\n", false);                    
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

    char option;
    std::cin >> option;
    std::cin.ignore(); // remove leftover newline
    option = std::tolower(static_cast<unsigned char>(option));

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

