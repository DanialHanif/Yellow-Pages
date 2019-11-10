#include <iostream>
#include "User.h"

int main(){

	/*int i; std::string user_N, passw;
	

	std::cout << "=============== User Registration and Login DEMO ===============" << std::endl << std::endl;
	std::cout << "1. Login" << std::endl;
	std::cout << "2. Register" << std::endl;
	std::cout << "3. Exit" << std::endl;
	std::cin >> i;
	
	switch (i) {

		case 1: std::cout << "Username: "; std::getline(std::cin, user_N);
				std::cout << "Password: "; std::getline(std::cin, passw);
				break;
			

		case 2:	User a;
				a.setup();
				a.printInfo();
				break;

		case 3: system("exit");
				break;

		default: std::cout << "Invalid input!";
	
	}*/

	User a;
	a.setup();
	a.printInfo();
	a.saveInfoToDatabase();

	system("pause");

    return 0;
}

/*#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;
struct work
{
	char name[100];
	int id;
	char job[10];
}workers[10];
int main()
{
	int numWorkers = 0;
	int option = 0;
	ofstream file;
	while (1)
	{
		cout << "\nThe db++ Database application\n1-To enter the data\n2-To read the data\n3-To save the data\n";
		cin >> option;
		switch (option)
		{
		case 1:
			cout << "Enter the no. of workers:" << endl;
			cin >> numWorkers;
			for (int i = 0; i < numWorkers; i++)
			{
				cout << endl << "Enter the name of the worker:" << endl;
				cin >> workers[i].name;
				cout << endl << "Enter the ID no. of the worker:" << endl;
				cin >> workers[i].id;
				cout << endl << "Enter the job of the worker:" << endl;
				cin >> workers[i].job;
				cout << endl;
			}
			break;
		case 2:
			for (int i = 0; i < numWorkers; i++)
				cout << endl << "The worker no. " << i + 1 << " is " << workers[i].name << " with an ID no. of " << workers[i].id;
			cout << endl << endl;
			break;
		case 3:
			file.open("report.txt");
			for (int i = 0; i < numWorkers; i++)
				file << endl << "The worker no. " << i + 1 << " is " << workers[i].name << " with an ID no. of " << workers[i].id << endl;
			file << endl;
			file.close();
			cout << "The file is saved" << endl;
			getch();
			break;
		}
	}
	return 0;
}*/