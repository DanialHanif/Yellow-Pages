//MUHAMMAD DANIAL AIMAN BIN MOHD HANIF BI18110242

#include "User.h"
#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstddef>
#include <locale>
#include <codecvt>

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
    UserData* User::getUserData(){ return this->userData; }

	std::string User::hexEncodeInfo(std::string const& info) {

		std::ostringstream stringstream;
		for (size_t i = 0; i < info.size(); ++i) {
			int j = info[i]; //converts characters into integers
			stringstream << std::setfill('0') << std::hex << std::setw(2) << std::uppercase; //set the stringstream to fill 0s and converts integers to hexadecimals
			stringstream << j;
		}
		return stringstream.str();

	}

	std::string User::decodeInfo(std::string const& encodedInfo) {

		static const char* const hexcharacters = "0123456789ABCDEF";
		std::string decodedInfo;
		size_t len = encodedInfo.length();
		if (len & 1) {

			return decodedInfo;
		}

		decodedInfo.reserve(len / 2);
		for (size_t i = 0; i < len; i += 2) {

			char a = encodedInfo[i];
			char b = encodedInfo[i + 1];

			const char* p = std::lower_bound(hexcharacters, hexcharacters + 16, a);
			const char* q = std::lower_bound(hexcharacters, hexcharacters + 16, b);

			if (*q != b || *p != a) {
				return decodedInfo;

			}

			decodedInfo.push_back(static_cast<char>(((p - hexcharacters) << 4) | (q - hexcharacters)));

		}

		return decodedInfo;

	}

	void User::saveInfoToDatabase() {

		std::string firstpart = "{" + std::to_string(getID()) + ";" + getUsername() + ";" + getPassword() + ";" + getFullName() + ";" + getEmailAddress() + ";" + getDateOfBirth() + ";" + getStreetAddress() + ";" + getRegistrationDate() + "}";
		std::string skillpart = getSkillsStringForm();
		std::string info = firstpart + skillpart;
		std::string existing;

		std::ofstream file;
		std::ifstream infile("userDB.dat");

		while (std::getline(infile, existing)) {

			if (existing.find(decodeInfo(std::to_string(getID())), 0) != std::string::npos) {
				existing.replace(0, existing.length(), "");
				return;
			}

		}
		file.open("userDB.dat", std::ios_base::app);
		file << hexEncodeInfo(info) << std::endl;
		file.close();
		std::cout << std::endl << "User data is saved!" << std::endl;
		return;


	}


	bool User::loadInfoFromDatabase(std::string& user_pass) {

		std::string info;
		std::ifstream infile("userDB.dat");
		std::string::size_type position = 0;
		//check if user_pass matches in DB
		while (std::getline(infile, info)) {

			info = decodeInfo(info);
			position = info.find(user_pass, position);
			if (position == std::string::npos) {
				std::cout << "Invalid account details entered!" << std::endl;
				return false;
			}
			else if (info.find(user_pass) != std::string::npos) {

				//trim first part of info
				std::string::size_type endOfFirstPart = 0;
				endOfFirstPart = info.find("}", endOfFirstPart);
				std::string firstTrimmedInfo;
				firstTrimmedInfo = info.substr(1, endOfFirstPart-1);

				//trim second part of info
				std::string::size_type firstOfSecondPart = 0;
				firstOfSecondPart = info.find("[", firstOfSecondPart);
				std::string secondTrimmedInfo;
				secondTrimmedInfo = info.substr(firstOfSecondPart+1, (info.length()-firstOfSecondPart-2));

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
				finish = false;
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

					return true;
					break;

				}
				else {
				
					for (int i = 0; i < secondTrimmedParts.size(); i=i+3) {

						addSkills(secondTrimmedParts.at(i), secondTrimmedParts.at(i+1), stoi(secondTrimmedParts.at(i+2)));

					}

					return true;
					break;

				}

			}


		}

	}

	void User::generateID() { time_t currentTime = time(0);  this->userData->USER_ID = currentTime; }
	void User::setUsername(std::string username) { this->userData->USER_NAME = username; checkValidInput(userData->USER_NAME); }
    void User::setFullName(std::string fullName){ this->userData->USER_FULL_NAME = fullName; }
    void User::setEmailAddress(std::string emailAddress){ this->userData->USER_EMAIL = emailAddress; }
    void User::setDateOfBirth(std::wstring& dateOfBirth){ 
		
		static const std::wstring dateTimeFormat{ L"%d:%m:%Y" };
		std::wistringstream ss{ dateOfBirth };
		std::tm dt;
		ss >> std::get_time(&dt, dateTimeFormat.c_str());

		this->userData->USER_DOB = std::mktime(&dt);
	}
    void User::setStreetAddress(std::string streetAddress){ this->userData->USER_ADDRESS = streetAddress; }
	void User::setPassword(std::string password) { this->userData->USER_PASSWORD = password; checkValidInput(userData->USER_PASSWORD); }
    void User::setRegistrationDate(){ time_t currentTime = time(0); char* dt = ctime(&currentTime); userData->USER_REG_DATE = dt;}


	

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
    void User::deleteSkills(int& id){
	
		Skills* cur = userData->USER_SKILLS;
		Skills* prev;
		bool found = false;
		while (cur != NULL && !found ) {
			if (cur->id == id) found = true;
			else prev = cur; cur = cur->next;
		}
		if (cur == NULL) { std::cout << "No skill with the selected number is found!" << std::endl; return; }
		else if (cur->id == id) {
			if (userData->USER_SKILLS == cur) { userData->USER_SKILLS = cur->next; delete cur; }
			else { prev->next = cur->next; delete cur; }
			while (prev->next != NULL) {
				--(prev->next->id);//decrements the skill id after deletion
				prev = prev->next;
			}
		}
		else { std::cout << "No skill with the selected number is found!" << std::endl; return; }
	
	}

	void User::updateSkills(int& id, std::string name, std::string description, int level) {

		Skills* cur = userData->USER_SKILLS;
		Skills* prev;
		bool found = false;
		while (cur != NULL && !found) {
			if (cur->id == id) found = true;
			else prev = cur; cur = cur->next;
		}
		if (cur == NULL) { std::cout << "No skill with the selected number is found!" << std::endl; return;  }
		else if (cur->id == id) {
			cur->name = name; cur->description = description; cur->level = level; return;
		}

		else std::cout << "No skill with the selected number is found!" << std::endl; return;
	}

    void User::printInfo(){

		std::cout << std::endl;
		std::cout << "============ Profile Info ============" << std::endl;
		std::cout << "User ID:  " << getID() << std::endl;
        std::cout << "Full Name:  " << getFullName() << std::endl;
        std::cout << "Email Address: " << getEmailAddress() << std::endl;
        std::cout << "Date of Birth: " << getDateOfBirth() << std::endl;
        std::cout << "Street Address: " << getStreetAddress() << std::endl;
		std::cout << "Username: " << getUsername() << std::endl;
        std::cout << "Registration Date: " << getRegistrationDate() << std::endl;
		std::cout << "Skills: " << std::endl;

		Skills* cur = getUserData()->USER_SKILLS;
		while (true) {
			if (getUserData()->USER_SKILLS == NULL) { std::cout << ("No skills found!");  return; }
			else { std::cout << "\t" << cur->id << ".Name: " << cur->name << "\n \t  Description: " << cur->description << "\n \t  Level: " << cur->level << std::endl;
			
			if (cur->next == NULL) {
				std::cout << std::endl;  return;
			}
			
			else cur = cur->next;}
		}
        
		std::cout << "============ Profile Info ============" << std::endl;

    }

	void User::checkValidInput(std::string& s) {

		size_t whitelistcharacters = s.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890-_");

		if ((whitelistcharacters != std::string::npos) || s == "") {

			std::cout << "Error! Please re-enter input with valid characters! Press enter to continue." << std::endl;
			std::cout << "Re-enter input: "; std::getline(std::cin, s);
			checkValidInput(s);
		}

		else return;

	}

	
    void User::setup(){
		generateID();
        std::cout << "Fill in the details:" << std::endl;
		std::cout << "Username(Alphanumberic A-z, 0-9): "; std::getline(std::cin, userData->USER_NAME);
		checkValidInput(userData->USER_NAME);
        std::cout << "Full Name:  "; std::getline(std::cin, userData->USER_FULL_NAME);
        std::cout << "Email Address: "; std::getline(std::cin, userData->USER_EMAIL);
		std::cout << "Date of Birth (Day:Month:Year): "; std::getline(std::cin, userData->USER_DOB); std::wstring date = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(userData->USER_DOB); setDateOfBirth(date);
        std::cout << "Street Address: "; std::getline(std::cin, userData->USER_ADDRESS);
        std::cout << "Password(Alphanumberic A-z, 0-9): "; std::getline(std::cin, userData->USER_PASSWORD);
		checkValidInput(userData->USER_PASSWORD);
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

			
			saveInfoToDatabase();
		}

		else saveInfoToDatabase(); return;

    }


