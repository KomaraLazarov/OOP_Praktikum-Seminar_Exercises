//#include <iostream>
//#include <fstream>
//
//
//constexpr int MAX_COLS = 100;
//constexpr int MAX_ROWS = 100;
//
//struct Row
//{
//	int elements[MAX_COLS];
//	unsigned elementsCount;
//};
//
//struct Matrix
//{
//	Row rows[MAX_ROWS];
//	unsigned rowsCount;
//};
//
//int getNumberFromSymbol(char symbol)
//{
//	if (symbol >= '0' && symbol <= '9')
//	{
//		return symbol - '0';
//	}
//
//	return symbol;
//}
//
//void copyArrays(const char* src, int* dest, size_t size)
//{
//	if (!src || !dest)
//	{
//		return;
//	}
//
//	for (size_t i = 0; i < size; i++)
//	{
//		dest[i] = (int)src[i];
//	}
//}
//
//void getNumbersFromStringWithCommas(Row& row, const char* str)
//{
//	if (!str)
//	{
//		return;
//	}
//
//	int number = 0;
//	size_t index = 0;
//
//	do
//	{
//		if (*str == ',')
//		{
//			row.elements[index++] = number;
//			number = 0;
//			*str++;
//		}
//
//		number = number * 10 + getNumberFromSymbol(*str);
//
//		if (*(str+1) == '\0')
//		{
//			row.elements[index++] = number;
//		}
//
//		*str++;
//
//	} while (*str);
//
//	row.elementsCount = index;
//}
//
//void readMatrixFromFile(Matrix& matrix, std::ifstream& myfile)
//{
//	char buff[1024];
//	size_t index = 0;
//
//	while (true)
//	{
//		myfile.getline(buff, 1024, '|');
//		getNumbersFromStringWithCommas(matrix.rows[index++], buff);
//
//		if (myfile.eof())
//		{
//			break;
//		}
//	}
//
//	matrix.rowsCount = index;
//}
//
//void readFromFile(Matrix& matrix, const char* fileName)
//{
//	if (!fileName)
//	{
//		return;
//	}
//	std::ifstream myFile(fileName);
//
//	if (!myFile.is_open())
//	{
//		return;
//	}
//
//	readMatrixFromFile(matrix, myFile);
//
//	myFile.close();
//}
//
//int rowAndColMultiplication(unsigned fixed, unsigned overall, unsigned curr, const Matrix& firstMatrix, const Matrix& secondMatrix)
//{
//	int result = 0;
//
//	for (size_t j = 0; j < overall; j++)
//	{
//		result += firstMatrix.rows[fixed].elements[j] * secondMatrix.rows[j].elements[curr];
//	}
//
//	return result;
//}
//
//void matrixMultiplication(const Matrix& firstMatrix, const Matrix& secondMatrix, Matrix& result)
//{
//	result.rowsCount = firstMatrix.rowsCount;
//	result.rows->elementsCount = secondMatrix.rows->elementsCount;
//
//	for (size_t j = 0; j < result.rowsCount; j++)
//	{
//		for (size_t k = 0; k < result.rows->elementsCount; k++)
//		{
//			result.rows[j].elements[k] = rowAndColMultiplication(j, secondMatrix.rowsCount, k, firstMatrix, secondMatrix);
//		}
//
//	}
//}
//
//void printArray(const Row& row, size_t size)
//{
//	for (size_t i = 0; i < size; i++)
//	{
//		std::cout << row.elements[i] << " ";
//	}
//
//	std::cout << std::endl;
//}
//
//void printMatrix(const Matrix& matrix)
//{
//	for (size_t i = 0; i < matrix.rowsCount; i++)
//	{
//		printArray(matrix.rows[i], matrix.rows->elementsCount);
//	}
//}
//
//void writeMatrixInFileInCorrectFormat(const Matrix& matrix, std::ofstream& myFile)
//{
//	for (size_t i = 0; i < matrix.rowsCount; i++)
//	{
//		for (size_t j = 0; j < matrix.rows->elementsCount; j++)
//		{
//			if (j == matrix.rows->elementsCount - 1)
//			{
//				myFile << matrix.rows[i].elements[j];
//				break;
//			}
//
//			myFile << matrix.rows[i].elements[j] << ',';
//		}
//
//		if (i == matrix.rowsCount - 1)
//		{
//			break;
//		}
//		myFile << '|';
//	}
//}
//
//void writeMatrixInFile(const Matrix& matrix, const char* fileName)
//{
//	if (!fileName)
//	{
//		return;
//	}
//	std::ofstream myFile(fileName);
//
//	if (!myFile.is_open())
//	{
//		return;
//	}
//
//	writeMatrixInFileInCorrectFormat(matrix, myFile);
//
//	myFile.close();
//}
//
//int main()
//{
//	Matrix firstMatrix;
//	Matrix secondMatrix;
//	Matrix resultMatrix;
//	readFromFile(firstMatrix, "fst.txt");
//	readFromFile(secondMatrix, "scd.txt");
//
//	matrixMultiplication(firstMatrix, secondMatrix, resultMatrix);
//	writeMatrixInFile(resultMatrix, "result.txt");
//	//printMatrix(resultMatrix);
//	//printMatrix(firstMatrix);
//	//std::cout << std::endl;
//	//printMatrix(secondMatrix);
//}