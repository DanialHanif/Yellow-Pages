#include<iostream>
using namespace std;

void Service(int ser)
{
	switch(ser)
	{
		int article;
		case 1: cout<<"1.ARTICLE1\n2.ARTICLE2\n3.ARTICLE3\n";
				cout<<"You may choose article (1)(2)and(3)";
				cin>>article;				
				if(article==1)
				{
					cout<<"ARTICLE 1\nhttps://www.yellowpages.my/article/amalan-menyambut-syawal.html\n";
				}
				else if(article==2)
				{
					cout<<"ARTICLE 2\nhttps://www.yellowpages.my/article/juadah-popular-ketika-ramadhan.html\n";
				}
				else if(article==3)
				{
					cout<<"ARTICLE 3\nhttps://www.yellowpages.my/article/top-7-sweet-ethnic-treats-of-malaysia.html\n";
				}
				else
				{
										cout<<"There is no ARTICLE\n";
					cout<<"PRESS s : ";
					char ssor;
					cin>>ssor;
					if(ssor=='s')
					{
						cout<<"SERVICE\n1.ARTICLES\n2.USEFUL HOTLINE\n3.SOCIAL MEDIA\n\n";
						cout<<"Which service : ";
						int ss;
						cin>>ss;
						Service(ss);
					}
					else
					{
						Service(1);
					}
				}
				
				break;
				
		case 2: cout<<"You choose useful hotline.\n";
				cout<<"EMERGENCY\nPolice & Ambulance 999\nFire Brigade 999\nCivil Defense 999\nFrom Mobile Phone 112\nTalian NUR 15999\n\n";
				cout<<"TELCO\nTM/TMNet 100\n\n";
				cout<<"UTILITIES\nAlam Flora 1 800 88 0880\nIndah Water 1 800 88 3495\nKementerian Kerjaraya Malaysia 1 800 88 5004\nPosLine 1 300 300 300S\nSYABAS 1 800 88 5252\nTNB Careline 15454\n\n";
				cout<<"LOCAL AUTHORITIES\nDBKL 03-2617 9931\nMPAJ 03-4296 8000\nMPK 03-3371 6044\nMPKJ 03-8737 0112\nMBPJ 03-7956 3544\nMBSA 03-5510 5133\nMPSJ 03-8026 3131\n\n";
				cout<<"PUBLIC TRANSPORT\nAirport Coach 03-8787 3894\nAirport Limousine\n03-9223 8080\nRapid KL 03-7650 7788\nKL Monorail 03-2267 9888\nKL Sentral 03-2730 2000\nKLIA Express 03-2267 8088\nKTM (KL) 03-2267 1200\nLRT-PUTRA/STAR 1-800-388-228\nPlusliner 03-2272 1586\nTransnasional 1 300 888 582\n\n";
				break;
		
		case 3: cout<<"Social Media\n";
		        cout<<"FACEBOOK\nhttps://www.facebook.com/YellowPagesMalaysia/\n";
		        cout<<"INSTAGRAM\nhttps://www.instagram.com/shoplokal/\n";
		        cout<<"YOUTUBE\nhttps://www.youtube.com/channel/UCgoEIYiby7fT7uBq6HZG6dw\n";
				break;
				
		default : cout<<"Wrong number... Please enter number 1, 2 or 3...";
				int services;
				cout<<"SERVICE\n1.ARTICLES\n2.USEFUL HOTLINE\n3.SOCIAL MEDIA\n\n";
				cout<<"which service : ";
				cin>>services;
				Service(services);
				
	}
}
int main()
{
	int service;
	cout<<"SERVICE\n1.ARTICLES\n2.USEFUL HOTLINE\n3.SOCIAL MEDIA\n\n";
	cout<<"Which service : ";
	cin>>service;
	Service(service);
}
