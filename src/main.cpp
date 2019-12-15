#include <iostream>
#include "User.h"
#include "Company.h"
#include "Promotion.h"
#include "Job.h"
#include "Service.h"


void MainMenu();

void checkInput(int& choice);

int main() {

	MainMenu();


	return 0;
}

void checkInput(int& choice) {

	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "You can only enter numbers.\n";
		system("pause");
		std::cout << "Enter a number: ";
		std::cin >> choice;
	}

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
		std::cout << "\nChoice (eg. 1) : ";
		std::cin >> choice;

		checkInput(choice);
		system("cls");
		std::cout << "\n";
		switch (choice)
		{
		case 0:
			break;

		case 1:
			{
				
				User userModule;
				userModule.setup();
				std::cout<< "You have successfully registered!\n";
				userModule.viewCurrentUserInfo(userModule.getUserData());
				break; 
			}

		case 2:
			{
			User userModule;
			Company companyModule;
			Job jobModule;
			Service serviceModule;
			Promotion promotionModule;
			if (userModule.login())
			{
				int choiceMenu;
				do
				{
					std::cout << "\n=========================================================\n\n";
					userModule.viewCurrentUserInfo(userModule.getUserData());
					std::cout << "\n=========================================================\n\n";
					userModule.userMenu();

					std::cout << "Choice: ";
					std::cin >> choiceMenu;
					checkInput(choiceMenu);
					system("cls");

					switch (choiceMenu)
						{
						case 1: //to update data about user
						{
						userModule.viewCurrentUserInfo(userModule.getUserData());
						userModule.editCurrentUser(userModule.getUserData(), userModule.getUserData());
						//std::cout << "\nYou choose to update your personal data \n";
						break;
					}
						case 2://view company
						{
						std::cout << "\nYou choose view Company \n\n";
						//system("pause");
						int chooseCompany;
						do
						{ 
							//system("cls");
							std::cout << "===================================================\n";
							std::cout << "1. Add company\n";
							std::cout << "2. View my company\n";
							std::cout << "3. Search company\n";
							std::cout << "0. Exit view company\n";
							std::cout <<"\nChoice (eg. 1) : ";
							
					
							std::cin >> chooseCompany;
							switch (chooseCompany)
							{
							case 0:
							{
								break;
							}
							case 1:
							{
								companyModule.addCompany(userModule.getUserData());
								break;
							}
							case 2:
							{
								companyModule.viewCompany(userModule.getUserData());
								system("cls");
								break;
							}
							case 3:
							{
								companyModule.searchCompany(userModule.getUserData());
								break;
							}
							default:
							{
								std::cout << "Wrong entry !\nPlease enter again\n";
								break;
							}
							}

						} while (chooseCompany);
						break;
					}
						case 3://view job
						{
						std::cout << "\nYou choose view Job \n\n";
						//system("pause");
						
						int chooseJob;
						do
						{
							//system("cls");
							std::cout << "===================================================\n";
							std::cout << "1. Add job\n";
							std::cout << "2. View my job\n";
							std::cout << "3. Search job\n";
							std::cout << "0. Exit view job\n";
							std::cout << "\nChoice (eg. 1) : ";


							std::cin >> chooseJob;
							switch (chooseJob)
							{
							case 1:
							{

								jobModule.addJob(userModule.getUserData());
								
								break;
							}
							case 2:
							{
								jobModule.viewJob(userModule.getUserData());
								break;
							}
							case 3:
							{
								jobModule.searchJob(userModule.getUserData());
								break;
							}
							default:
							{
								std::cout << "Wrong entry !\nPlease enter again\n";
								break;
							}
							}

						} while (chooseJob);

						break;
					}
						case 4://view service
						{
						std::cout << "\nYou choose view Service \n\n";
						system("pause");
						
						int chooseSer;
						do
						{
							system("cls");
							std::cout << "\n===================================================\n";
							std::cout << "1. Add service\n";
							std::cout << "2. View my service\n";
							std::cout << "3. Search service\n";
							std::cout << "0. Exit view service\n";
							std::cout << "\nChoice (eg. 1) : ";


							std::cin >> chooseSer;
							switch (chooseSer)
							{
							case 1:
							{

								serviceModule.addService(userModule.getUserData());
								
								break;
							}
							case 2:
							{
								serviceModule.viewService(userModule.getUserData());
								break;
							}
							case 3:
							{
								serviceModule.searchService(userModule.getUserData());
								break;
							}
							default:
							{
								std::cout << "Wrong entry !\nPlease enter again\n";
								break;
							}
							}

						} while (chooseSer);

						break;
					}
						case 5://view promotion
						{
						std::cout << "\nYou choose view Promotion \n\n";
						system("pause");
						
						int choosePromo;
						do
						{
							system("cls");
							std::cout << "\n===================================================\n";
							std::cout << "1. Add promotion\n";
							std::cout << "2. View my promotion\n";
							std::cout << "3. Search promotion\n";
							std::cout << "0. Exit view promotion\n";
							std::cout << "\nChoice (eg. 1) : ";


							std::cin >> choosePromo;
							switch (choosePromo)
							{
							case 1:
							{

								promotionModule.addPromotion(userModule.getUserData());
								
								break;
							}
							case 2:
							{
								promotionModule.viewPromotion(userModule.getUserData());
								break;
							}
							case 3:
							{
								promotionModule.searchPromotion(userModule.getUserData());
								break;
							}
							default:
							{
								std::cout << "Wrong entry !\nPlease enter again\n";
								break;
							}
							}

						} while (choosePromo);

						break;
					}
						case 6://view user
						{
						if (!userModule.getUserData()->isAdmin) {
							break;
						}
						std::cout << "\nYou choose view Users \n\n";
						system("pause");

						int chooseUser;
						do
						{
							system("cls");
							std::cout << "\n===================================================\n";
							std::cout << "1. Add User\n";
							std::cout << "2. Search users\n";
							std::cout << "0. Exit view users\n";
							std::cout << "\nChoice (eg. 1) : ";


							std::cin >> chooseUser;
							switch (chooseUser)
							{
							case 1:
							{

								userModule.addUser(userModule.getUserData());

								break;
							}
							case 2:
							{
								userModule.searchUser(userModule.getUserData());
								break;
							}
							default:
							{
								std::cout << "Wrong entry !\nPlease enter again\n";
								break;
							}
							}

						} while (chooseUser);

						break;
					}
						case 0://logout
						{
							std::cout << "You have been logout" << std::endl;
							userModule.logout();
							break;
						}
						default://wrong entry
						{
							break;
						}
					}
				}while (choiceMenu);
			}
			else
			{

			break;
		
			}

			break;
		}
		case 3:
		{
			User userModule;
			userModule.guest();
			//system("cls");
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
				checkInput(guestChoose);
				
				system("cls");
				switch(guestChoose)
				{
					case 0:
						break;

					case 1:
					{
						Company companyModule;
						companyModule.searchCompany(userModule.getUserData());
						system("pause");
						system("cls");
						break;
					}
					case 2:
					{
						Job jobModule;
						jobModule.searchJob(userModule.getUserData());
						system("pause");
						system("cls");
						break;
					}
					case 3:
					{
						Service serviceModule;
						serviceModule.searchService(userModule.getUserData());
						system("pause");
						system("cls");
						break;
					}
					case 4:
					{
						Promotion promotionModule;
						promotionModule.searchPromotion(userModule.getUserData());
						system("pause");
						system("cls");
						break;
					}
					default:
						std::cout << "\tPlease enter a valid choice!\n";
						system("pause");
						system("cls");
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
}

