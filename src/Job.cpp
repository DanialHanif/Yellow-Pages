#include "Job.h"

Job::Job() {

	this->jobList = new JobList;
	this->jobList->job = NULL;
	this->jobList->next = NULL;
	this->headerJobList = jobList;
	this->currentJobList = jobList;
	this->currentJob = NULL;
	this->headerforCurrentList = NULL;
	loadJobListFromDatabase();
}

JobData* Job::getJobData() { return this->currentJob; }
JobList* Job::getJobList() { return this->headerJobList; }

void Job::saveJobListToDatabase() {

	currentJobList = headerJobList;

	std::string firstpart;
	std::string info;
	std::ofstream file;
	file.open("jobDB.dat");


	while (true) {

		if (currentJobList->job != NULL) {
			firstpart = "{" + std::to_string(currentJobList->job->JOB_ID) + ";" + std::to_string(currentJobList->job->JOB_OWNERID) + ";" + currentJobList->job->JOB_NAME + ";" + currentJobList->job->JOB_DESCRIPTION + ";"
				+ currentJobList->job->JOB_POSITION + ";" + currentJobList->job->JOB_CONTACTNUMBER + ";" + currentJobList->job->JOB_WEBSITE + ";" + currentJobList->job->JOB_COMPANY + ";" + currentJobList->job->JOB_POSTING_DATE + "}";

			info = firstpart;

			file << info << std::endl;
		}
			if (currentJobList->next != NULL) {
				currentJobList = currentJobList->next;
			}
			else {
				break;
			}

		
	}

	file.close();
	std::cout << std::endl << "Job data is saved!" << std::endl;

}

void Job::clearList() {

	JobList* list;
	JobData* listData;
	while (jobList) {

		if (jobList->next != NULL) {
			list = jobList;
			listData = jobList->job;
			jobList = jobList->next;
			delete listData;
			delete list;
			listData = NULL;
			list = NULL;
		}
			
		else {
			list = jobList;
			listData = jobList->job;
			delete listData;
			delete list;
			listData = NULL;
			list = NULL;
			jobList->job = NULL;
			jobList = NULL;
			return;
		}
	}


}

void Job::loadJobListFromDatabase() {

	
	std::string info;
	std::ifstream jobDatabase("jobDB.dat");
	std::string::size_type position = 0;

	while (std::getline(jobDatabase, info)) {


		if (info.size() > 0) {
			//trim first line that contains job information
			std::string::size_type endOfRawJobData = 0;
			endOfRawJobData = info.find("}", endOfRawJobData);
			std::string jobRawData;
			jobRawData = info.substr(1, endOfRawJobData - 1);

			bool finish = false;
			position = 0;
			std::queue<std::string> jobDataContainer;
			//parse data
			while (!finish) {

				std::string::size_type start = position;
				position = jobRawData.find(";", position);
				if (position == std::string::npos) {
					position = jobRawData.length();
					finish = true;
				}
				jobDataContainer.push(jobRawData.substr(start, position - start));
				position++;

			}
			position = 0;
			finish = false;

			if ((jobDataContainer.size() == 9)) {

				addJobDataFromDBToList(jobDataContainer);


			}

		}
		else {
			return;
		}


	}



}

void Job::addJobDataFromDBToList(std::queue<std::string> jobDataContainer) {

	JobList* newJob = new JobList;
	newJob->job = new JobData;
	newJob->job->JOB_ID = stoi(jobDataContainer.front()); jobDataContainer.pop();
	newJob->job->JOB_OWNERID = stoi(jobDataContainer.front()); jobDataContainer.pop();
	newJob->job->JOB_NAME = jobDataContainer.front(); jobDataContainer.pop();
	newJob->job->JOB_DESCRIPTION = jobDataContainer.front(); jobDataContainer.pop();
	newJob->job->JOB_POSITION = jobDataContainer.front(); jobDataContainer.pop();
	newJob->job->JOB_CONTACTNUMBER = jobDataContainer.front(); jobDataContainer.pop();
	newJob->job->JOB_WEBSITE = jobDataContainer.front(); jobDataContainer.pop();
	newJob->job->JOB_COMPANY = jobDataContainer.front(); jobDataContainer.pop();
	newJob->job->JOB_POSTING_DATE = jobDataContainer.front(); jobDataContainer.pop();
	newJob->next = NULL;

	if (headerJobList->job == NULL) {//first load

		delete jobList;
		jobList = newJob;
		headerJobList = jobList;
		currentJobList = headerJobList;
	}

	else {

		JobList* current = headerJobList;
		while (true) {
			if (current->next == NULL) { current->next = newJob; return; }

			else {
				current = current->next;
			}
		}
	}

}

void Job::viewJob(UserData* currentUser) {

	if (headerJobList->job == NULL) {
		std::cout << "No Job in database. Please create one.";
		return;
	}
	else {
		system("cls");
		std::cout << "===================== Job Lists =====================" << std::endl;
		std::cout << "Job ID\t| " << "Owner ID\t| " << "Job Name" << std::endl << std::endl;

		currentJobList = headerJobList;
		while (currentJobList->job != NULL) {

			if (currentUser->isAdmin) {
				while (currentJobList->job != NULL) {

					std::cout << currentJobList->job->JOB_ID << "\t" << currentJobList->job->JOB_OWNERID << "\t" << currentJobList->job->JOB_NAME << std::endl;
					if (currentJobList->next != NULL) {
						currentJobList = currentJobList->next;
					}
					else {
						break;
					}
				}
				headerforCurrentList = headerJobList;
				goto done;
				break;
			}
			//iterate through job list until reach first match
			else if (currentUser->isEmployer && currentJobList->job->JOB_OWNERID == currentUser->USER_ID) {
				std::cout << currentJobList->job->JOB_ID << "\t" << currentJobList->job->JOB_OWNERID << "\t" << currentJobList->job->JOB_NAME << std::endl;
				//while (currentJobList->job != NULL) {

					//add matches to user jobs
					if (currentUser->USER_JOBS == NULL) {
						currentUser->USER_JOBS = new JobList;
						currentUser->USER_JOBS->next = NULL;
						currentUser->USER_JOBS->job = currentJobList->job;
						headerforCurrentList = currentUser->USER_JOBS;

						//break;
					}
					else if (currentUser->USER_JOBS->next == NULL) {
						currentUser->USER_JOBS->next = new JobList;
						currentUser->USER_JOBS->next->job = currentJobList->job;
						currentUser->USER_JOBS->next->next = NULL;
						currentUser->USER_JOBS = currentUser->USER_JOBS->next;
							//break;
					

					}
					else {
						//break;
					}
				//}

			}
			if (currentJobList->next != NULL) {
				currentJobList = currentJobList->next;
			}
			else {
			done:

				currentUser->USER_JOBS = headerforCurrentList;

				if (headerforCurrentList == NULL) std::cout << "No Company in database. Please create one.\n";
								
				std::cout << "\n=========================================================" << std::endl;
				int selected_id;

				std::cout << "[0]Back"; 
				if (headerforCurrentList != NULL) std::cout << " [1]Select Job to View" << std::endl;
				
				std::cout << std::endl;
				std::cin >> selected_id;
				checkInput(selected_id);
				switch (selected_id) {

				case 0: {
					system("cls");
					break;
				}
				case 1: {
					std::cout << "Enter Job ID to select:"; std::cin >> selected_id; checkInput(selected_id);

					currentJobList = headerforCurrentList;
					while (currentJobList) {

						if (currentJobList->job->JOB_ID == selected_id) {
							currentJob = currentJobList->job;
							break;
						}
						else if (currentJobList->next != NULL) {
							currentJobList = currentJobList->next;
							
						}
						else {
							std::cout << "No Job with the selected id is found!" << std::endl;
							system("pause");
							system("cls");
							return;
						}
					}

					viewCurrentJobInfo(currentJob);
					std::cout << "[0]Back ";
					if (currentUser->isAdmin || currentJob->JOB_OWNERID == currentUser->USER_ID) {
						std::cout << "[1]Edit " << std::endl;
					}
					std::cin >> selected_id; checkInput(selected_id);
					if (selected_id == 1 && (currentUser->isAdmin || currentJob->JOB_OWNERID == currentUser->USER_ID)) {
						editCurrentJob(currentUser, currentJob);
					}

					else {
						break;
					}
				}
				default: {
					break;
				}
				}
				break;
			}

		}

	}
	


}

void Job::checkValidInput(std::string& s) {

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

void Job::checkValidInputNumber(std::string& s) {

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

time_t Job::generateID() { time_t currentTime = time(0); return currentTime; }

std::string Job::postingDate() {
	time_t currentTime = time(0);
	std::string dt = ctime(&currentTime);
	dt = dt.substr(0, (dt.length() - 1));
	return dt;
}

void Job::addJob(UserData* currentUser) {

	JobList* newJob = new JobList;
	newJob->job = new JobData;
	newJob->next = NULL;
	newJob->job->JOB_POSTING_DATE = postingDate();
	std::cin.ignore();

	newJob->job->JOB_ID = generateID();
	if (currentUser->isAdmin) {
		std::cout << "Enter Owner ID: "; std::cin >> newJob->job->JOB_OWNERID;
		std::cin.ignore();
	}
	else if (currentUser->isEmployer) {
		newJob->job->JOB_OWNERID = currentUser->USER_ID;
	}
	else {
		std::cout << "You don't have permission to add a new Job!"; return; //tosolve
	}

	std::cout << "Enter Job Name: "; std::getline(std::cin, newJob->job->JOB_NAME);
	std::cout << "Enter Job Description: "; std::getline(std::cin, newJob->job->JOB_DESCRIPTION);
	std::cout << "Enter Job Position: "; std::getline(std::cin, newJob->job->JOB_POSITION);
	std::cout << "Enter Job Contact Number: "; std::getline(std::cin, newJob->job->JOB_CONTACTNUMBER);
	std::cout << "Enter Job Website: "; std::getline(std::cin, newJob->job->JOB_WEBSITE);
	std::cout << "Enter Job Company: "; std::getline(std::cin, newJob->job->JOB_COMPANY);
	newJob->job->JOB_POSTING_DATE = postingDate();


	if (headerJobList->job == NULL) {//first load

		jobList = newJob;
		headerJobList = jobList;
		currentJobList = headerJobList;
		saveJobListToDatabase();
		viewJob(currentUser);
	}

	else {

		JobList* current = headerJobList;
		while (true) {
			if (current->next == NULL) {
				current->next = newJob;
				saveJobListToDatabase();
				viewJob(currentUser);
				return;
			}

			else {
				current = current->next;
			}
		}
	}

	/*else {


		currentJobList = headerJobList;
		while (currentJobList->job) {
			if (currentUser->isEmployer) {
				if (currentUser->USER_JOBS == NULL) { currentUser->USER_JOBS = newJob; break; }
				if (currentUser->USER_JOBS != NULL && currentUser->USER_JOBS->next == NULL) { currentUser->USER_JOBS->next = newJob; break; }
			}
			if (currentJobList->next == NULL) { currentJobList->next = newJob; break; }

			else {
				currentJobList = currentJobList->next;
			}
		}
	}*/

	/*saveJobListToDatabase();
	viewJob(currentUser);
	system("Pause");*/
}

void Job::editJob(UserData* currentUser) {

	currentJobList = headerJobList;
	int selected_id;
	currentJob = NULL;
	std::cin.ignore();
	if (currentUser->isAdmin || currentUser->isEmployer) {

		std::cout << "Select Job ID:" << std::endl; std::cin >> selected_id; checkInput(selected_id);
	}
	else {
		std::cout << "You don't have permission to edit this Job!"; return;
	}

	if (currentUser->isAdmin) {
		while (currentJobList->job != NULL) {
			if (currentJobList->job->JOB_ID == selected_id) {
				currentJob = currentJobList->job;
				break;
			}
			else if (currentJobList->next == NULL) {
				std::cout << "No Job with the selected id is found!";
				return;
			}
			else {
				currentJobList = currentJobList->next;
			}
		}
	}
	else if (currentUser->isEmployer) {
		JobList* curr = currentUser->USER_JOBS;
		while (curr != NULL) {
			if (curr->job->JOB_ID == selected_id) {
				currentJob = curr->job;
				break;
			}
			else if (curr->next == NULL) {
				std::cout << "No Job with the selected id is found!";
				return;
			}
			else {
				curr = curr->next;
			}
		}
	}

	std::cout << "Selected Job to edit:" << std::endl;
	viewCurrentJobInfo(currentJob);

	editCurrentJob(currentUser, currentJob);

	saveJobListToDatabase();
}

void Job::deleteJob(UserData* currentUser) {

	currentJobList = headerJobList;
	int selected_id;
	currentJob = NULL;
	std::cin.ignore();
	if (currentUser->isAdmin || currentUser->isEmployer) {

		std::cout << "Select Job ID:" << std::endl; std::cin >> selected_id; checkInput(selected_id);
	}
	else {
		std::cout << "You don't have permission to edit this Job post!"; return;
	}

	if (currentUser->isAdmin) {
		while (currentJobList->job != NULL) {
			if (currentJobList->job->JOB_ID == selected_id) {
				currentJob = currentJobList->job;
				break;
			}
			else if (currentJobList->next == NULL) {
				std::cout << "No company with the selected id is found!";
				return;
			}
			else {
				currentJobList = currentJobList->next;
			}
		}
	}
	else if (currentUser->isEmployer) {
		JobList* curr = currentUser->USER_JOBS;
		while (curr != NULL) {
			if (curr->job->JOB_ID == selected_id) {
				currentJob = curr->job;
				break;
			}
			else if (curr->next == NULL) {
				std::cout << "No job with the selected id is found!";
				return;
			}
			else {
				curr = curr->next;
			}
		}
	}

	std::cout << "Selected Job to delete:" << std::endl;
	viewCurrentJobInfo(currentJob);

	deleteCurrentJob(currentUser, currentJob);

	saveJobListToDatabase();
}

void Job::searchJob(UserData* currentUser) {

	int selected_id;
	JobList* headerforCurrentList;
	do {

		std::string keyword = "";
		std::cin.ignore();
		currentJobList = headerJobList;
		currentJob = NULL;

		std::cout << "1. Search by Job ID" << std::endl;
		std::cout << "2. Search by Name" << std::endl;
		std::cout << "3. Search by Keyword" << std::endl;
		std::cout << "4. View All Jobs" << std::endl;
		std::cout << "0. Exit Search" << std::endl;
		std::cout << "\n\tChoice : ";
		std::cin >> selected_id; checkInput(selected_id);

		switch (selected_id) {
		case 0: {
			std::cin.ignore();
			system("cls");
			return;
		}
		case 1: {
			std::cin.ignore();
			std::cout << "Enter Job ID: "; std::cin >> selected_id; checkInput(selected_id);

			system("cls");
			std::cout << "===================== Results =====================" << std::endl;
			std::cout << "Job ID\t| " << "Job Name\t|" << "Job Description" << std::endl << std::endl;

			if (headerJobList->job == NULL) {
				std::cout << "No Job in database. Please create one." << std::endl;
				system("pause");
				return;
			}
			else {
				while (currentJobList->job != NULL) {
					if (std::to_string(currentJobList->job->JOB_ID).find(std::to_string(selected_id)) != std::string::npos) {
						if (currentJob == NULL) {
							headerforCurrentList = currentJobList;
						}
						currentJob = currentJobList->job;
						viewJobBrief(currentJob);
						if (currentJobList->next == NULL) {
							break;
						}
						else {
							currentJobList = currentJobList->next;
						}
					}
					else if (currentJobList->next == NULL && currentJob == NULL) {
						std::cout << "No Job with the id is found!" << std::endl;
						system("pause");
						break;
					}
					else if (currentJobList->next == NULL) {
						break;
					}
					else {
						currentJobList = currentJobList->next;
					}
				}
			}

			if (currentJob != NULL) {

				std::cout << "\n=========================================================" << std::endl;


				std::cout << "[0]Back"; std::cout << " [1]Select Job to View" << std::endl;
				currentJobList = headerforCurrentList;
				std::cin >> selected_id; checkInput(selected_id);

				switch (selected_id) {

				case 0: {
					break;
				}
				case 1: {
					std::cout << "Enter Job ID to select:"; std::cin >> selected_id; checkInput(selected_id);

					while (true) {
						if (currentJobList->job->JOB_ID == selected_id) {
							currentJob = currentJobList->job;
							break;
						}
						else if (currentJobList->next == NULL) {
							std::cout << "No Job with the selected id is found!" << std::endl;
							return;
						}
						else {
							currentJobList = currentJobList->next;
						}
					}

					viewCurrentJobInfo(currentJob);
					std::cout << "[0]Back ";
					if (currentUser->isAdmin || currentJob->JOB_OWNERID == currentUser->USER_ID) {
						std::cout << "[1]Edit " << std::endl;
					}
					std::cin >> selected_id; checkInput(selected_id);
					if (selected_id == 1 && (currentUser->isAdmin || currentJob->JOB_OWNERID == currentUser->USER_ID)) {
						editCurrentJob(currentUser, currentJob);
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
			std::cout << "Enter Job Name: "; std::cin >> keyword;

			system("cls");
			std::cout << "===================== Results =====================" << std::endl;
			std::cout << "Job ID\t| " << "Job Name\t|" << "Job Description" << std::endl << std::endl;

			if (headerJobList->job == NULL) {
				std::cout << "No Job in database. Please create one." << std::endl;
				system("pause");
				return;
			}
			else {
				while (currentJobList->job != NULL) {
					if (currentJobList->job->JOB_NAME.find(keyword) != std::string::npos) {
						if (currentJob == NULL) {
							headerforCurrentList = currentJobList;
						}
						currentJob = currentJobList->job;
						viewJobBrief(currentJob);
						if (currentJobList->next == NULL) {
							break;
						}
						else {
							currentJobList = currentJobList->next;
						}
					}
					else if (currentJobList->next == NULL && currentJob == NULL) {
						std::cout << "No Job with the name is found!" << std::endl;
						system("pause");
						break;
					}
					else if (currentJobList->next == NULL) {
						break;
					}
					else {
						currentJobList = currentJobList->next;
					}
				}
			}
			if (currentJob != NULL) {

				std::cout << "\n=========================================================" << std::endl;


				std::cout << "[0]Back"; std::cout << " [1]Select Job to View" << std::endl;
				currentJobList = headerforCurrentList;
				std::cin >> selected_id; checkInput(selected_id);

				switch (selected_id) {

				case 0: {
					break;
				}
				case 1: {
					std::cout << "Enter Job ID to select:"; std::cin >> selected_id; checkInput(selected_id);

					while (true) {
						if (currentJobList->job->JOB_ID == selected_id) {
							currentJob = currentJobList->job;
							break;
						}
						else if (currentJobList->next == NULL) {
							std::cout << "No Job with the selected id is found!" << std::endl;
							return;
						}
						else {
							currentJobList = currentJobList->next;
						}
					}

					viewCurrentJobInfo(currentJob);
					std::cout << "[0]Back ";
					if (currentUser->isAdmin || currentJob->JOB_OWNERID == currentUser->USER_ID) {
						std::cout << "[1]Edit " << std::endl;
					}
					std::cin >> selected_id; checkInput(selected_id);
					if (selected_id == 1 && (currentUser->isAdmin || currentJob->JOB_OWNERID == currentUser->USER_ID)) {
						editCurrentJob(currentUser, currentJob);
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
			std::cout << "Job ID\t| " << "Job Name\t|" << "Job Description" << std::endl << std::endl;

			if (headerJobList->job == NULL) {
				std::cout << "No Job in database. Please create one." << std::endl;
				system("pause");
				return;
			}
			else {
				while (currentJobList->job != NULL) {
					if ((currentJobList->job->JOB_DESCRIPTION.find(keyword) != std::string::npos) || (currentJobList->job->JOB_NAME.find(keyword) != std::string::npos)) {
						if (currentJob == NULL) {
							headerforCurrentList = currentJobList;
						}
						currentJob = currentJobList->job;
						viewJobBrief(currentJob);
						if (currentJobList->next == NULL) {
							break;
						}
						else {
							currentJobList = currentJobList->next;
						}
					}
					else if (currentJobList->next == NULL && currentJob == NULL) {
						std::cout << "No Job with the keyword is found!" << std::endl;
						system("pause");
						break;
					}
					else if (currentJobList->next == NULL) {
						break;
					}
					else {
						currentJobList = currentJobList->next;
					}
				}
			}

			if (currentJob != NULL) {

				std::cout << "\n=========================================================" << std::endl;


				std::cout << "[0]Back"; std::cout << " [1]Select Job to View" << std::endl;
				currentJobList = headerforCurrentList;
				std::cin >> selected_id; checkInput(selected_id);

				switch (selected_id) {

				case 0: {
					break;
				}
				case 1: {
					std::cout << "Enter Job ID to select:"; std::cin >> selected_id; checkInput(selected_id);

					while (true) {
						if (currentJobList->job->JOB_ID == selected_id) {
							currentJob = currentJobList->job;
							break;
						}
						else if (currentJobList->next == NULL) {
							std::cout << "No Job with the selected id is found!" << std::endl;
							return;
						}
						else {
							currentJobList = currentJobList->next;
						}
					}

					viewCurrentJobInfo(currentJob);
					std::cout << "[0]Back ";
					if (currentUser->isAdmin || currentJob->JOB_OWNERID == currentUser->USER_ID) {
						std::cout << "[1]Edit " << std::endl;
					}
					std::cin >> selected_id; checkInput(selected_id);
					if (selected_id == 1 && (currentUser->isAdmin || currentJob->JOB_OWNERID == currentUser->USER_ID)) {
						editCurrentJob(currentUser, currentJob);
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

			if (headerJobList->job == NULL) {
				std::cout << "No Job in database. Please create one." << std::endl;
				system("pause");
				return;
			}
			else {
				system("cls");
				std::cout << "===================== Results =====================" << std::endl;
				std::cout << "Job ID\t| " << "Job Name\t|" << "Job Description" << std::endl << std::endl;
				while (currentJobList->job != NULL) {
					if (currentJob == NULL) {
						headerforCurrentList = currentJobList;
					}
					currentJob = currentJobList->job;
					viewJobBrief(currentJob);

					if (currentJobList->next == NULL) {
						break;
					}
					else {
						currentJobList = currentJobList->next;
					}
				}

				if (currentJob != NULL) {

					std::cout << "\n=========================================================" << std::endl;


					std::cout << "[0]Back"; std::cout << " [1]Select Job to View" << std::endl;
					currentJobList = headerforCurrentList;
					std::cin >> selected_id; checkInput(selected_id);

					switch (selected_id) {

					case 0: {
						system("cls");
						break;
					}
					case 1: {
						do {
							std::cout << "Enter Job ID to select:"; std::cin >> selected_id; checkInput(selected_id);

							while (currentJobList->job != NULL) {
								if (currentJobList->job->JOB_ID == selected_id) {
									currentJob = currentJobList->job;
									break;
								}
								else if (currentJobList->next == NULL) {
									std::cout << "No Job with the selected id is found!" << std::endl;
									break;
								}
								else {
									currentJobList = currentJobList->next;
								}
							}
							if (currentJob != NULL) {
								break;
							}
						} while (selected_id);
						if (currentJob != NULL) {
							viewCurrentJobInfo(currentJob);
							std::cout << "[0]Back ";
							if (currentUser->isAdmin || currentJob->JOB_OWNERID == currentUser->USER_ID) {
								std::cout << "[1]Edit " << std::endl;
							}
							std::cin >> selected_id; checkInput(selected_id);
							if (selected_id == 1 && (currentUser->isAdmin || currentJob->JOB_OWNERID == currentUser->USER_ID)) {
								editCurrentJob(currentUser, currentJob);
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

					std::cout << "No Job in database!\n" << std::endl;


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

void Job::viewCurrentJobInfo(JobData* currentJob) {

	std::cout << std::endl;
	std::cout << "==================== Job Info =======================" << std::endl;
	std::cout << "ID:  " << currentJob->JOB_ID << std::endl;
	std::cout << "Name:  " << currentJob->JOB_NAME << std::endl;
	std::cout << "Position: " << currentJob->JOB_POSITION << std::endl;
	std::cout << "Description:  " << currentJob->JOB_DESCRIPTION << std::endl;
	std::cout << "Posting Date: " << currentJob->JOB_POSTING_DATE << std::endl;
	std::cout << "Contact Number: " << currentJob->JOB_CONTACTNUMBER << std::endl;
	std::cout << "Company: " << currentJob->JOB_COMPANY << std::endl;
	std::cout << "Website: " << currentJob->JOB_WEBSITE << std::endl;
	std::cout << "=========================================================" << std::endl << std::endl;

}

void Job::viewJobBrief(JobData* currentJob) {

	std::cout << currentJob->JOB_ID << "\t" << currentJob->JOB_NAME << "\t" << currentJob->JOB_DESCRIPTION << std::endl;
}

void Job::editCurrentJob(UserData* currentUser, JobData* selectedJob) {

	int selected_id;

	do {
		std::cout << "Selected Job to edit:" << std::endl;
		viewCurrentJobInfo(selectedJob);

		std::cout << "1. Update Job Name" << std::endl;
		std::cout << "2. Update Job Description" << std::endl;
		std::cout << "3. Update Job Posting Date" << std::endl;
		std::cout << "4. Update Job Position" << std::endl;
		if (currentUser->isAdmin) std::cout << "5. Update Job Owner ID" << std::endl;
		if (currentUser->isAdmin || currentUser->USER_ID == selectedJob->JOB_OWNERID) std::cout << "6. Delete Job Posting" << std::endl;
		std::cout << "0. Finish edit" << std::endl;

		std::cin >> selected_id; checkInput(selected_id);

		switch (selected_id) {
		case 0: {
			system("cls");
			break;
		}
		case 1: {
			std::cin.ignore();
			std::cout << "Enter new Job Name: "; std::getline(std::cin, selectedJob->JOB_NAME);
			break;
		}
		case 2: {
			std::cin.ignore();
			std::cout << "Enter new Job Description: "; std::getline(std::cin, selectedJob->JOB_DESCRIPTION);
			break;
		}
		case 3: {
			std::cin.ignore();
			std::cout << "Enter new Job Posting Date: "; std::getline(std::cin, selectedJob->JOB_POSTING_DATE);
			break;

		}
		case 4: {
			std::cin.ignore();
			std::cout << "Enter new Job Position: "; std::cin >> selectedJob->JOB_POSITION;
			break;
		}
		case 5: {
			std::cin.ignore();
			std::cout << "Enter new Job Owner ID: "; std::cin >> selectedJob->JOB_OWNERID;
			break;
		}
		case 6: {
			std::cin.ignore();
			std::cout << "Are you sure you want to delete the selected posting?\n";
			std::cout << "Please re-input Job ID to confirm: \n";
			std::cin >> selected_id;
			checkInput(selected_id);

			if (selectedJob->JOB_ID == selected_id) {
				deleteCurrentJob(currentUser, selectedJob);
			}
			else {
				std::cout << "Error! Confirmation failed!" << std::endl;
				system("pause");
				return;
			}

			return;
		}
		default: {
			std::cout << "Invalid input! Try again: "; std::cin >> selected_id; checkInput(selected_id);
			break;
		}

		}

	} while (selected_id);
	saveJobListToDatabase();
}

void Job::deleteCurrentJob(UserData* currentUser, JobData* selectedJob) {

	JobList* previous = NULL, * current;
	currentJobList = headerJobList;
	current = currentJobList;
	while (current) {

		if (current->job->JOB_ID == selectedJob->JOB_ID) {
			if (previous == NULL) {//if first in list
				headerJobList = current->next;
				delete current;
				current = NULL;
				break;
			}
			else {
				previous->next = current->next;
				delete current;
				current = NULL;
				break;
			}

		}
		else {
			if (previous == NULL) {
				previous = current;
				current = current->next;
			}
			else {
				previous = current;
				current = current->next;
			}
		}

	}


	std::cout << "Selected Job has been deleted" << std::endl;
	system("pause");

	saveJobListToDatabase();

	return;

}

void Job::checkInput(int& choice) {

	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "You can only enter numbers.\n";
		system("pause");
		std::cout << "Enter a number: ";
		std::cin >> choice;
	}

}