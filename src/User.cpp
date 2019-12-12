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

    UserData* User::getUserData(){ return this->currentUser; }
    UserList* User::getUsersList(){ return this->headerUserList; }


	void User::saveUserInfoToDatabase() {

		currentUserList = headerUserList;

		std::string firstpart;
		std::string info;
		std::ofstream file;
		file.open("userDB.dat");


		while (true) {
		
			if (currentUserList->user) {
				firstpart = "{" + std::to_string(currentUserList->user->USER_ID) + ";" + std::to_string(currentUserList->user->isAdmin) + ";" + std::to_string(currentUserList->user->isEmployer) + ";"
					+ currentUserList->user->USER_NAME + ";" + currentUserList->user->USER_PASSWORD + ";"
					+ currentUserList->user->USER_FULL_NAME + ";" + currentUserList->user->USER_EMAIL + ";"
					+ currentUserList->user->USER_DOB + ";" + currentUserList->user->USER_ADDRESS + ";"
					+ currentUserList->user->USER_REG_DATE + ";" + currentUserList->user->USER_REFERENCENUMBER + "}";

				info = firstpart;

				file << info << std::endl;
			}
			if (currentUserList->next != NULL) {
				currentUserList = currentUserList->next;
			}
			else break;
			
		
		}
		
		file.close();
		std::cout << std::endl << "User data is saved!" << std::endl;
	}

	void User::clearList() {

		UserList* list;
		UserData* listData;
		while (headerUserList) {

			if (headerUserList->next != NULL) {
				list = headerUserList;
				listData = headerUserList->user;
				headerUserList = headerUserList->next;
				delete listData;
				delete list;
				listData = NULL;
				list = NULL;
			}
			else {
				return;
			}
		}

	}

	bool User::login() {
	
		std::string username;
		std::string password;
		std::cout << "Enter username: ";
		std::cin >> username;
		std::cout << "Enter password: ";
		std::cin >> password;

		if (headerUserList->user == NULL) {
			std::cout << "No users in database. Please create one.\n";
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

	void User::logout() {

		delete currentUser;
	}

	void User::loadUserInfoFromDatabaseToList() {

		std::string info;
		std::ifstream userDatabase("userDB.dat");
		std::string::size_type position = 0;
		

		while (std::getline(userDatabase, info)) {

			
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
		newUser->user->USER_JOBS = NULL;

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

	void User::addUser(UserData* currentUser) {//TODO

		UserList* newUser = new UserList;
		newUser->user = new UserData;
		newUser->next = NULL;
		newUser->user->USER_REG_DATE = registrationDate();
		std::cin.ignore();

		newUser->user->USER_ID = generateID();
		if (currentUser->isAdmin) {
			std::cout << "Enter Reference Number: "; getline(std::cin, newUser->user->USER_REFERENCENUMBER);
			std::cin.ignore();
		}
		
		else {
			std::cout << "You don't have permission to add a new User!"; 
			system("pause");
			return;
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
		else if (currentUserList->user != NULL && currentUserList->next == NULL) {

			currentUserList->next = newUser;
		}

		saveUserInfoToDatabase();
		system("pause");
		system("cls");

		return;
	}


    void User::viewCurrentUserInfo(UserData* selectedUser){

		std::cout << std::endl<<std::endl; 
		std::cout << "============ Profile Info ============" << std::endl;
		std::cout << "User ID:  " << selectedUser->USER_ID << std::endl;
        std::cout << "Full Name:  " << selectedUser->USER_FULL_NAME << std::endl;
        std::cout << "Email Address: " << selectedUser->USER_EMAIL << std::endl;
        std::cout << "Date of Birth: " << selectedUser->USER_DOB << std::endl;
        std::cout << "Street Address: " << selectedUser->USER_ADDRESS << std::endl;
		std::cout << "Username: " << selectedUser->USER_NAME << std::endl;
        std::cout << "Registration Date: " << selectedUser->USER_REG_DATE << std::endl;   
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
		newUser->user->isEmployer = true;
		newUser->user->USER_ID = generateID();
		std::cout << "\nTo register yellow pages system, you must subscribe." << std::endl;

			
		std::cout << "\n******************* One time payment *******************\n" << std::endl;
		std::cout << "\t1. One time payment = RM 49.90 ";
		std::cout << std::endl;
		std::cout << "\tBenefits: Able to post, view and search for companies, services, jobs and promotions!" << std::endl;;
		std::cout << "***********************************************************\n\n";
		std::cout << "_______________________________________________________\n\n";
		system("pause");
		Payment payMenu;
		std:: cout<< "Enter reference number : ";
		std::cin.ignore();
		std::cin >> newUser->user->USER_REFERENCENUMBER;
		std::cin.ignore();
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
		system("pause");
		system("cls");

		return;
    }

	void User::userMenu() 
	{
		std::cout << "Dear " << currentUser->USER_FULL_NAME <<" Please enter your choice."<< std::endl;
		std::cout << "0. Logout" << std::endl;
		std::cout << "1. Update Profile" << std::endl;
		std::cout << "2. Company Management" << std::endl;
		std::cout << "3. Job Management" << std::endl;
		std::cout << "4. Service Management" << std::endl;
		std::cout << "5. Promotion Management" << std::endl;
		if (currentUser->isAdmin) {
			std::cout << "6. User Management" << std::endl;
		}
	}
	  
	void User::guest() {

		UserData* guestData = new UserData;
		guestData->isAdmin = 0;
		guestData->isEmployer = 0;
		guestData->isLoggedIn = 0;
		guestData->USER_ADDRESS = "";
		guestData->USER_DOB = "";
		guestData->USER_EMAIL = "";
		guestData->USER_FULL_NAME = "Guest";
		guestData->USER_ID = 0;
		guestData->USER_NAME = "Guest";
		guestData->USER_PASSWORD = "";
		guestData->USER_REFERENCENUMBER = "";
		guestData->USER_REG_DATE = "";
		guestData->USER_COMPANIES = NULL;
		guestData->USER_PROMOTION = NULL;
		guestData->USER_SERVICES = NULL;

		currentUser = guestData;


	}

	void User::searchUser(UserData* currentUser) {

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
			std::cout << "3. Search by Reference Number" << std::endl;
			std::cout << "4. View All Users" << std::endl;
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
				std::cout << "Enter User ID: "; std::cin >> selected_id;

				system("cls");
				std::cout << "===================== Results =====================" << std::endl;
				std::cout << "User ID\t| " << "User Name\t|" << std::endl << std::endl;

				if (headerUserList->user == NULL) {
					std::cout << "No Users in database. Please create one." << std::endl;
					system("pause");
					return;
				}
				else {
					while (currentUserList->user != NULL) {
						if (std::to_string(currentUserList->user->USER_ID).find(std::to_string(selected_id)) != std::string::npos) {
							if (searchedUser == NULL) {
								headerforCurrentList = currentUserList;
							}
							searchedUser = currentUserList->user;
							viewUserBrief(searchedUser);
							if (currentUserList->next == NULL) {
								break;
							}
							else {
								currentUserList = currentUserList->next;
							}
						}
						else if (currentUserList->next == NULL && searchedUser == NULL) {
							std::cout << "No user with the id is found!" << std::endl;
							system("pause");
							break;
						}
						else if (currentUserList->next == NULL) {
							break;
						}
						else {
							currentUserList = currentUserList->next;
						}
					}
				}

				if (searchedUser != NULL) {

					std::cout << "\n=========================================================" << std::endl;


					std::cout << "[0]Back"; std::cout << " [1]Select User to View" << std::endl;
					currentUserList = headerforCurrentList;
					std::cin >> selected_id;

					switch (selected_id) {

					case 0: {
						break;
					}
					case 1: {
						std::cout << "Enter User ID to select:"; std::cin >> selected_id;

						while (true) {
							if (currentUserList->user->USER_ID == selected_id) {
								searchedUser = currentUserList->user;
								break;
							}
							else if (currentUserList->next == NULL) {
								std::cout << "No user with the selected id is found!" << std::endl;
								return;
							}
							else {
								currentUserList = currentUserList->next;
							}
						}

						viewCurrentUserInfo(searchedUser);
						std::cout << "[0]Back ";
						if (currentUser->isAdmin) {
							std::cout << "[1]Edit " << std::endl;
						}
						std::cin >> selected_id;
						if (selected_id == 1 && currentUser->isAdmin) {
							editCurrentUser(currentUser, searchedUser);
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
				std::cout << "Enter Username: "; std::cin >> keyword;

				system("cls");
				std::cout << "===================== Results =====================" << std::endl;
				std::cout << "User ID\t| " << "User Name\t|" << std::endl << std::endl;

				if (headerUserList->user == NULL) {
					std::cout << "No Users in database. Please create one." << std::endl;
					system("pause");
					return;
				}
				else {
					while (currentUserList->user != NULL) {
						if (currentUserList->user->USER_NAME.find(keyword) != std::string::npos) {
							if (searchedUser == NULL) {
								headerforCurrentList = currentUserList;
							}
							searchedUser = currentUserList->user;
							viewUserBrief(searchedUser);
							if (currentUserList->next == NULL) {
								break;
							}
							else {
								currentUserList = currentUserList->next;
							}
						}
						else if (currentUserList->next == NULL && searchedUser == NULL) {
							std::cout << "No user with the name is found!" << std::endl;
							system("pause");
							break;
						}
						else if (currentUserList->next == NULL) {
							break;
						}
						else {
							currentUserList = currentUserList->next;
						}
					}
				}
				if (searchedUser != NULL) {

					std::cout << "\n=========================================================" << std::endl;


					std::cout << "[0]Back"; std::cout << " [1]Select User to View" << std::endl;
					currentUserList = headerforCurrentList;
					std::cin >> selected_id;

					switch (selected_id) {

					case 0: {
						break;
					}
					case 1: {
						std::cout << "Enter User ID to select:"; std::cin >> selected_id;

						while (true) {
							if (currentUserList->user->USER_ID == selected_id) {
								searchedUser = currentUserList->user;
								break;
							}
							else if (currentUserList->next == NULL) {
								std::cout << "No user with the selected id is found!" << std::endl;
								return;
							}
							else {
								currentUserList = currentUserList->next;
							}
						}

						viewCurrentUserInfo(searchedUser);
						std::cout << "[0]Back ";
						if (currentUser->isAdmin) {
							std::cout << "[1]Edit " << std::endl;
						}
						std::cin >> selected_id;
						if (selected_id == 1 && currentUser->isAdmin) {
							editCurrentUser(currentUser, searchedUser);
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
				std::cout << "Enter Reference Number: "; std::cin >> keyword;

				system("cls");
				std::cout << "===================== Results =====================" << std::endl;
				std::cout << "User ID\t| " << "User Name\t|" << std::endl << std::endl;

				if (headerUserList->user == NULL) {
					std::cout << "No users in database. Please create one." << std::endl;
					system("pause");
					return;
				}
				else {
					while (currentUserList->user != NULL) {
						if (currentUserList->user->USER_REFERENCENUMBER.find(keyword) != std::string::npos) {
							if (searchedUser == NULL) {
								headerforCurrentList = currentUserList;
							}
							searchedUser = currentUserList->user;
							viewUserBrief(searchedUser);
							if (currentUserList->next == NULL) {
								break;
							}
							else {
								currentUserList = currentUserList->next;
							}
						}
						else if (currentUserList->next == NULL && searchedUser == NULL) {
							std::cout << "No users with the reference is found!" << std::endl;
							system("pause");
							break;
						}
						else if (currentUserList->next == NULL) {
							break;
						}
						else {
							currentUserList = currentUserList->next;
						}
					}
				}

				if (searchedUser != NULL) {

					std::cout << "\n=========================================================" << std::endl;


					std::cout << "[0]Back"; std::cout << " [1]Select User to View" << std::endl;
					currentUserList = headerforCurrentList;
					std::cin >> selected_id;

					switch (selected_id) {

					case 0: {
						break;
					}
					case 1: {
						std::cout << "Enter User ID to select:"; std::cin >> selected_id;

						while (true) {
							if (currentUserList->user->USER_ID == selected_id) {
								searchedUser = currentUserList->user;
								break;
							}
							else if (currentUserList->next == NULL) {
								std::cout << "No user with the selected id is found!" << std::endl;
								return;
							}
							else {
								currentUserList = currentUserList->next;
							}
						}

						viewCurrentUserInfo(searchedUser);
						std::cout << "[0]Back ";
						if (currentUser->isAdmin) {
							std::cout << "[1]Edit " << std::endl;
						}
						std::cin >> selected_id;
						if (selected_id == 1 && currentUser->isAdmin) {
							editCurrentUser(currentUser, searchedUser);
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

				if (headerUserList->user == NULL) {
					std::cout << "No Users in database. Please create one." << std::endl;
					system("pause");
					return;
				}
				else {
					system("cls");
					std::cout << "===================== Results =====================" << std::endl;
					std::cout << "User ID\t| " << "User Name\t|" << std::endl << std::endl;
					while (currentUserList->user != NULL) {
						if (searchedUser == NULL) {
							headerforCurrentList = currentUserList;
						}
						searchedUser = currentUserList->user;
						viewUserBrief(searchedUser);

						if (currentUserList->next == NULL) {
							break;
						}
						else {
							currentUserList = currentUserList->next;
						}
					}

					if (searchedUser != NULL) {

						std::cout << "\n=========================================================" << std::endl;


						std::cout << "[0]Back"; std::cout << " [1]Select User to View" << std::endl;
						currentUserList = headerforCurrentList;
						std::cin >> selected_id;

						switch (selected_id) {

						case 0: {
							system("cls");
							break;
						}
						case 1: {
							do {
								std::cout << "Enter User ID to select:"; std::cin >> selected_id;

								while (currentUserList->user != NULL) {
									if (currentUserList->user->USER_ID == selected_id) {
										searchedUser = currentUserList->user;
										break;
									}
									else if (currentUserList->next == NULL) {
										std::cout << "No user with the selected id is found!" << std::endl;
										break;
									}
									else {
										currentUserList = currentUserList->next;
									}
								}
								if (searchedUser != NULL) {
									break;
								}
							} while (selected_id);
							if (searchedUser != NULL) {
								viewCurrentUserInfo(searchedUser);
								std::cout << "[0]Back ";
								if (currentUser->isAdmin) {
									std::cout << "[1]Edit " << std::endl;
								}
								std::cin >> selected_id;
								if (selected_id == 1 && currentUser->isAdmin) {
									editCurrentUser(currentUser, searchedUser);
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

						std::cout << "No Users in database!\n" << std::endl;


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


	}

	void User::viewUserBrief(UserData* currentUser) {

		std::cout << currentUser->USER_ID << "\t" << currentUser->USER_NAME << std::endl;
	}

	void User::editCurrentUser(UserData* currentUser, UserData* selectedUser) {

		int selected_id;

		do {
			system("cls");
			std::cout << "Selected User to edit:" << std::endl;
			viewCurrentUserInfo(selectedUser);

			std::cout << "1. Update Username" << std::endl;
			std::cout << "2. Update Full Name" << std::endl;
			std::cout << "3. Update Email" << std::endl;
			std::cout << "4. Update Date of Birth" << std::endl;
			std::cout << "5. Update Address" << std::endl;
			std::cout << "6. Update Password" << std::endl;
			if (currentUser->isAdmin) {
				std::cout << "7. Update Reference Number" << std::endl;
				std::cout << "8. Delete User" << std::endl;
			}
			std::cout << "0. Finish edit" << std::endl;

			std::cin >> selected_id;

			switch (selected_id) {
			case 0: {
				system("cls");
				break;
			}
			case 1: {
				std::cin.ignore();
				std::string input;
				std::cout << "Enter new Username: "; std::getline(std::cin, input);
				checkIfUserExist(input);
				selectedUser->USER_NAME = input;
				break;
			}
			case 2: {
				std::cin.ignore();
				std::cout << "Enter new Full Name: "; std::getline(std::cin, selectedUser->USER_FULL_NAME);
				break;
			}
			case 3: {
				std::cin.ignore();
				std::cout << "Enter new Email: "; std::getline(std::cin, selectedUser->USER_EMAIL);
				break;
			}
			case 4: {
				std::cin.ignore();
				std::cout << "Enter new Date of Birth: "; std::getline(std::cin, selectedUser->USER_DOB);
				break;
			}
			case 5: {
				std::cin.ignore();
				std::cout << "Enter new Address: "; std::getline(std::cin, selectedUser->USER_ADDRESS);
				break;
			}
			case 6: {
				std::cin.ignore();
				std::cout << "Enter new Password: "; std::getline(std::cin, selectedUser->USER_PASSWORD);
				break;
			}
			case 7: {
				std::cin.ignore();
				std::cout << "Enter new Reference Number: "; std::cin >> selectedUser->USER_REFERENCENUMBER;
				break;
			}
			case 8: {
				std::cin.ignore();
				std::cout << "Are you sure you want to delete the selected user?\n";
				std::cout << "Please re-input User ID to confirm: \n"; std::cin >> selected_id;
				if (selected_id == selectedUser->USER_ID) {
					deleteCurrentUser(currentUser, selectedUser);
				}


				break;
			}
			default: {
				std::cout << "Invalid input! Try again: "; std::cin >> selected_id;
				break;
			}
			}

		} while (selected_id);
		saveUserInfoToDatabase();
	}

	void User::deleteCurrentUser(UserData* currentUser, UserData* selectedUser) {

		delete selectedUser;
		selectedUser = NULL;

		std::cout << "Selected User has been deleted" << std::endl;

		saveUserInfoToDatabase();

		return;



	}

	void User::editUser(UserData* currentUser) {

		currentUserList = headerUserList;
		int selected_id;
		UserData* selectedUser;
		selectedUser = NULL;
		std::cin.ignore();
		if (currentUser->isAdmin) {

			std::cout << "Select User ID:" << std::endl; std::cin >> selected_id;
		}
		else {
			std::cout << "You don't have permission to edit this User!"; return;
		}

		if (currentUser->isAdmin) {
			while (currentUserList->user != NULL) {
				if (currentUserList->user->USER_ID == selected_id) {
					selectedUser = currentUserList->user;
					break;
				}
				else if (currentUserList->next == NULL) {
					std::cout << "No user with the selected id is found!";
					return;
				}
				else {
					currentUserList = currentUserList->next;
				}
			}
		}

		std::cout << "Selected User to edit:" << std::endl;
		viewCurrentUserInfo(selectedUser);

		editCurrentUser(currentUser, selectedUser);

		saveUserInfoToDatabase();
	}

