# Student Profiles Generator  
## Who created this program?  
Ignatius Lim Sheng Hoong

## Why was this program created?  
I created this program to apply my C++ skills for the purpose of practice and learning.  
If you look at my codes, you may notice some minor inconsistency.  
The inconsistences are the results of me practicing on applying different solutions.  

## When did this project start and complete?
1. **START:** 17 Dec 2025
2. **Hiatus:** 19 Dec 2025 to 27 Dec 2025 *(Holiday and sick)*
3. **Porting:** 28 Dec 2025 *(Imported the codes from my old Github account due to account issue, then continue to develop the codes)*
4. **Clean-up:** 3 Jan 2026 *(Tidying is completed. README.md file is completed. Codes are committed and pushed)*
5. **COMPLETE:** 7 Jan 2026
6. **Update 1:** 7 Jan 2026 (Added feature to inform user that database file exists and asks if user wants to regenerate a new one)
7. **Update 2:** 7 Jan 2026 (Added feature to allow user to customize the number of student profiles to generate)
    
## What does this program do?  
This program will generate 100 random student profiles and save them to a file.  
Each student profile will have the following information:
1. Random name (Determined by randomly generated ethnicity)
2. Random dominant language (Influenced by ethnicity. Note that this is not the same as native languages)
3. Random student ID

Once the student profiles are generated and saved to the database file, the other parts of the program rely on the database file for their respective functions. So users can actually modify this database file to make changes to the entries according to their will.  

<u>Below are all the functions of the program:</u>
1. Generate 100 student profiles and save them to a file.
2. Read from the file and show a formatted display of the profiles on terminal.
3. Randomly pick a school representative from the 100 generated students and save the result.  
User can delete the result and re-pick a school representative randomly.
4. Delete the file containing the 100 student profile data.
5. Exit the program.  

## How does the program work?  
The program is splited into multiple modules. Each module is responsible for one or a group of related functions.  
Below are the modules and their workings:  

### <u>Student name generator</u>   
This module will randomly pick an ethnicity from a fix list of ethnicities.
Then, it will use the selected ethnicity to generate a random full name for each student profile.  
The RNG engine will randomly pick names from a long list of names and combine them into a single full name.
The module is designed to prevent the generation of duplicated names.  

Below are the ethnicities and how they influence the creation of a full name:
1. **Chinese**: There is an equal random chance that the full name is either 3 or 4 letters long.  
If the name is 3 letters long, the first name can either Chinese surname, or a Western given name, followed by a Chinese surname.  
If the name is 4 letters long, the first name must be a Western given name, followed by a Chinese surname.
In both cases, the surnames are trailed by Chinese given names.  
2. **Japanese**: The full name is always 2 letters long.  
The full name consists of a Japanese family name and a Japanese given name.
3. **Western**: The full name is always 2 letters long.  
The full name consists of a given Western given name and a Western surname.  
A student's given name may be equal to the surname.

### <u>Dominant language generator</u>  
This module will randomly pick a language that the student is best in.  
This is not the same as their native language.  
Just because a language is someone's native language does not mean it is their best language.  
Based on the ethnicity of the student, the module will randomly pick a dominant language.  

Below are the ethnicities and how they influence the selection of a dominant language:  
1. **Chinese**: Chinese: 60% chance, English: 20% chance, Japanese: 5% chance, Others: 15% chance
2. **Japanese**: Japanese: 90% chance, English: 8% chance, Others: 2% chance
3. **Western**: Equal random chance of either Chinese, English, Japanese, and Others 

"Others" consists of the following languages, which will be randomly chosen:  
*Spanish, German, France, Spanish, Latin, Greek, Irish, Polish, Swiss*  

### <u>Student ID generator</u>  
This module will randomly generate a student ID with the following format:  

**[year][code][position]**
1. The **year** is a 2-digit number randomly generated from 15 (2015) to 26 (2026)
2. The **code** is a 3-character string randomly generated from AAA to ZZZ
3. The **position** is a 4-digit number randomly generated from 0000 to 9999.  

If a duplicate student ID is generated, the position number will be re-generated until no more duplicate.

### <u>Student profiles generator</u>  
This module is the heart of the program. It triggers the previous 3 modules to generate their respective data.  
The module then combines those data into a single student profile.  
The module generates 100 of such student profiles, and then save them to a database file.  

### <u>Main menu</u>  
This module handles the user interface and some minor logics. Below are what it does:  
1. Triggers the student profiles generator.  
2. Read the database file generated, formats the data, and then displays it to the terminal screen. 
If database file is not found, prompts user to generate it by using the generate function in Main Menu. 
3. Checks if there is an existing record of a chosen school representative or not.  
    - If yes, shows the chosen school representative from the record in a fomatted display and then ask if user wanna delete the record.  
    - If no existing record, randomly chooses a school representative from the database file, then shows the result in a formatted display.  
    After that, save the student profile of the chosen school representative into a file to record it.  
4. Deletes the database file.
5. Terminates the program.

