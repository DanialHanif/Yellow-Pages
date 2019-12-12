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
		void addCompany(UserData*);//add company to database
		void editCompany(UserData*);
		void deleteCompany(UserData*);
		void searchCompany(UserData*);
		void viewCompany(UserData*);
		void saveCompanyListToDatabase();
		void loadCompanyListFromDatabase();
		void addCompanyDataFromDBToList(std::queue<std::string>);//convert raw company database to list
		void checkValidInput(std::string&);
		void checkValidInputNumber(std::string&);
		time_t generateID();
		std::string registrationDate();

		void viewCurrentCompanyInfo(CompanyData*);
		void viewCompanyBrief(CompanyData*);
		void editCurrentCompany(UserData*, CompanyData*);//edit current selected company
		void deleteCurrentCompany(UserData*, CompanyData*);//delete current selected company
		//void viewCompanyguest();//for guest

		void clearList();

};

#endif // !COMPANY_H

