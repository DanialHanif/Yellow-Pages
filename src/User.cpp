//MUHAMMAD DANIAL AIMAN BIN MOHD HANIF BI18110242

#include "User.h"
#include "Payment.h"


    User::User(){

		this->usersList = new UserList;
		this->usersList->user = NULL;
		this->usersList->next = NULL;
		this->headerUserList = usersList;
		this->currentUserList = usersList;
		loadUserInfoFromDatabaseToList();

    }

	/*int User::getID() { return this->userData->USER_ID; }
    std::string User::getUsername(){ return this->userData->USER_NAME; }
    std::string User::getFullName(){ return this->userData->USER_FULL_NAME; }
    std::string User::getEmailAddress(){ return this->userData->USER_EMAIL; }
    std::string User::getDateOfBirth(){ return this->userData->USER_DOB; }
    std::string User::getStreetAddress(){ return this->userData->USER_ADDRESS; }
    std::string User::getPassword(){ return this->userData->USER_PASSWORD; }
    std::string User::getRegistrationDate(){ return this->userData->USER_REG_DATE; }*/

    UserData* User::getUserData(){ return this->currentUser; }
    UserList* User::getUsersList(){ return this->headerUserList; }


	/*std::string User::hexEncodeInfo(std::string const& info) {

		std::ostringstream stringstream;
		for (size_t i = 0; i < info.size(); ++i) {
			int j = info[i]; //converts characters into integers
			stringstream << std::setfill('0') << std::hex << std::setw(2) << std::uppercase; //set the stringstream to fill 0s and converts integers to hexadecimals
			stringstream << j;
		}
		return stringstream.str();

	}*/

	/*std::string User::decodeInfo(std::string const& encodedInfo) {

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

	}*/

	void User::saveUserInfoToDatabase() {

		currentUserList = headerUserList;

		std::string firstpart;
		std::string info;
		std::ofstream file;
		file.open("userDB.dat");


		while (true) {
		
			firstpart = "{" + std::to_string(currentUserList->user->USER_ID) + ";" + std::to_string(currentUserList->user->isAdmin) + ";" + std::to_string(currentUserList->user->isEmployer) + ";"
						+ currentUserList->user->USER_NAME + ";" + currentUserList->user->USER_PASSWORD + ";" 
						+ currentUserList->user->USER_FULL_NAME + ";" + currentUserList->user->USER_EMAIL + ";" 
						+ currentUserList->user->USER_DOB + ";" + currentUserList->user->USER_ADDRESS + ";" 
						+ currentUserList->user->USER_REG_DATE + "}";

			info = firstpart;
			
			file << info << std::endl;
			
			if (currentUserList->next != NULL) {
				currentUserList = currentUserList->next;
			}
			else break;
			
		
		}
		
		file.close();
		std::cout << std::endl << "User data is saved!" << std::endl;
	}

	bool User::login() {
	
		std::string username;
		std::string password;
		std::cout << "Enter username: ";
		std::cin >> username;
		std::cout << "Enter password: ";
		std::cin >> password;

		if (headerUserList->user == NULL) {
			std::cout << "No users in database. Please create one.";
			return false;
		}
		else {

			currentUserList = headerUserList;
			while (currentUserList->user != NULL) {

				if (currentUserList->user->USER_NAME == username) {
					if (currentUserList->user->USER_PASSWORD == password) {
						currentUser = currentUserList->user;
						return true;
					}
					else {
						std::cout << "Invalid password!" << std::endl;
						return false;
					}
				}
				else {

					if (currentUserList->next != NULL) {
						currentUserList = currentUserList->next;
					}
					else {
						std::cout << "No user found!" << std::endl;
						return false;
					}
				}
			}
		}
	}

	void User::loadUserInfoFromDatabaseToList() {

		std::string info;
		std::ifstream userDatabase("userDB.dat");
		std::string::size_type position = 0;
		
		/*if (userDatabase.fail()) {
			std::cout << "User Database is not found!" << std::endl;
			std::cout << "Creating new user database..." << std::endl;
			std::ofstream outputFile;
			outputFile.open("userDB.dat", std::ios_base::app);
			outputFile.close();
		}*/

		while (std::getline(userDatabase, info)) {

			//info = decodeInfo(info);
			//position = info.rfind(user_pass, info.length());
			/*if (position == std::string::npos) {
				std::cout << "Invalid account details entered!" << std::endl;
				return false;
			}*/
			//if (info.rfind(user_pass) != std::string::npos) {
			if (info.size() > 0) {
				//trim first part of info that contains user information
				std::string::size_type endOfFirstPart = 0;
				endOfFirstPart = info.find("}", endOfFirstPart);
				std::string firstTrimmedInfo;
				firstTrimmedInfo = info.substr(1, endOfFirstPart - 1);

				//trim second part of info that contains postings
				std::string::size_type firstOfSecondPart = 0;
				firstOfSecondPart = info.find("[", firstOfSecondPart);
				std::string secondTrimmedInfo;
				secondTrimmedInfo = info.substr(firstOfSecondPart + 1, (info.length() - firstOfSecondPart - 2));

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
				/*while (!finish) {

					std::string::size_type start = position;
					position = secondTrimmedInfo.find(";", position);
					if (position == std::string::npos) {
						position = secondTrimmedInfo.length();
						finish = true;
					}
					secondTrimmedParts.push_back(secondTrimmedInfo.substr(start, position - start));
					position++;

				}*/

				if ((firstTrimmedParts.size() == 10)) {

					addUserFromDBToList(firstTrimmedParts);


				}

				/*if ((secondTrimmedParts.size() <= 1)) {

					return;
					break;

				}*/
				//else {

				//	for (int i = 0; i < secondTrimmedParts.size(); i = i + 3) {

				//		//addPostings(secondTrimmedParts.at(i), secondTrimmedParts.at(i + 1), stoi(secondTrimmedParts.at(i + 2)));

				//	}

				//}

			}
			else {
				return;
			}


			}



		}


	time_t User::generateID() { time_t currentTime = time(0); return currentTime; }
	
	std::string User::registrationDate() { 
			time_t currentTime = time(0);
			std::string dt = ctime(&currentTime);
			dt = dt.substr(0, (dt.length() - 1));
			return dt; 
		}
	/*void User::setUsername(std::string username) { this->usersList->user->USER_NAME = username; checkValidInput(usersList->user->USER_NAME); }
    void User::setFullName(std::string fullName){ this->usersList->user->USER_FULL_NAME = fullName; }
    void User::setEmailAddress(std::string emailAddress){ this->usersList->user->USER_EMAIL = emailAddress; }
    void User::setDateOfBirth(std::wstring& dateOfBirth){ 
		
		static const std::wstring dateTimeFormat{ L"%d:%m:%Y" };
		std::wistringstream ss{ dateOfBirth };
		std::tm dt;
		ss >> std::get_time(&dt, dateTimeFormat.c_str());

		this->usersList->user->USER_DOB = std::mktime(&dt);
	}
    void User::setStreetAddress(std::string streetAddress){ this->usersList->user->USER_ADDRESS = streetAddress; }
	void User::setPassword(std::string password) { this->usersList->user->USER_PASSWORD = password; checkValidInput(usersList->user->USER_PASSWORD); }*/



	/*void checkSkillsFields(std::string& n, std::string& d, int& l) {
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
	}*/

	void User::addUserFromDBToList(std::vector<std::string> userInfo) {

		UserList* newUser = new UserList;
		newUser->user = new UserData;
		newUser->user->USER_ID = stoi(userInfo.at(0));
		newUser->user->isAdmin = ("1" == userInfo.at(1));
		newUser->user->isEmployer = ("1" == userInfo.at(2));
		newUser->user->isGuest = false;
		newUser->user->isLoggedIn = false;
		newUser->user->USER_NAME = userInfo.at(3);
		newUser->user->USER_PASSWORD = userInfo.at(4);
		newUser->user->USER_FULL_NAME = userInfo.at(5);
		newUser->user->USER_EMAIL = userInfo.at(6);
		newUser->user->USER_DOB = userInfo.at(7);
		newUser->user->USER_ADDRESS = userInfo.at(8);
		newUser->user->USER_REG_DATE = userInfo.at(9);
		newUser->next = NULL;

		if (headerUserList->user == NULL) {//first load
			delete usersList;
			usersList = newUser;
			headerUserList = usersList;
			currentUserList = headerUserList;
		}

		else {

			UserList* current = headerUserList;
			while (current) {
				if (current->next == NULL) { current->next = newUser; return; }

				else current = current->next;
			}
		}
	}

	void User::addUserToList(UserData* user) {



	}

	/*void User::addPostings(std::string name, std::string description, int level){

		Skills* newSkill = new Skills;
		newSkill->SKILL_ID = 0;
		newSkill->SKILL_NAME = name;
		newSkill->SKILL_DESCRIPTION = description;
		newSkill->SKILL_LEVEL = level;
		newSkill->next = NULL;
	
		Skills* cur = data->USER_SKILLS;
		while (true) {
			//check if first skill is empty
			if (cur == NULL) { data->USER_SKILLS = newSkill; newSkill->SKILL_ID = 1; return; }
			else if (cur->next == NULL) {  cur->next = newSkill; newSkill->SKILL_ID = (cur->SKILL_ID) + 1; return; }//check if there is next skill
			
			else cur = cur->next;
		}
	
	}*/
    /*void User::deleteSkills(int& id){
	
		Skills* cur = data->USER_SKILLS;
		Skills* prev;
		bool found = false;
		while (cur != NULL && !found ) {
			if (cur->SKILL_ID == id) found = true;
			else prev = cur; cur = cur->next;
		}
		if (cur == NULL) { std::cout << "No skill with the selected number is found!" << std::endl; return; }
		else if (cur->SKILL_ID == id) {
			if (data->USER_SKILLS == cur) { data->USER_SKILLS = cur->next; delete cur; }
			else { prev->next = cur->next; delete cur; }
			while (prev->next != NULL) {
				--(prev->next->SKILL_ID);//decrements the skill id after deletion
				prev = prev->next;
			}
		}
		else { std::cout << "No skill with the selected number is found!" << std::endl; return; }
	
	}*/

	/*void User::updateSkills(int& id, std::string name, std::string description, int level) {

		Skills* cur = data->USER_SKILLS;
		Skills* prev;
		bool found = false;
		while (cur != NULL && !found) {
			if (cur->SKILL_ID == id) found = true;
			else prev = cur; cur = cur->next;
		}
		if (cur == NULL) { std::cout << "No skill with the selected number is found!" << std::endl; return;  }
		else if (cur->SKILL_ID == id) {
			cur->SKILL_NAME = name; cur->SKILL_DESCRIPTION = description; cur->SKILL_LEVEL = level; return;
		}

		else std::cout << "No skill with the selected number is found!" << std::endl; return;
	}*/

    void User::printInfo(){

		std::cout << std::endl;
		std::cout << "============ Profile Info ============" << std::endl;
		std::cout << "User ID:  " << currentUser->USER_ID << std::endl;
        std::cout << "Full Name:  " << currentUser->USER_FULL_NAME << std::endl;
        std::cout << "Email Address: " << currentUser->USER_EMAIL << std::endl;
        std::cout << "Date of Birth: " << currentUser->USER_DOB << std::endl;
        std::cout << "Street Address: " << currentUser->USER_ADDRESS << std::endl;
		std::cout << "Username: " << currentUser->USER_NAME << std::endl;
        std::cout << "Registration Date: " << currentUser->USER_REG_DATE << std::endl;   
		std::cout << "============ Profile Info ============" << std::endl << std::endl;

    }

	void User::checkValidInput(std::string& s) {

		while (true) {
		
			size_t whitelistcharacters = s.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890-_");
			
			if ((whitelistcharacters != std::string::npos) || s == "") {

				std::cout << "Error! Please re-enter input with valid characters!" << std::endl;
				std::cin.ignore();
				system("pause");
				std::cout << "Re-enter input: "; std::getline(std::cin, s);
			}

			else return;
		}

	}

	void User::checkIfUserExist(std::string& s) {

		UserList* current;
		current = headerUserList;
		if (current->user != NULL) {
			while (true) {
				if (current->user->USER_NAME == s) {
					std::cout << "Username already exists! Please enter a different username!" << std::endl;
					system("pause");
					std::cout << "Re-enter username: "; std::getline(std::cin, s);
					checkValidInput(s);
				}
				else if (current->next == NULL) {

					return;
				}

				else {
					current = current->next;
				}
			}
		}
		else return;
	}

	//void User::
	
    void User::setup(){

		std::string employerState;
		std::cin.clear();
		std::cin.ignore();
		//if users are loaded from DB, we iterate till last list
		if (currentUserList->user != NULL){
			
			while (currentUserList->next) {

				currentUserList = currentUserList->next;

			}
		}

		UserList* newUser = new UserList;
		newUser->user = new UserData;
		newUser->next = NULL;
		newUser->user->isAdmin = false;
		newUser->user->USER_ID = generateID();
		std::cout << "Fill in the details:" << std::endl;
		std::cout << "Are you an employer?[y/N]: ";

		while (true) {
			std::getline(std::cin,employerState);
			if (employerState == "y" || employerState == "Y") { 
				std::cout << "Employer requires a subscription to be registered. Do you want to proceed?[y/N]";
				
				employerState = "";
				std::cin >> employerState;
				if (employerState == "y" || employerState == "Y") {
					Payment payMenu;
					if (payMenu.result() == true) {
						newUser->user->isEmployer = 1; 
						std::cin.ignore();
						break;
					}
					else {
						std::cout << "Payment is not successful. Returning back to menu.";
						break;
					}
				}
				
			}
			else if (employerState == "n" || employerState == "N") { newUser->user->isEmployer = 0; break; }
			else { std::cout << "Invalid input! Please re-enter: "; }
		}

		std::cout << "Username(Alphanumberic A-z, 0-9): "; std::getline(std::cin, newUser->user->USER_NAME);
		checkValidInput(newUser->user->USER_NAME);
		checkIfUserExist(newUser->user->USER_NAME);
		std::cout << "Full Name:  "; std::getline(std::cin, newUser->user->USER_FULL_NAME);
		std::cout << "Email Address: "; std::getline(std::cin, newUser->user->USER_EMAIL);
		std::cout << "Date of Birth (Day/Month/Year eg. 23/08/1998): "; std::getline(std::cin, newUser->user->USER_DOB); /*std::wstring date = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(usersList->user->USER_DOB); setDateOfBirth(date)*/;
		std::cout << "Street Address: "; std::getline(std::cin, newUser->user->USER_ADDRESS);
		std::cout << "Password(Alphanumberic A-z, 0-9): "; std::getline(std::cin, newUser->user->USER_PASSWORD);
		checkValidInput(newUser->user->USER_PASSWORD);
		newUser->user->USER_REG_DATE = registrationDate();

		if (currentUserList->user == NULL && currentUserList->next == NULL) {
		
			delete usersList;
			usersList = newUser;
			headerUserList = usersList;
			currentUserList = headerUserList;
		}
		else if (currentUserList->user != NULL && currentUserList->next == NULL){

			currentUserList->next = newUser;
		}

		currentUser = newUser->user;
		saveUserInfoToDatabase();
		system("pause");
		system("cls");

		return;
    }

	  