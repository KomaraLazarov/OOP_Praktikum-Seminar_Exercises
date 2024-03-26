#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)

constexpr unsigned MAX_TITLE_LENGTH = 64;
constexpr unsigned MAX_GAMES_COUNT = 30;

class Game
{
private:
	char title[MAX_TITLE_LENGTH] = "";
	double price = 0;
	bool isAvailable = false;

public:

	Game(const char* title, double price, bool isAvailable)
	{
		setTitle(title);
		setPrice(price);
		setIsAvailable(isAvailable);
	}

	Game() = default;

	void setTitle(const char* title)
	{
		if (!title)
		{
			return;
		}
		if (std::strlen(title) <= MAX_TITLE_LENGTH)
		{
			std::strcpy(this->title, title);
		}
	}

	void setPrice(double price)
	{
		this->price = price;
	}

	void setIsAvailable(bool isAvailable)
	{
		this->isAvailable = isAvailable;
	}

	const char* getTitle() const
	{
		return this->title;
	}

	const double getPrice() const
	{
		return this->price;
	}

	const bool getIsAvailable() const
	{
		return this->isAvailable;
	}

	bool isFree()
	{
		return price == 0;
	}

	void print()
	{
		std::cout << "Title: " << this->title << std::endl;
		std::cout << "Price: " << this->price << std::endl;
		std::cout << "Is available: " << this->isAvailable << std::endl;
	}
};

class GamePlatform
{
private:
	Game library[MAX_GAMES_COUNT];
	unsigned gamesCount = 0;

	void writeLibraryInFile(std::ofstream& myFile)
	{
		myFile.write((const char*)this->library, sizeof(GamePlatform));
	}
	void readLibraryFromFile(std::ifstream& myFile)
	{
		myFile.read((char*)this->library, sizeof(GamePlatform));
	}

public:

	void addGame(const char* title, double price, bool isAvailable)
	{
		if (!title && !isAvailable)
		{
			return;
		}

		if (this->gamesCount == MAX_GAMES_COUNT)
		{
			return;
		}

		Game newGame = Game(title, price, isAvailable);

		this->library[this->gamesCount] = newGame;
		this->gamesCount++;
	}

	void removeGameByIndex(unsigned index)
	{
		if (index >= this->gamesCount)
		{
			return;
		}

		for (size_t i = index; i < this->gamesCount; i++)
		{
			this->library[i] = this->library[i + 1];
		}
		this->gamesCount--;
	}

	void printGames()
	{
		for (size_t i = 0; i < this->gamesCount; i++)
		{
			this->library[i].print();
			std::cout << std::endl;
		}
	}

	void printTheMostCheaperAndExpensiveGame()
	{
		unsigned minIndex = 0;
		double minPrice = INT32_MAX;
		unsigned maxIndex = 0;
		double maxPrice = INT32_MIN;
		for (size_t i = 0; i < this->gamesCount; i++)
		{
			if (this->library[i].getPrice() < minPrice)
			{
				minPrice = this->library[i].getPrice();
				minIndex = i;
			}
			if (this->library[i].getPrice() > maxPrice)
			{
				maxPrice = this->library[i].getPrice();
				maxIndex = i;
			}
		}

		std::cout << "The most cheaper game is: " << std::endl;
		this->library[minIndex].print();
		std::cout << "The most expensive game is: " << std::endl;
		this->library[maxIndex].print();
	}

	void printAllFreeGames()
	{
		for (size_t i = 0; i < this->gamesCount; i++)
		{
			if (this->library[i].isFree())
			{
				this->library[i].print();
			}
		}
	}

	void printGameByIndex(unsigned index)
	{
		if (index >= this->gamesCount)
		{
			return;
		}

		for (size_t i = 0; i < this->gamesCount; i++)
		{
			if (i == index)
			{
				this->library[i].print();
			}
		}
	}

	void writeInFile(const char* filename)	
	{
		std::ofstream myFile(filename, std::ios::binary);
		if (!myFile.is_open())
		{
			return;
		}

		writeLibraryInFile(myFile);

		myFile.close();
	}

	void readFromFile(const char* filename)
	{
		std::ifstream myFile(filename, std::ios::binary);
		if (!myFile.is_open())
		{
			return;
		}

		readLibraryFromFile(myFile);

		myFile.close();
	}
};

int main()
{
	GamePlatform library;
	library.addGame("koko", 3.45, true);
	library.addGame("chefo", 0.0, true);
	library.addGame("pepi", 1.45, false);

	library.writeInFile("games.dat");
	library.readFromFile("games.dat");
	//library.printAllFreeGames();
	//library.printGameByIndex(2);
	//library.printGames();
	//library.printTheMostCheaperAndExpensiveGame();
	library.removeGameByIndex(1);
	library.printGames();
}