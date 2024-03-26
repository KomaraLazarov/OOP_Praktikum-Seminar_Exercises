#pragma once
#include "Waffle.h"
#define MAX_WAFFLE_COUNT 20

class Shop
{
	Waffle waffles[MAX_WAFFLE_COUNT];
	int wafflesCount = 0;
	double income = 0;
	double expenses = 0;

	int findIndexByBrand(const char* brand);

public:

	void setWaffles(const Waffle* waffle);
	void addWaffle(const Waffle& waffle);
	void setIncome(double income);
	void setExpenses(double expenses);

	const Waffle* getWaffles() const;
	const Waffle& getWaffle(int index) const;
	double getIncome() const;
	double getExpenses() const;

	void sellWaffle(const char* brand);
	void countWafflesFromGivenBrand(const char* brand);
	void winning();
};

