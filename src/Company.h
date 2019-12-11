#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include "Nodes.h"
#include <ctime>

#ifndef COMPANY_H
#define COMPANY_H


class Company {

	protected:
		CompanyList* companyList;
		CompanyList* headerCompanyList;
		CompanyList* currentCompanyList;
		CompanyData* currentCompany;


	public:
		Company();
		CompanyData* getCompanyData();
		CompanyList* getCompanyList();
		void addCompany(UserData*);
		void editCompany(UserData*);
		void deleteCompany(UserData*);
		void searchCompany(UserData*);
		void viewCompany(UserData*);
		void saveCompanyListToDatabase();
		void loadCompanyListFromDatabase();
		void addCompanyDataFromDBToList(std::queue<std::string>);
		void checkValidInput(std::string&);
		void checkValidInputNumber(std::string&);
		time_t generateID();
		std::string registrationDate();

};

#endif // !COMPANY_H

