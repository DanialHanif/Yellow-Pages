#include <iostream>
#include <vector>
#include <string>
#include <ctime>

#ifndef USER_H
#define USER_H

class User {

	//skill with descriptions
	struct Skills {

		int id;
		std::string name;
		std::string description;
		int level;
		Skills* next;

	};

	//userdata structure
	struct UserData {

		int id;
		std::string username;
		std::string fullName;
		std::string emailAddress;
		std::string dateOfBirth;
		std::string streetAddress;
		std::string password;
		std::string	registrationDate;
		Skills* skills;
	};



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
        UserData getSkills();

        void setup();
		void setID(int id);
        void setUsername(std::string);
        void setFullName(std::string);
        void setEmailAddress(std::string);
        void setDateOfBirth(std::string);
        void setStreetAddress(std::string);
        void setPassword(std::string);
        void setRegistrationDate(std::string);
        void addSkills(std::string);
        void deleteSkills(int n);

        void printInfo();
        

};


#endif