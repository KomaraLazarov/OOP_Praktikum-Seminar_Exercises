#include <iostream>

namespace complex
{
	struct ComplexNumber
	{
		int realPart;
		int imaginaryPart;
	};

	ComplexNumber& sumComplexEq(ComplexNumber& fst, const ComplexNumber& scd)
	{
		fst.realPart += scd.realPart;
		fst.imaginaryPart += scd.imaginaryPart;

		return fst;
	}

	ComplexNumber sumComplexNumbers(const ComplexNumber& fst, const ComplexNumber& scd)
	{
		ComplexNumber num = fst;

		sumComplexEq(num, scd);

		return num;
	}

	ComplexNumber& multiplyComplexEq(ComplexNumber& fst, const ComplexNumber& scd)
	{
		fst.realPart *= scd.realPart;
		fst.imaginaryPart *= scd.imaginaryPart;

		return fst;
	}

	ComplexNumber multipleComplexNumbers(const ComplexNumber& fst, const ComplexNumber& scd)
	{
		ComplexNumber num = { 1, 1 };

		multiplyComplexEq(num, fst);
		multiplyComplexEq(num, scd);

		return num;
	}

	void printComplex(const ComplexNumber& num)
	{
		std::cout << num.realPart << " + " << num.imaginaryPart << "i" << std::endl;
	}
}

using namespace complex;

int main()
{
	ComplexNumber first = {3, 6};
	ComplexNumber second = {2, 3};
	ComplexNumber result;

	result = sumComplexNumbers(first, second);
	printComplex(result);
	result = multipleComplexNumbers(first, second);
	printComplex(result);
}