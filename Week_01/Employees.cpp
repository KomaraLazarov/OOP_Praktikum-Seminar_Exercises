#include <iostream>

const int MAX_NAME_LENGTH = 100;
const int MAX_POSITION_LENGTH = 50;
const int MAX_EMPLOYEES_IN_COMPANY = 50;
constexpr int POSITIONS_COUNT = 4;

enum Position
{
	SoftwareEngineer,
	SeniorSoftwareEngineer,
	EngineerManager,
	LeadSoftwareEngineer,
	NotExist
};

struct Employee
{
	double salary;
	int rating;
	char name[MAX_NAME_LENGTH];
	Position position;
};

struct Company
{
	Employee employees[MAX_EMPLOYEES_IN_COMPANY];
	double averageSalary;
	unsigned employeesCount;
};

bool isValidRating(double rating)
{
	return rating >= 0 || rating <= 10;
}

bool isValidSalary(double salary)
{
	return salary >= 0;
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
	
bool isValidEmployeesCount(int count)
{
	return count >= 0 && count <= MAX_EMPLOYEES_IN_COMPANY;
}

Position getPosition(const char* position)
{
	if (!position)
	{
		return Position::NotExist;
	}

	if (std::strcmp(position, "Software Engineer") == 0)
	{
		return Position::SoftwareEngineer;
	}
	else if (std::strcmp(position, "Senior Software Engineer") == 0)
	{
		return Position::SeniorSoftwareEngineer;
	}
	else if (std::strcmp(position, "Engineer Manager") == 0)
	{
		return Position::EngineerManager;
	}
	else if (std::strcmp(position, "Lead Software Engineer") == 0)
	{
		return Position::LeadSoftwareEngineer;
	}
	else
	{
		return Position::NotExist;
	}
}

bool initializeEmployee(Employee& em)
{
	std::cout << "Enter name: ";
	std::cin.getline(em.name, MAX_NAME_LENGTH);
	if (!isValidName(em.name))
	{
		return false;
	}

	std::cout << "Enter position: ";
	char position[MAX_POSITION_LENGTH];
	std::cin.getline(position, MAX_POSITION_LENGTH);
	em.position = getPosition(position);

	std::cout << "Enter salary: ";
	std::cin >> em.salary;
	if (!isValidSalary(em.salary))
	{
		return false;
	}

	std::cout << "Enter rating: ";
	std::cin >> em.rating;
	if (!isValidRating(em.rating))
	{
		return false;
	}
	std::cin.ignore(1);
	std::cout << std::endl;

	return true;
}

void printPosition(const Position position)
{
	switch (position)
	{
	case Position::SoftwareEngineer: std::cout << "Software Engineer" << std::endl;
		break;
	case Position::SeniorSoftwareEngineer: std::cout << "Senior Software Engineer" << std::endl;
		break;
	case Position::EngineerManager: std::cout << "Engineer Manager" << std::endl;
		break;
	case Position::LeadSoftwareEngineer: std::cout << "Lead Software Engineer" << std::endl;
		break;
	default:
		std::cout << "Position is not exist!" << std::endl;
		break;
	}
}

void printEmployeeInfo(const Employee& employee)
{
	std::cout << "Position: ";
	printPosition(employee.position);
	std::cout << "Name: ";
	std::cout << employee.name << std::endl;
	std::cout << "Salary: ";
	std::cout << employee.salary << std::endl;
	std::cout << "Rating: ";
	std::cout << employee.rating << std::endl;
}

bool createCompany(Company& company)
{
	double employeesSalaries = 0;
	std::cin >> company.employeesCount;
	if (!isValidEmployeesCount(company.employeesCount))
	{
		return false;
	}
	std::cin.ignore(1);

	for (size_t i = 0; i < company.employeesCount; i++)
	{
		std::cout << "Info about employee " << i + 1 << std::endl;
		if (!initializeEmployee(company.employees[i]))
		{
			return false;
		}
		employeesSalaries += company.employees[i].salary;
	}

	company.averageSalary = employeesSalaries / company.employeesCount;

	return true;
}

void sortEmployeesByName(Employee* employees, unsigned size)
{
	if (!employees)
	{
		return;
	}

	for (size_t i = 0; i < size - 1; i++)
	{
		unsigned min = i;
		for (size_t j = i + 1; j < size; j++)
		{
			if (std::strcmp(employees[j].name, employees[min].name) < 0)
			{
				min = j;
			}
		}

		if (min != i)
		{
			std::swap(employees[min], employees[i]);
		}
	}
}

void copyArrays(const Employee* employees, Employee* employeesCopy, unsigned size)
{
	if (!employees || !employeesCopy	)
	{
		return;
	}

	for (size_t i = 0; i < size; i++)
	{
		employeesCopy[i] = employees[i];
	}
}

void showEmployeesNamesReceiveAverageSalaraySorted(const Company& company)
{
	Employee* employeesCopy = new Employee[company.employeesCount];
	copyArrays(company.employees, employeesCopy, company.employeesCount);
	sortEmployeesByName(employeesCopy, company.employeesCount);

	for (int i = 0; i < company.employeesCount; i++)
	{
		if (employeesCopy[i].salary > company.averageSalary)
		{
			std::cout << employeesCopy[i].name << std::endl;
		}
	}

	delete[] employeesCopy;
}

void fillWithDefaultValues(int* arr, unsigned size, int defaultValue)
{
	if (!arr)
	{
		return;
	}

	for (size_t i = 0; i < size; i++)
	{
		arr[i] = defaultValue;
	}
}

Position getPositionByIndex(unsigned index)
{
	switch (index)
	{
	case 0:
		return Position::SoftwareEngineer;
		break;
	case 1:
		return Position::SeniorSoftwareEngineer;
		break;
	case 2:
		return Position::EngineerManager;
		break;
	case 3:
		return Position::LeadSoftwareEngineer;
		break;

	default:
		return Position::NotExist;
		break;
	}
}

void printMinRatingForPositions(const Company& company)
{
	int minRatings[POSITIONS_COUNT];

	fillWithDefaultValues(minRatings, POSITIONS_COUNT, INT_MAX);
	for (size_t i = 0; i < company.employeesCount; i++)
	{
		int currentIndex = company.employees[i].position;
		if (currentIndex != POSITIONS_COUNT && company.employees[i].rating < minRatings[currentIndex])
		{
			minRatings[currentIndex] = company.employees[i].rating;
		}
	}

	for (size_t i = 0; i < POSITIONS_COUNT; i++)
	{
		if (minRatings[i] != INT_MAX)
		{
			Position position = getPositionByIndex(i);
			printPosition(position);
			std::cout << "Min rating:" << minRatings[i] << std::endl;
		}
	}
}

void printMaxRatingForPositions(const Company& company)
{
	int maxRatings[POSITIONS_COUNT];

	fillWithDefaultValues(maxRatings, POSITIONS_COUNT, INT_MIN);
	for (size_t i = 0; i < company.employeesCount; i++)
	{
		int currentIndex = company.employees[i].position;
		if (currentIndex != POSITIONS_COUNT && company.employees[i].rating > maxRatings[currentIndex])
		{
			maxRatings[currentIndex] = company.employees[i].rating;
		}
	}

	for (size_t i = 0; i < POSITIONS_COUNT; i++)
	{
		if (maxRatings[i] != INT_MIN)
		{
			Position position = getPositionByIndex(i);
			printPosition(position);
			std::cout << "Max rating:" << maxRatings[i] << std::endl;
		}
	}
}

void printMaxAndMinRatingsForAllPositions(const Company& company)
{
	printMinRatingForPositions(company);
	std::cout << std::endl;
	printMaxRatingForPositions(company);
}

int main()
{
	Company company;
	if (!createCompany(company))
	{
		return 0;
	}
	//printEmployeeInfo(em);
	//showEmployeesNamesReceiveAverageSalaraySorted(company);
	printMaxAndMinRatingsForAllPositions(company);
}