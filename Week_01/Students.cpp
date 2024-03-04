#include <iostream>

const int MAX_STUDENTS_IN_GROUP = 40;
const int MAX_FACULTY_NUMBER_LENGTH = 50;
const int MAX_NAME_LENGTH = 30;
const int MAX_MAJOR_LENGTH = 5;

enum class Major
{
	SI,
	IS,
	KN,
	PM,
	M,
	INF,
	NOTEXIST
};

struct Student
{
	double grade;
	char facultyNumber[MAX_FACULTY_NUMBER_LENGTH];
	char name[MAX_NAME_LENGTH];
	Major major;
};

struct Group
{
	Student students[MAX_STUDENTS_IN_GROUP];
	double averageSuccess;
    unsigned studentsCount;
};

bool isValidGrade(double rating)
{
	return rating >= 2 || rating <= 6;
} 

bool isValidName(const char* name)
{
	if (!name)
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

Major getMajor(const char* major)
{
	if (std::strcmp(major, "SI") == 0)
	{
		return Major::SI;
	}
	else if (std::strcmp(major, "IS") == 0)
	{
		return Major::IS;
	}
	else if (std::strcmp(major, "KN") == 0)
	{
		return Major::KN;
	}
	else if (std::strcmp(major, "PM") == 0)
	{
		return Major::PM;
	}
	else if (std::strcmp(major, "M") == 0)
	{
		return Major::M;
	}
	else if (std::strcmp(major, "INF") == 0)
	{
		return Major::INF;
	}
	else
	{
		return Major::NOTEXIST;
	}
}

bool initializeStudent(Student& student)
{
	std::cout << "Enter name: ";
	std::cin.getline(student.name, MAX_NAME_LENGTH);
	if (!isValidName(student.name))
	{
		return false;
	}

	std::cout << "Enter faculty number: ";
	std::cin >> student.facultyNumber;

	std::cout << "Enter grade: ";
	std::cin >> student.grade;
	if (!isValidGrade(student.grade))
	{
		return false;
	}

	std::cout << "Enter major: ";
	char major[MAX_MAJOR_LENGTH];
	std::cin >> major;
	student.major = getMajor(major);
	std::cout << std::endl;
	std::cin.ignore(1);

	return true;
}

bool createGroup(Group& group)
{
	double studentGrades = 0;
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
		studentGrades += group.students[i].grade;
	}

	group.averageSuccess = studentGrades / group.studentsCount;

	return true;
}

unsigned findStudentsReceiveScholarshipCount(const Group& group, double minSuccess)
{
	unsigned passedStudentsCount = 0;
	for (size_t i = 0; i < group.studentsCount; i++)
	{
		if (group.students[i].grade >= minSuccess)
		{
			passedStudentsCount++;
		}
	}

	return passedStudentsCount;
}

void copyArrays(const Student* students, Student* studentsCopy, unsigned size)
{
	if (!students || !studentsCopy)
	{
		return;
	}

	for (size_t i = 0; i < size; i++)
	{
		studentsCopy[i] = students[i];
	}
}

void sortStudentsByGrade(Student* students, unsigned size)
{
	for (size_t i = 0; i < size - 1; i++)
	{
		unsigned min = i;
		for (size_t j = i + 1; j < size; j++)
		{
			if (students[j].grade < students[min].grade)
			{
				min = j;
			}
		}

		if (min != i)
		{
			std::swap(students[min], students[i]);
		}
	}
}

void sortStudentsByFacultyNumber(Student* students, unsigned size)
{
	for (size_t i = 0; i < size - 1; i++)
	{
		unsigned min = i;
		for (size_t j = i + 1; j < size; j++)
		{
			if (std::strcmp(students[j].facultyNumber, students[min].facultyNumber) < 0)
			{
				min = j;
			}
		}

		if (min != i)
		{
			std::swap(students[min], students[i]);
		}
	}
}

void printMajor(const Major major)
{
	switch (major)
	{
	case Major::SI: std::cout << "SI" << std::endl;
		break;
	case Major::IS: std::cout << "IS" << std::endl;
		break;
	case Major::KN: std::cout << "KN" << std::endl;
		break;
	case Major::PM: std::cout << "PM" << std::endl;
		break;
	case Major::M: std::cout << "M" << std::endl;
		break;
	case Major::INF: std::cout << "INF" << std::endl;
		break;

	default:
		std::cout << "Major is not exist!" << std::endl;
		break;
	}
}

void printStudentInfo(const Student& student)
{
	std::cout << "Major: ";
	printMajor(student.major);
	std::cout << "Faculty number: ";
	std::cout << student.facultyNumber << std::endl;
	std::cout << "Name: ";
	std::cout << student.name << std::endl;
	std::cout << "Grade: ";
	std::cout << student.grade << std::endl;
}

void showStudentsReceiveScholarshipSorted(const Group& group, double minSuccess)
{
	Student* studentsCopy = new Student[group.studentsCount];
	copyArrays(group.students, studentsCopy, group.studentsCount);
	sortStudentsByGrade(studentsCopy, group.studentsCount);

	for (int i = group.studentsCount - 1; i >= 0; i--)
	{
		if (group.students[i].grade > minSuccess || abs(group.students[i].grade - minSuccess) < 0.000001)
		{
			printStudentInfo(group.students[i]);
		}
	}

	delete[] studentsCopy;
}

bool findStudentInGroup(const Group& group, const char* facultyNumber)
{
	Student* studentsCopy = new Student[group.studentsCount];
	copyArrays(group.students, studentsCopy, group.studentsCount);
	sortStudentsByFacultyNumber(studentsCopy, group.studentsCount);

	unsigned left = 0;
	unsigned right = group.studentsCount - 1;

	while (left <= right)
	{
		unsigned mid = left + (right - left) / 2;

		if (std::strcmp(group.students[mid].facultyNumber, facultyNumber) == 0)
		{
			delete[] studentsCopy;
			return true;
		}
		else if (std::strcmp(group.students[mid].facultyNumber, facultyNumber) < 0)
		{
			left = mid + 1;
		}
		else if (std::strcmp(group.students[mid].facultyNumber, facultyNumber) > 0)
		{
			right = mid - 1;
		}
	}

	delete[] studentsCopy;
	return false;
}

int main()
{
	Group group;
	if (!createGroup(group))
	{
		return 0;
	}
	std::cout << findStudentsReceiveScholarshipCount(group, 4.25) << std::endl;
	showStudentsReceiveScholarshipSorted(group, 4.25);
	std::cout << findStudentInGroup(group, "5MI");
}