#pragma once

#define MAX_BRAND_LENGTH 20
class Waffle
{
	char brand[MAX_BRAND_LENGTH];
	double weight = 0;
	double wholePrice = 0;
	double singlePrice = 0;

public:
	const char* getBrand() const;
	double getWeight() const;
	double getWholePrice() const;
	double getSinglePrice() const;

	void setBrand(const char* brand);
	void setWeight(double weight);
	void setWholePrice(double wholePrice);
	void setSinglePrice(double singlePrice);
};

