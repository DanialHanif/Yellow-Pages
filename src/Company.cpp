#include "Company.h"


Company::Company() {

	this->companyList = new CompanyList;
	this->companyList->company = NULL;
	this->companyList->next = NULL;
	this->headerCompanyList = companyList;
	this->currentCompanyList = companyList;
	loadCompanyListFromDatabase();
}

CompanyData* Company::getCompanyData() { return this->currentCompany; }
CompanyList* Company::getCompanyList() { return this->headerCompanyList; }

void Company::saveCompanyListToDatabase(){

	currentCompanyList = headerCompanyList;

	std::string firstpart;
	std::string info;
	std::ofstream file;
	file.open("companyDB.dat");


	while (true) {

		firstpart = "{" + std::to_string(currentCompanyList->company->COMPANY_ID) + ";" + std::to_string(currentCompanyList->company->COMPANY_OWNERID) + ";" + currentCompanyList->company->COMPANY_NAME + ";" + currentCompanyList->company->COMPANY_DESCRIPTION
						+ ";" + currentCompanyList->company->COMPANY_EMAIL + ";" + currentCompanyList->company->COMPANY_CONTACTNUMBER + ";" + currentCompanyList->company->COMPANY_WEBSITE + "}";

		info = firstpart;

		file << info << std::endl;

		if (currentCompanyList->next != NULL) {
			currentCompanyList = currentCompanyList->next;
		}
		else break;


	}

	file.close();
	std::cout << std::endl << "Company data is saved!" << std::endl;
}

void Company::loadCompanyListFromDatabase() {

	std::string info;
	std::ifstream companyDatabase("companyDB.dat");
	std::string::size_type position = 0;

	/*if (userDatabase.fail()) {
		std::cout << "User Database is not found!" << std::endl;
		std::cout << "Creating new user database..." << std::endl;
		std::ofstream outputFile;
		outputFile.open("userDB.dat", std::ios_base::app);
		outputFile.close();
	}*/

	while (std::getline(companyDatabase, info)) {

		
		if (info.size() > 0) {
			//trim first line that contains company information
			std::string::size_type endOfRawCompanyData = 0;
			endOfRawCompanyData = info.find("}", endOfRawCompanyData);
			std::string companyRawData;
			companyRawData = info.substr(1, endOfRawCompanyData - 1);

			bool finish = false;
			position = 0;
			std::queue<std::string> companyDataContainer;
			//parse data
			while (!finish) {

				std::string::size_type start = position;
				position = companyRawData.find(";", position);
				if (position == std::string::npos) {
					position = companyRawData.length();
					finish = true;
				}
				companyDataContainer.push(companyRawData.substr(start, position - start));
				position++;

			}
			position = 0;
			finish = false;

			if ((companyDataContainer.size() == 7)) {

				addCompanyDataFromDBToList(companyDataContainer);


			}

		}
		else {
			return;
		}


	}



}

void Company::addCompanyDataFromDBToList(std::queue<std::string> companyDataContainer) {

	CompanyList* newCompany = new CompanyList;
	newCompany->company = new CompanyData;
	newCompany->company->COMPANY_ID = stoi(companyDataContainer.front()); companyDataContainer.pop();
	newCompany->company->COMPANY_OWNERID = stoi(companyDataContainer.front()); companyDataContainer.pop();
	newCompany->company->COMPANY_NAME = companyDataContainer.front(); companyDataContainer.pop();
	newCompany->company->COMPANY_DESCRIPTION = companyDataContainer.front(); companyDataContainer.pop();
	newCompany->company->COMPANY_EMAIL = companyDataContainer.front(); companyDataContainer.pop();
	newCompany->company->COMPANY_CONTACTNUMBER = companyDataContainer.front(); companyDataContainer.pop();
	newCompany->company->COMPANY_WEBSITE = companyDataContainer.front(); companyDataContainer.pop();
	newCompany->next = NULL;

	if (headerCompanyList->company == NULL) {//first load
		delete companyList;
		companyList = newCompany;
		headerCompanyList = companyList;
		currentCompanyList = headerCompanyList;
	}

	else {

		CompanyList* current = headerCompanyList;
		while (current) {
			if (current->next == NULL) { current->next = newCompany; return; }

			else current = current->next;
		}
	}

}

void Company::viewCompany(UserData* currentUser) {

	
	if (headerCompanyList->company == NULL) {
		std::cout << "No Company in database. Please create one.";
		return;
	}
	else {
		system("cls");
		std::cout << "===================== Company Lists =====================" << std::endl;
		std::cout << "Company ID\t| " << "Owner ID\t| " << "Company Name" << std::endl;
		
		currentCompanyList = headerCompanyList;
		while (currentCompanyList->company != NULL) {

			if (currentUser->isAdmin == true) {
				while (currentCompanyList->company != NULL) {
		
					std::cout << currentCompanyList->company->COMPANY_ID << "\t" << currentCompanyList->company->COMPANY_OWNERID << "\t" << currentCompanyList->company->COMPANY_NAME << std::endl;
					if (currentCompanyList->next != NULL) {
						currentCompanyList = currentCompanyList->next;
					}
					else break;
				}
				std::cout << "=========================================================" << std::endl;
			}
			//iterate through company list until reach first match
			else if (currentCompanyList->company->COMPANY_OWNERID == currentUser->USER_ID) {
				while (currentCompanyList->company != NULL) {

					std::cout << currentCompanyList->company->COMPANY_ID << "\t" << currentCompanyList->company->COMPANY_OWNERID << "\t" << currentCompanyList->company->COMPANY_NAME << std::endl;
					//add matches to user companies
					if (currentUser->USER_COMPANIES->company == NULL) {
						currentUser->USER_COMPANIES->company = currentCompanyList->company;
					}
					else if (currentUser->USER_COMPANIES->company != NULL) {
						CompanyList* current = currentUser->USER_COMPANIES;

						while (current->company) {
							if (current->next == NULL) {
								current->next = currentCompanyList;
								break;
							}
							else current = current->next;
						}
					
					}
					if (currentCompanyList->next != NULL) {
						currentCompanyList = currentCompanyList->next;
					}
					else break;
				}
				std::cout << "=========================================================" << std::endl;
			}
			else {
				currentCompanyList = currentCompanyList->next;
			}

		}

	}
}

void Company::checkValidInput(std::string& s) {

	while (true) {

		size_t whitelistcharacters = s.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890-_. ");

		if ((whitelistcharacters != std::string::npos) || s == "") {

			std::cout << "Error! Please re-enter input with valid characters!" << std::endl;
			std::cin.ignore();
			system("pause");
			std::cout << "Re-enter input: "; std::getline(std::cin, s);
		}

		else return;
	}

}

void Company::checkValidInputNumber(std::string& s) {

	while (true) {

		size_t whitelistcharacters = s.find_first_not_of("1234567890");

		if ((whitelistcharacters != std::string::npos) || s == "") {

			std::cout << "Error! Please re-enter input with valid characters [0-9]!" << std::endl;
			std::cin.ignore();
			system("pause");
			std::cout << "Re-enter input: "; std::getline(std::cin, s);
		}

		else return;
	}

}

time_t Company::generateID() { time_t currentTime = time(0); return currentTime; }

std::string Company::registrationDate() {
	time_t currentTime = time(0);
	std::string dt = ctime(&currentTime);
	dt = dt.substr(0, (dt.length() - 1));
	return dt;
}

void Company::addCompany(UserData* currentUser) {

		CompanyList* newCompany = new CompanyList;
		newCompany->next = NULL;
		std::cin.ignore();

		newCompany->company->COMPANY_ID = generateID();
		if (currentUser->isAdmin){
			std::cout << "Enter Owner ID: "; std::cin >> newCompany->company->COMPANY_OWNERID;
		}
		else if (currentUser->isEmployer) {
			newCompany->company->COMPANY_OWNERID = currentUser->USER_ID;
		}
		else { std::cout << "You don't have permission to add a new Company!"; return; }

		std::cout << "Enter Company Name: "; std::getline(std::cin, newCompany->company->COMPANY_NAME);
		std::cout << "Enter Company Description: "; std::getline(std::cin, newCompany->company->COMPANY_DESCRIPTION);
		std::cout << "Enter Company Address: "; std::getline(std::cin, newCompany->company->COMPANY_DESCRIPTION);
		std::cout << "Enter Company Contact Number: "; std::getline(std::cin, newCompany->company->COMPANY_DESCRIPTION);
		checkValidInputNumber(newCompany->company->COMPANY_DESCRIPTION);
		std::cout << "Enter Company Website: "; std::getline(std::cin, newCompany->company->COMPANY_DESCRIPTION);


		if (headerCompanyList->company == NULL) {//first load
			delete companyList;
			companyList = newCompany;
			headerCompanyList = companyList;
			currentCompanyList = headerCompanyList;
		}

		else {

			currentCompanyList = headerCompanyList;
			while (currentCompanyList) {
				if (currentCompanyList->next == NULL) { currentCompanyList->next = newCompany; return; }

				else currentCompanyList = currentCompanyList->next;
			}
		}

		saveCompanyListToDatabase();
		viewCompany(currentUser);
}

void Company::editCompany(UserData* currentUser){

		currentCompanyList = headerCompanyList;
		int selected_id;
		CompanyData* selectedCompany;
		std::cin.ignore();
		if (currentUser->isAdmin || currentUser->isEmployer) {
			
			std::cout << "Select Company ID:" << std::endl; std::cin >> selected_id;
		}
		else {
			std::cout << "You don't have permission to edit this Company!"; return;
		}
			
		if (currentUser->isAdmin) {
			while (true) {
				if (currentCompanyList->company->COMPANY_ID == selected_id) {
					selectedCompany = currentCompanyList->company;
					break;
				}
				else if (currentCompanyList->next == NULL) {
					std::cout << "No company with the selected id is found!";
					return;
				}
				else {
					currentCompanyList = currentCompanyList->next;
				}
			}
		}
		else if(currentUser->isEmployer){
			CompanyList* curr = currentUser->USER_COMPANIES;
			while (true) {
				if (curr->company->COMPANY_ID == selected_id) {
					selectedCompany = curr->company;
					break;
				}
				else if (curr->next == NULL) {
					std::cout << "No company with the selected id is found!";
					return;
				}
				else {
					curr = curr->next;
				}
			}
		}

		do {
			std::cout << "Selected Company to edit:" << std::endl;
			std::cout << "Company ID: " << selectedCompany->COMPANY_ID << std::endl;
			std::cout << "Company Name: " << selectedCompany->COMPANY_NAME << std::endl;
			std::cout << "Company Description: " << selectedCompany->COMPANY_DESCRIPTION << std::endl;
			std::cout << "Company Address: " << selectedCompany->COMPANY_EMAIL << std::endl;
			std::cout << "Company Contact Number: " << selectedCompany->COMPANY_CONTACTNUMBER << std::endl;
			std::cout << "Company Website: " << selectedCompany->COMPANY_WEBSITE << std::endl;
			std::cout << "Company Registration Date: " << selectedCompany->COMPANY_REGISTRATION_DATE << std::endl << std::endl;
			
			std::cout << "1. Update Company Name" << std::endl;
			std::cout << "2. Update Company Description" << std::endl;
			std::cout << "3. Update Company Email" << std::endl;
			std::cout << "4. Update Company Contact Number" << std::endl;
			std::cout << "5. Update Company Website" << std::endl;
			if(currentUser->isAdmin) std::cout << "6. Update Company Owner ID" << std::endl;
			std::cout << "0. Finish edit" << std::endl;

			std::cin >> selected_id;

			switch (selected_id) {
				case 0: {
					break;
				}
				case 1: {
					std::cin.ignore();
					std::cout << "Enter new Company Name: "; std::getline(std::cin, selectedCompany->COMPANY_NAME);
					break;
				}
				case 2: {
					std::cin.ignore();
					std::cout << "Enter new Company Description: "; std::getline(std::cin, selectedCompany->COMPANY_DESCRIPTION);
					break;
				}
				case 3: {
					std::cin.ignore();
					std::cout << "Enter new Company Email: "; std::getline(std::cin, selectedCompany->COMPANY_EMAIL);
					break;
				}
				case 4: {
					std::cin.ignore();
					std::cout << "Enter new Company Contact Number: "; std::getline(std::cin, selectedCompany->COMPANY_CONTACTNUMBER);
					break;
				}
				case 5: {
					std::cin.ignore();
					std::cout << "Enter new Company Website: "; std::getline(std::cin, selectedCompany->COMPANY_WEBSITE);
					break;
				}
				case 6: {
					std::cin.ignore();
					std::cout << "Enter new Company Owner ID: "; std::cin >> selectedCompany->COMPANY_OWNERID;
					break;
				}
				default: {
					std::cout << "Invalid input! Try again: "; std::cin >> selected_id;
					break;
				}
			}

		} while (selected_id);		   							

		saveCompanyListToDatabase();
}

void Company::deleteCompany(UserData* currentUser){


}

/*void Company::searchCompany(UserData* currentUser) {//TODO


	currentCompanyList = headerCompanyList;
	int selected_id;
	CompanyData* selectedCompany;
	std::cin.ignore();

	do {
		std::cout << "1. Search by Company ID:";
		std::cout << "2. Search by Name:";
		std::cout << "3. Search by Keyword:";
		std::cout << "3. View All Companies";
		std::cout << "0. Exit Search:";
		
		switch (selected_id) {
			case 0: {
				std::cout << "Enter Company ID: "; std::cin >> selected_id;
				break;
			}
			default: {
			}
		}

		system("cls");
		std::cout << "===================== Company Lists =====================" << std::endl;
		std::cout << "Company ID\t| " << "Company Name" << std::endl;

		while (true) {
			if (currentCompanyList->company->COMPANY_ID == selected_id) {
				selectedCompany = currentCompanyList->company;       
				break;
			}
			else if (currentCompanyList->next == NULL) {
				std::cout << "No company with the selected id is found!";
				break;
			}
			else {
				currentCompanyList = currentCompanyList->next;
			}
		}

	} while (selected_id);

	if (currentUser->isAdmin) {
		while (true) {
			if (currentCompanyList->company->COMPANY_ID == selected_id) {
				selectedCompany = currentCompanyList->company;
				break;
			}
			else if (currentCompanyList->next == NULL) {
				std::cout << "No company with the selected id is found!";
				return;
			}
			else {
				currentCompanyList = currentCompanyList->next;
			}
		}
	}
	else if (currentUser->isEmployer) {
		CompanyList* curr = currentUser->USER_COMPANIES;
		while (true) {
			if (curr->company->COMPANY_ID == selected_id) {
				selectedCompany = curr->company;
				break;
			}
			else if (curr->next == NULL) {
				std::cout << "No company with the selected id is found!";
				return;
			}
			else {
				curr = curr->next;
			}
		}
	}


}*/