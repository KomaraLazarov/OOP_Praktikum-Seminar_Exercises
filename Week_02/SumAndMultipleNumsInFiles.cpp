//#include <iostream>
//#include <fstream>
//
//int writeInFile(const char* fileName, int first, int second, int third)
//{
//	if (!fileName)
//	{
//		return 0;
//	}
//
//	std::ofstream myFile(fileName);
//	myFile.clear();
//
//	if (!myFile.is_open())
//	{
//		return 1;
//	}
//
//	int sum = first + second + third;
//	myFile << sum << std::endl;
//
//	int multiply = first * second * third;
//	myFile << multiply;
//
//	myFile.close();
//	return 0;
//}
//
//int readFromFile(const char* fileName)
//{
//	if (!fileName)
//	{
//		return 0;
//	}
//
//	std::ifstream myFile(fileName);
//
//	if (!myFile.is_open())
//	{
//		return 1;
//	}
//
//	int sum = 0, multiply = 1;
//	myFile >> sum;
//	myFile >> multiply;
//
//	std::cout << sum - multiply;
//
//	return 0;
//}
//
//int main()
//{
//	int first = 0, second = 0, third = 0;
//	std::cin >> first >> second >> third;
//
//	writeInFile("result.txt", first, second, third);
//	readFromFile("result.txt");
//}
//
