#include "Job.h"

Job::Job() {

	this->jobList = new JobList;
	this->jobList->job = NULL;
	this->jobList->next = NULL;
	this->headerJobList = jobList;
	this->currentJobList = jobList;
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

		firstpart = "{" + std::to_string(currentJobList->job->JOB_ID) + ";" + std::to_string(currentJobList->job->JOB_OWNERID) + ";" + currentJobList->job->JOB_NAME + ";" + currentJobList->job->JOB_DESCRIPTION + ";"
						+ currentJobList->job->JOB_POSITION + ";" + currentJobList->job->JOB_CONTACTNUMBER + ";" + currentJobList->job->JOB_WEBSITE + ";" + currentJobList->job->JOB_COMPANY + ";" + currentJobList->job->JOB_POSTING_DATE + "}";

		info = firstpart;

		file << info << std::endl;

		if (currentJobList->next != NULL) {
			currentJobList = currentJobList->next;
		}
		else {
			break;
		}


	}

	file.close();
	std::cout << std::endl << "Job data is saved!" << std::endl;
	delete jobList;
	jobList = new JobList;
	jobList->job = NULL;
	jobList->next = NULL;
	headerJobList = jobList;
	loadJobListFromDatabase();
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

			if ((jobDataContainer.size() == 6)) {

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
	newJob->job->JOB_CONTACT = jobDataContainer.front(); jobDataContainer.pop();
	newJob->job->JOB_WEBSITE = jobDataContainer.front(); jobDataContainer.pop();
	newJob->job->JOB_COMPANY = jobDataContainer.front(); jobDataContainer.pop();
	newJob->job->JOB_POSTING_DATE = jobDataContainer.front(); jobDataContainer.pop();
	newJob->next = NULL;

	if (headerJobList->job == NULL) {//first load

		delete jobList;
		jobList = newJob;
		headerJobList = JobList;
		currentJobList = headerJobList;
	}

	else {

		JobList* current = headerJobList;
		while (current) {
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
		std::cout << "Job ID\t| " << "Owner ID\t| " << "Job Name" << std::endl;

		currentJobList = headerJobList;
		while (currentJobList->job != NULL) {

			if (currentUser->isAdmin == true) {
				while (currentJobList->job != NULL) {

					std::cout << currentJobList->job->JOB_ID << "\t" << currentJobList->job->JOB_OWNERID << "\t" << currentJobList->job->JOB_NAME << std::endl;
					if (currentJobList->next != NULL) {
						currentJobList = currentJobList->next;
					}
					else {
						break;
					}
				}
				std::cout << "=========================================================" << std::endl;
				break;
			}
			//iterate through job list until reach first match
			else if (currentJobList->job->JOB_OWNERID == currentUser->USER_ID) {
				std::cout << currentJobList->job->JOB_ID << "\t" << currentJobList->job->JOB_OWNERID << "\t" << currentJobList->job->JOB_NAME << std::endl;
				while (currentJobList->job != NULL) {

					//add matches to user jobs
					if (currentUser->USER_JOB == NULL) {
						currentUser->USER_JOB = currentJobList;
						break;
					}
					else if (currentUser->USER_JOB != NULL && currentUser->USER_JOB->next == NULL) {

						currentUser->USER_JOB->next = currentJobList;
						break;

					}
					else {
						break;
					}
				}

			}
			if (currentJobList->next != NULL) {
				currentJobList = currentJobList->next;
			}
			else {
				break;
			}

		}

	}
	std::cout << "=========================================================" << std::endl;
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
	newJob->job->JOB_POSTING_DATE = postingDate();
	std::cout << "Enter Job Position: "; std::cin >> newJob->job->JOB_POSITION;


	if (headerJobList->job == NULL) {//first load

		jobList = newJob;
		headerJobList = jobList;
		currentJobList = headerJobList;
	}

	else {

		currentJobList = headerJobList;
		while (currentJobList) {
			if (currentUser->isEmployer) {
				if (currentUser->USER_JOB == NULL) { currentUser->USER_JOB = newJob; break; }
				if (currentUser->USER_JOB != NULL && currentUser->USER_JOB->next == NULL) { currentUser->USER_JOB->next = newJob; break; }
			}
			if (currentJobList->next == NULL) { currentJobList->next = newJob; break; }

			else {
				currentJobList = currentJobList->next;
			}
		}
	}

	saveJobListToDatabase();
	viewJob(currentUser);
}

void Job::editJob(UserData* currentUser) {

	currentJobList = headerJobList;
	int selected_id;
	currentJob = NULL;
	std::cin.ignore();
	if (currentUser->isAdmin || currentUser->isEmployer) {

		std::cout << "Select Job ID:" << std::endl; std::cin >> selected_id;
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
		JobList* curr = currentUser->USER_JOB;
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

		std::cout << "Select Job ID:" << std::endl; std::cin >> selected_id;
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
			std::cout << "Enter Job ID: "; std::cin >> selected_id;

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
				std::cin >> selected_id;

				switch (selected_id) {

				case 0: {
					break;
				}
				case 1: {
					std::cout << "Enter Job ID to select:"; std::cin >> selected_id;

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
					std::cin >> selected_id;
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
				std::cin >> selected_id;

				switch (selected_id) {

				case 0: {
					break;
				}
				case 1: {
					std::cout << "Enter Job ID to select:"; std::cin >> selected_id;

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
					std::cin >> selected_id;
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
					if (currentJobList->job->JOB_DESCRIPTION.find(keyword) != std::string::npos) {
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
				std::cin >> selected_id;

				switch (selected_id) {

				case 0: {
					break;
				}
				case 1: {
					std::cout << "Enter Job ID to select:"; std::cin >> selected_id;

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
					std::cin >> selected_id;
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
					std::cin >> selected_id;

					switch (selected_id) {

					case 0: {
						system("cls");
						break;
					}
					case 1: {
						do {
							std::cout << "Enter Job ID to select:"; std::cin >> selected_id;

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
							std::cin >> selected_id;
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
	std::cout << "Description:  " << currentJob->JOB_DESCRIPTION << std::endl;
	std::cout << "Posting Date: " << currentJob->JOB_POSTING_DATE << std::endl;
	std::cout << "Position: " << currentJob->JOB_POSITION << std::endl;
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
		std::cout << "0. Finish edit" << std::endl;

		std::cin >> selected_id;

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
		default: {
			std::cout << "Invalid input! Try again: "; std::cin >> selected_id;
			break;
		}

		}

	} while (selected_id);
	saveJobListToDatabase();
	loadJobListFromDatabase();
}

void Job::deleteCurrentJob(UserData* currentUser, JobData* selectedCompany) {

	delete selectedCompany;
	selectedCompany = NULL;

	std::cout << "Selected Company has been deleted" << std::endl;

	saveJobListToDatabase();
	loadJobListFromDatabase();

	return;



}