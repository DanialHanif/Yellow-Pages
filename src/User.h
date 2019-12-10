//MUHAMMAD DANIAL AIMAN BIN MOHD HANIF BI18110242

#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <cstddef>
#include <locale>
#include <codecvt>
#include "Nodes.h"

#ifndef USER_H
#define USER_H

class User {


    protected:

        UserList* usersList;
        UserList* headerUserList;
        UserList* currentUserList;
        UserData* currentUser;

    public:

        User();

		/*int getID();
        std::string getUsername();
        std::string getFullName();
        std::string getEmailAddress();
        std::string getDateOfBirth();
        std::string getStreetAddress();
        std::string getPassword();
        std::string getRegistrationDate();
		std::string hexEncodeInfo(std::string const&);
		std::string decodeInfo(std::string const&);
		std::string getSkillsStringForm();*/
		UserData* getUserData();
		UserList* getUsersList();

		bool login();
        void setup();
		time_t generateID();
        /*void setUsername(std::string);
        void setFullName(std::string);
        void setEmailAddress(std::string);
        void setDateOfBirth(std::wstring&);
        void setStreetAddress(std::string);
        void setPassword(std::string);*/
        std::string registrationDate();
        void addUserFromDBToList(std::vector<std::string>);
        void addUserToList(UserData*);
        /*void addPostings(std::string, std::string, int);
        void deleteSkills(int&);
		void updateSkills(int&, std::string, std::string, int);*/
		void saveUserInfoToDatabase();
		void loadUserInfoFromDatabaseToList();
		void checkValidInput(std::string&);
		void checkIfUserExist(std::string&);
        void printInfo();
        

};


#endif