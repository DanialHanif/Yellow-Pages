#include "Payment.h"

using namespace std;

Payment::Payment() {
	this->paid = false;
	payment();
}

bool Payment::result() {
	return paid;
}

void Payment::Description()
{
	cout<<"\n\t   _____________________________________\n";
	cout<<"\t  |                                     |\n";
	cout<<"\t  |This program will execute deals and  |\n";
	cout<<"\t  |payment from Yellow Pages system..   |\n";
	cout<<"\t  |_____________________________________|\n\n";
	cout<<"\n\t   Name : NUR SUFIA BINTI AHMAD ZULKIFLI\n";
	cout<<"\t   Matric No : BI18110023\n";
	cout<<"\n\n\n\n\n";
	system("pause");
	system("cls");
}
void Payment::OnlineBanking()
{
	cout<<"\nWhich internet banking do you prefer?\n\t1.Maybank\n\t2.CIMB\n\t3.Public Bank\n\t"
	<<"4.Hong Leong Bank\n\t5.RHB\n\t6.Bank Islam\n\t7.AmBank\n\t8.Standard Chartered Bank"
	<<"\n\t9.Alliance Bank\n\t10.Bank Rakyat\n\t11.HSBC\n\t12.OCBC\n\t13.UOB\n\t14.Affin"
	<<" Bank\n\t15.Bank Muamalat\n\t16.Kuwait Finance House\n\t17.BSN\n\n";
	cout<<" Internet banking (eg: 14) : ";
	int ob; //online banking
	cin>>ob;
	
	while(ob<1||ob>17)
	{
		cout<<"\n\nError !! Please enter the number again : ";
		cin>>ob;
	}
	
	cout<<"\n\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	
	if(ob==1)
	{
		cout<<"\nYou are choosing Maybank Online Banking";
		char mb[100]="https://www.maybank2u.com.my/home/m2u/common/login.do";
		ShellExecute(NULL, "open", mb, NULL, NULL, SW_SHOWNORMAL);
	}
		
	else if(ob==2)
	{
		cout<<"\nYou are choosing CIMB Online Banking";
		char cimb[100]="https://www.cimbclicks.com.my/clicks/#/";
		ShellExecute(NULL, "open", cimb, NULL, NULL, SW_SHOWNORMAL);
	}
		
	else if(ob==3)
	{		
		cout<<"\nYou are choosing Public Bank Online Banking";
		char pb[100]="https://www2.pbebank.com/myIBK/apppbb/servlet/BxxxServlet?RDOName=BxxxAuth&MethodName=login";
		ShellExecute(NULL, "open", pb, NULL, NULL, SW_SHOWNORMAL);
	}
	
	else if(ob==4)
	{			
		cout<<"\nYou are choosing Hong Leong Bank Online Banking";
		char hl[100]="https://s.hongleongconnect.my/rib/app/fo/login?t=1&s=191108000945";
		ShellExecute(NULL, "open", hl, NULL, NULL, SW_SHOWNORMAL);
	}
	
	else if(ob==5)
	{			
		cout<<"\nYou are choosing RHB Online Banking";
		char rhb[100]="https://logon.rhb.com.my/";
		ShellExecute(NULL, "open", rhb, NULL, NULL, SW_SHOWNORMAL);
	}
			
	else if(ob==6)
	{	
		cout<<"\nYou are choosing Bank Islam Online Banking";
		char bi[100]="https://www.bankislam.biz/";
		ShellExecute(NULL, "open", bi, NULL, NULL, SW_SHOWNORMAL);
	}
	
	else if(ob==7)
	{			
		cout<<"\nYou are choosing AmBank Online Banking";
		char ab[100]="https://ambank.amonline.com.my/";
		ShellExecute(NULL, "open", ab, NULL, NULL, SW_SHOWNORMAL);
	}
	
	else if(ob==8)
	{			
		cout<<"\nYou are choosing Standard Chartered Bank Online Banking";
		char stb[100]="https://ibank.standardchartered.com.my/nfs/login.htm";
		ShellExecute(NULL, "open", stb, NULL, NULL, SW_SHOWNORMAL);
	}
	
	else if(ob==9)
	{			
		cout<<"\nYou are choosing Alliance Bank Online Banking";
		char alb[100]="https://www.allianceonline.com.my/personal/login/login.do";
		ShellExecute(NULL, "open", alb, NULL, NULL, SW_SHOWNORMAL);
	}
	
	else if(ob==10)
	{			
		cout<<"\nYou are choosing Bank Rakyat Online Banking";
		char br[100]="https://www2.irakyat.com.my/personal/login/login.do?step1=";
		ShellExecute(NULL, "open", br, NULL, NULL, SW_SHOWNORMAL);
	}
	
	else if(ob==11)
	{			
		cout<<"\nYou are choosing HCBC Online Banking";
		char hsbc[100]="https://www.hsbc.com.my/security/";
		ShellExecute(NULL, "open", hsbc, NULL, NULL, SW_SHOWNORMAL);
	}
	
	else if(ob==12)
	{			
		cout<<"\nYou are choosing OCBC Online Banking";
		char ocbc[100]="https://internet.ocbc.com.my/internet-banking";
		ShellExecute(NULL, "open", ocbc, NULL, NULL, SW_SHOWNORMAL);
	}
	
	else if(ob==13)
	{			
		cout<<"\nYou are choosing UOB Online Banking";
		char uob[100]="https://pib.uob.com.my/PIBLogin/Public/processPreCapture.do?keyId=lpc&lang=en_MY";
		ShellExecute(NULL, "open", uob, NULL, NULL, SW_SHOWNORMAL);
	}
	
	else if(ob==14)
	{			
		cout<<"\nYou are choosing Affin Bank Online Banking";
		char afb[100]="https://rib.affinonline.com/retail/#!/login";
		ShellExecute(NULL, "open", afb, NULL, NULL, SW_SHOWNORMAL);
	}
	
	else if(ob==15)
	{			
		cout<<"\nYou are choosing Bank Muamalat Online Banking";
		char bmu[100]="https://www.i-muamalat.com.my/rib/index.do";
		ShellExecute(NULL, "open", bmu, NULL, NULL, SW_SHOWNORMAL);
	}
	
	else if(ob==16)
	{			
		cout<<"\nYou are choosing Kuwait Finance House Online Banking";
		char kfh[100]="https://www.kfhonline.com.my/kfh_consumer/common/Login.do";
		ShellExecute(NULL, "open", kfh, NULL, NULL, SW_SHOWNORMAL);
	}
	
	else
	{			
		cout<<"\nYou are choosing BSN Online Banking";
		char bsn[100]="https://www.mybsn.com.my/mybsn/login/login.do";
		ShellExecute(NULL, "open", bsn, NULL, NULL, SW_SHOWNORMAL);
	}
	
	cout<<"\n\n\t Insert your reference number : ";
	int ref;
	cin>>ref;
	paid = true;
	result();
	cout<<endl<<endl;
}

void Payment::payment()
{
	cout<<"\n***************************************************************************************************\n";
	cout<<"\t\t1. Essential = RM 49.90 / monthly \n\t\t2. Commerce = RM 79.90 / monthly \n\t\t3. Deluxe = RM 149.90 / monthly \n\n";
	cout<<"Enter number of deals (1/2/3):";
	
	int pay;
	cin>>pay;
	while(pay<1||pay>3)
	{
		system("cls");
		cout<<"\n\t\tWrong number!!";
		cout<<"\n\t\t1. Essential = RM 49.90 / monthly \n\t\t2. Commerce = RM 79.90 / monthly \n\t\t3. Deluxe = RM 149.90 / monthly \n\n";
		cout<<"Enter number of deals (1/2/3):";
		cin>>pay;
	}
	cout<<"\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
	
	if(pay==1)
	{
		cout<<"\n\tYou are choosing Essential deal ^_^\n";
		cout<<"\tYou may pay RM 49.90";
	}
	else if(pay==2)
	{
		cout<<"\n\tYou are choosing Commerce deal ^_^\n";
		cout<<"\tYou may pay RM 79.90";
	}
	else
	{
		cout<<"\n\tYou are choosing Deluxe deal ^_^\n";
		cout<<"\tYou may pay RM 149.90";
	}
	
	cout<<"\n\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
	cout<<"\n\n\tWhich payment method do you prefer?\n";
	cout<<"\t1.Online transfer(internet banking)\n\t2.Cash transfer(ATM)\n\n*you may"
		<<" insert 3 if you need trusted agent consultation about payment\n\n\tPayment Method (1/2/3): ";
	int PaymentMethod;
	cin>>PaymentMethod;
	while(pay<1||pay>3)
	{
		cout<<"\t\tWrong number!!";
		cout<<"\n\tWhich payment method do you prefer?\n\n";
		cout<<"\t1.Online transfer(internet banking)\n\t2.Cash transfer(ATM)\n\n*you may"
		<<" insert 3 if you need trusted agent consultation about payment\n\n\tPayment Method (1/2/3): ";
		cin>>PaymentMethod;
	}
	system("cls");
	
	if(PaymentMethod==1)
	{
		OnlineBanking();
	}
	else if(PaymentMethod==2)
	{
		cout<<"\nYou may transfer to number account below\n";
		cout<<"__________________________________________";
		cout<<"\n\t1560161678903\n\tYellow Pages Data Structure\n";
		cout<<"__________________________________________";
		cout<<"\n\n*Snap your resit and sent to our staff\n\n";
		char phone[100]="https://wa.me/601111425342";
		ShellExecute(NULL, "open", phone, NULL, NULL, SW_SHOWNORMAL);
	}
	else
	{
		cout<<"\nYou may contact our staff\n";
		char phones[100]="https://wa.me/601111425342";
		ShellExecute(NULL, "open", phones, NULL, NULL, SW_SHOWNORMAL);
	}
	
}

void Payment::viewDeals(int deal)
{
	switch(deal)
	{
		case 1: cout<<"################################ Advantages of choosing Essential ################################\n\n";
		
				cout<<"1.Business presence\t~~Business Listing in e-Directory\n\t\t\t~~5 Images and 1 Logo in e-Directory\n";
				cout<<"\t\t\t~~10 Keywords\n\t\t\t~~Web Builder with unlimited pages\n\t\t\t~~Over 20+ website theme /template ";
				cout<<"ready to use\n\t\t\t~~FREE Domain and Hosting (.com, .net, .org)\n\t\t\t~~Mobile Website Responsive\n\n";
				
				cout<<"2.Business engagement\t~~Chat System / Auto Reply Comment\n\t\t\t~~Ready Newsletter integration";
				cout<<"\n\t\t\t~~Form Builder\n\n";
				
				cout<<"3.Business analytics\t~~Analytics Dashboards\n\n\n";
				break;
		
		case 2: cout<<"################################# Advantages of choosing Commerce #################################\n\n";

				cout<<"1.Business presence\t~~Business Listing in e-Directory\n\t\t\t~~5 Images and 1 Logo in e-Directory\n";
				cout<<"\t\t\t~~10 Keywords\n\t\t\t~~Web Builder with unlimited pages\n\t\t\t~~Over 20+ website theme /template ";
				cout<<"ready to use\n\t\t\t~~FREE Domain and Hosting (.com, .net, .org)\n\t\t\t~~Mobile Website Responsive\n\n";
				
				cout<<"2.Business engagement\t~~Chat System / Auto Reply Comment\n\t\t\t~~Ready Newsletter integration";
				cout<<"\n\t\t\t~~Form Builder\n\n";
				
				cout<<"3.Business analytics\t~~Analytics Dashboards\n\n";
				
				cout<<"4.Business E-Commerce\t~~Payment Gateway\n\t\t\t~~Web store and Product Catalogue\n\n\n";
				break;

		case 3: cout<<"################################ Advantages of choosing Essential #################################\n\n";
						
				cout<<"1.Business presence\t~~Business Listing in e-Directory\n\t\t\t~~5 Images and 1 Logo in e-Directory\n";
				cout<<"\t\t\t~~10 Keywords\n\t\t\t~~Web Builder with unlimited pages\n\t\t\t~~Over 20+ website theme /template ";
				cout<<"ready to use\n\t\t\t~~FREE Domain and Hosting (.com, .net, .org)\n\t\t\t~~Mobile Website Responsive\n\n";
				
				cout<<"2.Business engagement\t~~Chat System / Auto Reply Comment\n\t\t\t~~Ready Newsletter integration";
				cout<<"\n\t\t\t~~Form Builder\n\n";
				
				cout<<"3.Business analytics\t~~Analytics Dashboards\n\n";
				
				cout<<"4.Business E-Commerce\t~~Payment Gateway\n\t\t\t~~Web store and Product Catalogue\n\n\n";
				
				cout<<"5.Business support\t~~Online video tutorial\n\t\t\t~~Live chat and Email Support\n\t\t\t";
				cout<<"~~FREE hands on training for yearly subscription\n\t\t\t~~FREE consultation\n\t\t\t~~";
				cout<<"FREE business page set up in portal & app\n\n";
				
				cout<<"6.Business marketing\t~~FB or Google Ads Campaigns\n\t\t\t~~Flexible Campaign Ads format\n\n\n";
				break;
		
		default:
		
				cout<<"\n\t\tProceed to payment ? (y/n) : ";
				char confirm;  
				cin>>confirm;
		
				while(confirm!='y'&&confirm!='n')
				{
					cout<<"\n!!!!!!!!!!!!!!!!!!!!!!!!!  Wrong entry !! Please insert y or n ONLY. ^-^  !!!!!!!!!!!!!!!!!!!!!!!!!";
					cout<<"\n\n\t\tProceed to payment ? (y/n) : ";
					cin>>confirm;
				}
				
				
				if(confirm=='y') 
				{ 
					system("cls");
					payment(); 
					return;
				}
				else
				{
					cout<<"___________________________________________________________________________________________________\n\n";
					cout<<"\n\t\tDON'T MISS THE CHANCE TO BE OUR LUCKY CUSTOMER !!\n\n\t\tFor your information, there is";
					cout<<" so much PROMOTIONS \n\t\twaiting for you once you choose our deal !!\n\n\t\tDon't miss the chance to ";
					cout<<"grab our deal and enjoy the promotions !!\n\n\t\tAre you sure you want to cancel? (y/n) : ";
					char cancel; 
					cin>>cancel;
					while(cancel!='y'&&cancel!='n')
					{
						cout<<"\n\t\tAre you sure you want to cancel? (y/n) : ";
						cin>>cancel;
					}
					cout<<"___________________________________________________________________________________________________\n\n";
					if(cancel=='y') 
					{ 
						system("cls");
						cout<<"\n***************************************************************************************************\n";
						cout<<"\t\t\tYour deal's cancellation successful ^_^\n\t\t\tHope to see you again on our page next time....";
						cout<<"\n\n\t\t\tThank you !!";
						cout<<"\n***************************************************************************************************\n";
						return; 
					}
					else
					{
						cout<<"\t\t GREAT CHOICE ^-^\n\n"<<endl;
					}
				}
			}
		system("pause");
		cout<<"___________________________________________________________________________________________________\n\n";
		cout<<"\t\tInsert a number of deals you wants to know more , (1/2/3)\n\t\tInsert any other number to continue or cancel the payment : ";
		cin>>deal;
		cout<<"___________________________________________________________________________________________________\n\n";
		viewDeals(deal);  //using recursion
}

