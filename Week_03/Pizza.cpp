#include <iostream>
#include <fstream>

constexpr int MAX_ORDERS = 100;
constexpr int MAX_PHONE_NUMBER_LENGTH = 20;
constexpr int MAX_NAME_LENGTH = 50;
constexpr int MAX_ADDRESS_LENGTH = 100;
constexpr int MAX_PIZZAS_COUNT_IN_ORDER = 20;
constexpr int MAX_TYPE_LENGTH = 10;
constexpr int MAX_SIZE_LENGTH = 2;


enum class Type
{
	margarita,
	calzone,
	burrata,
	pepperoni,
	vegan
};

enum class Size
{
	S,
	M, 
	L
};

struct Pizza
{
	double price;
	Type type;
	Size size;
};

struct Order
{
	double orderPrice;
	int pizzasCount;
	char phoneNumber[MAX_PHONE_NUMBER_LENGTH];
	char name[MAX_NAME_LENGTH];
	char address[MAX_ADDRESS_LENGTH];
	Pizza pizzas[MAX_PIZZAS_COUNT_IN_ORDER];
};

struct Delivery
{
	int ordersCount = 0;
	Order orders[MAX_ORDERS];
};

void writeDeliveryToFile(const Delivery& delivery, std::ofstream& myFile)
{
	myFile.write((const char*)&delivery, sizeof(delivery));
}

void writeToFile(const Delivery& delivery, const char* filename)
{
	std::ofstream myFile(filename, std::ios::binary);

	if (!myFile.is_open())
	{
		return;
	}

	writeDeliveryToFile(delivery, myFile);

	myFile.close();
}

void printType(const Type type)
{
	switch (type)
	{
	case Type::margarita: std::cout << "margarita" << std::endl;
		break;
	case Type::calzone: std::cout << "calzone" << std::endl;
		break;
	case Type::burrata: std::cout << "burrata" << std::endl;
		break;
	case Type::pepperoni: std::cout << "pepperoni" << std::endl;
		break;
	case Type::vegan: std::cout << "vegan" << std::endl;
		break;
	default:
		break;
	}
}

void printSize(const Size size)
{
	switch (size)
	{
	case Size::S: std::cout << "S" << std::endl;
		break;
	case Size::M: std::cout << "M" << std::endl;
		break;
	case Size::L: std::cout << "L" << std::endl;
		break;
	default:
		break;
	}
}

void printInfoAboutPizza(const Pizza& pizza)
{
	printType(pizza.type);
	printSize(pizza.size);
	std::cout << pizza.price << std::endl;
}

void printInfoAboutOrder(const Order& order)
{
	std::cout << order.name << std::endl;
	std::cout << order.phoneNumber << std::endl;
	std::cout << order.address << std::endl;
	std::cout << order.orderPrice << std::endl;
	std::cout << "Pizzas that are " << order.pizzasCount << ": " << std::endl;

	for (size_t i = 0; i < order.pizzasCount; i++)
	{
		printInfoAboutPizza(order.pizzas[i]);
	}
}

void printInfoAboutDelivery(const Delivery& delivery)
{
	for (size_t i = 0; i < delivery.ordersCount; i++)
	{
		printInfoAboutOrder(delivery.orders[i]);
	}
}

void readDeliveryFromFile(Delivery& delivery, std::ifstream& myFile)
{
	myFile.read((char*)&delivery, sizeof(delivery));
}

void readFromFile(Delivery& delivery, const char* filename)
{
	std::ifstream myFile(filename, std::ios::binary);

	if (!myFile.is_open())
	{
		return;
	}

	readDeliveryFromFile(delivery, myFile);

	myFile.close();
}

int main()
{
	Delivery delivery;
	readFromFile(delivery, "pizza.dat");

	delivery.ordersCount = 2;

	delivery.orders[0] = {
		38,
		3,
		"087762534",
		"Kosatdin",
		"abc",
		{
			{12, Type::margarita, Size::L}, 
			{15, Type::burrata, Size::M},
			{11, Type::pepperoni, Size::S}
		}
	};

	delivery.orders[1] = {
		32,
		2,
		"08232334",
		"Nikola",
		"cba",
		{
			{10, Type::calzone, Size::S},
			{13, Type::burrata, Size::M},
			{9, Type::vegan, Size::L}
		}
	};

	printInfoAboutDelivery(delivery);

	//writeToFile(delivery, "pizza.dat");
}
