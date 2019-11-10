#include <iostream>
#include <string>

struct Company {

	int id;
	std::string name;
	std::string description;
	std::string address;
	std::string contactNumber;
	std::string website;
	Company* next;

};
 
struct Job {

	int id;
	std::string name;
	std::string description;
	std::string position;
	std::string contactNumber;
	std::string website;
	std::string company;
	Company* companyLink;
	Job* next;

};

struct Service {

	int id;
	std::string name;
	std::string description;
	std::string contactNumber;
	std::string company;
	std::string website;
	Company* companyLink;
	Service* next;

};

struct Hotel {

	int id;
	std::string name;
	std::string description;
	std::string contactNumber;
	std::string company;
	std::string website;
	Company* companyLink;
	Hotel* next;

};

struct UserList {


	UserList* link;

};

//skill with descriptions
struct Skills {

	int id;
	std::string name;
	std::string description;
	int level;
	Skills* next;

};

//userdata structure
struct UserData {

	int USER_ID;
	std::string USER_NAME;
	std::string USER_FULL_NAME;
	std::string USER_EMAIL;
	std::string USER_DOB;
	std::string USER_ADDRESS;
	std::string USER_PASSWORD;
	std::string	USER_REG_DATE;
	Skills* USER_SKILLS;
};