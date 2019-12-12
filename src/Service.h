#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include "Nodes.h"
#include <ctime>

#ifndef SERVICE_H
#define SERVICE_H


class Service {

protected:
	ServiceList* serviceList;
	ServiceList* headerServiceList;
	ServiceList* currentServiceList;
	ServiceData* currentService;


public:
	Service();
	ServiceData* getServiceData();
	ServiceList* getServiceList();
	void addService(UserData*);
	void editService(UserData*);
	void deleteService(UserData*);
	void searchService(UserData*);
	void viewService(UserData*);
	void saveServiceListToDatabase();
	void loadServiceListFromDatabase();
	void addServiceDataFromDBToList(std::queue<std::string>);
	void checkValidInput(std::string&);
	void checkValidInputNumber(std::string&);
	time_t generateID();
	std::string postingDate();
	void viewCurrentServiceInfo(ServiceData*);
	void viewServiceBrief(ServiceData*);
	void editCurrentService(UserData*, ServiceData*);
	void deleteCurrentService(UserData*, ServiceData*);

	void clearList();

};

#endif // !SERVICE_H
