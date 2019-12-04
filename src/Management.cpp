#include "Management.h"


	Management::Management() {

		
		userLists->user = NULL;
		userLists->next = NULL;
		user = userLists->user;
		companyLists->company = NULL;
		companyLists->next = NULL;
		jobLists->job = NULL;
		jobLists->next = NULL;
		serviceLists->service = NULL;
		serviceLists->next = NULL;
		hotelLists->hotel = NULL;
		hotelLists->next = NULL;
		
}

	


	void Management::mainMenu() {

		if (user->isAdmin == false) {

			std::cout << "+==================== Menu ====================+\n" << std::endl;
			
		}
		else {

			std::cout << "+==================== Admin Menu ====================+\n" << std::endl;
		}

		std::cout << "\t 1. Search Jobs, Services and Hotels" << std::endl;
		std::cout << "\t 2. View Job listings" << std::endl;
		std::cout << "\t 3. View Services listings" << std::endl;
		std::cout << "\t 4. View Hotel listings" << std::endl;
		std::cout << "\t 5. View Profile" << std::endl;
		std::cout << "\t 6. Logout" << std::endl;
		std::cout << "\t 7. Exit" << std::endl;
		std::cout << std::endl;
		std::cout << "+==============================================+\n" << std::endl;
	}

	


