/*Пример с std::unordered_map (хэш-таблица, быстрее, порядок не гарантирован)*/

#include <iostream>
#include <unordered_map>  // вместо <map>
#include <string>

int main() {
    std::unordered_map<std::string, int> students;  // объявление
    
    students["Alice"] = 20;
    students["Bob"] = 22;
    students["Charlie"] = 19;
    
    std::cout << "Bob's age: " << students["Bob"] << std::endl;
    
    // Проверка наличия ключа
    if (students.find("David") == students.end()) {
        std::cout << "David not found\n";
    }
    
    // Перебор (порядок НЕ гарантирован - будет случайным!)
    for (const auto& [name, age] : students) {
        std::cout << name << " → " << age << "\n";
    }
    
    return 0;
}