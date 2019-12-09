//MUHAMMAD DANIAL AIMAN BIN MOHD HANIF BI18110242

#include <iostream>
#include "User.h"


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

/*int main()
{
	Payment a;

	a.Description();

	cout << "\n****************************************** List of deals ******************************************\n" << endl;
	cout << "\t\t1. Essential = RM 49.90 / monthly \n\t\t2. Commerce = RM 79.90 / monthly \n\t\t3. Deluxe = RM 149.90 / monthly \n\n";
	cout << "***************************************************************************************************\n\n";
	cout << "___________________________________________________________________________________________________\n\n";
	cout << "\t\tInsert a number of deals you wants to know more , (1/2/3)\n\t\tInsert any other number to continue or cancel the payment : ";

	int deals;
	cin >> deals;
	cout << "___________________________________________________________________________________________________\n\n";
	a.viewDeals(deals);
	cout << "\n\n___________________________________________________________________________________________________\n";
	cout << "___________________________________________________________________________________________________\n\n";
	cout << "\t\tThank you for dealing with us!!  ^_^\n\n\n";

	return 0;
}*/

void MainMenu();

int main() {

	MainMenu();


	

	return 0;
}

void MainMenu() {

	
	int choice;

	do {
		
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

		std::cin >> choice;
		switch (choice)
		{
		case 0:
			break;

		case 1:
			{
			User a;
			a.setup();
			a.printInfo();
			break; 
		}

		case 2:
			{
			User a;
			std::cout << "isloggedin = " << std::boolalpha << a.login() << std::endl;
			break;
		}
		case 3:
			/*User a;
			a.loginGuest();*/
			break;

		default:
			std::cout << "Please enter a valid choice!\n";
			system("pause");
			system("cls");
			break;
		}
	} while (choice);
}