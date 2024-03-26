#include <iostream>
#include "Shop.h"

int Shop::findIndexByBrand(const char* brand)
{
    for (size_t i = 0; i < wafflesCount; i++)
    {
        if (std::strcmp(this->waffles[i].getBrand(), brand) == 0)
        {
            return i;
        }
    }

    return -1;
}

void Shop::setWaffles(const Waffle* waffle)
{
    for (size_t i = 0; i < this->wafflesCount; i++)
    {
        addWaffle(waffle[i]);
    }
}

void Shop::addWaffle(const Waffle& waffle)
{
    this->waffles[wafflesCount++] = waffle;
    this->expenses += waffle.getSinglePrice();
}

void Shop::setIncome(double income)
{
    this->income = income;
}

void Shop::setExpenses(double expenses)
{
    this->expenses = expenses;
}

const Waffle* Shop::getWaffles() const
{
    return waffles;
}

const Waffle& Shop::getWaffle(int index) const
{
    return waffles[index];
}

double Shop::getIncome() const
{
    return income;
}

double Shop::getExpenses() const
{
    return expenses;
}

void Shop::sellWaffle(const char* brand)
{
    if (!brand)
    {
        return;
    }
    if (findIndexByBrand(brand) != -1)
    {
        unsigned index = findIndexByBrand(brand);
        this->income += this->waffles[index].getSinglePrice();
        for (size_t i = index; i < this->wafflesCount; i++)
        {
            this->waffles[i] = this->waffles[i + 1];
        }
    }
}

void Shop::countWafflesFromGivenBrand(const char* brand)
{
    if (!brand)
    {
        return;
    }
    unsigned count = 0;

    for (size_t i = 0; i < this->wafflesCount; i++)
    {
        if (std::strcmp(this->waffles[i].getBrand(), brand) == 0)
        {
            count++;
        }
    }

    std::cout << count << std::endl;
}

void Shop::winning()
{
    std::cout << "Winning is: " << this->income - this->expenses << std::endl;
}




