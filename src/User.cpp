#include "User.h"
#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>

    User::User(){

		this->userData = new UserData;
		this->userData->USER_ADDRESS = "";
		this->userData->USER_DOB = "";
		this->userData->USER_EMAIL = "";
		this->userData->USER_FULL_NAME = "";
		this->userData->USER_ID = 0;
		this->userData->USER_NAME = "";
		this->userData->USER_PASSWORD = "";
		this->userData->USER_REG_DATE = "";
		this->userData->USER_SKILLS = NULL;


    }

	int User::getID() { return this->userData->USER_ID; }
    std::string User::getUsername(){ return this->userData->USER_NAME; }
    std::string User::getFullName(){ return this->userData->USER_FULL_NAME; }
    std::string User::getEmailAddress(){ return this->userData->USER_EMAIL; }
    std::string User::getDateOfBirth(){ return this->userData->USER_DOB; }
    std::string User::getStreetAddress(){ return this->userData->USER_ADDRESS; }
    std::string User::getPassword(){ return this->userData->USER_PASSWORD; }
    std::string User::getRegistrationDate(){ return this->userData->USER_REG_DATE; }
    std::string User::getSkillsStringForm(){
	
		Skills* cur = userData->USER_SKILLS;
		std::ostringstream skillsstring;
		skillsstring << "[";
		size_t i = 0;
		while (true) {
			if (userData->USER_SKILLS == NULL) { return "[]"; }
			else {
				skillsstring << cur->name + ";" + cur->description + ";" + std::to_string(cur->level);

				if (cur->next == NULL) {
					skillsstring << "]";
					return skillsstring.str();
				}

				else {
					skillsstring << ";"; cur = cur->next;
				}
			}
		}
	
	
	}
    Skills* User::getSkills(){ return this->userData->USER_SKILLS; }

	std::string User::hexEncodeInfo(std::string const& info) {

		std::ostringstream stringstream;
		for (size_t i = 0; i < info.size(); ++i) {
			int j = info[i]; //converts characters into integers
			stringstream << std::setfill('0') << std::hex << std::setw(2) << std::uppercase; //set the stringstream to fill 0s and converts integers to hexadecimals
			stringstream << j;
		}
		return stringstream.str();

	}

	void User::saveInfoToDatabase() {

		std::string firstpart = "{" + std::to_string(getID()) + ";" + getUsername() + ";" + getPassword() + ";" + getFullName() + ";" + getEmailAddress() + ";" + getDateOfBirth() + ";" + getStreetAddress() + ";" + getRegistrationDate() + ";" + "}";
		std::string skillpart = getSkillsStringForm();
		std::string info = firstpart + skillpart;

		std::ofstream file;
		file.open("userDB.dat");
		file << hexEncodeInfo(info) << std::endl;
		file.close();
		std::cout << "User data is saved!" << std::endl;
		return;


	}

	void User::loadInfoFromDatabase(std::string& user_pass) {

		std::string info;
		std::ifstream infile("userDB.dat");
		std::string::size_type position = 0;
		//check if user_pass matches in DB
		while (std::getline(infile, info)) {

			position = info.find(user_pass, position);
			if (position == std::string::npos && !std::cin) {
				std::cout << "Invalid account details entered!" << std::endl;
				return;
			}
			else if (position > 0 && position < std::string::npos) {

				//trim first part of info
				std::string::size_type endOfFirstPart;
				endOfFirstPart = info.find("}", endOfFirstPart);
				std::string firstTrimmedInfo;
				firstTrimmedInfo = info.substr(1, endOfFirstPart);

				//trim second part of info
				std::string::size_type firstOfSecondPart;
				firstOfSecondPart = info.find("[", firstOfSecondPart);
				std::string secondTrimmedInfo;
				secondTrimmedInfo = info.substr(firstOfSecondPart, info.length() - 2);

				bool finish = false;
				position = 0;
				std::vector<std::string> firstTrimmedParts, secondTrimmedParts;
				//parse first part
				while (!finish) {

					std::string::size_type start = position;
					position = firstTrimmedInfo.find(";", position);
					if (position == std::string::npos) {
						position = firstTrimmedInfo.length();
						finish = true;
					}
					firstTrimmedParts.push_back(firstTrimmedInfo.substr(start, position - start));
					position++;

				}

				position = 0;
				//parse second part
				while (!finish) {

					std::string::size_type start = position;
					position = secondTrimmedInfo.find(";", position);
					if (position == std::string::npos) {
						position = secondTrimmedInfo.length();
						finish = true;
					}
					secondTrimmedParts.push_back(secondTrimmedInfo.substr(start, position - start));
					position++;

				}

				if ((firstTrimmedParts.size() == 8)) {
				
					userData->USER_ID = stoi(firstTrimmedParts.at(0));
					userData->USER_NAME = firstTrimmedParts.at(1);
					userData->USER_PASSWORD = firstTrimmedParts.at(2);
					userData->USER_FULL_NAME = firstTrimmedParts.at(3);
					userData->USER_EMAIL = firstTrimmedParts.at(4);
					userData->USER_DOB = firstTrimmedParts.at(5);
					userData->USER_ADDRESS = firstTrimmedParts.at(6);
					userData->USER_REG_DATE = firstTrimmedParts.at(7);
				
				}

				if ((secondTrimmedParts.size() <= 1)) {

					return;

				}
				else {
				
					int i = 0;
					while (true) {

						addSkills(secondTrimmedParts.at(i), secondTrimmedParts.at(i + 1), stoi(secondTrimmedParts.at(i + 2)));
						i++;//todo

					}

				}

			}

		}


	}

	void User::setID(int USER_ID) { this->userData->USER_ID = USER_ID; }
    void User::setUsername(std::string username){ this->userData->USER_NAME = username; }
    void User::setFullName(std::string fullName){ this->userData->USER_FULL_NAME = fullName; }
    void User::setEmailAddress(std::string emailAddress){ this->userData->USER_EMAIL = emailAddress; }
    void User::setDateOfBirth(std::string dateOfBirth){ this->userData->USER_DOB = dateOfBirth; }
    void User::setStreetAddress(std::string streetAddress){ this->userData->USER_ADDRESS = streetAddress; }
    void User::setPassword(std::string password){ this->userData->USER_PASSWORD = password; }
    void User::setRegistrationDate(){ time_t currentTime = time(0); char* dt = ctime(&currentTime); userData->USER_REG_DATE = dt;}
	
	void User::addSkills(std::string name, std::string description, int level){

		Skills* newSkill = new Skills;
		newSkill->id = 0;
		newSkill->name = name;
		newSkill->description = description;
		newSkill->level = level;
		newSkill->next = NULL;
	
		Skills* cur = userData->USER_SKILLS;
		while (true) {
			//check if first skill is empty
			if (cur == NULL) { userData->USER_SKILLS = newSkill; newSkill->id = 1; return; }
			else if (cur->next == NULL) {  cur->next = newSkill; newSkill->id = (cur->id) + 1; return; }//check if there is next skill
			
			else cur = cur->next;
		}
	
	}

	void checkSkillsFields(std::string& n, std::string& d, int& l) {
		if ((n.empty() == true) || (d.empty() == true) || ((l > 5) || (l < 0))) {
			std::cout << "Input Error! Please enter valid input!"; 	std::cin.ignore();
			std::cout << "Skill name: "; std::getline(std::cin, n); std::cin.ignore();
			std::cout << "Skill description: "; std::getline(std::cin, d);
			std::cout << "Skill level(1-5): "; std::cin >> l;

			checkSkillsFields(n, d, l);
		}

		else {

			return;
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

		std::cout << std::endl;
		std::cout << "============ Profile Info ============" << std::endl;
        std::cout << "Full Name:  " << getFullName() << std::endl;
        std::cout << "Email Address: " << getEmailAddress() << std::endl;
        std::cout << "Date of Birth: " << getDateOfBirth() << std::endl;
        std::cout << "Street Address: " << getStreetAddress() << std::endl;
		std::cout << "Username: " << getUsername() << std::endl;
        std::cout << "Registration Date: " << getRegistrationDate() << std::endl;
		std::cout << "Skills: " << std::endl;

		Skills* cur = userData->USER_SKILLS;
		while (true) {
			if (userData->USER_SKILLS == NULL) { std::cout << ("No skills found!");  return; }
			else { std::cout << cur->id << ". " << cur->name << "\t Description:" << cur->description << "\t" << "Level: " << cur->level << std::endl;
			
			if (cur->next == NULL) {
				std::cout << std::endl;  return;
			}
			
			else cur = cur->next;}
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
        
		setRegistrationDate();

        std::cout << "Please add a Skill: "; 

		std::string name, description;
		int level = 0;
		
			
		std::cout << "Skill name: ";
		std::getline(std::cin, name);
		std::cout << "Skill description: ";
		std::getline(std::cin, description);
		std::cout << "Skill level(1-5): ";
		std::cin >> std::noskipws >> level;

		if (!name.empty() || !description.empty() || level == !0) {

			checkSkillsFields(name, description, level);

			addSkills(name, description, level);
		}

		else return;

    }


