#include "User.h"

    User::User(){

        this->id = 0;
        this->username = "";
        this->fullName = "";
        this->emailAddress = "";
        this->dateOfBirth = "";
        this->streetAddress = "";
        this->password = "";
        this->registrationDate = "";
        this->skills;

    }

    std::string User::getUsername(){ return username; }
    std::string User::getFullName(){ return fullName; }
    std::string User::getEmailAddress(){ return emailAddress; }
    std::string User::getDateOfBirth(){ return dateOfBirth; }
    std::string User::getStreetAddress(){ return streetAddress; }
    std::string User::getPassword(){ return password; }
    std::string User::getRegistrationDate(){ return registrationDate; }
    std::vector<std::string> User::getSkills(){ return skills; }

    void User::setUsername(std::string username){ this-> username = username; }
    void User::setFullName(std::string fullName){ this-> fullName = fullName; }
    void User::setEmailAddress(std::string emailAddress){ this-> emailAddress = emailAddress; }
    void User::setDateOfBirth(std::string dateOfBirth){ this-> dateOfBirth = dateOfBirth; }
    void User::setStreetAddress(std::string streetAddress){ this-> streetAddress = streetAddress; }
    void User::setPassword(std::string password){ this-> password = password; }
    void User::setRegistrationDate(std::string registrationDate){ this-> registrationDate = registrationDate; }
    void User::addSkills(std::string skill){ this-> skills.push_back(skill); }
    void User::deleteSkills(int n){ this-> skills.erase(skills.begin() + n); }

    void User::printInfo(){

        std::cout << "Username: " << getUsername() << std::endl;
        std::cout << "Full Name:  " << getFullName() << std::endl;
        std::cout << "Email Address: " << getEmailAddress() << std::endl;
        std::cout << "Date of Birth: " << getDateOfBirth() << std::endl;
        std::cout << "Street Address: " << getStreetAddress() << std::endl;
        std::cout << "Password: " << getPassword() << std::endl;
        std::cout << "Registration Date: " << getRegistrationDate() << std::endl;
        std::cout << "Skills: "; 

        int n = 1;
        for(std::vector<std::string>::const_iterator i = skills.begin(); i != skills.end(); ++i){

            std::cout << n << ". " << *i <<std::endl;
            n++;

        }
        

    }

    void User::signUp(){

        std::cout << "Fill in the details:" << std::endl;
        std::cout << "Username: "; std::cin >> username; std::cin.ignore();
        std::cout << "Full Name:  "; std::getline(std::cin, fullName);
        std::cout << "Email Address: "; std::cin >> emailAddress; std::cin.ignore();
        std::cout << "Date of Birth: "; std::getline(std::cin, dateOfBirth);
        std::cout << "Street Address: "; std::getline(std::cin, streetAddress);
        std::cout << "Password: "; std::cin >> password; std::cin.ignore();
        std::cout << "Registration Date: "; std::getline(std::cin, registrationDate);
        std::cout << "Skills: "; 

        for(int i = 0; i < 5; ++i){

            std::string s;
            std::cout << i+1 << ": "; std::cin >> s; addSkills(s);
        }
    }

