//MUHAMMAD DANIAL AIMAN BIN MOHD HANIF BI18110242

#include <queue>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <cstddef>
#include <locale>
#include <codecvt>
#include "Nodes.h"

#ifndef USER_H
#define USER_H

class User {


    protected:

        UserList* usersList;
        UserList* headerUserList;
        UserList* currentUserList;
        UserData* currentUser;

    public:

        User();


		UserData* getUserData();
		UserList* getUsersList();

		bool login();
		void logout();
		//void userMenu();

        void setup();
		time_t generateID();
        std::string registrationDate();
        void addUserFromDBToList(std::queue<std::string>);
        

		void saveUserInfoToDatabase();
		void loadUserInfoFromDatabaseToList();
		void checkValidInput(std::string&);
		void checkIfUserExist(std::string&);

        void addUser(UserData*);
        void editUser(UserData*);
        void searchUser(UserData*);




        void viewCurrentUserInfo(UserData*);
        void viewUserBrief(UserData*);
        void editCurrentUser(UserData*, UserData*);
        void deleteCurrentUser(UserData*, UserData*);
        
        void userMenu();
        void guest();

        void clearList();
		void checkInput(int&);
        

};


#endif