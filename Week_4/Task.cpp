#include <iostream>
#include <fstream>
#pragma warning(disable: 4996)

constexpr int MAX_DESCRIPTION_LENGTH = 50;
constexpr int MAX_PASSWORD_LENGTH = 20;
constexpr int MAX_TASK_COUNT = 10;

class Task
{
private:
	char description[MAX_DESCRIPTION_LENGTH];
	char answer;
	unsigned points;
	char password[MAX_PASSWORD_LENGTH];

public:

	Task(const char* description, char answer, int points, const char* password)
	{
		setDescription(description);
		setAnswer(answer);
		setPoints(points);
		setPassword(password);
	}

	Task()
	{

	}


	void setDescription(const char* description)
	{
		if (!description)
		{
			return;
		}

		if (std::strlen(description) < MAX_DESCRIPTION_LENGTH)
		{
			std::strcpy(this->description, description);
		}
	}

	void setAnswer(char answer)
	{
		if (answer == 'a' || answer == 'b' || answer == 'c' || answer == 'd')
		{
			this->answer = answer;
		}
	}

	void setPoints(unsigned points)
	{
		this->points = points;
	}

	void setPassword(const char* password)
	{
		if (!password)
		{
			return;
		}

		if (std::strlen(password) < MAX_PASSWORD_LENGTH)
		{
			std::strcpy(this->password, password);
		}
	}

	const char* getDescription() const
	{
		return this->description;
	}

	unsigned getPoints() const
	{
		return this->points;
	}



	void editDescription(const char* password, const char* newDescription)
	{
		if (!newDescription || !password)
		{
			return;
		}

		if (!std::strcmp(password, this->password))
		{
			setDescription(newDescription);
		}
	}

	void editAnswer(const char* password, char newAnswer)
	{
		if (!newAnswer || !password)
		{
			return;
		}
		if (!std::strcmp(password, this->password))
		{
			setAnswer(newAnswer);
		}
	}

	void editPoints(const char* password, int newPoints)
	{
		if (!password)
		{
			return;
		}
		if (!std::strcmp(password, this->password))
		{
			setPoints(newPoints);
		}
	}

	bool isAnswerCorrect(char answer)
	{
		return this->answer == answer;
	}
};

class Exam
{
private:
	Task tasks[MAX_TASK_COUNT];
	unsigned taskCount = 0;

	void printDescriptions()
	{
		for (size_t i = 0; i < this->taskCount; i++)
		{
			std::cout << this->tasks[i].getDescription() << std::endl;
		}
	}
public:

	void writeExamToFile(std::ofstream& myFile)
	{
		myFile.write((const char*)this, sizeof(Exam));
	}

	void writeToFile(const char* filename)
	{
		std::ofstream myFile(filename, std::ios::binary);

		if (!myFile.is_open())
		{
			return;
		}

		writeExamToFile(myFile);

		myFile.close();
	}

	unsigned getMaxPoints() const
	{
		unsigned maxPoints = 0;
		for (size_t i = 0; i < this->taskCount; i++)
		{
			maxPoints += this->tasks[i].getPoints();
		}

		return maxPoints;
	}

	void addTask(const char* description, char answer, unsigned points, const char* password)
	{
		if (!description && !password)
		{
			return;
		}

		Task newTask = Task(description, answer, points, password);

		this->tasks[this->taskCount] = newTask;
		this->taskCount++;
	}

	unsigned simulatingExam()
	{
		unsigned scoredPoints = 0;
		printDescriptions();
		std::cout << "Enter your answers:" << std::endl;
		for (size_t i = 1; i <= this->taskCount; i++)
		{
			char answer = ' ';
			std::cout << "The answer of " << i << " question is: ";
			std::cin >> answer;
			std::cout << std::endl;

			if (this->tasks[i -1].isAnswerCorrect(answer))
			{
				scoredPoints += this->tasks[i - 1].getPoints();
			}
		}

		return scoredPoints;
	}
};

void readExamFromFile(Exam& exam, std::ifstream& myFile)
{
	myFile.read((char*)&exam, sizeof(Exam));
}

void readFromFile(Exam& exam, const char* filename)
{
	std::ifstream myFile(filename, std::ios::binary);

	if (!myFile.is_open())
	{
		return;
	}

	readExamFromFile(exam, myFile);

	myFile.close();
}

int main()
{
	Exam exam;
	exam.addTask("Is Chefo stupid?", 'y', 9, "sasX");
	exam.addTask("Is Petyo stupid?", 'y', 10, "sasX");
	exam.addTask("Is Koko stupid?", 'n', 16, "sasX");

	exam.writeToFile("exam.dat");
	readFromFile(exam, "exam.dat");

	unsigned scoredPoints = 0;
	scoredPoints = exam.simulatingExam();
	std::cout << "You scored: " << scoredPoints << " from " << exam.getMaxPoints();
}
