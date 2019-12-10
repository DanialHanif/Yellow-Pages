#include <iostream>
#include <Windows.h>
//#include <bits/stdc++.h> 
#pragma once

#ifndef PAYMENT_H
#define PAYMENT_H

class Payment {

	private:

		bool paid;


	public:

		Payment();
		void Description();
		void OnlineBanking();
		void payment();
		void viewDeals(int deal);
		bool result();

};

#endif // !PAYMENT_H
