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
	Hotel next;

};

struct UserList {

	User user;
	UserList* link;

}