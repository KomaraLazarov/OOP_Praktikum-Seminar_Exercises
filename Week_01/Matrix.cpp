#include <iostream>

int** createMatrix(unsigned rows, unsigned colls)
{
	int** mtx = new int* [rows];

	for (size_t i = 0; i < rows; i++)
	{
		mtx[i] = new int[colls];
	}
	return mtx;
}

int** transposeMatrix(const int* const* matrix, unsigned M, unsigned N)
{
	int** transposedMatrix = createMatrix(N, M);
	for (size_t i = 0; i < M; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			transposedMatrix[j][i] = matrix[i][j];
		}
	}

	return transposedMatrix;
}

void copyArr(int* dest, const int* src, unsigned size)
{
	if (!dest || !src)
	{
		return;
	}

	for (size_t i = 0; i < size; i++)
	{
		dest[i] = src[i];
	}
}

void interChangeTwoRows(int** matrix, unsigned rows, unsigned colls, unsigned firstRow, unsigned secondRow)
{
	if ((firstRow < 0 || firstRow > rows - 1) || 
		(secondRow < 0 || secondRow > rows - 1))
	{
		std::cout << "Incorrect rows input!" << std::endl;
		return;
	}

	int* copyArray = new int[colls];
	copyArr(copyArray, matrix[firstRow], colls);
	copyArr(matrix[firstRow], matrix[secondRow], colls);
	copyArr(matrix[secondRow], copyArray, colls);

	delete[] copyArray;
}

void readMatrix(int** matrix, unsigned rows, unsigned colls)
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < colls; j++)
		{
			int element = 0;
			std::cin >> element;
			matrix[i][j] = element;
		}
	}
}

void printMatrix(const int* const* matrix, unsigned rows, unsigned colls)
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < colls; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void deleteMatrix(const int* const* matrix, int rows)
{
	for (int i = 0; i < rows; i++)
	{
		delete[] matrix[i];
	}

	delete[] matrix;
}

int main()
{
	unsigned M = 0, N = 0;
	std::cin >> M >> N;

	int** matrix = createMatrix(M, N);
	readMatrix(matrix, M, N);

	interChangeTwoRows(matrix, M, N, 0, 2);

	int** transposed = transposeMatrix(matrix, M, N);

	printMatrix(matrix, M, N);
	printMatrix(transposed, N, M);

	deleteMatrix(matrix, M);
	deleteMatrix(transposed, N);
}