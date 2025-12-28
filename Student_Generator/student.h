#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <random>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


class StudentIdGen
{
private:
    int year;           //2 digits at the front
    std::string code;   //3 alphabets next to year
    int position;       //Last 4 digits

    std::string full_id; //Concatinate: year + code + position

public:
    /*int set_year() const;
    int set_position() const;
    std::string set_code() const;
    std::string set_full_id() const;*/

    StudentIdGen(); //Constructor

    int get_year() const;
    int get_position() const;
    std::string get_code() const;
    std::string get_full_id() const;    
};

class StudentName
{
public:
    enum class Ethnic 
    {
        Chinese,
        Japanese,
        Western,
        count //Used only to determine the max length of the enum
    };

    StudentName();
    Ethnic get_ethnic() const;
    std::string get_name() const;

private:
    Ethnic race;
    std::string full_name;
};

class Forte
{
private:
    std::string language;

public:
    Forte(StudentName::Ethnic); //The constructor takes the obj of StudentName
    Forte(); //Test constructor
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
};


#endif //STUDENT_H