#include <iostream>
#include <string>

struct CompanyData {

	int COMPANY_ID;
	std::string COMPANY_NAME;
	std::string COMPANY_DESCRIPTION;
	std::string COMPANY_ADDRESS;
	std::string COMPANY_CONTACTNUMBER;
	std::string COMPANY_WEBSITE;

};
 
struct JobData {

	int JOB_ID;
	std::string JOB_NAME;
	std::string JOB_DESCRIPTION;
	std::string JOB_POSITION;
	std::string JOB_CONTACTNUMBER;
	std::string JOB_WEBSITE;
	std::string JOB_COMPANY;
	CompanyData* companyLink;

};

struct ServiceData {

	int SERVICE_ID;
	std::string SERVICE_NAME;
	std::string SERVICE_DESCRIPTION;
	std::string SERVICE_CONTACTNUMBER;
	std::string SERVICE_COMPANY;
	std::string SERVICE_WEBSITE;
	CompanyData* companyLink;

};

struct HotelData {

	int HOTEL_ID;
	std::string HOTEL_NAME;
	std::string HOTEL_DESCRIPTION;
	std::string HOTEL_CONTACTNUMBER;
	std::string HOTEL_COMPANY;
	std::string HOTEL_WEBSITE;
	CompanyData* companyLink;

};



//skill with descriptions
struct Skills {

	int SKILL_ID;
	std::string SKILL_NAME;
	std::string SKILL_DESCRIPTION;
	int SKILL_LEVEL;
	Skills* next;

};

//userdata structure
struct UserData {

	int USER_ID;
	bool isAdmin;
	std::string USER_NAME;
	std::string USER_FULL_NAME;
	std::string USER_EMAIL;
	std::string USER_DOB;
	std::string USER_ADDRESS;
	std::string USER_PASSWORD;
	std::string	USER_REG_DATE;
	Skills* USER_SKILLS;
};

struct UserList {

	UserData* user;
	UserList* next;

};
struct CompanyList {

	CompanyData* company;
	CompanyList* next;

};
struct HotelList {

	HotelData* hotel;
	HotelList* next;

};
struct JobList {

	JobData* job;
	JobList* next;

};
struct ServiceList {

	ServiceData* service;
	ServiceList* next;

};
