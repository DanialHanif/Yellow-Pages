#include <iostream>
#include <string>


/*static const char* const CATEGORY_LISTS[] = { "Computing", "Network & Communications", "Management", "Software",//0,1,2,3
									  "Professional Services", "Consulting", "Training", "Finance",//4,5,6,7
									  "Insurance", "Travel", "Events", "Food", "Marketing", "Research",//8,9,10,11,12,13
									  "Media", "Distribution", "Supply", "Printing & Prototyping", "Production", "Engineering",//14,15,16,17,18,19
									  "Design", "Utilities", "Real Estate", "Quality of Life", "Logistics", "Waste Management" };//20,21,22,23,24,25*/

struct CompanyData {

	int COMPANY_ID;
	int COMPANY_OWNERID;
	std::string COMPANY_NAME;
	std::string COMPANY_DESCRIPTION;
	std::string COMPANY_EMAIL;
	std::string COMPANY_CONTACTNUMBER;
	std::string COMPANY_WEBSITE;
	std::string COMPANY_REGISTRATION_DATE;
	//std::string COMPANY_CATEGORY;

};
 
struct JobData {

	int JOB_ID;
	std::string JOB_NAME;
	std::string JOB_DESCRIPTION;
	std::string JOB_POSITION;
	std::string JOB_CONTACTNUMBER;
	std::string JOB_WEBSITE;
	std::string JOB_COMPANY;
	std::string POSTING_DATE;
	//std::string JOB_CATEGORY;
	CompanyData* companyLink;

};

struct ServiceData {

	int SERVICE_ID;
	std::string SERVICE_NAME;
	std::string SERVICE_DESCRIPTION;
	std::string SERVICE_CONTACTNUMBER;
	std::string SERVICE_COMPANY;
	std::string SERVICE_WEBSITE;
	std::string POSTING_DATE;
	//std::string SERVICE_CATEGORY;
	CompanyData* companyLink;
	ServiceData* next;

};

struct DealData {

	int DEAL_ID;
	std::string DEAL_NAME;
	std::string DEAL_DESCRIPTION;
	//std::string DEAL_CATEGORY;
	double DEAL_PRICE;

};

struct PromotionData {

	std::string DEAL_NAME;
	std::string DEAL_DESCRIPTION;
	double DEAL_PRICE;
	std::string POSTING_DATE;

};

struct CompanyList {

	CompanyData* company;
	CompanyList* next;

};

struct JobList {

	JobData* job;
	JobList* next;

};
struct ServiceList {

	ServiceData* service;
	//Category* category;
	ServiceList* next;

};

struct DealList {

	DealData* deal;
	//Category* category;
	DealList* next;

};

struct PromotionList {

	PromotionData* promotion;
	//Category* category;
	PromotionList* next;

};

//userdata structure
struct UserData {

	int USER_ID;
	bool isAdmin;
	bool isEmployer;
	bool isGuest;
	bool isLoggedIn;
	std::string USER_NAME;
	std::string USER_FULL_NAME;
	std::string USER_EMAIL;
	std::string USER_DOB;
	std::string USER_ADDRESS;
	std::string USER_PASSWORD;
	std::string	USER_REG_DATE;
	CompanyList* USER_COMPANIES;
	ServiceList* USER_SERVICES;
	DealList* USER_DEALS;
	PromotionList* USER_PROMOTION;

};

struct UserList {

	UserData* user;
	UserList* next;

};


/*struct Category {

	std::string CATEGORY_NAME;
	DealList* deal;
	JobList* job;
	ServiceList* service;


};*/

struct Invoice {

	std::string INVOICE_NUMBER;
	DealData* INVOICE_DEALS;

};

