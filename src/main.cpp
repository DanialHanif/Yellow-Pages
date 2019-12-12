#include <iostream>
#include "User.h"
#include "Company.h"
#include "Promotion.h"
#include "Job.h"
#include "Service.h"


/*void loggedInMenu(User& a, bool& loggedin) {

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
			break;
		}

		//register
		case '2': {

			std::cin.clear();
			std::cin.ignore();
			User a;

			a.setup();
			bool loggedin = false;

			std::string credentials = a.getUsername() + ";" + a.getPassword();
			loggedin = a.loadInfoFromDatabase(credentials);
			if (loggedin) {
				while (loggedin) {
					loggedInMenu(a, loggedin);
				}
				break;
			}
			break;
		}

			  //exit
		case '3': {

			system("exit");
			break;
		}

			  //when invalid input
		default: std::cout << "Invalid input!" << std::endl;

		}

		
	}

}*/

void MainMenu();

int main() {

	MainMenu();


	

	return 0;
}

void MainMenu() {

	
	int choice;

	do {
		User a;
		std::cout << "+========================================================================+" << std::endl;
		std::cout << "+                     Welcome to Yellow Pages system!                    +" << std::endl;
		std::cout << "+    The yellow pages are any telephone directory of businesses          +" << std::endl;
		std::cout << "+    organised by category rather than alphabetically by business name   +" << std::endl;
		std::cout << "+    and in which advertising is sold.                                   +" << std::endl;
		std::cout << "+========================================================================+" << std::endl;
		std::cout << "1) Register" << std::endl;
		std::cout << "2) Login" << std::endl;
		std::cout << "3) Login as Guest" << std::endl;
		std::cout << "0) Exit" << std::endl;
		std::cout << "\nChoice (eg. 1) : ";
		std::cin >> choice;
		std::cout << "\n";
		switch (choice)
		{
		case 0:
			break;

		case 1:
			{
				system("cls");
				User a;
				a.setup();
				std::cout<< "You have successfully registered!\n\n";
				a.viewCurrentUserInfo(a.getUserData());
				break; 
			}

		case 2:
			{


			//std::cout << "isloggedin = " << std::boolalpha << a.login() << std::endl;

			if (a.login() == true)
			{
				int choiceMenu;
				do
				{
					system("cls");
					a.viewCurrentUserInfo(a.getUserData());
					std::cout << "\n=========================================================\n\n";
					a.userMenu();

					std::cout << "Choice : ";
					std::cin >> choiceMenu;
					system("cls");

					switch (choiceMenu)
					{
					case 1: //to update data about user
					{
						a.viewCurrentUserInfo(a.getUserData());
						std::cout << "\nYou choose to update your personal data \n";
						break;
					}
					case 2://view company
					{
						std::cout << "\nYou choose view Company \n\n";
						system("pause");
						Company companyObject;
						int chooseCompany;
						do
						{ 
							system("cls");
							std::cout << "\n===================================================\n\n";
							std::cout << "1.		Add company";
							std::cout << "2.		View my company";
							std::cout << "3.		Search company\n";
							std::cout << "0.		Exit view company\n";
							std::cout <<"\nChoice (eg. 1) : ";
							
					
							std::cin >> chooseCompany;
							switch (chooseCompany)
							{
							case 1:
							{
								companyObject.addCompany(a.getUserData());
								break;
							}
							case 2:
							{
								companyObject.viewCompany(a.getUserData());
								break;
							}
							case 3:
							{
								companyObject.searchCompany(a.getUserData());
								break;
							}
							default:
							{
								std::cout << "Wrong entry !\nPlease enter again\n";
							}
							}

						} while (chooseCompany != 0);
						break;
					}
					case 3://view job
					{
						std::cout << "\nYou choose view Job \n\n";
						system("pause");
						Job jobObject;
						int chooseJob;
						do
						{
							system("cls");
							std::cout << "\n===================================================\n\n";
							std::cout << "1.		Add job";
							std::cout << "2.		View my job";
							std::cout << "3.		Search job\n";
							std::cout << "0.		Exit view job\n";
							std::cout << "\nChoice (eg. 1) : ";


							std::cin >> chooseJob;
							switch (chooseJob)
							{
							case 1:
							{

								jobObject.addJob(a.getUserData());
								
								break;
							}
							case 2:
							{
								jobObject.viewJob(a.getUserData());
								break;
							}
							case 3:
							{
								jobObject.searchJob(a.getUserData());
								break;
							}
							default:
							{
								std::cout << "Wrong entry !\nPlease enter again\n";
							}
							}

						} while (chooseJob != 0);

						break;
					}
					case 4://view service
					{
						std::cout << "\nYou choose view Service \n\n";
						system("pause");
						Service serObject;
						int chooseSer;
						do
						{
							system("cls");
							std::cout << "\n===================================================\n\n";
							std::cout << "1.		Add service";
							std::cout << "2.		View my service";
							std::cout << "3.		Search service\n";
							std::cout << "0.		Exit view service\n";
							std::cout << "\nChoice (eg. 1) : ";


							std::cin >> chooseSer;
							switch (chooseSer)
							{
							case 1:
							{

								serObject.addService(a.getUserData());
								
								break;
							}
							case 2:
							{
								serObject.viewService(a.getUserData());
								break;
							}
							case 3:
							{
								serObject.searchService(a.getUserData());
								break;
							}
							default:
							{
								std::cout << "Wrong entry !\nPlease enter again\n";
							}
							}

						} while (chooseSer != 0);

						break;
					}
					case 5://view promotion
					{
						std::cout << "\nYou choose view Promotion \n\n";
						system("pause");
						Promotion promoObject;
						int choosePromo;
						do
						{
							system("cls");
							std::cout << "\n===================================================\n\n";
							std::cout << "1.		Add promotion";
							std::cout << "2.		View my promotion";
							std::cout << "3.		Search promotion\n";
							std::cout << "0.		Exit view promotion\n";
							std::cout << "\nChoice (eg. 1) : ";


							std::cin >> choosePromo;
							switch (choosePromo)
							{
							case 1:
							{

								promoObject.addPromotion(a.getUserData());
								
								break;
							}
							case 2:
							{
								promoObject.viewPromotion(a.getUserData());
								break;
							}
							case 3:
							{
								promoObject.searchPromotion(a.getUserData());
								break;
							}
							default:
							{
								std::cout << "Wrong entry !\nPlease enter again\n";
							}
							}

						} while (choosePromo != 0);

						break;
					}
					case 6://logout
					{
						std::cout << "You have been logout" << std::endl;
						break;
					}
					default://wrong entry
					{
						break;
					}
					}
				}while (choiceMenu != 6);
			}
			else
			{
				std::cout << "\n\nUser not found ! Please login again\n\n";
					system("cls");
		
			}

			break;
		}
		case 3:
		{
			a.guest();
			system("cls");
			int guestChoose;
			do
			{
				std::cout << "\t+================================================================+\n";
				std::cout << "\tAs guest, you can only view without adding or editing our system\n";
				std::cout << "\t1.	Search Companies" << std::endl;
				std::cout << "\t2.	Search Jobs" << std::endl;
				std::cout << "\t3.	Search Services" << std::endl;
				std::cout << "\t4.	Search Promotion" << std::endl;
				std::cout << "\t0.	Exit" << std::endl;
				std::cout << "\t+================================================================+\n";
				std::cout << "\n\tChoice (eg. 1) : ";
				std::cin >> guestChoose;
				std::cout << "\n\n\t----------------------------------------------------------------\n\n\n";
				system("cls");
				switch(guestChoose)
				{
					case 1:
					{
						Company companyObjects;
						companyObjects.searchCompany(a.getUserData());
						system("pause");
						system("cls");
						break;
					}
					case 2:
					{
						Job jobsObjects;
						jobsObjects.searchJob(a.getUserData());
						system("pause");
						system("cls");
						break;
					}
					case 3:
					{
						Service serviceObjects;
						serviceObjects.searchService(a.getUserData());
						system("pause");
						system("cls");
						break;
					}
					case 4:
					{
						Promotion promotionObjects;
						promotionObjects.searchPromotion(a.getUserData());
						system("pause");
						system("cls");
						break;
					}
					default:
						break;

				}
			} while (guestChoose);
			break;
		}
		default:
			std::cout << "\tPlease enter a valid choice!\n";
			system("pause");
			system("cls");
			break;
		}
	} while (choice);
	system("pause");
	system("cls");
}

