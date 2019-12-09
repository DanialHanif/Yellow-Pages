#include "Manager.h"


	DataManager::DataManager() {

		this->userLists = new UserList;
		this->userLists->user = NULL;
		this->userLists->next = NULL;
		this->companyLists = new CompanyList;
		this->companyLists->company = NULL;
		this->companyLists->next = NULL;
		this->jobLists = new JobList;
		this->jobLists->job = NULL;
		this->jobLists->next = NULL;
		this->serviceLists = new ServiceList;
		this->serviceLists->service = NULL;
		this->serviceLists->next = NULL;
		
}

	



	


