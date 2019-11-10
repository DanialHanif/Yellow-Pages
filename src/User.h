#include <iostream>
#include <vector>
#include <string>
#include "Nodes.h"

#ifndef USER_H
#define USER_H

class User {


    protected:

		UserData* userData;
		Skills* skills;
		

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
        Skills* getSkills();

        void setup();
		void setID(int);
        void setUsername(std::string);
        void setFullName(std::string);
        void setEmailAddress(std::string);
        void setDateOfBirth(std::string);
        void setStreetAddress(std::string);
        void setPassword(std::string);
        void setRegistrationDate(std::string);
        void addSkills(std::string, std::string, int);
        void deleteSkills(int&);

        void printInfo();
        

};


#endif