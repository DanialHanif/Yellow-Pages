//MUHAMMAD DANIAL AIMAN BIN MOHD HANIF BI18110242

#include <iostream>
#include <locale>
#include <codecvt>
#include "User.h"

void loggedInMenu(User& a, bool& loggedin) {

	a.printInfo();
	char i;

	std::cout << "1. Update Profile" << std::endl;
	std::cout << "2. Change Password" << std::endl;
	std::cout << "3. Logout" << std::endl;

	std::cin >> i;
	std::cout << std::endl;


	switch (i) {

		//update profile
	case '1': {

		std::cout << "1. Update Username" << std::endl;
		std::cout << "2. Update Full Name" << std::endl;
		std::cout << "3. Update Email address" << std::endl;
		std::cout << "4. Update Date of Birth" << std::endl;
		std::cout << "5. Update Skills" << std::endl;
		std::cout << "6. Add Skills" << std::endl;
		std::cout << "7. Delete Skills" << std::endl;

		std::cin >> i;

		std::string input;
		switch (i) {
		case '1': {
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Enter new Username: "; std::getline(std::cin, input); a.setUsername(input);
			a.saveInfoToDatabase();
			a.printInfo(); }
				break;
		case '2': {
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Enter Full Name: "; std::getline(std::cin, input); a.setFullName(input);
			a.saveInfoToDatabase();
			a.printInfo(); }
				break;
		case '3': {
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Update Email address: "; std::getline(std::cin, input); a.setEmailAddress(input);
			a.saveInfoToDatabase();
			a.printInfo(); }
				break;
		case '4': {
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Update Date of Birth (Day:Month:Year): "; std::getline(std::cin, input); std::wstring date = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(input); a.setDateOfBirth(date);
			a.saveInfoToDatabase();
			a.printInfo(); }
				break;
		case '5': { //edit skill

			std::string name, description;
			int level, id;
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Select skill number to edit: "; std::cin >> id;
			std::cout << "Enter Skill name: ";  std::getline(std::cin, name);
			std::cout << "Enter Skill description: "; std::getline(std::cin, description);
			std::cout << "Enter Skill level(1-5): "; std::cin >> level;

			a.updateSkills(id, name, description, level);
			a.saveInfoToDatabase();
			a.printInfo();
			break;
		}

		case '6': { //add skill

			std::string name, description;
			int level;
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Enter Skill name: ";  std::getline(std::cin, name);
			std::cout << "Enter Skill description: "; std::getline(std::cin, description);
			std::cout << "Enter Skill level(1-5): "; std::cin >> level;

			a.addSkills(name, description, level);
			a.saveInfoToDatabase();
			a.printInfo();
			break;
		}

		case '7': { //delete


			std::string name, description;
			int level, id;
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Select skill number to delete: "; std::cin >> id;

			a.deleteSkills(id);
			a.saveInfoToDatabase();
			a.printInfo();
			break;
		}

		}
		break;
	}
		  //change password
	case '2': {
		std::cin.clear();
		std::cin.ignore();
		std::string oldPass, newPass;
		std::cout << "Enter old password: ";
		while (std::getline(std::cin, oldPass)) {
			if (oldPass != a.getPassword()) {
				std::cout << "Wrong password entered!";

			}
			else {
				std::cout << "Enter new password: ";
				std::getline(std::cin, newPass);
				a.setPassword(newPass);
				a.saveInfoToDatabase();
				break;
			}
		}
	}

		  //logout
	case '3': {

		a.saveInfoToDatabase();
		loggedin = false;
		break;

	}

	}

}

int main() {

	while (true) {

		char i;


		std::cout << "=============== User Registration and Login DEMO ===============" << std::endl << std::endl;
		std::cout << "1. Login" << std::endl;
		std::cout << "2. Register" << std::endl;
		std::cout << "3. Exit" << std::endl;
		std::cin >> i;
		switch (i) {

			//login
		case '1':
		{
			std::cin.clear();
			std::cin.ignore();
			std::string user_n, passw;
			std::cout << "Username: "; std::cin >> user_n;
			std::cout << "Password: "; std::cin >> passw;
			User a;
			std::string credentials = user_n + ";" + passw;
			bool loggedin = false;
			loggedin = a.loadInfoFromDatabase(credentials);
			if (loggedin) {
				while (loggedin) {
					loggedInMenu(a, loggedin);
				}
				break;
			}
		}

		//register
		case '2': {

			std::cin.clear();
			std::cin.ignore();
			User a;
			std::string user_n, passw;

			a.setup();
			bool loggedin = false;

			std::string credentials = user_n + ";" + passw;
			loggedin = a.loadInfoFromDatabase(credentials);
			if (loggedin) {
				while (loggedin) {
					loggedInMenu(a, loggedin);
				}
				break;
			}
		}

			  //exit
		case '3': {

			system("exit");

		}

			  //when invalid input
		default: std::cout << "Invalid input!" << std::endl;

		}

		
	}

}