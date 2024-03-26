#include <iostream>
#include <fstream>

constexpr int MAX_NAME_LENGTH = 25;
const char* FILE_NAME = "offer.dat";
const char* FILE_NAME1 = "offer1.dat";


struct Offer
{
	long long salary;
	char name[MAX_NAME_LENGTH];
	int programmersCount;
	int gapDaysCount;
};

void writeOfferToFile(Offer& offer, std::ofstream& myFile)
{
	myFile.write((const char*)&offer, sizeof(Offer));
}

void writeToFile(Offer& offer, const char* filename)
{
	std::ofstream myFile(filename, std::ios::app | std::ios::binary);

	if (!myFile.is_open())
	{
		return;
	}

	writeOfferToFile(offer, myFile);

	myFile.close();
}

size_t getFileSize(std::ifstream& myFile) 
{
	size_t currentPos = myFile.tellg();
	myFile.seekg(0, std::ios::end);
	size_t size = myFile.tellg();

	myFile.seekg(currentPos);
	return size;
}

void init(Offer& offer)
{
	std::cout << "Eter name: ";
	std::cin >> offer.name;

	std::cout << "Programmers count: ";
	std::cin >> offer.programmersCount;

	std::cout << "Gap days: ";
	std::cin >> offer.gapDaysCount;

	std::cout << "Salary: ";
	std::cin >> offer.salary;
}

void readOffersFromConsole()
{
	int offersCount = 0;
	std::cin >> offersCount;

	for (size_t i = 0; i < offersCount; i++)
	{
		Offer offer;
		init(offer);
		writeToFile(offer, FILE_NAME);
	}
}

void readOfferFromFile(Offer& offer, std::ifstream& myFile)
{
	myFile.read((char*)&offer, sizeof(Offer));
}

void readFromFile(Offer& offer, const char* filename)
{
	std::ifstream myFile(filename, std::ios::binary);
	if (!myFile.is_open())
	{
		return;
	}

	readOfferFromFile(offer, myFile);

	myFile.close();
}

void printOffer(const Offer& offer) 
{
	std::cout << offer.name << " " << offer.programmersCount << " " << offer.gapDaysCount << " " << offer.salary << std::endl;
} 

void filterOffers(const char* filePath, long long minSalary)
{
	if (!filePath)
	{
		return;
	}
	std::ifstream myFile(filePath);
	if (!myFile.is_open())
	{
		return;
	}
	int offersCount = getFileSize(myFile) / sizeof(Offer);

	for (size_t i = 0; i < offersCount; i++)
	{
		Offer offer;
		readOfferFromFile(offer, myFile);
		if (offer.salary >= minSalary)
		{
			printOffer(offer);
		}
	}

	myFile.close();
}

bool existOffer(const char* filePath, const char* name)
{
	if (!filePath)
	{
		return false;
	}
	std::ifstream myFile(filePath);
	if (!myFile.is_open())
	{
		return false;
	}
	int offersCount = getFileSize(myFile) / sizeof(Offer);

	for (size_t i = 0; i < offersCount; i++)
	{
		Offer offer;
		readOfferFromFile(offer, myFile);
		if (std::strcmp(offer.name, name) == 0)
		{
			myFile.close();
			return true;
		}
	}

	myFile.close();
	return false;
}

void perfectOffer(const char* filePath, const char* filePath1, int maxCoworkers, int minVacancyDays, int minSalary)
{
	if (!filePath)
	{
		return;
	}
	std::ifstream myFileRead(filePath, std::ios::in | std::ios::binary);
	std::ofstream myFileWrite(filePath1, std::ios::out | std::ios::binary);
	if (!myFileRead.is_open() && !myFileWrite.is_open())
	{
		return;
	}

	int offersCount = getFileSize(myFileRead) / sizeof(Offer);

	for (size_t i = 0; i < offersCount; i++)
	{
		Offer offer;
		readOfferFromFile(offer, myFileRead);
		if (offer.programmersCount <= maxCoworkers && offer.gapDaysCount >= minVacancyDays && offer.salary >= minSalary)
		{
			writeOfferToFile(offer, myFileWrite);
		}
	}

	myFileRead.close();
	myFileWrite.close();
}

int main()
{
	readOffersFromConsole();
	std::cout << existOffer(FILE_NAME, "sds");
	perfectOffer(FILE_NAME, FILE_NAME1, 1, 1, 1);
	Offer offer;
	readFromFile(offer, FILE_NAME1);
	readFromFile(offer, FILE_NAME);
	printOffer(offer);
}