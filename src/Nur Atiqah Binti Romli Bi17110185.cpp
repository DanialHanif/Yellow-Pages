#include<iostream>
#include<string>
#include<fstream>

using namespace std;

void Intro()
{
	cout<<"\nWelcome to Yellow Pages system"<<endl;
	cout<<"The yellow pages are any telephone directory of businesses,"<<endl;
	cout<<"organised by category rather than alphabetically by business name,"<<endl;
	cout<<"and in which advertising is sold. \n"<<endl ;
	system("pause");
	cout<<"___________________________________________________________________"<<endl;
}

void signup()
{
	string Fname,Lname,Pword;
	int year,month,day,Nphone;

    cout<<"\n\nPlease enter your information\n\n";
    cout<<"First name : ";
    cin>>Fname;
    cout<<"Last name : ";
    cin>>Lname;
    cout<<"Birthday( eg: 1990 12 30) : ";
    cin>>year>>month>>day;
    while (year<1900||year>2002||month<1||month>12||day<1||day>31)
    {
    	cout<<"\n\nPlease enter your correct birth date\n";
    	cout<<"Birthday( eg: 1990 12 30) : ";
    	cin>>year>>month>>day;
	}
	cout<<"No Phone : ";
	cin>>Nphone;
	cout<<"Password : ";
	cin>>Pword;
	
	cout<<"\n\nDear "<<Fname<<" "<<Lname<<", you have successfully sign up "<<endl;
	cout<<"___________________________________________________________________"<<endl;
	
	system("pause");
	system("cls");

	ofstream a((Fname+Pword+".txt").c_str(),ios::binary);
    a<<Fname;
	a<<" ";
	a<<Lname;
	/*a<<'\n';
    a<<Pword;
	a<<'\n';
    a<<Lname;
	a<<'\n';
    a<<year;
	a<<'\n';
    a<<month;
	a<<'\n';
    a<<day;
	a<<'\n';
    a<<Nphone;
	a<<'\n';*/
	a.close();
	
}

void login() 
{
	string Fname,Pword,Firstname;
	cout<<"\nPlease enter your First Name and Password for LOGIN "<<endl;
	cout<<"First Name: ";
	cin>>Fname;
	cout<<"Password: ";
	cin>>Pword;
	ifstream b((Fname+Pword+".txt").c_str(),ios::binary);
	if(b.good())
	{    
 		cout<<"\nDear ";
		while(b.good()){   cout << (char) b.get();  }
        cout<<"You have succesfully log in ^.^ "<<endl;
    }
	else
	{
		cout<<"___________________________________________________________________"<<endl;
		cout<<"Please log in back"<<endl;;
    	login(); //recursion 
	}
	cout<<"___________________________________________________________________"<<endl;
	cout<<"You may proceed to next stage "<<endl;
}

int main()
{
	
	Intro();
	cout<<"\nDo you have an acc? (y/n) : ";
	char acc;
	cin>>acc;
	while(acc!='y'&&acc!='n')
	{
		cout<<" \nYou have enter wrong answer please enter correctly\n";
		cout<<"Do you have an acc? (y/n) : ";
		cin>>acc;
	}
	if (acc=='n' )
	{
		cout<<"You need to sign up first\n";
		signup();
		login();
	}
	else
	{
	 	login();
	}
	

	
	return 0;
}


