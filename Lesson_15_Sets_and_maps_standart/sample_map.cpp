/*
Пример с std::map (отсортированный по ключам)
*/


#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> students; // имя → возраст

    // Добавление
    students["Alice"] = 20;
    students["Bob"] = 22;
    students["Charlie"] = 19;

    // Доступ
    std::cout << "Bob's age: " << students["Bob"] << "\n"; // 22

    // Проверка наличия
    if (students.find("David") == students.end()) {
        std::cout << "David not found\n";
    }

    // Перебор (всегда по возрастанию ключей)
    for (const auto& [name, age] : students) {
        std::cout << name << " → " << age << "\n";
    }

    return 0;
}
