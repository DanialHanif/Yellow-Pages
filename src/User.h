//MUHAMMAD DANIAL AIMAN BIN MOHD HANIF BI18110242

#include <iostream>
#include <vector>
#include <string>
#include "Nodes.h"

#ifndef USER_H
#define USER_H

class User {


    protected:

		UserData* userData;
		

    public:

        User();

		int getID();
        std::string getUsername();
        std::string getFullName();
        std::string getEmailAddress();
        std::string getDateOfBirth();
        std::string getStreetAddress();
        std::string getPassword();
        std::string getRegistrationDate();
		std::string hexEncodeInfo(std::string const&);
		std::string decodeInfo(std::string const&);
		std::string getSkillsStringForm();
        Skills* getSkills();
		UserData* getUserData();

        void setup();
		void generateID();
        void setUsername(std::string);
        void setFullName(std::string);
        void setEmailAddress(std::string);
        void setDateOfBirth(std::wstring&);
        void setStreetAddress(std::string);
        void setPassword(std::string);
        void setRegistrationDate();
        void addSkills(std::string, std::string, int);
        void deleteSkills(int&);
		void updateSkills(int&, std::string, std::string, int);
		void saveInfoToDatabase();
		bool loadInfoFromDatabase(std::string&);
		void checkValidInput(std::string&);
        void printInfo();
        

};


#endif