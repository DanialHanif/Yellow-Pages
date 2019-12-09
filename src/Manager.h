#include <iostream>
#include "Nodes.h"
#include "User.h"
#include <string>

#ifndef MANAGER_H
#define MANAGER_H

class DataManager {

	private:
		UserList* userLists;
		CompanyList* companyLists;
		JobList* jobLists;
		ServiceList* serviceLists;

	public:

		DataManager();


		void loadUsersFromDB();
		void loadCompaniesFromDB();
		void loadServicesFromDB();
		void loadDealsFromDB();
		void loadPromotionFromDB();

		void login(std::string);

		void search(std::string);
		
		void addUser(UserData*);
		void editUser(UserData*);
		void deleteUser(UserData*);

		JobData getJobData();
		void printJobLists();
		void addJob();
		void editJob();
		void deleteJob();
		
		CompanyData getCompanyData();
		void printCompanyLists();
		void addCompany(CompanyData*);
		void deleteCompany(CompanyData*);
		void editCompany(CompanyData*);

		ServiceData getServiceData();
		void printServiceList();
		void addService(CompanyData*);
		void editService(CompanyData*);
		void deleteService(CompanyData*);
		
		DealData getDealData();
		void addDeal(DealData*);
		void deleteDeal(DealData*);


};

#endif
