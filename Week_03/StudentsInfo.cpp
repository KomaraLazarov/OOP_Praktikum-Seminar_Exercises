#include <iostream>
#include <fstream>
#include <sstream>

constexpr unsigned MAX_NAME_LENGTH = 16;
constexpr unsigned MAX_FACULTY_NUMBER_LENGTH = 5;
constexpr unsigned MAX_AVERAGE_SUCCESS_LENGTH = 10;
constexpr unsigned MAX_STUDENTS_IN_GROUP = 1024;
constexpr unsigned MAX_HAIRCOLOR_LENGTH = 10;
constexpr char SEP = ';';
constexpr unsigned BUFFER_SIZE = 1024;

enum class HairColor
{
	brown,
	black,
	blond,
	red,
	white
};

struct Student
{
	double averageSuccess;
	int facultyNumber;
	HairColor color;
	char firstName[MAX_NAME_LENGTH];
	char lastName[MAX_NAME_LENGTH];
};

struct Group
{
	Student students[MAX_STUDENTS_IN_GROUP];
	unsigned studentsCount;
};

bool isValidSuccess(double success)
{
	return success >= 2 && success <= 6;
}

unsigned countDigits(int number)
{
	unsigned count = 0;

	while (number != 0)
	{
		count++;
		number /= 10;
	}

	return count;
}

bool isValidFacultyNumber(double facultyNumber)
{
	return countDigits(facultyNumber) == MAX_FACULTY_NUMBER_LENGTH;
}

bool isValidName(const char* name)
{
	if (!name)
	{
		return false;
	}

	if (std::strlen(name) > 16)
	{
		return false;
	}

	while (*name)
	{
		if ((*name >= 'a' && *name <= 'z') || (*name >= 'A' && *name <= 'Z') || (*name == ' '))
		{
			*name++;
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool isValidStudentsCount(int count)
{
	return count >= 0 && count <= MAX_STUDENTS_IN_GROUP;
}

HairColor getColor(const char* color)
{
	if (std::strcmp(color, "brown") == 0)
	{
		return HairColor::brown;
	}
	else if (std::strcmp(color, "black") == 0)
	{
		return HairColor::black;
	}
	else if (std::strcmp(color, "blond") == 0)
	{
		return HairColor::blond;
	}
	else if (std::strcmp(color, "red") == 0)
	{
		return HairColor::red;
	}
	else if (std::strcmp(color, "white") == 0)
	{
		return HairColor::white;
	}
}

bool initializeStudent(Student& student)
{
	std::cout << "Enter first name: ";
	std::cin.getline(student.firstName, MAX_NAME_LENGTH);
	if (!isValidName(student.firstName))
	{
		return false;
	}

	std::cout << "Enter last name: ";
	std::cin.getline(student.lastName, MAX_NAME_LENGTH);
	if (!isValidName(student.lastName))
	{
		return false;
	}

	std::cout << "Enter faculty number: ";
	std::cin >> student.facultyNumber;
	if (!isValidFacultyNumber(student.facultyNumber))
	{
		return false;
	}

	std::cout << "Enter average success: ";
	std::cin >> student.averageSuccess;
	if (!isValidSuccess(student.averageSuccess))
	{
		return false;
	}

	std::cout << "Enter hair color: ";
	char color[MAX_HAIRCOLOR_LENGTH];
	std::cin >> color;
	student.color = getColor(color);
	std::cout << std::endl;
	std::cin.ignore(1);

	return true;
}

bool createGroup(Group& group)
{
	std::cin >> group.studentsCount;
	std::cin.ignore(1);
	if (!isValidStudentsCount(group.studentsCount))
	{
		return false;
	}

	for (size_t i = 0; i < group.studentsCount; i++)
	{
		std::cout << "Info about student " << i + 1 << std::endl;
		if (!initializeStudent(group.students[i]))
		{
			return false;
		}
	}

	return true;
}

void printColor(const HairColor color)
{
	switch (color)
	{
	case HairColor::brown: std::cout << "brown" << std::endl;
		break;
	case HairColor::black: std::cout << "black" << std::endl;
		break;
	case HairColor::blond: std::cout << "blond" << std::endl;
		break;
	case HairColor::red: std::cout << "red" << std::endl;
		break;
	case HairColor::white: std::cout << "white" << std::endl;
		break;
	default:
		std::cout << "Major is not exist!" << std::endl;
		break;
	}
}

void printStudentInfo(const Student& student)
{
	std::cout << "First name: ";
	std::cout << student.firstName << std::endl;
	std::cout << "Last name: ";
	std::cout << student.lastName << std::endl;
	std::cout << "Faculty number: ";
	std::cout << student.facultyNumber << std::endl;
	std::cout << "Average success: ";
	std::cout << student.averageSuccess << std::endl;
	std::cout << "Hair color: ";
	printColor(student.color);
}

void writeHairColorToFile(const HairColor color, std::ofstream& myFile)
{
	switch (color)
	{
	case HairColor::brown: myFile << "brown";
		break;
	case HairColor::black: myFile << "black";
		break;
	case HairColor::blond: myFile << "blond";
		break;
	case HairColor::red: myFile << "red";
		break;
	case HairColor::white: myFile << "white";
		break;
	default:
		myFile << "Major is not exist!";
		break;
	}
}

void writeGroupToFile(const Group& group, std::ofstream& myFile)
{
	for (size_t i = 0; i < group.studentsCount; i++)
	{
		myFile << group.students[i].firstName << SEP << group.students[i].lastName << SEP
			<< group.students[i].facultyNumber << SEP << group.students[i].averageSuccess << SEP;
		if (i == group.studentsCount - 1)
		{
			writeHairColorToFile(group.students[i].color, myFile);
			break;
		}
		writeHairColorToFile(group.students[i].color, myFile);
		myFile << std::endl;
	}
}

void writeToFile(const Group& group, const char* filename)
{
	if (!filename)
	{
		return;
	}
	std::ofstream myFile(filename);

	if (!myFile.is_open())
	{
		return;
	}

	writeGroupToFile(group, myFile);

	myFile.close();
}

int getNumberFromSymbol(char symbol)
{
	if (symbol >= '0' && symbol <= '9')
	{
		return symbol - '0';
	}

	return symbol;
}

int parseToInt(const char* str)
{
	if (!str)
	{
		return -1;
	}

	int result = 0;
	while (*str)
	{
		result = result * 10 + getNumberFromSymbol(*str);
		*str++;
	}

	return result;
}

double parseToDouble(const char* str)
{
	if (!str)
	{
		return -1;
	}

	int result = 0;
	int count = 0;
	bool flag = false;

	while (*str)
	{
		if (*str != '.')
		{
			result = result * 10 + getNumberFromSymbol(*str);
		}
		else
		{
			flag = true;
			*str++;
			continue;
		}

		if (flag)
		{
			count++;
		}

		*str++;
	}

	return result / (std::pow(10, count));
}

void readStudentInfo(const char* info, Student& student)
{
	std::stringstream ss(info);

	ss.getline(student.firstName, MAX_NAME_LENGTH, SEP);
	ss.getline(student.lastName, MAX_NAME_LENGTH, SEP);

	char buffFacultyNumber[MAX_FACULTY_NUMBER_LENGTH + 1];
	ss.getline(buffFacultyNumber, MAX_FACULTY_NUMBER_LENGTH + 1, SEP);
	student.facultyNumber = parseToInt(buffFacultyNumber);

	char buffAverageSuccess[MAX_AVERAGE_SUCCESS_LENGTH];
	ss.getline(buffAverageSuccess, MAX_AVERAGE_SUCCESS_LENGTH, SEP);
	student.averageSuccess = parseToDouble(buffAverageSuccess);

	char buffHairColor[MAX_HAIRCOLOR_LENGTH];
	ss.getline(buffHairColor, MAX_HAIRCOLOR_LENGTH, SEP);
	student.color = getColor(buffHairColor);
}

void readGroupFromFile(Group& group, std::ifstream& myFile)
{
	char buff[BUFFER_SIZE];
	int currIndex = 0;
	while (!myFile.eof())
	{
		myFile.getline(buff, BUFFER_SIZE);
		readStudentInfo(buff, group.students[currIndex++]);
	}

	group.studentsCount = currIndex;
}

void readFromFile(Group& group, const char* filename)
{
	if (!filename)
	{
		return;
	}
	std::ifstream myFile(filename);

	if (!myFile.is_open())
	{
		return;
	}

	readGroupFromFile(group, myFile);

	myFile.close();
}

int main()
{
	Group group;
	/*if (!createGroup(group))
	{
		return 0;
	}

	writeToFile(group, "studentsGroup.csv");*/
	readFromFile(group, "studentsGroup.csv");

	for (size_t i = 0; i < group.studentsCount; i++)
	{
		printStudentInfo(group.students[i]);
		std::cout << std::endl;
	}
}
