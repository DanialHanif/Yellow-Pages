#include "Promotion.h"

Promotion::Promotion() {

	this->promotionList = new PromotionList;
	this->promotionList->promotion = NULL;
	this->promotionList->next = NULL;
	this->headerPromotionList = promotionList;
	this->currentPromotionList = promotionList;
	loadPromotionListFromDatabase();
}

PromotionData* Promotion::getPromotionData() { return this->currentPromotion; }
PromotionList* Promotion::getPromotionList() { return this->headerPromotionList; }

void Promotion::savePromotionListToDatabase(){

	currentPromotionList = headerPromotionList;

	std::string firstpart;
	std::string info;
	std::ofstream file;
	file.open("promotionDB.dat");


	while (true) {

		firstpart = "{" + std::to_string(currentPromotionList->promotion->PROMOTION_ID) + ";" + std::to_string(currentPromotionList->promotion->PROMOTION_OWNERID) + ";" + currentPromotionList->promotion->PROMOTION_NAME + ";" + currentPromotionList->promotion->PROMOTION_DESCRIPTION
						+ ";" + currentPromotionList->promotion->PROMOTION_POSTING_DATE + ";" + std::to_string(currentPromotionList->promotion->PROMOTION_PRICE) + "}";

		info = firstpart;

		file << info << std::endl;

		if (currentPromotionList->next != NULL) {
			currentPromotionList = currentPromotionList->next;
		}
		else {
			break;
		}


	}

	file.close();
	std::cout << std::endl << "Promotion data is saved!" << std::endl;
	delete promotionList;
	promotionList = new PromotionList;
	promotionList->promotion = NULL;
	promotionList->next = NULL;
	headerPromotionList = promotionList;
	loadPromotionListFromDatabase();
}

void Promotion::loadPromotionListFromDatabase() {

	std::string info;
	std::ifstream promotionDatabase("promotionDB.dat");
	std::string::size_type position = 0;

	/*if (userDatabase.fail()) {
		std::cout << "User Database is not found!" << std::endl;
		std::cout << "Creating new user database..." << std::endl;
		std::ofstream outputFile;
		outputFile.open("userDB.dat", std::ios_base::app);
		outputFile.close();
	}*/

	while (std::getline(promotionDatabase, info)) {

		
		if (info.size() > 0) {
			//trim first line that contains promotion information
			std::string::size_type endOfRawPromotionData = 0;
			endOfRawPromotionData = info.find("}", endOfRawPromotionData);
			std::string promotionRawData;
			promotionRawData = info.substr(1, endOfRawPromotionData - 1);

			bool finish = false;
			position = 0;
			std::queue<std::string> promotionDataContainer;
			//parse data
			while (!finish) {

				std::string::size_type start = position;
				position = promotionRawData.find(";", position);
				if (position == std::string::npos) {
					position = promotionRawData.length();
					finish = true;
				}
				promotionDataContainer.push(promotionRawData.substr(start, position - start));
				position++;

			}
			position = 0;
			finish = false;

			if ((promotionDataContainer.size() == 6)) {

				addPromotionDataFromDBToList(promotionDataContainer);


			}

		}
		else {
			return;
		}


	}



}

void Promotion::addPromotionDataFromDBToList(std::queue<std::string> promotionDataContainer) {

	PromotionList* newPromotion = new PromotionList;
	newPromotion->promotion = new PromotionData;
	newPromotion->promotion->PROMOTION_ID = stoi(promotionDataContainer.front()); promotionDataContainer.pop();
	newPromotion->promotion->PROMOTION_OWNERID = stoi(promotionDataContainer.front()); promotionDataContainer.pop();
	newPromotion->promotion->PROMOTION_NAME = promotionDataContainer.front(); promotionDataContainer.pop();
	newPromotion->promotion->PROMOTION_DESCRIPTION = promotionDataContainer.front(); promotionDataContainer.pop();
	newPromotion->promotion->PROMOTION_POSTING_DATE = promotionDataContainer.front(); promotionDataContainer.pop();
	newPromotion->promotion->PROMOTION_PRICE = stod(promotionDataContainer.front()); promotionDataContainer.pop();
	newPromotion->next = NULL;

	if (headerPromotionList->promotion == NULL) {//first load
		
		delete promotionList;
		promotionList = newPromotion;
		headerPromotionList = promotionList;
		currentPromotionList = headerPromotionList;
	}

	else {

		PromotionList* current = headerPromotionList;
		while (current) {
			if (current->next == NULL) { current->next = newPromotion; return; }

			else {
				current = current->next;
			}
		}
	}

}

void Promotion::viewPromotion(UserData* currentUser) {

	
	if (headerPromotionList->promotion == NULL) {
		std::cout << "No Promotion in database. Please create one.";
		return;
	}
	else {
		system("cls");
		std::cout << "===================== Promotion Lists =====================" << std::endl;
		std::cout << "Promotion ID\t| " << "Owner ID\t| " << "Promotion Name" << std::endl;
		
		currentPromotionList = headerPromotionList;
		while (currentPromotionList->promotion != NULL) {

			if (currentUser->isAdmin == true) {
				while (currentPromotionList->promotion != NULL) {
		
					std::cout << currentPromotionList->promotion->PROMOTION_ID << "\t" << currentPromotionList->promotion->PROMOTION_OWNERID << "\t" << currentPromotionList->promotion->PROMOTION_NAME << std::endl;
					if (currentPromotionList->next != NULL) {
						currentPromotionList = currentPromotionList->next;
					}
					else {
						break;
					}
				}
				std::cout << "=========================================================" << std::endl;
				break;
			}
			//iterate through promotion list until reach first match
			else if (currentPromotionList->promotion->PROMOTION_OWNERID == currentUser->USER_ID) {
				std::cout << currentPromotionList->promotion->PROMOTION_ID << "\t" << currentPromotionList->promotion->PROMOTION_OWNERID << "\t" << currentPromotionList->promotion->PROMOTION_NAME << std::endl;
				while (currentPromotionList->promotion != NULL) {
										
					//add matches to user companies
					if (currentUser->USER_PROMOTION == NULL) {
						currentUser->USER_PROMOTION = currentPromotionList;
						break;
					}
					else if (currentUser->USER_PROMOTION != NULL && currentUser->USER_PROMOTION->next == NULL) {

						currentUser->USER_PROMOTION->next = currentPromotionList;
						break;

					}
					else {
						break;
					}
				}
				
			}
			if (currentPromotionList->next != NULL) {
				currentPromotionList = currentPromotionList->next;
			}
			else {
				std::cout << "=========================================================" << std::endl;
				break;
			}

		}

	}
	
}

void Promotion::checkValidInput(std::string& s) {

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

void Promotion::checkValidInputNumber(std::string& s) {

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

time_t Promotion::generateID() { time_t currentTime = time(0); return currentTime; }

std::string Promotion::postingDate() {
	time_t currentTime = time(0);
	std::string dt = ctime(&currentTime);
	dt = dt.substr(0, (dt.length() - 1));
	return dt;
}

void Promotion::addPromotion(UserData* currentUser) {

		PromotionList* newPromotion = new PromotionList;
		newPromotion->promotion = new PromotionData;
		newPromotion->next = NULL;
		newPromotion->promotion->PROMOTION_POSTING_DATE = postingDate();
		std::cin.ignore();

		newPromotion->promotion->PROMOTION_ID = generateID();
		if (currentUser->isAdmin){
			std::cout << "Enter Owner ID: "; std::cin >> newPromotion->promotion->PROMOTION_OWNERID;
			std::cin.ignore();
		}
		else if (currentUser->isEmployer) {
			newPromotion->promotion->PROMOTION_OWNERID = currentUser->USER_ID;
		}
		else { 
			std::cout << "You don't have permission to add a new Promotion!"; return; //tosolve
		}

		std::cout << "Enter Promotion Name: "; std::getline(std::cin, newPromotion->promotion->PROMOTION_NAME);
		std::cout << "Enter Promotion Description: "; std::getline(std::cin, newPromotion->promotion->PROMOTION_DESCRIPTION);
		newPromotion->promotion->PROMOTION_POSTING_DATE = postingDate();
		std::cout << "Enter Promotion Price: "; std::cin >> newPromotion->promotion->PROMOTION_PRICE;


		if (headerPromotionList->promotion == NULL) {//first load
			
			promotionList = newPromotion;
			headerPromotionList = promotionList;
			currentPromotionList = headerPromotionList;
		}

		else {

			currentPromotionList = headerPromotionList;
			while (currentPromotionList) {
				if (currentUser->isEmployer) {
					if (currentUser->USER_PROMOTION == NULL) { currentUser->USER_PROMOTION = newPromotion; break; }
					if (currentUser->USER_PROMOTION != NULL && currentUser->USER_PROMOTION->next == NULL) { currentUser->USER_PROMOTION->next = newPromotion; break; }
				}
				if (currentPromotionList->next == NULL) { currentPromotionList->next = newPromotion; break; }

				else {
					currentPromotionList = currentPromotionList->next;
				}
			}
		}

		savePromotionListToDatabase();
		viewPromotion(currentUser);
}

void Promotion::editPromotion(UserData* currentUser){

		currentPromotionList = headerPromotionList;
		int selected_id;
		currentPromotion = NULL;
		std::cin.ignore();
		if (currentUser->isAdmin || currentUser->isEmployer) {
			
			std::cout << "Select Promotion ID:" << std::endl; std::cin >> selected_id;
		}
		else {
			std::cout << "You don't have permission to edit this Promotion!"; return;
		}
			
		if (currentUser->isAdmin) {
			while (currentPromotionList->promotion != NULL) {
				if (currentPromotionList->promotion->PROMOTION_ID == selected_id) {
					currentPromotion = currentPromotionList->promotion;
					break;
				}
				else if (currentPromotionList->next == NULL) {
					std::cout << "No promotion with the selected id is found!";
					return;
				}
				else {
					currentPromotionList = currentPromotionList->next;
				}
			}
		}
		else if(currentUser->isEmployer){
			PromotionList* curr = currentUser->USER_PROMOTION;
			while (curr != NULL) {
				if (curr->promotion->PROMOTION_ID == selected_id) {
					currentPromotion = curr->promotion;
					break;
				}
				else if (curr->next == NULL) {
					std::cout << "No promotion with the selected id is found!";
					return;
				}
				else {
					curr = curr->next;
				}
			}
		}

		std::cout << "Selected Promotion to edit:" << std::endl;
		viewCurrentPromotionInfo(currentPromotion);

		editCurrentPromotion(currentUser, currentPromotion);
	   							
		savePromotionListToDatabase();
}

void Promotion::deletePromotion(UserData* currentUser){

	currentPromotionList = headerPromotionList;
	int selected_id;
	currentPromotion = NULL;
	std::cin.ignore();
	if (currentUser->isAdmin || currentUser->isEmployer) {

		std::cout << "Select Promotion ID:" << std::endl; std::cin >> selected_id;
	}
	else {
		std::cout << "You don't have permission to edit this Promotion!"; return;
	}

	if (currentUser->isAdmin) {
		while (currentPromotionList->promotion != NULL) {
			if (currentPromotionList->promotion->PROMOTION_ID == selected_id) {
				currentPromotion = currentPromotionList->promotion;
				break;
			}
			else if (currentPromotionList->next == NULL) {
				std::cout << "No promotion with the selected id is found!";
				return;
			}
			else {
				currentPromotionList = currentPromotionList->next;
			}
		}
	}
	else if (currentUser->isEmployer) {
		PromotionList* curr = currentUser->USER_PROMOTION;
		while (curr != NULL) {
			if (curr->promotion->PROMOTION_ID == selected_id) {
				currentPromotion = curr->promotion;
				break;
			}
			else if (curr->next == NULL) {
				std::cout << "No promotion with the selected id is found!";
				return;
			}
			else {
				curr = curr->next;
			}
		}
	}

	std::cout << "Selected Promotion to delete:" << std::endl;
	viewCurrentPromotionInfo(currentPromotion);

	deleteCurrentPromotion(currentUser, currentPromotion);

	savePromotionListToDatabase();
}

void Promotion::searchPromotion(UserData* currentUser) {

	int selected_id;
	PromotionList* headerforCurrentList;
	do {
		
		std::string keyword = "";
		std::cin.ignore();
		currentPromotionList = headerPromotionList;
		currentPromotion = NULL;

		std::cout << "1. Search by Promotion ID" << std::endl;
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
				std::cout << "Enter Promotion ID: "; std::cin >> selected_id;

				system("cls");
				std::cout << "===================== Results =====================" << std::endl;
				std::cout << "Promotion ID\t| " << "Promotion Name\t|" << "Promotion Description" << std::endl << std::endl;

				if (headerPromotionList->promotion == NULL) {
					std::cout << "No Promotion in database. Please create one." << std::endl;
					system("pause");
					return;
				}
				else {
					while (currentPromotionList->promotion != NULL) {
						if (std::to_string(currentPromotionList->promotion->PROMOTION_ID).find(std::to_string(selected_id)) != std::string::npos) {
							if (currentPromotion == NULL) {
								headerforCurrentList = currentPromotionList;
							}
							currentPromotion = currentPromotionList->promotion;
							viewPromotionBrief(currentPromotion);
							if (currentPromotionList->next == NULL) {
								break;
							}
							else {
								currentPromotionList = currentPromotionList->next;
							}
						}
						else if (currentPromotionList->next == NULL && currentPromotion == NULL) {
							std::cout << "No promotion with the id is found!" << std::endl;
							system("pause");
							break;
						}
						else if (currentPromotionList->next == NULL) {
							break;
						}
						else {
							currentPromotionList = currentPromotionList->next;
						}
					}
				}

				if (currentPromotion != NULL) {

					std::cout << "\n=========================================================" << std::endl;

					
					std::cout << "[0]Back"; std::cout << " [1]Select Promotion to View" << std::endl;
					currentPromotionList = headerforCurrentList;
					std::cin >> selected_id;

					switch (selected_id) {

						case 0: {
							break;
						}
						case 1: {
							std::cout << "Enter Promotion ID to select:"; std::cin >> selected_id;

							while (true) {
								if (currentPromotionList->promotion->PROMOTION_ID == selected_id) {
									currentPromotion = currentPromotionList->promotion;
									break;
								}
								else if (currentPromotionList->next == NULL) {
									std::cout << "No promotion with the selected id is found!" << std::endl;
									return;
								}
								else {
									currentPromotionList = currentPromotionList->next;
								}
							}

							viewCurrentPromotionInfo(currentPromotion);
							std::cout << "[0]Back ";
							if (currentUser->isAdmin || currentPromotion->PROMOTION_OWNERID == currentUser->USER_ID) {
								std::cout << "[1]Edit " << std::endl;
							}
							std::cin >> selected_id;
							if (selected_id == 1 && (currentUser->isAdmin || currentPromotion->PROMOTION_OWNERID == currentUser->USER_ID)) {
								editCurrentPromotion(currentUser, currentPromotion);
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
				std::cout << "Enter Promotion Name: "; std::cin >> keyword;

				system("cls");
				std::cout << "===================== Results =====================" << std::endl;
				std::cout << "Promotion ID\t| " << "Promotion Name\t|" << "Promotion Description"<< std::endl << std::endl;

				if (headerPromotionList->promotion == NULL) {
					std::cout << "No Promotion in database. Please create one." << std::endl;
					system("pause");
					return;
				}
				else {
					while (currentPromotionList->promotion != NULL) {
						if (currentPromotionList->promotion->PROMOTION_NAME.find(keyword) != std::string::npos) {
							if (currentPromotion == NULL) {
								headerforCurrentList = currentPromotionList;
							}
							currentPromotion = currentPromotionList->promotion;
							viewPromotionBrief(currentPromotion);
							if (currentPromotionList->next == NULL) {
								break;
							}
							else {
								currentPromotionList = currentPromotionList->next;
							}
						}
						else if (currentPromotionList->next == NULL && currentPromotion == NULL) {
							std::cout << "No promotion with the name is found!" << std::endl;
							system("pause");
							break;
						}
						else if (currentPromotionList->next == NULL) {
							break;
						}
						else {
							currentPromotionList = currentPromotionList->next;
						}
					}
				}
				if (currentPromotion != NULL) {

					std::cout << "\n=========================================================" << std::endl;


					std::cout << "[0]Back"; std::cout << " [1]Select Promotion to View" << std::endl;
					currentPromotionList = headerforCurrentList;
					std::cin >> selected_id;

					switch (selected_id) {

					case 0: {
						break;
					}
					case 1: {
						std::cout << "Enter Promotion ID to select:"; std::cin >> selected_id;

						while (true) {
							if (currentPromotionList->promotion->PROMOTION_ID == selected_id) {
								currentPromotion = currentPromotionList->promotion;
								break;
							}
							else if (currentPromotionList->next == NULL) {
								std::cout << "No promotion with the selected id is found!" << std::endl;
								return;
							}
							else {
								currentPromotionList = currentPromotionList->next;
							}
						}

						viewCurrentPromotionInfo(currentPromotion);
						std::cout << "[0]Back ";
						if (currentUser->isAdmin || currentPromotion->PROMOTION_OWNERID == currentUser->USER_ID) {
							std::cout << "[1]Edit " << std::endl;
						}
						std::cin >> selected_id;
						if (selected_id == 1 && (currentUser->isAdmin || currentPromotion->PROMOTION_OWNERID == currentUser->USER_ID)) {
							editCurrentPromotion(currentUser, currentPromotion);
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
				std::cout << "Promotion ID\t| " << "Promotion Name\t|" << "Promotion Description" << std::endl << std::endl;

				if (headerPromotionList->promotion == NULL) {
					std::cout << "No Promotion in database. Please create one." << std::endl;
					system("pause");
					return;
				}
				else {
					while (currentPromotionList->promotion != NULL) {
						if (currentPromotionList->promotion->PROMOTION_DESCRIPTION.find(keyword) != std::string::npos) {
							if (currentPromotion == NULL) {
								headerforCurrentList = currentPromotionList;
							}
							currentPromotion = currentPromotionList->promotion;
							viewPromotionBrief(currentPromotion);
							if (currentPromotionList->next == NULL) {
								break;
							}
							else {
								currentPromotionList = currentPromotionList->next;
							}
						}
						else if (currentPromotionList->next == NULL && currentPromotion == NULL) {
							std::cout << "No promotion with the keyword is found!" << std::endl;
							system("pause");
							break;
						}
						else if (currentPromotionList->next == NULL) {
							break;
						}
						else {
							currentPromotionList = currentPromotionList->next;
						}
					}
				}

				if (currentPromotion != NULL) {

					std::cout << "\n=========================================================" << std::endl;


					std::cout << "[0]Back"; std::cout << " [1]Select Promotion to View" << std::endl;
					currentPromotionList = headerforCurrentList;
					std::cin >> selected_id;

					switch (selected_id) {

						case 0: {
							break;
						}
						case 1: {
							std::cout << "Enter Promotion ID to select:"; std::cin >> selected_id;

							while (true) {
								if (currentPromotionList->promotion->PROMOTION_ID == selected_id) {
									currentPromotion = currentPromotionList->promotion;
									break;
								}
								else if (currentPromotionList->next == NULL) {
									std::cout << "No promotion with the selected id is found!" << std::endl;
									return;
								}
								else {
									currentPromotionList = currentPromotionList->next;
								}
							}

							viewCurrentPromotionInfo(currentPromotion);
							std::cout << "[0]Back ";
							if (currentUser->isAdmin || currentPromotion->PROMOTION_OWNERID == currentUser->USER_ID) {
								std::cout << "[1]Edit " << std::endl;
							}
							std::cin >> selected_id;
							if (selected_id == 1 && (currentUser->isAdmin || currentPromotion->PROMOTION_OWNERID == currentUser->USER_ID)) {
								editCurrentPromotion(currentUser, currentPromotion);
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

				if (headerPromotionList->promotion == NULL) {
					std::cout << "No Promotion in database. Please create one." << std::endl;
					system("pause");
					return;
				}
				else {
					system("cls");
					std::cout << "===================== Results =====================" << std::endl;
					std::cout << "Promotion ID\t| " << "Promotion Name\t|" << "Promotion Description" << std::endl << std::endl;
					while (currentPromotionList->promotion != NULL) {
						if (currentPromotion == NULL) {
							headerforCurrentList = currentPromotionList;
						}
						currentPromotion = currentPromotionList->promotion;
						viewPromotionBrief(currentPromotion);

						if (currentPromotionList->next == NULL) {
							break;
						}
						else {
							currentPromotionList = currentPromotionList->next;
						}
					}

					if (currentPromotion != NULL) {

						std::cout << "\n=========================================================" << std::endl;


						std::cout << "[0]Back"; std::cout << " [1]Select Promotion to View" << std::endl;
						currentPromotionList = headerforCurrentList;
						std::cin >> selected_id;

						switch (selected_id) {

						case 0: {
							system("cls");
							break;
						}
						case 1: {
							do {
								std::cout << "Enter Promotion ID to select:"; std::cin >> selected_id;

								while (currentPromotionList->promotion != NULL) {
									if (currentPromotionList->promotion->PROMOTION_ID == selected_id) {
										currentPromotion = currentPromotionList->promotion;
										break;
									}
									else if (currentPromotionList->next == NULL) {
										std::cout << "No promotion with the selected id is found!" << std::endl;
										break;
									}
									else {
										currentPromotionList = currentPromotionList->next;
									}
								}
								if (currentPromotion != NULL) {
									break;
								}
							} while (selected_id);
							if (currentPromotion != NULL) {
								viewCurrentPromotionInfo(currentPromotion);
								std::cout << "[0]Back ";
								if (currentUser->isAdmin || currentPromotion->PROMOTION_OWNERID == currentUser->USER_ID) {
									std::cout << "[1]Edit " << std::endl;
								}
								std::cin >> selected_id;
								if (selected_id == 1 && (currentUser->isAdmin || currentPromotion->PROMOTION_OWNERID == currentUser->USER_ID)) {
									editCurrentPromotion(currentUser, currentPromotion);
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

						std::cout << "No Promotion in database!\n" << std::endl;


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

void Promotion::viewCurrentPromotionInfo(PromotionData* currentPromotion) {

	std::cout << std::endl;
	std::cout << "==================== Promotion Info =======================" << std::endl;
	std::cout << "ID:  " << currentPromotion->PROMOTION_ID << std::endl;
	std::cout << "Name:  " << currentPromotion->PROMOTION_NAME << std::endl;
	std::cout << "Description:  " << currentPromotion->PROMOTION_DESCRIPTION << std::endl;
	std::cout << "Posting Date: " << currentPromotion->PROMOTION_POSTING_DATE << std::endl;
	std::cout << "Price: " << currentPromotion->PROMOTION_PRICE << std::endl;
	std::cout << "=========================================================" << std::endl << std::endl;

}

void Promotion::viewPromotionBrief(PromotionData* currentPromotion) {

	std::cout << currentPromotion->PROMOTION_ID << "\t" << currentPromotion->PROMOTION_NAME << "\t" << currentPromotion->PROMOTION_DESCRIPTION << std::endl;
}

void Promotion::editCurrentPromotion(UserData* currentUser, PromotionData* selectedPromotion) {

	int selected_id;

	do {
		std::cout << "Selected Promotion to edit:" << std::endl;
		viewCurrentPromotionInfo(selectedPromotion);

		std::cout << "1. Update Promotion Name" << std::endl;
		std::cout << "2. Update Promotion Description" << std::endl;
		std::cout << "3. Update Promotion Posting Date" << std::endl;
		std::cout << "4. Update Promotion Price" << std::endl;
		if (currentUser->isAdmin) std::cout << "5. Update Promotion Owner ID" << std::endl;
		std::cout << "0. Finish edit" << std::endl;

		std::cin >> selected_id;

		switch (selected_id) {
		case 0: {
			system("cls");
			break;
		}
		case 1: {
			std::cin.ignore();
			std::cout << "Enter new Promotion Name: "; std::getline(std::cin, selectedPromotion->PROMOTION_NAME);
			break;
		}
		case 2: {
			std::cin.ignore();
			std::cout << "Enter new Promotion Description: "; std::getline(std::cin, selectedPromotion->PROMOTION_DESCRIPTION);
			break;
		}
		case 3: {
			std::cin.ignore();
			std::cout << "Enter new Promotion Posting Date: "; std::getline(std::cin, selectedPromotion->PROMOTION_POSTING_DATE);
			break;
			
		}
		case 4: {
			std::cin.ignore();
			std::cout << "Enter new Promotion Price: "; std::cin >> selectedPromotion->PROMOTION_PRICE;
			break;
		}
		case 5: {
			std::cin.ignore();
			std::cout << "Enter new Promotion Owner ID: "; std::cin >> selectedPromotion->PROMOTION_OWNERID;
			break;
		}
		default: {
			std::cout << "Invalid input! Try again: "; std::cin >> selected_id;
			break;
		}
			
		}

	} while (selected_id);
	savePromotionListToDatabase();
	loadPromotionListFromDatabase();
}

void Promotion::deleteCurrentPromotion(UserData* currentUser, PromotionData* selectedPromotion) {

	delete selectedPromotion;
	selectedPromotion = NULL;

	std::cout << "Selected Promotion has been deleted" << std::endl;

	savePromotionListToDatabase();
	loadPromotionListFromDatabase();

	return;



}

//void Promotion::viewPromotionGuest()
//{
//	if (headerPromotionList->promotion == NULL) {
//		std::cout << "No Promotion in database." << std::endl;
//		system("pause");
//		return;
//	}
//	else {
//		std::cout << "===================== Promotion list =====================" << std::endl;
//		std::cout << "Promotion ID\t| " << "Promotion Name\t|" << "Promotion Description" << std::endl << std::endl;
//		while (currentPromotionList->promotion != NULL) {
//			if (currentPromotion == NULL) {
//				currentPromotionList = currentPromotionList->next;
//			}
//			currentPromotion = currentPromotionList->promotion;
//			viewPromotionBrief(currentPromotion);
//
//			if (currentPromotionList->next == NULL) {
//				break;
//			}
//			else {
//				currentPromotionList = currentPromotionList->next;
//			}
//		}
//		std::cout<<"==========================================================";
//	}
//}