#include "User.h"

    User::User(){

		this->userData = NULL;
		this->skills = NULL;

    }

	int User::getID() { return this->userData->USER_ID; }
    std::string User::getUsername(){ return this->userData->USER_NAME; }
    std::string User::getFullName(){ return this->userData->USER_FULL_NAME; }
    std::string User::getEmailAddress(){ return this->userData->USER_EMAIL; }
    std::string User::getDateOfBirth(){ return this->userData->USER_DOB; }
    std::string User::getStreetAddress(){ return this->userData->USER_ADDRESS; }
    std::string User::getPassword(){ return this->userData->USER_PASSWORD; }
    std::string User::getRegistrationDate(){ return this->userData->USER_REG_DATE; }
    Skills* User::getSkills(){ return this->userData->USER_SKILLS; }

	void User::setID(int USER_ID) { this->userData->USER_ID = USER_ID; }
    void User::setUsername(std::string username){ this->userData->USER_NAME = username; }
    void User::setFullName(std::string fullName){ this->userData->USER_FULL_NAME = fullName; }
    void User::setEmailAddress(std::string emailAddress){ this->userData->USER_EMAIL = emailAddress; }
    void User::setDateOfBirth(std::string dateOfBirth){ this->userData->USER_DOB = dateOfBirth; }
    void User::setStreetAddress(std::string streetAddress){ this->userData->USER_ADDRESS = streetAddress; }
    void User::setPassword(std::string password){ this->userData->USER_PASSWORD = password; }
    void User::setRegistrationDate(std::string registrationDate){ this->userData->USER_REG_DATE = registrationDate; }
    void User::addSkills(std::string name, std::string description, int level){
		
	void checkSkillsFields(std::string * &n, std::string * &d, int*& l);

		Skills* newSkill = new Skills;
		newSkill->id = 0;
		newSkill->name = name;
		newSkill->description = description;
		newSkill->level = level;
		newSkill->next = NULL;
	
		Skills* cur = userData->USER_SKILLS;
		while (cur) {
			//check if first skill is empty
			if (userData->USER_SKILLS == NULL) { userData->USER_SKILLS = newSkill; newSkill->id = (cur->id) + 1; return; }
			else { cur = cur->next; }
			//check if there is next skill
			if (cur->next == NULL) { cur->next = newSkill; newSkill->id = (cur->id) + 1; return; }
			cur = cur->next;
		}
	
	}
    void User::deleteSkills(int& id){
	
		Skills* cur = userData->USER_SKILLS;
		Skills* prev;
		bool found = false;
		while (cur != NULL && !found ) {
			if (cur->id == id) found = true;
			else prev = cur; cur = cur->next;
		}
		if (cur == NULL) { std::cout << "No skill with the selected number is found!" << std::endl; }
		else if (cur->id == id) {
			if (userData->USER_SKILLS == cur) { userData->USER_SKILLS = cur->next; delete cur; }
			else { prev->next = cur->next; delete cur; }
			while (prev->next != NULL) {
				--(prev->next->id);//decrements the skill id after deletion
				prev = prev->next;
			}
		}
		else { std::cout << "No skill with the selected number is found!" << std::endl; }
	
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

		Skills* cur = getSkills();
		while (cur) {
			if (cur == NULL) return;
			else cur = cur->next; std::cout << cur->id << ". " << cur->name << "\t" << "Level: " << cur->level << "\t" << cur->description << std::endl;
		}
        

    }

	void checkSkillsFields(std::string*& n, std::string*& d, int*& l) {
		if ((n->empty() == true) || (d->empty() == true) || ((*l > 5) || (*l < 0))) {
			std::cout << "Input Error! Please enter valid input!";
			std::getline(std::cin, *n);
			std::getline(std::cin, *d);
			std::cin >> *l;
			checkSkillsFields(n, d, l);
		}

		else {
			
			return;
		}
	}

    void User::setup(){

        std::cout << "Fill in the details:" << std::endl;
        std::cout << "Username: "; std::cin >> userData->USER_NAME; std::cin.ignore();
        std::cout << "Full Name:  "; std::getline(std::cin, userData->USER_FULL_NAME);
        std::cout << "Email Address: "; std::cin >> userData->USER_EMAIL; std::cin.ignore();
        std::cout << "Date of Birth: "; std::getline(std::cin, userData->USER_DOB);
        std::cout << "Street Address: "; std::getline(std::cin, userData->USER_ADDRESS);
        std::cout << "Password: "; std::cin >> userData->USER_PASSWORD; std::cin.ignore();
        std::cout << "Registration Date: "; std::getline(std::cin, userData->USER_REG_DATE);
        std::cout << "Please add a Skill: "; 

		std::string *name, *description;
		int* level;
		name = new std::string;
		description = new std::string;
		level = new int;
			
		std::cout << "Skill name: ";
		std::getline(std::cin, *name);
		std::cout << "Skill description: ";
		std::getline(std::cin, *description);
		std::cout << "Skill level: ";
		std::cin >> *level;

		checkSkillsFields(name, description, level);


    }


