#include "Waffle.h"
#include <cstring>
#pragma warning(disabled:4996)

const char* Waffle::getBrand() const
{
    return brand;
}

double Waffle::getWeight() const
{
    return weight;
}

double Waffle::getWholePrice() const
{
    return wholePrice;
}

double Waffle::getSinglePrice() const
{
    return singlePrice;
}

void Waffle::setBrand(const char* brand)
{
    if (!brand)
    {
        return;
    }
    size_t size = strlen(brand);
    if (size < MAX_BRAND_LENGTH)
    {
        strcpy(this->brand, brand);
    }
}

void Waffle::setWeight(double weight)
{
    this->weight = weight;
}

void Waffle::setWholePrice(double wholePrice)
{
    this->wholePrice = wholePrice;
}

void Waffle::setSinglePrice(double singlePrice)
{
    this->singlePrice = singlePrice;
}
