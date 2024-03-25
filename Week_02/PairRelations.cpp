#include <iostream>
#include <fstream>

constexpr int MAX_PAIRS_COUNT = 25;
constexpr int MAX_BUFF_LENGTH = 1024;

struct Pair
{
	int a;
	int b;
};

struct Relation
{
	Pair pairs[MAX_PAIRS_COUNT];
	int pairsCount;
};

void creatPair(Pair& pair)
{
	std::cout << "Enter a: ";
	std::cin >> pair.a;

	std::cout << "Enter b: ";
	std::cin >> pair.b;
	std::cin.ignore(1);
}

void createRelation(Relation& rel)
{
	std::cout << "Enter pairs count: ";
	std::cin >> rel.pairsCount;
	std::cin.ignore(1);

	for (size_t i = 0; i < rel.pairsCount; i++)
	{
		std::cout << "Enter pair info: " << std::endl;
		creatPair(rel.pairs[i]);
	}
}

void writePairToFile(const Pair& pair, std::ofstream& writeInFile)
{
	writeInFile << pair.a << " " << pair.b << std::endl;
}

void printPairToConsole(const Pair& pair)
{
	std::cout << pair.a << " " << pair.b << std::endl;
}

void printRelation(const Relation& relation)
{
	std::cout << relation.pairsCount << std::endl;

	for (size_t i = 0; i < relation.pairsCount; i++)
	{
		printPairToConsole(relation.pairs[i]);
	}
}

void writeRelationToFile(const char* fileName, const Relation& relation)
{
	std::ofstream myFile(fileName);

	if (!myFile.is_open())
	{
		return;
	}

	myFile << relation.pairsCount << std::endl;
	for (size_t i = 0; i < relation.pairsCount; i++)
	{
		writePairToFile(relation.pairs[i], myFile);
	}
	
	myFile.close();
}

void readRelationFromFile(const char* fileName, Relation& rel)
{
	std::ifstream myFile(fileName);

	if (!myFile.is_open())
	{
		return;
	}

	myFile >> rel.pairsCount;

	for (size_t i = 0; i < rel.pairsCount; i++)
	{
		myFile >> rel.pairs[i].a;
		myFile >> rel.pairs[i].b;
	}

	myFile.close();
}

void addPairToRelation(const Pair& pair, Relation& relation)
{
	if (relation.pairsCount >= MAX_PAIRS_COUNT - 1)
	{
		return;
	}

	relation.pairsCount++;
	relation.pairs[relation.pairsCount - 1].a = pair.a;
	relation.pairs[relation.pairsCount - 1].b = pair.b;
}

void readPairFromFile(const char* fileName, Pair& pair, unsigned number)
{
	std::ifstream myFile(fileName);
	char buff[MAX_BUFF_LENGTH];

	if (!myFile.is_open())
	{
		return;
	}

	unsigned pairsCount = 0;
	myFile >> pairsCount;

	if (number > pairsCount || number <= 0)
	{
		return;
	}

	myFile.ignore(1);
	for (size_t i = 1; i <= pairsCount; i++)
	{
		if (i == number)
		{
			myFile >> pair.a;
			myFile >> pair.b;
			break;
		}
		myFile.getline(buff, MAX_BUFF_LENGTH);
	}

	myFile.close();
}

int main()
{
	Relation relation;
	//createRelation(relation);

	readRelationFromFile("relations.txt", relation);
	//writeRelationToFile("relations.txt", relation);
	//printRelation(relation);
	Pair pair = { 2, 4 };
	//addPairToRelation(pair, relation);
	//printRelation(relation);
	readPairFromFile("relations.txt", pair, 3);
	printPairToConsole(pair);
}
