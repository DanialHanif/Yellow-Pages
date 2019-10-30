#include "User.h"

    User::User(){

		this->userData = NULL;
		this->userData->skills = NULL;

    }

	int User::getID() { return this->userData->id; }
    std::string User::getUsername(){ return this->userData->username; }
    std::string User::getFullName(){ return this->userData->fullName; }
    std::string User::getEmailAddress(){ return this->userData->emailAddress; }
    std::string User::getDateOfBirth(){ return this->->dateOfBirth; }
    std::string User::getStreetAddress(){ return this->userData->streetAddress; }
    std::string User::getPassword(){ return this->userData->password; }
    std::string User::getRegistrationDate(){ return this->userData->registrationDate; }
    UserData User::getSkills(){ return this->userData->skills; }

	void User::setID(int id) { this->userData->id = id; }
    void User::setUsername(std::string username){ this->userData->username = username; }
    void User::setFullName(std::string fullName){ this->userData->fullName = fullName; }
    void User::setEmailAddress(std::string emailAddress){ this->userData->emailAddress = emailAddress; }
    void User::setDateOfBirth(std::string dateOfBirth){ this->userData->dateOfBirth = dateOfBirth; }
    void User::setStreetAddress(std::string streetAddress){ this->userData->streetAddress = streetAddress; }
    void User::setPassword(std::string password){ this->userData->password = password; }
    void User::setRegistrationDate(std::string registrationDate){ this->userData->registrationDate = registrationDate; }
    void User::addSkills(std::string name, std::string description, int level){
		
		Skills* newSkill = new Skills;
		newSkill->id = 0;
		newSkill->name = name;
		newSkill->description = description;
		newSkill->level = level;
		newSkill->next = NULL;
	
		Skills* cur = userData->skills;
		while (cur) {
			//check if first skill is empty
			if (userData->skills == NULL) userData->skills = newSkill; newSkill->id = (cur->id)+1; return;
			else cur = cur->next;
			//check if there is nexc skill
			if (cur->next == NULL) cur->next = newSkill; newSkill->id = (cur->id) + 1; return;
			cur = cur->next;
		}
	
	}
    void User::deleteSkills(int& id){
	
		Skills* cur = userData->skills;
		Skills* prev;
		bool found = false;
		while (cur != NULL && !found ) {
			if (cur->id == id) found = true;
			else prev = cur; cur = cur->next;
		}
		if (cur == NULL) cout << "No skill with the selected number is found!" << std::endl;
		else if (cur->id == id) {
			if (userData->skills == cur) userData->skills = cur->next; delete cur;
			else prev->next = cur->next; delete cur;
		}
		else cout << "No skill with the selected number is found!" << std::endl;
	
	}

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

