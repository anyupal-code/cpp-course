/*
2. Инкапсуляция
Смысл:      Сокрытие внутреннего состояния объекта от внешнего мира.
            Доступ к данным осуществляется только через публичные методы (геттеры/сеттеры).
Зачем:      Защита данных от некорректного изменения и скрытие сложности реализации.
*/
#include <iostream>

class BankAccount {
private: // Данные скрыты (приватны)
    double balance;

public:
    // Конструктор (устанавливает начальное состояние)
    BankAccount(double initial) {
        if (initial >= 0) balance = initial;
        else balance = 0;
    }

    // Публичный интерфейс для доступа
    void deposit(double amount) {
        if (amount > 0) balance += amount;
    }

    double getBalance() { // Геттер
        return balance;
    }
};

int main() {
    BankAccount acc(1000);
    // acc.balance = -500; // Ошибка! Нет доступа (инкапсуляция)
    acc.deposit(500);
    std::cout << acc.getBalance(); // 1500
    return 0;
}