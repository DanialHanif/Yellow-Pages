#include <iostream>
#include "Nodes.h"
#include "User.h"
#include <string>

#ifndef MANAGEMENT_H
#define MANAGEMENT_H

class Management {

	private:
		UserList* userLists;
		CompanyList* companyLists;
		JobList* jobLists;
		ServiceList* serviceLists;
		HotelList* hotelLists;
		UserData* user;

	public:

		Management();

		void loadUsersFromDB();

		void loginMenu();
		void login(std::string);
		void mainMenu();

		void searchMenu();
		void search(std::string);
		
		void userProfileMenu();
		void addProfile(User);
		void editProfile(User);
		void deleteProfile(User);

		void JobsMenu();
		std::string getJobLists();
		
		void CompanyMenu();
		void addCompany();
		void deleteCompany();
		void editCompany();

		void ServicesMenu();
		std::string getServiceLists();
		void addService();
		void deleteService();


};

#endif
