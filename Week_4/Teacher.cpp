//#include <iostream>
//#pragma warning (disable:4996)
//
//constexpr int MAX_NAME_LENGTH = 50;
//
//enum class Subject
//{
//	Math,
//	English,
//	IT,
//	undefined
//};
//
//class Teacher
//{
//	char name[MAX_NAME_LENGTH];
//	int age = 0;
//	Subject subject = Subject::undefined;
//	unsigned salary = 0;
//
//public:
//	Teacher(const char* name, int age, Subject subject, double salary)
//	{
//		setName(name);
//		setAge(age);
//		setSubject(subject);
//		setSalary(salary);
//	}
//
//	Teacher()
//	{
//
//	}
//
//	void setName(const char* name)
//	{
//		if (!name)
//		{
//			return;
//		}
//
//		if (std::strlen(name) < MAX_NAME_LENGTH)
//		{
//			std::strcpy(this->name, name);
//		}
//	}
//
//	void setAge(int age)
//	{
//		if (age >= 18 && age <= 70)
//		{
//			this->age = age;
//		}
//	}
//	
//	void setSubject(Subject subject)
//	{
//		this->subject = subject;
//	}
//
//	void setSalary(double salary)
//	{
//		if (salary > 500)
//		{
//			this->salary = salary;
//		}
//	}
//
//	const char* getName() const
//	{
//		return this->name;
//	}
//
//	int getAge() const
//	{
//		return this->age;
//	}
//
//	Subject getSubject() const
//	{
//		return this->subject;
//	}
//
//	double getSalary() const
//	{
//		return this->salary;
//	}
//};
//
//int main()
//{
//
//}