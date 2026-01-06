//***This file contains code for random generation of a student's full name***
#include "student.h"

std::vector<std::string> chinese_surnames = { "Lim", "Tan", "Lee", "Wong", "Ng", "Chan", "Cheong", "Chew", "Chow", 
    "Chong", "Teo", "Goh", "Ong", "Low", "Lau", "Chin", "Khoo", "Yong", "Koh", "Khor", "Sim", "Ngoh", "See", 
    "Soh", "Ho", "Chua", "Chau", "Poh", "Quek", "Loh", "Ang", "Gan", "Hong", "Fong", "Lean" };

std::vector<std::string> chinese_givenNames = { "Wei", "Wai", "Ming", "Jun", "Hui", "Hwee", "Hock", "Heng", 
    "Hong", "Beng", "Boon", "Huat", "Kiat", "Keong", "Kiong", "Khoon", "Soon", "Seng", "Sheng", "Sin", "Chin", 
    "Chee", "Choon", "Chong", "Teck", "Tong", "Yong", "Yew", "Yee", "Yan", "Kai", "Kim", "Ling", "Lian", 
    "Long", "Fai", "Fatt", "Foo", "Fong", "Gan", "Guan", "Han", "Jin", "Lam", "Leong", "Meng", "Onn", 
    "Peng", "Poh", "Sam", "Tai", "Ting", "Wing", "Wan", "Hoong", "Theng", "Yi" };

std::vector<std::string> western_names = { "Mark", "Parker", "Park", "George", "Mate", "Nathan",
    "Howard", "Ally", "James", "John", "Michael", "David", "Daniel", "Matthew", 
    "Andrew", "Joseph", "Christopher", "William", "Robert", "Thomas", "Nicholas", "Benjamin", "Samuel", 
    "Anthony", "Jonathan", "Ryan", "Kevin", "Jason", "Eric", "Adam", "Justin", "Brian", "Jacob", "Ethan", 
    "Noah", "Liam", "Lucas", "Alexander", "Sebastian", "Victor", "Adrian", "Julian", "Marcus", "Leo", 
    "Max", "Paul", "Simon", "Peter", "Emma", "Emily", "Sarah", "Elizabeth", "Jessica", "Ashley", "Amanda", 
    "Jennifer", "Melissa", "Michelle", "Rebecca", "Rachel", "Hannah", "Lauren", "Natalie", "Samantha", 
    "Olivia", "Sophia", "Isabella", "Grace", "Chloe", "Abigail", "Victoria", "Anna", "Julia", "Claire", 
    "Maria", "Laura", "Alice", "Eva", "Nina", "Elena", "Clara", "Daniela", "Alex", "Sam", "Jordan", "Taylor", 
    "Jamie", "Morgan", "Cameron", "Avery" };

std::vector<std::string> japanese_familyNames = { "Sato", "Suzuki", "Takahashi", "Tanaka", 
    "Watanabe", "Ito", "Yamamoto", "Nakamura", "Kobayashi", "Kato", "Yoshida", "Yamada", "Sasaki", "Sagara",
    "Yamaguchi", "Matsumoto", "Inoue", "Kimura", "Hayashi", "Shimizu", "Yamazaki", "Mori", "Abe", "Ikeda", 
    "Hashimoto", "Ishikawa", "Nakajima", "Maeda", "Fujita", "Ogawa", "Okada", "Hasegawa", "Murakami", "Kaneko", 
    "Fujii", "Kondo", "Ishii", "Saito", "Sakai", "Endo", "Arai", "Ota", "Aoki", "Takeuchi", "Kawai", "Nishimura", 
    "Ueda", "Sugiyama", "Hirano", "Kojima", "Noguchi", "Iwasaki", "Nakagawa", "Okamoto", "Matsuda", "Fujimoto", 
    "Nakano", "Harada", "Ono", "Tamura", "Ueno", "Sugawara", "Ando", "Miyazaki", "Kuroda", "Takagi", "Morita", 
    "Ishida", "Sakurai", "Matsui", "Otsuka", "Kishi", "Hirata", "Araki", "Kawaguchi", "Uchida", "Shibata",
    "Hattori", "Komatsu", "Minami", "Kitamura", "Nishida", "Okabe", "Nagata", "Hosokawa", "Kaneda", "Shinohara", 
    "Tsuchiya", "Kawamoto", "Nomura", "Saeki", "Sakuma", "Matsubara", "Oshima", "Nagai", "Toyoda", "Nakasu"};

std::vector<std::string> japanese_givenNames = { "Haruto", "Yuto", "Sota", "Yuki", "Hayato", "Ryota", 
    "Kaito", "Ren", "Daiki", "Takumi", "Kenta", "Shota", "Riku", "Sosuke", "Kouki", "Ryo", "Taiga", 
    "Itsuki", "Sho", "Haruki", "Hinata", "Reo", "Minato", "Tsubasa", "Yuma", "Ryusei", "Hiroto", "Keita", 
    "Souta", "Kazuki", "Ryota", "Shun", "Taishi", "Yudai", "Koki", "Shoma", "Takuto", "Haruki", "Yuya", 
    "Masato", "Ren", "Itsuki", "Yoshiki", "Kaito", "Shohei", "Ryunosuke", "Daichi", "Takumi", "Ayaka", 
    "Yui", "Hina", "Sakura", "Riko", "Mei", "Yuna", "Mao", "Haruka", "Akari", "Hinata", "Miku", "Miyu", 
    "Rina", "Sara", "Kanon", "Noa", "Yuzuki", "Aoi", "Nanami", "Mao", "Yuka", "Emi", "Kaho", "Miyu", "Rika", 
    "Hana", "Saki", "Mio", "Ayane", "Riko", "Mai", "Hinata", "Yui", "Mayu", "Kasumi" };


StudentName::StudentName()
{       
    //The code below generates random numbers, then type cast it to Enum Ethnic class type & assigned to race.
    //For the max value of the RNG_engine, "count" which is Enum Ethnic class type is type casted to int.
    ethnicity = static_cast<Ethnic>(Common::RNG_engine(0, static_cast<int>(Ethnic::count) - 1));

    generate_name(ethnicity);
}

void StudentName::generate_name(StudentName::Ethnic ethnicity)
{
    switch(ethnicity)
    {
        case Ethnic::Chinese:
            full_name = chinese_name();
            break;
        case Ethnic::Japanese:
            full_name = japanese_name();
            break;
        case Ethnic::Western:
            full_name = west_name();
            break;
        default:
            std::cout << "Ethinicity not found! Out-of-bound error!" << std::endl;
            full_name = "Ethnic Failure";
            break;
    }
}

std::string StudentName::chinese_name()
{
    if(!chinese_surnames.empty() && !chinese_givenNames.empty())
    {
        int RNG_length_chance = Common::RNG_engine(1, 3); //Random probabilty a name is 3 or 4 words long

        surname = chinese_surnames[Common::RNG_engine(0, chinese_surnames.size() - 1)];
        Chi_given_name = chinese_givenNames[Common::RNG_engine(0, chinese_givenNames.size() - 1)];

        if(RNG_length_chance == 1) //For 3 word names, the probability is 1/3
        {
            //Random chance first name is either Western or Chinese surname
            int RNG_first_name = Common::RNG_engine(1, 2); 

            if(RNG_first_name == 1) //50% chance the first name is Western 
            {
                given_name = western_names[Common::RNG_engine(0, western_names.size() - 1)];

                return given_name + " " + surname + " " + Chi_given_name;
            }

            else
            {
                Chi_given_name += " " + chinese_givenNames[Common::RNG_engine(0, chinese_givenNames.size() - 1)];

                return surname + " " + Chi_given_name;
            }
        }

        else
        {
            given_name = western_names[Common::RNG_engine(0, western_names.size() - 1)];
            Chi_given_name += " " + chinese_givenNames[Common::RNG_engine(0, chinese_givenNames.size() - 1)];

            return given_name + " " + surname + " " + Chi_given_name;
        }
    }

    else
    {
        std::cout << "Chinese name list is empty!" << std::endl;
        return "Chinese name list is empty!";
    }
    
}

std::string StudentName::west_name()
{
    if (!western_names.empty())
    {
        given_name = western_names[Common::RNG_engine(0, western_names.size() - 1)];
        surname = western_names[Common::RNG_engine(0, western_names.size() - 1)];

        return given_name + " " + surname;
    }
    else
    {
        std::cout << "Western name list is empty!" << std::endl;
        return "Western name list is empty!";        
    }   
    
}

std::string StudentName::japanese_name()
{              
    if (!japanese_familyNames.empty() && !japanese_givenNames.empty())
    {
        surname = japanese_familyNames[Common::RNG_engine(0, japanese_familyNames.size() - 1)];
        given_name = japanese_givenNames[Common::RNG_engine(0, japanese_givenNames.size() - 1)];

        return surname + " " + given_name;
    }
    else
    {
        std::cout << "Japanese name list is empty!" << std::endl;
        return "Japanese name list is empty!";
    }  
  
}

StudentName::Ethnic StudentName::get_ethnic() const
{
    return ethnicity;
}

std::string StudentName::get_full_name() const
{
    return full_name;
}

std::string StudentName::get_given_name() const
{
    if (given_name.empty())
    {
        std::cout << "This name has no non-Chinese given name" << std::endl;
    }

    return given_name;
}

std::string StudentName::get_surname() const
{
    return surname;
}

std::string StudentName::get_Chi_given_name() const
{
    if (Chi_given_name.empty())
    {
        std::cout << "This name has no Chinese given name" << std::endl;
    }
    
    return Chi_given_name;
}