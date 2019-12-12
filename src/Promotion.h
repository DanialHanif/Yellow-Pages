#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include "Nodes.h"
#include <ctime>

#ifndef PROMOTION_H
#define PROMOTION_H


class Promotion {

protected:
	PromotionList* promotionList;
	PromotionList* headerPromotionList;
	PromotionList* currentPromotionList;
	PromotionData* currentPromotion;


public:
	Promotion();
	PromotionData* getPromotionData();
	PromotionList* getPromotionList();
	void addPromotion(UserData*);
	void editPromotion(UserData*);
	void deletePromotion(UserData*);
	void searchPromotion(UserData*);
	void viewPromotion(UserData*);
	void savePromotionListToDatabase();
	void loadPromotionListFromDatabase();
	void addPromotionDataFromDBToList(std::queue<std::string>);
	void checkValidInput(std::string&);
	void checkValidInputNumber(std::string&);
	time_t generateID();
	std::string postingDate();
	void viewCurrentPromotionInfo(PromotionData*);
	void viewPromotionBrief(PromotionData*);
	void editCurrentPromotion(UserData*, PromotionData*);
	void deleteCurrentPromotion(UserData*, PromotionData*);
	//void viewPromotionGuest();
};

#endif // !PROMOTION_H