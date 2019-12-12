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
						+ currentUserList->user->USER_REG_DATE + ";" + currentUserList->user->USER_REFERENCENUMBER +"}";

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
				//trim first line that contains user information
				std::string::size_type endOfUserRawData = 0;
				endOfUserRawData = info.find("}", endOfUserRawData);
				std::string endOfRawUserData;
				endOfRawUserData = info.substr(1, endOfUserRawData - 1);

				bool finish = false;
				position = 0;
				std::queue<std::string> userDataContainer;
				//parse data
				while (!finish) {

					std::string::size_type start = position;
					position = endOfRawUserData.find(";", position);
					if (position == std::string::npos) {
						position = endOfRawUserData.length();
						finish = true;
					}
					userDataContainer.push(endOfRawUserData.substr(start, position - start));
					position++;

				}

				position = 0;
				finish = false;

				if ((userDataContainer.size() == 11)) {
					addUserFromDBToList(userDataContainer);
				}
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

	void User::addUserFromDBToList(std::queue<std::string> userDataContainer) {

		UserList* newUser = new UserList;
		newUser->user = new UserData;
		newUser->user->USER_ID = stoi(userDataContainer.front()); userDataContainer.pop();
		newUser->user->isAdmin = ("1" == userDataContainer.front()); userDataContainer.pop();
		newUser->user->isEmployer = ("1" == userDataContainer.front()); userDataContainer.pop();
		newUser->user->isLoggedIn = false;
		newUser->user->USER_NAME = userDataContainer.front(); userDataContainer.pop();
		newUser->user->USER_PASSWORD = userDataContainer.front(); userDataContainer.pop();
		newUser->user->USER_FULL_NAME = userDataContainer.front(); userDataContainer.pop();
		newUser->user->USER_EMAIL = userDataContainer.front(); userDataContainer.pop();
		newUser->user->USER_DOB = userDataContainer.front(); userDataContainer.pop();
		newUser->user->USER_ADDRESS = userDataContainer.front(); userDataContainer.pop();
		newUser->user->USER_REG_DATE = userDataContainer.front(); userDataContainer.pop();
		newUser->user->USER_REFERENCENUMBER = userDataContainer.front(); userDataContainer.pop();
		newUser->next = NULL;
		newUser->user->USER_COMPANIES = NULL;
		newUser->user->USER_PROMOTION = NULL;
		newUser->user->USER_SERVICES = NULL;

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

	void User::addUserToList(UserData* user) {//TODO

		UserList* newUser = new UserList;
		newUser->user = new UserData;
		newUser->next = NULL;
		newUser->user->USER_COMPANIES = NULL;
		newUser->user->USER_PROMOTION = NULL;
		newUser->user->USER_SERVICES = NULL;
		newUser->user->USER_JOBS = NULL;
		newUser->user->isAdmin = false;
		newUser->user->USER_ID = generateID();
		
	}


    void User::viewCurrentUserInfo(){

		std::cout << std::endl<<std::endl; 
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
	
    void User::setup(){

		int viewdeal;
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
		newUser->user->USER_COMPANIES = NULL;
		newUser->user->USER_PROMOTION = NULL;
		newUser->user->USER_SERVICES = NULL;
		newUser->user->USER_JOBS = NULL;
		newUser->user->isAdmin = false;
		newUser->user->USER_ID = generateID();
		std::cout << "\nTo register yellow pages system, you must subscribes." << std::endl;

		while (true) {
			Payment payMenu;
			std::cout << "\n****************************************** List of deals ******************************************\n" << std::endl;
			std::cout << "\t\t1. Essential = RM 49.90 / monthly \n\t\t2. Commerce = RM 79.90 / monthly \n\t\t3. Deluxe = RM 149.90 / monthly \n\n";
			std::cout << "***************************************************************************************************\n\n";
			std::cout << "___________________________________________________________________________________________________\n\n";
			std::cout << "\t\tInsert a number of deals you wants to know more , (1/2/3)\n\t\tInsert any other number to continue or cancel the payment : ";
			std::cin >> viewdeal;
			payMenu.viewDeals(viewdeal);
			std:: cout<< "Enter reference number : ";
			std::cin.ignore();
			std::cin >> newUser->user->USER_REFERENCENUMBER;
		}

		std::cout << "Username(Alphanumberic A-z, 0-9): "; std::getline(std::cin, newUser->user->USER_NAME);
		checkValidInput(newUser->user->USER_NAME);
		checkIfUserExist(newUser->user->USER_NAME);
		std::cout << "Full Name:  "; std::getline(std::cin, newUser->user->USER_FULL_NAME);
		std::cout << "Email Address: "; std::getline(std::cin, newUser->user->USER_EMAIL);
		std::cout << "Date of Birth (Day/Month/Year eg. 23/08/1998): "; std::getline(std::cin, newUser->user->USER_DOB);
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
		loadUserInfoFromDatabaseToList();
		system("pause");
		system("cls");

		return;
    }

	void User::userMenu() 
	{
		std::cout << "Dear " << currentUser->USER_FULL_NAME <<" Please enter your choice."<< std::endl;
		std::cout << "1.	Update Profile" << std::endl;
		std::cout << "2.	View Company Profile" << std::endl;
		std::cout << "3.	View Jobs" << std::endl;
		std::cout << "4.	View services" << std::endl;
		std::cout << "5.	View promotion" << std::endl;
		std::cout << "6.	Logout" << std::endl;
	}
	  

	/*void User::searchUser(UserData* currentUser) {

		int selected_id;
		UserList* headerforCurrentList;
		UserData* searchedUser;
		do {

			std::string keyword = "";
			std::cin.ignore();
			currentUserList = headerUserList;
			searchedUser = NULL;

			std::cout << "1. Search by User ID" << std::endl;
			std::cout << "2. Search by Name" << std::endl;
			std::cout << "3. Search by Keyword" << std::endl;
			std::cout << "4. View All Companies" << std::endl;
			std::cout << "0. Exit Search" << std::endl;
			std::cout << "\n\tChoice : ";
			std::cin >> selected_id;

			switch (selected_id) {
			case 0: {
				std::cin.ignore();
				system("cls");
				return;
			}
			case 1: {
				std::cin.ignore();
				std::cout << "Enter Company ID: "; std::cin >> selected_id;

				system("cls");
				std::cout << "===================== Results =====================" << std::endl;
				std::cout << "Company ID\t| " << "Company Name\t|" << "Company Description" << std::endl << std::endl;

				if (headerCompanyList->company == NULL) {
					std::cout << "No Company in database. Please create one." << std::endl;
					system("pause");
					return;
				}
				else {
					while (currentCompanyList->company != NULL) {
						if (std::to_string(currentCompanyList->company->COMPANY_ID).find(std::to_string(selected_id)) != std::string::npos) {
							if (searchedUser == NULL) {
								headerforCurrentList = currentCompanyList;
							}
							searchedUser = currentCompanyList->company;
							viewCompanyBrief(searchedUser);
							if (currentCompanyList->next == NULL) {
								break;
							}
							else {
								currentCompanyList = currentCompanyList->next;
							}
						}
						else if (currentCompanyList->next == NULL && searchedUser == NULL) {
							std::cout << "No company with the id is found!" << std::endl;
							system("pause");
							break;
						}
						else if (currentCompanyList->next == NULL) {
							break;
						}
						else {
							currentCompanyList = currentCompanyList->next;
						}
					}
				}

				if (searchedUser != NULL) {

					std::cout << "\n=========================================================" << std::endl;


					std::cout << "[0]Back"; std::cout << " [1]Select Company to View" << std::endl;
					currentCompanyList = headerforCurrentList;
					std::cin >> selected_id;

					switch (selected_id) {

					case 0: {
						break;
					}
					case 1: {
						std::cout << "Enter Company ID to select:"; std::cin >> selected_id;

						while (true) {
							if (currentCompanyList->company->COMPANY_ID == selected_id) {
								searchedUser = currentCompanyList->company;
								break;
							}
							else if (currentCompanyList->next == NULL) {
								std::cout << "No company with the selected id is found!" << std::endl;
								return;
							}
							else {
								currentCompanyList = currentCompanyList->next;
							}
						}

						viewCurrentCompanyInfo(searchedUser);
						std::cout << "[0]Back ";
						if (currentUser->isAdmin || searchedUser->COMPANY_OWNERID == currentUser->USER_ID) {
							std::cout << "[1]Edit " << std::endl;
						}
						std::cin >> selected_id;
						if (selected_id == 1 && (currentUser->isAdmin || searchedUser->COMPANY_OWNERID == currentUser->USER_ID)) {
							editCurrentCompany(currentUser, searchedUser);
						}

						else {
							break;
						}
					}
					default: {
						break;
					}
					}
				}

				else {
					std::cout << "\n=========================================================" << std::endl;
					break;
				}

				break;
			}
			case 2: {
				std::cin.ignore();
				std::cout << "Enter Company Name: "; std::cin >> keyword;

				system("cls");
				std::cout << "===================== Results =====================" << std::endl;
				std::cout << "Company ID\t| " << "Company Name\t|" << "Company Description" << std::endl << std::endl;

				if (headerCompanyList->company == NULL) {
					std::cout << "No Company in database. Please create one." << std::endl;
					system("pause");
					return;
				}
				else {
					while (currentCompanyList->company != NULL) {
						if (currentCompanyList->company->COMPANY_NAME.find(keyword) != std::string::npos) {
							if (searchedUser == NULL) {
								headerforCurrentList = currentCompanyList;
							}
							searchedUser = currentCompanyList->company;
							viewCompanyBrief(searchedUser);
							if (currentCompanyList->next == NULL) {
								break;
							}
							else {
								currentCompanyList = currentCompanyList->next;
							}
						}
						else if (currentCompanyList->next == NULL && searchedUser == NULL) {
							std::cout << "No company with the name is found!" << std::endl;
							system("pause");
							break;
						}
						else if (currentCompanyList->next == NULL) {
							break;
						}
						else {
							currentCompanyList = currentCompanyList->next;
						}
					}
				}
				if (searchedUser != NULL) {

					std::cout << "\n=========================================================" << std::endl;


					std::cout << "[0]Back"; std::cout << " [1]Select Company to View" << std::endl;
					currentCompanyList = headerforCurrentList;
					std::cin >> selected_id;

					switch (selected_id) {

					case 0: {
						break;
					}
					case 1: {
						std::cout << "Enter Company ID to select:"; std::cin >> selected_id;

						while (true) {
							if (currentCompanyList->company->COMPANY_ID == selected_id) {
								searchedUser = currentCompanyList->company;
								break;
							}
							else if (currentCompanyList->next == NULL) {
								std::cout << "No company with the selected id is found!" << std::endl;
								return;
							}
							else {
								currentCompanyList = currentCompanyList->next;
							}
						}

						viewCurrentCompanyInfo(searchedUser);
						std::cout << "[0]Back ";
						if (currentUser->isAdmin || searchedUser->COMPANY_OWNERID == currentUser->USER_ID) {
							std::cout << "[1]Edit " << std::endl;
						}
						std::cin >> selected_id;
						if (selected_id == 1 && (currentUser->isAdmin || searchedUser->COMPANY_OWNERID == currentUser->USER_ID)) {
							editCurrentCompany(currentUser, searchedUser);
						}

						else {
							break;
						}
					}
					default: {
						break;
					}
					}
				}

				else {
					std::cout << "\n=========================================================" << std::endl;
					break;
				}

				break;
			}
			case 3: {
				std::cin.ignore();
				std::cout << "Enter Keyword: "; std::cin >> keyword;

				system("cls");
				std::cout << "===================== Results =====================" << std::endl;
				std::cout << "Company ID\t| " << "Company Name\t|" << "Company Description" << std::endl << std::endl;

				if (headerCompanyList->company == NULL) {
					std::cout << "No Company in database. Please create one." << std::endl;
					system("pause");
					return;
				}
				else {
					while (currentCompanyList->company != NULL) {
						if (currentCompanyList->company->COMPANY_DESCRIPTION.find(keyword) != std::string::npos) {
							if (searchedUser == NULL) {
								headerforCurrentList = currentCompanyList;
							}
							searchedUser = currentCompanyList->company;
							viewCompanyBrief(searchedUser);
							if (currentCompanyList->next == NULL) {
								break;
							}
							else {
								currentCompanyList = currentCompanyList->next;
							}
						}
						else if (currentCompanyList->next == NULL && searchedUser == NULL) {
							std::cout << "No company with the keyword is found!" << std::endl;
							system("pause");
							break;
						}
						else if (currentCompanyList->next == NULL) {
							break;
						}
						else {
							currentCompanyList = currentCompanyList->next;
						}
					}
				}

				if (searchedUser != NULL) {

					std::cout << "\n=========================================================" << std::endl;


					std::cout << "[0]Back"; std::cout << " [1]Select Company to View" << std::endl;
					currentCompanyList = headerforCurrentList;
					std::cin >> selected_id;

					switch (selected_id) {

					case 0: {
						break;
					}
					case 1: {
						std::cout << "Enter Company ID to select:"; std::cin >> selected_id;

						while (true) {
							if (currentCompanyList->company->COMPANY_ID == selected_id) {
								searchedUser = currentCompanyList->company;
								break;
							}
							else if (currentCompanyList->next == NULL) {
								std::cout << "No company with the selected id is found!" << std::endl;
								return;
							}
							else {
								currentCompanyList = currentCompanyList->next;
							}
						}

						viewCurrentCompanyInfo(searchedUser);
						std::cout << "[0]Back ";
						if (currentUser->isAdmin || searchedUser->COMPANY_OWNERID == currentUser->USER_ID) {
							std::cout << "[1]Edit " << std::endl;
						}
						std::cin >> selected_id;
						if (selected_id == 1 && (currentUser->isAdmin || searchedUser->COMPANY_OWNERID == currentUser->USER_ID)) {
							editCurrentCompany(currentUser, searchedUser);
						}

						else {
							break;
						}
					}
					default: {
						break;
					}
					}
				}

				else {
					std::cout << "\n=========================================================" << std::endl;
					break;
				}

				break;
			}
			case 4: {

				if (headerCompanyList->company == NULL) {
					std::cout << "No Company in database. Please create one." << std::endl;
					system("pause");
					return;
				}
				else {
					system("cls");
					std::cout << "===================== Results =====================" << std::endl;
					std::cout << "Company ID\t| " << "Company Name\t|" << "Company Description" << std::endl << std::endl;
					while (currentCompanyList->company != NULL) {
						if (searchedUser == NULL) {
							headerforCurrentList = currentCompanyList;
						}
						searchedUser = currentCompanyList->company;
						viewCompanyBrief(searchedUser);

						if (currentCompanyList->next == NULL) {
							break;
						}
						else {
							currentCompanyList = currentCompanyList->next;
						}
					}

					if (searchedUser != NULL) {

						std::cout << "\n=========================================================" << std::endl;


						std::cout << "[0]Back"; std::cout << " [1]Select Company to View" << std::endl;
						currentCompanyList = headerforCurrentList;
						std::cin >> selected_id;

						switch (selected_id) {

						case 0: {
							system("cls");
							break;
						}
						case 1: {
							do {
								std::cout << "Enter Company ID to select:"; std::cin >> selected_id;

								while (currentCompanyList->company != NULL) {
									if (currentCompanyList->company->COMPANY_ID == selected_id) {
										searchedUser = currentCompanyList->company;
										break;
									}
									else if (currentCompanyList->next == NULL) {
										std::cout << "No company with the selected id is found!" << std::endl;
										break;
									}
									else {
										currentCompanyList = currentCompanyList->next;
									}
								}
								if (searchedUser != NULL) {
									break;
								}
							} while (selected_id);
							if (searchedUser != NULL) {
								viewCurrentCompanyInfo(searchedUser);
								std::cout << "[0]Back ";
								if (currentUser->isAdmin || searchedUser->COMPANY_OWNERID == currentUser->USER_ID) {
									std::cout << "[1]Edit " << std::endl;
								}
								std::cin >> selected_id;
								if (selected_id == 1 && (currentUser->isAdmin || searchedUser->COMPANY_OWNERID == currentUser->USER_ID)) {
									editCurrentCompany(currentUser, searchedUser);
								}

								else {
									break;
								}
							}
						}
						default: {
							break;
						}
						}
					}
					else {

						std::cout << "No Companies in database!\n" << std::endl;


						std::cout << "\n=========================================================" << std::endl;


					}
				}
				break;
			}

			default: {
				break;
			}
			}

		} while (selected_id);


	}*/