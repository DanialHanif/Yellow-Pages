#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include "Nodes.h"
#include <ctime>

#ifndef JOB_H
#define JOB_H


class Job {

protected:
	JobList* jobList;
	JobList* headerJobList;
	JobList* currentJobList;
	JobData* currentJob;


public:
	Job();
	JobData* getJobData();
	JobList* getJobList();
	void addJob(UserData*);
	void editJob(UserData*);
	void deleteJob(UserData*);
	void searchJob(UserData*);
	void viewJob(UserData*);
	void saveJobListToDatabase();
	void loadJobListFromDatabase();
	void addJobDataFromDBToList(std::queue<std::string>);
	void checkValidInput(std::string&);
	void checkValidInputNumber(std::string&);
	time_t generateID();
	std::string postingDate();
	void viewCurrentJobInfo(JobData*);
	void viewJobBrief(JobData*);
	void editCurrentJob(UserData*, JobData*);
	void deleteCurrentJob(UserData*, JobData*);

	void clearList();

};

#endif // !JOB_H