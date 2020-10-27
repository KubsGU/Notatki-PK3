//laborki_4_notatka.cpp
//klasy wirtualne

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

class Shape {
public:
    virtual double Area() const = 0;
};

class Circle : public Shape {
    double r;
public:
    Circle(const double r) : r(r) {
    }

    virtual double Area() const { //wystarczy napisac virtual w metodzie klasy bazowej, 
    //ale piszemy wszędzie gdzie jest odziedziczona metoda, żeby było bardziej czytelnie dla kogoś kto analizuje kod
        return M_PI * r * r;
    }
};

class Rectangle : public Shape {
    double a;
    double b;
public:
    Rectangle(const double a, const double b) : a(a), b(b) {
    }

    virtual double Area() const {
        return a * b;
    }
};

class Triangle : public Shape {
    double a;
    double b;
    double c;
public:
    Triangle(const double a, const double b, const double c) : a(a), b(b), c(c) {
    }

    virtual double Area() const {
        double p = (a + b + c) / 2.0;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
};
class User {
    std::string firstName;
    std::string lastName;
public:
    User(const std::string& firstName, const std::string& lastName) :
        firstName(firstName),
        lastName(lastName) {
    }

    std::string FirstName() const noexcept {
        return firstName;
    }

    void FirstName(const std::string& name) {
        firstName = name;
    }

    std::string LastName() const noexcept {
        return lastName;
    }

    void LastName(const std::string& lastname) {
        firstName = lastname;
    }

    std::string ToString() const noexcept {
        return firstName + " " + lastName;
    }

    bool operator ==(const User& user) const {
        return firstName == user.firstName && lastName == user.lastName;
    }
};

class DataSource {
public:
    virtual void AddUser(const User& user) = 0;
    virtual void DeleteUser(const User& user) = 0;
};

class FileDataSource : public DataSource {
    std::vector<User> users;
    std::string fileName;

    void saveData() const {
        std::ofstream stream(fileName);
        for (auto user : users) {
            stream << user.FirstName() << ";" << user.LastName() << std::endl;
        }

        stream.close();
    }

public:
    FileDataSource(const std::string& fileName) : fileName(fileName) {
        std::ifstream stream(fileName);
        char buffer[1024];
        while (stream.getline(buffer, sizeof(buffer))) {
            std::stringstream ss(buffer);
            ss.getline(buffer, sizeof(buffer), ';');
            std::string s(buffer);
            ss.getline(buffer, sizeof(buffer), ';');
            users.push_back(User(s, buffer));
        }

        stream.close();
    }

    virtual void AddUser(const User& user) {
        users.push_back(user);
        saveData();
    }

    virtual void DeleteUser(const User& user) {
        auto i = std::find(users.begin(), users.end(), user);
        if (i != users.end()) {
            users.erase(i);
            saveData();
        }
    }
    virtual std::vector<User> Select() {
        return users;
    }
};

class SqliteDataSource : public DataSource {

public:
    virtual void AddUser(const User& user) {
        throw std::exception();
    }

    virtual void DeleteUser(const User& user) {
        throw std::exception();
    }
};

//int main() {
//    std::vector<Shape*> shapes;
//    shapes.push_back(new Circle(1.0));
//    shapes.push_back(new Rectangle(1.0, 2.0));
//    shapes.push_back(new Triangle(3.0, 4.0, 5.0));
//
//    for (auto shape : shapes) {
//        std::cout << shape->Area() << std::endl;
//    }
//
//    for (auto shape : shapes) {
//        delete shape;
//    }
//    shapes.clear();
//
//    
//    Circle circle(1.0);
//    std::cout << circle.Area() << std::endl;
//    Rectangle rectangle(1.0, 2.0);
//    std::cout << rectangle.Area() << std::endl;
//    Triangle triangle(3.0, 4.0, 5.0);
//    std::cout << triangle.Area() << std::endl;
//    
//}