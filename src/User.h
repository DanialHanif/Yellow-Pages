#include <iostream>
#include <vector>
#include <string>

#ifndef USER_H
#define USER_H

class User {


    protected:
        int id;
        std::string username, fullName, emailAddress, dateOfBirth, streetAddress, password, registrationDate;
        std::vector<std::string> skills;

    public:

        User();

        std::string getUsername();
        std::string getFullName();
        std::string getEmailAddress();
        std::string getDateOfBirth();
        std::string getStreetAddress();
        std::string getPassword();
        std::string getRegistrationDate();
        std::vector<std::string> getSkills();

        void signUp();
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