#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <random>
#include <sstream>
#include <iomanip>
#include <chrono>
#include "Personnames.h"

class People {
private:
    std::string firstName;
    std::string surname;
    std::string patronymic;
    std::string birthDate;
    int salary;

    std::string GenerateRandomBirthDate() {
        // Установка диапазона для дат
        auto start = std::chrono::system_clock::from_time_t(std::mktime(new tm{0, 0, 0, 1, 0, 60})); // 1960-01-01
        auto end = std::chrono::system_clock::from_time_t(std::mktime(new tm{0, 0, 0, 1, 0, 120})); // 2020-01-01

        // Генерация случайного времени
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<std::chrono::system_clock::rep> dist(
                start.time_since_epoch().count(),
                end.time_since_epoch().count()
        );

        auto random_time = std::chrono::system_clock::time_point(std::chrono::system_clock::duration(dist(gen)));
        std::time_t random_time_t = std::chrono::system_clock::to_time_t(random_time);

        // Форматирование даты
        std::ostringstream oss;
        oss << std::put_time(std::localtime(&random_time_t), "%d.%m.%Y");
        return oss.str();
    }

    int GenerateRandomSalary() {
        // Установка диапазона и распределения для зп
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 1000000); // Диапазон от 0 до 1,000,000
        return dist(gen);
    }

public:
    People() {
        std::random_device rd;
        std::mt19937 gen(rd());

        firstName = russianFirstNames[std::uniform_int_distribution<>(0, countRussianFirstNames - 1)(gen)];
        surname = russiansurnames[std::uniform_int_distribution<>(0, countRussiansurnames - 1)(gen)];
        patronymic = russianPatronymics[std::uniform_int_distribution<>(0, countRussianPatronymics - 1)(gen)];
        birthDate = GenerateRandomBirthDate();
        salary = GenerateRandomSalary();
    }

    People(std::string firstName, std::string surname, std::string patronymic, std::string birthDate, int salary)
            : firstName(std::move(firstName)), surname(std::move(surname)), patronymic(std::move(patronymic)),
              birthDate(std::move(birthDate)), salary(salary) {}

    // Операторы сравнения
    bool operator<(const People& other) const { return salary < other.salary; }
    bool operator>(const People& other) const { return salary > other.salary; }
    bool operator<=(const People& other) const { return salary <= other.salary; }
    bool operator>=(const People& other) const { return salary >= other.salary; }
    bool operator==(const People& other) const { return salary == other.salary; }
    bool operator!=(const People& other) const { return salary != other.salary; }

    // Геттеры
    std::string GetFirstName() const { return firstName; }
    std::string Getsurname() const { return surname; }
    std::string GetPatronymic() const { return patronymic; }
    std::string GetBirthDate() const { return birthDate; }
    double Getsalary() const { return salary; }
};

#endif
