#include <iostream>
#include <fstream>

namespace GlobalConstants
{
	constexpr unsigned MAX_COLORS_COUNT = 3;
	constexpr unsigned MAX_BUFF_LENGTH = 1024;
}

struct Color
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
};

struct Colors
{
	Color color[GlobalConstants::MAX_COLORS_COUNT];
	unsigned colorsCount;
};

unsigned powerofTwo(int n)
{
	return 1 << n;
}

void decimalToRGB(Color& color, int number)
{
	color.R = number / powerofTwo(16);
	color.G = (number / powerofTwo(8)) % powerofTwo(8);
	color.B = number % powerofTwo(8);
}

unsigned rgbToDecimal(int r, int g, int b)
{
	return b + (g * powerofTwo(8)) + (r * powerofTwo(16));
}

unsigned getDigit(char sym)
{
	return sym - '0';
}

int charToNumber(const char* str)
{
	if (!str)
	{
		return -1;
	}

	int num = 0;
	while (*str)
	{
		(num *= 10) += getDigit(*str);
		str++;
	}

	return num;
}

void extractColor(std::ifstream& myFile, Color& color)
{
	char buff[GlobalConstants::MAX_BUFF_LENGTH];
	myFile.getline(buff, GlobalConstants::MAX_BUFF_LENGTH, '|');
	int number = charToNumber(buff);
	decimalToRGB(color, number);
}

void readColors(const char* fileName, Colors& colors)
{
	if (!fileName)
	{
		return;
	}

	std::ifstream myFile(fileName);

	if (!myFile.is_open())
	{
		return;
	}

	int index = 0;
	while (true)
	{
		extractColor(myFile, colors.color[index++]);
		if (myFile.eof())
		{
			break;
		}
	}
	colors.colorsCount = index;

	myFile.close();
}

void writeColor(std::ofstream& myFile, const Color& color)
{
	myFile << rgbToDecimal(color.R, color.G, color.B);
}

void writeColors(const char* fileName, const Colors& colors)
{
	if (!fileName)
	{
		return;
	}

	std::ofstream myFile(fileName);

	if (!myFile.is_open())
	{
		return;
	}

	for (size_t i = 0; i < colors.colorsCount; i++)
	{
		writeColor(myFile, colors.color[i]);
		if (i == colors.colorsCount - 1)
		{
			break;
		}
		myFile << '|';
	}

	myFile.close();
}

void writeRedColors(const char* fileName, const Colors& colors)
{
	if (!fileName)
	{
		return;
	}

	std::ofstream myFile(fileName);

	if (!myFile.is_open())
	{
		return;
	}

	for (size_t i = 0; i < colors.colorsCount; i++)
	{
		if (colors.color[i].R > 250)
		{
			writeColor(myFile, colors.color[i]);
			myFile << '|';
		}
	}

	myFile.close();
}

void printColors(const Colors& colors)
{
	for (size_t i = 0; i < colors.colorsCount; i++)
	{
		Color color = colors.color[i];
		std::cout << (int)color.R << ' ' << (int)color.G << ' ' << (int)color.B << std::endl;
	}
}
int main()
{
	Colors colors = { 0 };
	readColors("colors.txt", colors);
	writeColors("colors.txt", colors);
	writeRedColors("red.txt", colors);
	printColors(colors);

	return 0;
}