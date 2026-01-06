#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <random>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//========================= Below are class declarations ================================

class Common
{
public:
    //The static keyword below ensures that any function can access the member function without having to create an obj
    static int RNG_engine(int, int); 

    //.txt file names, used for file read, write, and delete. 
    static const std::string database_file; 
    static const std::string representative_file;

    // The number of student profile entries to be created
    static const int entries_amt;

};

class StudentIdGen
{
private:
    int year;           //2 digits at the front
    std::string code;   //3 alphabets next to year
    int position;       //Last 4 digits

    std::string full_id; //Concatinate: year + code + position

public:
    StudentIdGen(); //Constructor

    //Getters
    int get_year() const;
    int get_position() const;
    std::string get_code() const;
    std::string get_full_id() const;   
    
    //Functions
    void generate_position();
    void generate_full_id();
};

class StudentName
{
public:
    StudentName();    

    enum class Ethnic 
        {
            Chinese,
            Japanese,
            Western,
            count //Used only to determine the max length of the enum
        };       

    //Getters
    Ethnic get_ethnic() const;
    std::string get_full_name() const;
    std::string get_given_name() const;
    std::string get_surname() const;
    std::string get_Chi_given_name() const;

    //Functions
    void generate_name(StudentName::Ethnic);
    std::string west_name();
    std::string japanese_name();
    std::string chinese_name();

private:
    Ethnic ethnicity;
    std::string full_name;
    std::string surname;
    std::string given_name;
    std::string Chi_given_name;
};

class Forte
{
private:
    std::string language;

public:
    Forte(StudentName::Ethnic); //The constructor takes an obj of StudentName and access its ethnicity
    std::string get_language() const; 
};

class StudentProfile
{
private:
    std::vector<StudentName> name;
    std::vector<StudentIdGen> id_gen;
    std::vector<Forte> forte;

public:
    StudentProfile();
    
    void add_student_id();
    void add_forte(StudentName::Ethnic ethnic);    
    void add_name();

    bool id_exists(const std::string& fullID) const;
    bool name_exists(const std::string& fullName) const;   
};

#endif //STUDENT_H