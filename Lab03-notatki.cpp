#include <iostream>
#include <string>

enum Genders { MAN, WOMAN };

std::string GenderToString(const Genders gender)
{
	switch (gender)
	{
	case MAN: return "mezczyzna";
	case WOMAN: return "kobieta";
	default: return "";
	}
}

class Person {
	std::string firstName;
	std::string lastName;
	Genders gender;

public:
	Person(const std::string& firstName, const std::string& lastName, const Genders gender) :
		firstName(firstName),
		lastName(lastName),
		gender(gender)
	{ }

	//getter
	std::string FirstName() const noexcept
	{
		return firstName; //mozna zwrocic referencje albo kopie
	}

	//setter
	void FirstName(const std::string& name)
	{
		firstName = name;
	}

	std::string ToString() const noexcept
	{
		return firstName + " " + lastName + "[" + GenderToString(gender) +  "]";
	}


};

std::ostream& operator << (std::ostream& stream, const Person& person)
{
	stream << person.ToString();
	return stream;
}

class Employee : public Person
{
	double salary;
public:
	Employee(const std::string& firstName, const std::string& lastName, const Genders gender, const double salary):
		Person(firstName, lastName, gender),
		salary(salary)
	{ }

	Employee(const Person &person, const double salary) :
		Person(person),
		salary(salary)
	{ }

	std::string ToString() const noexcept
	{
		return Person::ToString() + " < " + std::to_string(salary) + " >";
	}
};

class Student : public Person
{
	int id;
public:
	Student(const std::string& firstName, const std::string& lastName, const Genders gender, const int id) :
		Person(firstName, lastName, gender),
		id(id)
	{ }

	Student(const Person& person, const int id) :
		Person(person),
		id(id)
	{ }

	std::string ToString() const noexcept
	{
		return Person::ToString() + " { " + std::to_string(id) + " }";
	}
};

class Client : public Person
{
	std::string registrationDate;
public:
	Client(const std::string& firstName, const std::string& lastName, const Genders gender, const std::string registrationDate) :
		Person(firstName, lastName, gender),
		registrationDate(registrationDate)
	{ }

	Client(const Person& person, const std::string &registrationDate) :
		Person(person),
		registrationDate(registrationDate)
	{ }

	std::string ToString() const noexcept
	{
		return Person::ToString() + " { " +  registrationDate + " }";
	}
};

class ClientVip : public Client
{
	double discount;
public:
	ClientVip(const std::string& firstName, const std::string& lastName, const Genders gender, const std::string registrationDate, const double discount) :
		Client(firstName, lastName, gender, registrationDate),
		discount(discount)
	{ }

	ClientVip(const Client& person, const double discount) :
		Client(person),
		discount(discount)
	{ }

	std::string ToString() const noexcept
	{
		return Client::ToString() + " $ " + std::to_string(discount) + " $";
	}
};



int main()
{
	Person person("Jan", "Kowalski", MAN);
	std::cout << person.ToString() << std::endl;
	std::cout << person << std::endl;

	Employee employee("Jan", "Kowalski", MAN, 0.0);
	std::cout << employee.ToString() << std::endl;
	Employee employee1("Jan", "Kowalski", MAN, 3.0);
	std::cout << employee1.ToString() << std::endl;

	Student student("Jan", "Kowalski", MAN, 2);
	std::cout << student.ToString() << std::endl;
	Student student1("Jan", "Kowalski", MAN, 1);
	std::cout << student1.ToString() << std::endl;

	Client client("Jan", "Kowalski", MAN, "4.04.1999");
	std::cout << client.ToString() << std::endl;
	Client client1("Jan", "Kowalski", MAN, "2.02.2000");
	std::cout << client1.ToString() << std::endl;

	ClientVip clientVip("Jan", "Kowalski", MAN, "4.04.1999", 45.0);
	std::cout << clientVip.ToString() << std::endl;
	ClientVip clientVip1("Jan", "Kowalski", MAN, "2.02.2000", 25.0);
	std::cout << clientVip1.ToString() << std::endl;


}
