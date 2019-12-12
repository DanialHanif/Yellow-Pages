#include<iostream>
using namespace std;

void Deals(int deal)
{
	switch(deal)
	{
		int promotion;
		case 1: cout<<"1.ONEBUSINESS FIBRE\n2.HONEYMOON PACKAGE\n3.5% OFF FOR STUDENTS\n";
				cout<<"You may choose any of the Promotions (1)(2)and(3)";
				cin>>promotion;				
				if(promotion==1)
				{
					cout<<"ONEBUSINESS FIBRE\nhttps://www.yellowpages.my/deal/how-can-i-keep-my-business-always-on-onebusiness-fibre-allows-you-to-enjoy-superfast-speeds-of-up-t.html\n\n";
				}
				else if(promotion==2)
				{
					cout<<"HONEYMOON PACKAGE\nhttps://www.yellowpages.my/deal/honeymoon-package.html\n\n";
				}
				else if(promotion==3)
				{
					cout<<"5% OFF FOR STUDENTS\nhttps://www.yellowpages.my/deal/5-off-for-students.html\n\n";
				}
				else
				{
										cout<<"There are no Promotions\n";
					cout<<"PRESS s : ";
					char ssor;
					cin>>ssor;
					if(ssor=='s')
					{
						cout<<"DEALS\n1.PROMOTION\n2.REWARDS\n\n";
						cout<<"which deal : ";
						int ss;
						cin>>ss;
						Deals(ss);
					}
					else
					{
						Deals(1);
					}
				}
				
				break;
				
				case 2: cout<<"REWARDS\n";
						cout<<"You may choose any of the REWARDS.\n\n";
						cout<<"YELLOW USER\nMonthy Rewards will be updated\nTEALIVE Voucher Worth RM10 for Birthday Treat\n\n";
						cout<<"SILVER USER\nWeekly Rewards will be updated\nSTARBUCKS Voucher Worth RM15 for Birthday Treat\n3x points for active usage\n\n";
						cout<<"GOLD USER\nDaily Rewards will be updated\nSeol Garden Voucher Worth RM30 for Birthday Treat\n5x points for active usage\n\n";
						break;
				
				
		default : cout<<"Wrong number... Please enter number 1 or 2...";
				int services;
				cout<<"DEALS\n1.PROMOTION\n2.REWARDS\n\n";
				cout<<"which deal : ";
				cin>>deal;
				Deals(deal);
				
	}
}
int main()
{
	int deal;
	cout<<"DEALS\n1.PROMOTION\n2.REWARDS\n\n";
	cout<<"Which Deal : ";
	cin>>deal;
	Deals(deal);
}
