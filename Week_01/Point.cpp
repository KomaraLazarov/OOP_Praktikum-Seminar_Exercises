#include <iostream>

const int FIRST_QUADRANT = 1;
const int SECOND_QUADRANT = 2;
const int THIRD_QUADRANT = 3;
const int FORTH_QUADRANT = 4;
const int NEUTRAL_QUADRANT = 4;

struct Point
{
	double x;
	double y;
};

void readPoint(Point& point)
{
	std::cout << "Enter x: ";
	std::cin >> point.x;

	std::cout << "Enter y: ";
	std::cin >> point.y;
}

void printPoint(const Point& point)
{
	std::cout << "(" << point.x << ", " << point.y << ")" << std::endl;
}

void distanceBetweenCenterAndPoint(const Point& point, double& distance)
{
	distance = sqrt(pow(point.x, 2) + pow(point.y, 2));
}

void distanceBetweenTwoPoints(const Point& point1, const Point& point2, double& distance)
{
	distance = sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}

int quadrant(const Point& point)
{
	if (point.x > 0 && point.y > 0)
	{
		return FIRST_QUADRANT;
	}
	else if (point.x < 0 && point.y > 0)
	{
		return SECOND_QUADRANT;
	}
	else if (point.x < 0 && point.y < 0)
	{
		return THIRD_QUADRANT;
	}
	else if (point.x > 0 && point.y < 0)
	{
		return FORTH_QUADRANT;
	}
	else if (point.x == 0 || point.y == 0)
	{
		return NEUTRAL_QUADRANT;
	}
}

bool isPointInOnCircle(const Point& point, double radius)
{
	double distance = sqrt(pow(point.x, 2) + pow(point.y, 2));

	return distance < radius || abs(distance - radius) < 0.000001;
}

int main()
{
	Point point1;
	Point point2;
	readPoint(point1);
	readPoint(point2);
	double distance = 0;
	//printPoint(point);
	//distanceBetweenCenterAndPoint(point1, distance);
	//std::cout << distance << std::endl;
	//distanceBetweenTwoPoints(point1, point2, distance);
	//std::cout << quadrant(point1);
	//std::cout << isPointInOnCircle(point1, 5) << std::endl;

}