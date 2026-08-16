/*
4. Полиморфизм

Смысл:  Способность объектов с одинаковым интерфейсом вести себя по-разному.
        Чаще всего реализуется через виртуальные функции и указатели на базовый класс.

Зачем:  Единообразная работа с разными типами объектов (например, массив разных фигур, у каждой свой расчет площади).
*/

#include <iostream>

// Базовый класс с виртуальным методом
class Shape {
public:
    virtual double area() { // virtual = может быть переопределен
        return 0;
    }
    virtual ~Shape() {} // Виртуальный деструктор (для корректного удаления)
};

class Circle : public Shape {
private:
    double r;
public:
    Circle(double radius) : r(radius) {}
    double area() override { // override = переопределяем родительский метод
        return 3.14 * r * r;
    }
};

class Square : public Shape {
private:
    double side;
public:
    Square(double s) : side(s) {}
    double area() override {
        return side * side;
    }
};

// Функция, работающая с любыми наследниками Shape
void printArea(Shape* s) {
    // Вызовется нужная версия area (Circle::area или Square::area)
    std::cout << "Площадь: " << s->area() << std::endl;
}

int main() {
    Circle c(5);
    Square sq(4);

    printArea(&c); // Площадь: 78.5
    printArea(&sq); // Площадь: 16
    return 0;
}