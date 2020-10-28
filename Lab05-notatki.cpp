#include <iostream>
#include <string>

class IView
{
public:
	virtual void View() const = 0;
};

class IEnable
{
public:
	virtual void Enable() = 0;
};

class Animal : public IView, public IEnable
{
protected:
	std::string name;
	double weight;
	Animal(const std::string& name, const double weight) : name(name), weight(weight) {
		std::cout << "Animal()" << std::endl;
	}
public: 

	void View() const 
	{
		std::cout << "Nazwa: " << name << std::endl;
		std::cout << "Waga: " << weight << std::endl;
	}
};

class Horse : public virtual Animal
{
protected:
	double speed;
public:
	Horse(const std::string& name, const double weight, const double speed) : Animal(name, weight), speed(speed) {
		std::cout << "Horse()" << std::endl;

	}

	void View() const
	{
		Animal::View();
		std::cout << "Predkosc galopu: " << speed << std::endl;
	}
};

class Bird : public virtual Animal
{
protected:
	double speed;
public:
	Bird(const std::string& name, const double weight, const double speed) : Animal(name, weight), speed(speed) {
		std::cout << "Bird()" << std::endl;

	}

	void View() const
	{
		Animal::View();
		std::cout << "Predkosc lotu: " << speed << std::endl;
	}
};

class Pegasus : public Horse, public Bird
{
public:
	Pegasus(const std::string& name, const double weight, const double speed, const double flightspeed) :
		Animal(name,weight),
		Horse("", 0, speed),
		Bird("", 2, flightspeed) {}

	void Enable() {};

	void View() const
	{
		Horse::View();
		std::cout << "Predkosc lotu " << Bird::speed << std::endl;
	}
};

//int main()
//{
//	//Horse horse("kon", 1500,100);
//	//horse.View();
//
//	//Bird bird("ptak", 2.0, 200);
//	//bird.View();
//
//	Pegasus pegasus("pegaz", 230, 80, 210);
//	pegasus.View();
//
//	return 0;
//}

/*
wiele interfejsow jedna klasa => spoko
wiele klasy => problem z dublowaniem pól
*/