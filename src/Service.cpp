#include "Service.h"

Service::Service() {

	this->serviceList = new ServiceList;
	this->serviceList->service = NULL;
	this->serviceList->next = NULL;
	this->headerServiceList = serviceList;
	this->currentServiceList = serviceList;
	loadServiceListFromDatabase();
}

ServiceData* Service::getServiceData() { return this->currentService; }
ServiceList* Service::getServiceList() { return this->headerServiceList; }

void Service::saveServiceListToDatabase(){

	currentServiceList = headerServiceList;

	std::string firstpart;
	std::string info;
	std::ofstream file;
	file.open("serviceDB.dat");


	while (true) {

		if (currentServiceList->service) {
			firstpart = "{" + std::to_string(currentServiceList->service->SERVICE_ID) + ";" + std::to_string(currentServiceList->service->SERVICE_OWNERID) + ";" + currentServiceList->service->SERVICE_NAME + ";"
				+ currentServiceList->service->SERVICE_DESCRIPTION + ";" + currentServiceList->service->SERVICE_CONTACTNUMBER + ";" + currentServiceList->service->SERVICE_COMPANY + ";"
				+ currentServiceList->service->SERVICE_WEBSITE + ";" + currentServiceList->service->SERVICE_POSTING_DATE + ";" + std::to_string(currentServiceList->service->SERVICE_PRICE) + "}";

			info = firstpart;

			file << info << std::endl;
		}
		if (currentServiceList->next != NULL) {
			currentServiceList = currentServiceList->next;
		}
		else {
			break;
		}


	}

	file.close();
	std::cout << std::endl << "Service data is saved!" << std::endl;

}

void Service::clearList() {

	ServiceList* list;
	ServiceData* listData;
	while (headerServiceList) {

		if (headerServiceList->next != NULL) {
			list = headerServiceList;
			listData = headerServiceList->service;
			headerServiceList = headerServiceList->next;
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

void Service::loadServiceListFromDatabase() {

	std::string info;
	std::ifstream serviceDatabase("serviceDB.dat");
	std::string::size_type position = 0;

	/*if (userDatabase.fail()) {
		std::cout << "User Database is not found!" << std::endl;
		std::cout << "Creating new user database..." << std::endl;
		std::ofstream outputFile;
		outputFile.open("userDB.dat", std::ios_base::app);
		outputFile.close();
	}*/

	while (std::getline(serviceDatabase, info)) {

		
		if (info.size() > 0) {
			//trim first line that contains service information
			std::string::size_type endOfRawServiceData = 0;
			endOfRawServiceData = info.find("}", endOfRawServiceData);
			std::string serviceRawData;
			serviceRawData = info.substr(1, endOfRawServiceData - 1);

			bool finish = false;
			position = 0;
			std::queue<std::string> serviceDataContainer;
			//parse data
			while (!finish) {

				std::string::size_type start = position;
				position = serviceRawData.find(";", position);
				if (position == std::string::npos) {
					position = serviceRawData.length();
					finish = true;
				}
				serviceDataContainer.push(serviceRawData.substr(start, position - start));
				position++;

			}
			position = 0;
			finish = false;

			if ((serviceDataContainer.size() == 6)) {

				addServiceDataFromDBToList(serviceDataContainer);


			}

		}
		else {
			return;
		}


	}



}

void Service::addServiceDataFromDBToList(std::queue<std::string> serviceDataContainer) {

	ServiceList* newService = new ServiceList;
	newService->service = new ServiceData;
	newService->service->SERVICE_ID = stoi(serviceDataContainer.front()); serviceDataContainer.pop();
	newService->service->SERVICE_OWNERID = stoi(serviceDataContainer.front()); serviceDataContainer.pop();
	newService->service->SERVICE_NAME = serviceDataContainer.front(); serviceDataContainer.pop();
	newService->service->SERVICE_DESCRIPTION = serviceDataContainer.front(); serviceDataContainer.pop();
	newService->service->SERVICE_CONTACTNUMBER = serviceDataContainer.front(); serviceDataContainer.pop();
	newService->service->SERVICE_COMPANY = serviceDataContainer.front(); serviceDataContainer.pop();
	newService->service->SERVICE_WEBSITE = serviceDataContainer.front(); serviceDataContainer.pop();
	newService->service->SERVICE_POSTING_DATE = serviceDataContainer.front(); serviceDataContainer.pop();
	newService->service->SERVICE_PRICE= stod(serviceDataContainer.front()); serviceDataContainer.pop();
	newService->next = NULL;

	if (headerServiceList->service == NULL) {//first load
		
		delete serviceList;
		serviceList = newService;
		headerServiceList = serviceList;
		currentServiceList = headerServiceList;
	}

	else {

		ServiceList* current = headerServiceList;
		while (current) {
			if (current->next == NULL) { current->next = newService; return; }

			else {
				current = current->next;
			}
		}
	}

}

void Service::viewService(UserData* currentUser) {

	ServiceList* headerforCurrentList;
	if (headerServiceList->service == NULL) {
		std::cout << "No Service in database. Please create one.";
		return;
	}
	else {
		system("cls");
		std::cout << "===================== Service Lists =====================" << std::endl;
		std::cout << "Service ID\t| " << "Owner ID\t| " << "Service Name" << std::endl;

		currentServiceList = headerServiceList;
		while (currentServiceList->service != NULL) {

			if (currentUser->isAdmin == true) {
				while (currentServiceList->service != NULL) {

					std::cout << currentServiceList->service->SERVICE_ID << "\t" << currentServiceList->service->SERVICE_OWNERID << "\t" << currentServiceList->service->SERVICE_NAME << std::endl;
					if (currentServiceList->next != NULL) {
						currentServiceList = currentServiceList->next;
					}
					else {
						break;
					}
				}
				goto done;
				std::cout << "=========================================================" << std::endl;
				break;
			}
			//iterate through service list until reach first match
			else if (currentServiceList->service->SERVICE_OWNERID == currentUser->USER_ID) {
				std::cout << currentServiceList->service->SERVICE_ID << "\t" << currentServiceList->service->SERVICE_OWNERID << "\t" << currentServiceList->service->SERVICE_NAME << std::endl;
				while (currentServiceList->service != NULL) {

					//add matches to user companies
					if (currentUser->USER_SERVICES == NULL) {
						currentUser->USER_SERVICES = currentServiceList;
						headerforCurrentList = currentUser->USER_SERVICES;
						break;
					}
					else if (currentUser->USER_SERVICES != NULL && currentUser->USER_SERVICES->next == NULL) {

						currentUser->USER_SERVICES->next = currentServiceList;
						break;

					}
					else {
						break;
					}
				}

			}
			if (currentServiceList->next != NULL) {
				currentServiceList = currentServiceList->next;
			}
			else {
				done:
				int selected_id;

				std::cout << "\n=========================================================" << std::endl;


				std::cout << "[0]Back"; std::cout << " [1]Select Service to View" << std::endl;
				currentServiceList = headerforCurrentList;
				std::cin >> selected_id;

				switch (selected_id) {

				case 0: {
					system("cls");
					break;
				}
				case 1: {
					do {
						std::cout << "Enter Service ID to select:"; std::cin >> selected_id;

						while (currentServiceList->service != NULL) {
							if (currentServiceList->service->SERVICE_ID == selected_id) {
								currentService = currentServiceList->service;
								break;
							}
							else if (currentServiceList->next == NULL) {
								std::cout << "No service with the selected id is found!" << std::endl;
								break;
							}
							else {
								currentServiceList = currentServiceList->next;
							}
						}
						if (currentService != NULL) {
							break;
						}
					} while (selected_id);
					if (currentService != NULL) {
						viewCurrentServiceInfo(currentService);
						std::cout << "[0]Back ";
						if (currentUser->isAdmin || currentService->SERVICE_OWNERID == currentUser->USER_ID) {
							std::cout << "[1]Edit " << std::endl;
						}
						std::cin >> selected_id;
						if (selected_id == 1 && (currentUser->isAdmin || currentService->SERVICE_OWNERID == currentUser->USER_ID)) {
							editCurrentService(currentUser, currentService);
						}

						else {
							break;
						}
					}
				}
					  break;
				}

			}

		}

	}
}

void Service::checkValidInput(std::string& s) {

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

void Service::checkValidInputNumber(std::string& s) {

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

time_t Service::generateID() { time_t currentTime = time(0); return currentTime; }

std::string Service::postingDate() {
	time_t currentTime = time(0);
	std::string dt = ctime(&currentTime);
	dt = dt.substr(0, (dt.length() - 1));
	return dt;
}

void Service::addService(UserData* currentUser) {

		ServiceList* newService = new ServiceList;
		newService->service = new ServiceData;
		newService->next = NULL;
		newService->service->SERVICE_POSTING_DATE = postingDate();
		std::cin.ignore();

		newService->service->SERVICE_ID = generateID();
		if (currentUser->isAdmin){
			std::cout << "Enter Owner ID: "; std::cin >> newService->service->SERVICE_OWNERID;
			std::cin.ignore();
		}
		else if (currentUser->isEmployer) {
			newService->service->SERVICE_OWNERID = currentUser->USER_ID;
		}
		else { 
			std::cout << "You don't have permission to add a new Service!"; return; //tosolve
		}
		
		std::cout << "Enter Service Name: "; std::getline(std::cin, newService->service->SERVICE_NAME);
		std::cout << "Enter Service Description: "; std::getline(std::cin, newService->service->SERVICE_DESCRIPTION);
		std::cout << "Enter Service Contact Number: "; std::getline(std::cin, newService->service->SERVICE_CONTACTNUMBER);
		checkValidInputNumber(newService->service->SERVICE_CONTACTNUMBER);
		std::cout << "Enter Service Company: "; std::getline(std::cin, newService->service->SERVICE_COMPANY);
		std::cout << "Enter Service Website: "; std::getline(std::cin, newService->service->SERVICE_WEBSITE);
		newService->service->SERVICE_POSTING_DATE = postingDate();
		std::cout << "Enter Service Price: "; std::cin >> newService->service->SERVICE_PRICE;


		if (headerServiceList->service == NULL) {//first load
			
			serviceList = newService;
			headerServiceList = serviceList;
			currentServiceList = headerServiceList;
		}

		else {

			ServiceList* current = headerServiceList;
			while (current) {
				if (current->next == NULL) { current->next = newService; return; }

				else {
					current = current->next;
				}
			}
		}

		/*else {

			currentServiceList = headerServiceList;
			while (currentServiceList) {
				if (currentUser->isEmployer) {
					if (currentUser->USER_SERVICES == NULL) { currentUser->USER_SERVICES = newService; break; }
					if (currentUser->USER_SERVICES != NULL && currentUser->USER_SERVICES->next == NULL) { currentUser->USER_SERVICES->next = newService; break; }
				}
				if (currentServiceList->next == NULL) { currentServiceList->next = newService; break; }

				else {
					currentServiceList = currentServiceList->next;
				}
			}
		}*/

		saveServiceListToDatabase();
		viewService(currentUser);
		system("Pause");
}

void Service::editService(UserData* currentUser){

		currentServiceList = headerServiceList;
		int selected_id;
		currentService = NULL;
		std::cin.ignore();
		if (currentUser->isAdmin || currentUser->isEmployer) {
			
			std::cout << "Select Service ID:" << std::endl; std::cin >> selected_id;
		}
		else {
			std::cout << "You don't have permission to edit this Service!"; return;
		}
			
		if (currentUser->isAdmin) {
			while (currentServiceList->service != NULL) {
				if (currentServiceList->service->SERVICE_ID == selected_id) {
					currentService = currentServiceList->service;
					break;
				}
				else if (currentServiceList->next == NULL) {
					std::cout << "No service with the selected id is found!";
					return;
				}
				else {
					currentServiceList = currentServiceList->next;
				}
			}
		}
		else if(currentUser->isEmployer){
			ServiceList* curr = currentUser->USER_SERVICES;
			while (curr != NULL) {
				if (curr->service->SERVICE_ID == selected_id) {
					currentService = curr->service;
					break;
				}
				else if (curr->next == NULL) {
					std::cout << "No service with the selected id is found!";
					return;
				}
				else {
					curr = curr->next;
				}
			}
		}

		std::cout << "Selected Service to edit:" << std::endl;
		viewCurrentServiceInfo(currentService);

		editCurrentService(currentUser, currentService);
	   							
		saveServiceListToDatabase();
}

void Service::deleteService(UserData* currentUser){


}

void Service::searchService(UserData* currentUser) {

	int selected_id;
	ServiceList* headerforCurrentList;
	do {
		
		std::string keyword = "";
		std::cin.ignore();
		currentServiceList = headerServiceList;
		currentService = NULL;

		std::cout << "1. Search by Service ID" << std::endl;
		std::cout << "2. Search by Service Name" << std::endl;
		std::cout << "3. Search by Service Company" << std::endl;
		std::cout << "4. View All  Services" << std::endl;
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
				std::cout << "Enter Service ID: "; std::cin >> selected_id;

				system("cls");
				std::cout << "===================== Results =====================" << std::endl;
				std::cout << "Service ID\t| " << "Service Name\t|" << "Service Description" << std::endl << std::endl;

				if (headerServiceList->service == NULL) {
					std::cout << "No Service in database. Please create one." << std::endl;
					system("pause");
					return;
				}
				else {
					while (currentServiceList->service != NULL) {
						if (std::to_string(currentServiceList->service->SERVICE_ID).find(std::to_string(selected_id)) != std::string::npos) {
							if (currentService == NULL) {
								headerforCurrentList = currentServiceList;
							}
							currentService = currentServiceList->service;
							viewServiceBrief(currentService);
							if (currentServiceList->next == NULL) {
								break;
							}
							else {
								currentServiceList = currentServiceList->next;
							}
						}
						else if (currentServiceList->next == NULL && currentService == NULL) {
							std::cout << "No service with the id is found!" << std::endl;
							system("pause");
							break;
						}
						else if (currentServiceList->next == NULL) {
							break;
						}
						else {
							currentServiceList = currentServiceList->next;
						}
					}
				}

				if (currentService != NULL) {

					std::cout << "\n=========================================================" << std::endl;

					
					std::cout << "[0]Back"; std::cout << " [1]Select Service to View" << std::endl;
					currentServiceList = headerforCurrentList;
					std::cin >> selected_id;

					switch (selected_id) {

						case 0: {
							break;
						}
						case 1: {
							std::cout << "Enter Service ID to select:"; std::cin >> selected_id;

							while (true) {
								if (currentServiceList->service->SERVICE_ID == selected_id) {
									currentService = currentServiceList->service;
									break;
								}
								else if (currentServiceList->next == NULL) {
									std::cout << "No service with the selected id is found!" << std::endl;
									return;
								}
								else {
									currentServiceList = currentServiceList->next;
								}
							}

							viewCurrentServiceInfo(currentService);
							std::cout << "[0]Back ";
							if (currentUser->isAdmin || currentService->SERVICE_OWNERID == currentUser->USER_ID) {
								std::cout << "[1]Edit " << std::endl;
							}
							std::cin >> selected_id;
							if (selected_id == 1 && (currentUser->isAdmin || currentService->SERVICE_OWNERID == currentUser->USER_ID)) {
								editCurrentService(currentUser, currentService);
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
				std::cout << "Enter Service Name: "; std::cin >> keyword;

				system("cls");
				std::cout << "===================== Results =====================" << std::endl;
				std::cout << "Service ID\t| " << "Service Name\t|" << "Service Description"<< std::endl << std::endl;

				if (headerServiceList->service == NULL) {
					std::cout << "No Service in database. Please create one." << std::endl;
					system("pause");
					return;
				}
				else {
					while (currentServiceList->service != NULL) {
						if (currentServiceList->service->SERVICE_NAME.find(keyword) != std::string::npos) {
							if (currentService == NULL) {
								headerforCurrentList = currentServiceList;
							}
							currentService = currentServiceList->service;
							viewServiceBrief(currentService);
							if (currentServiceList->next == NULL) {
								break;
							}
							else {
								currentServiceList = currentServiceList->next;
							}
						}
						else if (currentServiceList->next == NULL && currentService == NULL) {
							std::cout << "No service with the name is found!" << std::endl;
							system("pause");
							break;
						}
						else if (currentServiceList->next == NULL) {
							break;
						}
						else {
							currentServiceList = currentServiceList->next;
						}
					}
				}
				if (currentService != NULL) {

					std::cout << "\n=========================================================" << std::endl;


					std::cout << "[0]Back"; std::cout << " [1]Select Service to View" << std::endl;
					currentServiceList = headerforCurrentList;
					std::cin >> selected_id;

					switch (selected_id) {

					case 0: {
						break;
					}
					case 1: {
						std::cout << "Enter Service ID to select:"; std::cin >> selected_id;

						while (true) {
							if (currentServiceList->service->SERVICE_ID == selected_id) {
								currentService = currentServiceList->service;
								break;
							}
							else if (currentServiceList->next == NULL) {
								std::cout << "No service with the selected id is found!" << std::endl;
								return;
							}
							else {
								currentServiceList = currentServiceList->next;
							}
						}

						viewCurrentServiceInfo(currentService);
						std::cout << "[0]Back ";
						if (currentUser->isAdmin || currentService->SERVICE_OWNERID == currentUser->USER_ID) {
							std::cout << "[1]Edit " << std::endl;
						}
						std::cin >> selected_id;
						if (selected_id == 1 && (currentUser->isAdmin || currentService->SERVICE_OWNERID == currentUser->USER_ID)) {
							editCurrentService(currentUser, currentService);
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
				std::cout << "Service ID\t| " << "Service Name\t|" << "Service Description" << std::endl << std::endl;

				if (headerServiceList->service == NULL) {
					std::cout << "No Service in database. Please create one." << std::endl;
					system("pause");
					return;
				}
				else {
					while (currentServiceList->service != NULL) {
						if (currentServiceList->service->SERVICE_COMPANY.find(keyword) != std::string::npos) {
							if (currentService == NULL) {
								headerforCurrentList = currentServiceList;
							}
							currentService = currentServiceList->service;
							viewServiceBrief(currentService);
							if (currentServiceList->next == NULL) {
								break;
							}
							else {
								currentServiceList = currentServiceList->next;
							}
						}
						else if (currentServiceList->next == NULL && currentService == NULL) {
							std::cout << "No service with the keyword is found!" << std::endl;
							system("pause");
							break;
						}
						else if (currentServiceList->next == NULL) {
							break;
						}
						else {
							currentServiceList = currentServiceList->next;
						}
					}
				}

				if (currentService != NULL) {

					std::cout << "\n=========================================================" << std::endl;


					std::cout << "[0]Back"; std::cout << " [1]Select Service to View" << std::endl;
					currentServiceList = headerforCurrentList;
					std::cin >> selected_id;

					switch (selected_id) {

						case 0: {
							break;
						}
						case 1: {
							std::cout << "Enter Service ID to select:"; std::cin >> selected_id;

							while (true) {
								if (currentServiceList->service->SERVICE_ID == selected_id) {
									currentService = currentServiceList->service;
									break;
								}
								else if (currentServiceList->next == NULL) {
									std::cout << "No service with the selected id is found!" << std::endl;
									return;
								}
								else {
									currentServiceList = currentServiceList->next;
								}
							}

							viewCurrentServiceInfo(currentService);
							std::cout << "[0]Back ";
							if (currentUser->isAdmin || currentService->SERVICE_OWNERID == currentUser->USER_ID) {
								std::cout << "[1]Edit " << std::endl;
							}
							std::cin >> selected_id;
							if (selected_id == 1 && (currentUser->isAdmin || currentService->SERVICE_OWNERID == currentUser->USER_ID)) {
								editCurrentService(currentUser, currentService);
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

				if (headerServiceList->service == NULL) {
					std::cout << "No Service in database. Please create one." << std::endl;
					system("pause");
					return;
				}
				else {
					system("cls");
					std::cout << "===================== Results =====================" << std::endl;
					std::cout << "Service ID\t| " << "Service Name\t|" << "Service Description" << std::endl << std::endl;
					while (currentServiceList->service != NULL) {
						if (currentService == NULL) {
							headerforCurrentList = currentServiceList;
						}
						currentService = currentServiceList->service;
						viewServiceBrief(currentService);

						if (currentServiceList->next == NULL) {
							break;
						}
						else {
							currentServiceList = currentServiceList->next;
						}
					}

					if (currentService != NULL) {

						std::cout << "\n=========================================================" << std::endl;


						std::cout << "[0]Back"; std::cout << " [1]Select Service to View" << std::endl;
						currentServiceList = headerforCurrentList;
						std::cin >> selected_id;

						switch (selected_id) {

						case 0: {
							system("cls");
							break;
						}
						case 1: {
							do {
								std::cout << "Enter Service ID to select:"; std::cin >> selected_id;

								while (currentServiceList->service != NULL) {
									if (currentServiceList->service->SERVICE_ID == selected_id) {
										currentService = currentServiceList->service;
										break;
									}
									else if (currentServiceList->next == NULL) {
										std::cout << "No service with the selected id is found!" << std::endl;
										break;
									}
									else {
										currentServiceList = currentServiceList->next;
									}
								}
								if (currentService != NULL) {
									break;
								}
							} while (selected_id);
							if (currentService != NULL) {
								viewCurrentServiceInfo(currentService);
								std::cout << "[0]Back ";
								if (currentUser->isAdmin || currentService->SERVICE_OWNERID == currentUser->USER_ID) {
									std::cout << "[1]Edit " << std::endl;
								}
								std::cin >> selected_id;
								if (selected_id == 1 && (currentUser->isAdmin || currentService->SERVICE_OWNERID == currentUser->USER_ID)) {
									editCurrentService(currentUser, currentService);
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

						std::cout << "No Service in database!\n" << std::endl;


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

void Service::viewCurrentServiceInfo(ServiceData* currentService) {

	std::cout << std::endl;
	std::cout << "==================== Service Info =======================" << std::endl;
	std::cout << "ID:  " << currentService->SERVICE_ID << std::endl;
	std::cout << "Owner Id:  " << currentService->SERVICE_OWNERID << std::endl;
	std::cout << "Name:  " << currentService->SERVICE_NAME << std::endl;
	std::cout << "Description:  " << currentService->SERVICE_DESCRIPTION << std::endl;
	std::cout << "Contact Number:  " << currentService->SERVICE_CONTACTNUMBER << std::endl;
	std::cout << "Company:  " << currentService->SERVICE_COMPANY << std::endl;
	std::cout << "Website:  " << currentService->SERVICE_WEBSITE << std::endl;
	std::cout << "Posting Date: " << currentService->SERVICE_POSTING_DATE << std::endl;
	std::cout << "Price: " << currentService->SERVICE_PRICE << std::endl;
	std::cout << "=========================================================" << std::endl << std::endl;

}

void Service::viewServiceBrief(ServiceData* currentService) {

	std::cout << currentService->SERVICE_ID << "\t" << currentService->SERVICE_NAME << "\t" << currentService->SERVICE_DESCRIPTION << std::endl;
}

void Service::editCurrentService(UserData* currentUser, ServiceData* selectedService) {

	int selected_id;

	do {
		std::cout << "Selected Service to edit:" << std::endl;
		viewCurrentServiceInfo(selectedService);

		std::cout << "1. Update Service Name" << std::endl;
		std::cout << "2. Update Service Description" << std::endl;
		std::cout << "3. Update Service Contact Number" << std::endl;
		std::cout << "4. Update Service Company" << std::endl;
		std::cout << "5. Update Service Website" << std::endl;
		std::cout << "6. Update Service Posting Date" << std::endl;
		std::cout << "7. Update Service Price" << std::endl;
		if (currentUser->isAdmin) std::cout << "8. Update Service Owner ID" << std::endl;
		std::cout << "0. Finish edit" << std::endl;

		std::cin >> selected_id;

		switch (selected_id) {
		case 0: {
			system("cls");
			break;
		}
		case 1: {
			std::cin.ignore();
			std::cout << "Enter new Service Name: "; std::getline(std::cin, selectedService->SERVICE_NAME);
			break;
		}
		case 2: {
			std::cin.ignore();
			std::cout << "Enter new Service Description: "; std::getline(std::cin, selectedService->SERVICE_DESCRIPTION);
			break;
		}
		case 3: {
			std::cin.ignore();
			std::cout << "Enter new Service Contact NUmber: "; std::getline(std::cin, selectedService->SERVICE_CONTACTNUMBER);
			break;
			
		}
		case 4: {
			std::cin.ignore();
			std::cout << "Enter new Service Company: "; std::cin >> selectedService->SERVICE_COMPANY;
			break;
		}
		case 5: {
			std::cin.ignore();
			std::cout << "Enter new Service Website: "; std::cin >> selectedService->SERVICE_WEBSITE;
			break;
		}
		case 6: {
			std::cin.ignore();
			std::cout << "Enter new Service Posting Date: "; std::cin >> selectedService->SERVICE_POSTING_DATE;
			break;
		}
		case 7: {
			std::cin.ignore();
			std::cout << "Enter new Service Price: "; std::cin >> selectedService->SERVICE_PRICE;
			break;
		}
		default: {
			std::cout << "Invalid input! Try again: "; std::cin >> selected_id;
			break;
		}
			
		}

	} while (selected_id);
	saveServiceListToDatabase();
}

void Service::deleteCurrentService(UserData* currentUser, ServiceData* selectedService) {

	delete selectedService;
	selectedService = NULL;

	std::cout << "Selected Service has been deleted" << std::endl;

	saveServiceListToDatabase();

	return;



}