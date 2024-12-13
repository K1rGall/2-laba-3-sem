#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <random>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <vector>
#include "Personnames.h"

// Глобальный генератор случайных чисел для всех нужд
static std::random_device rd;
static std::mt19937 gen(rd());

class People {
private:
    std::string firstName;
    std::string surname;
    std::string patronymic;
    std::string birthDate;
    int salary;

    // Генерация случайной даты рождения
    std::string GenerateRandomBirthDate() {
        // Установка диапазона для дат
        auto start = std::chrono::system_clock::from_time_t(std::mktime(new tm{0, 0, 0, 1, 0, 60})); // 1960-01-01
        auto end = std::chrono::system_clock::from_time_t(std::mktime(new tm{0, 0, 0, 1, 0, 120})); // 2020-01-01

        // Генерация случайного времени
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

    // Генерация случайной зарплаты
    int GenerateRandomSalary() {
        std::uniform_int_distribution<> dist(0, 1000000); // Диапазон от 0 до 1,000,000
        return dist(gen);
    }

public:
    People() {
        std::uniform_int_distribution<> firstNameDist(0, countRussianFirstNames - 1);
        std::uniform_int_distribution<> surnameDist(0, countRussiansurnames - 1);
        std::uniform_int_distribution<> patronymicDist(0, countRussianPatronymics - 1);

        firstName = russianFirstNames[firstNameDist(gen)];
        surname = russiansurnames[surnameDist(gen)];
        patronymic = russianPatronymics[patronymicDist(gen)];
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
    std::string GetSurname() const { return surname; }
    std::string GetPatronymic() const { return patronymic; }
    std::string GetBirthDate() const { return birthDate; }
    double GetSalary() const { return salary; }

    // Статическая функция для массовой генерации данных
    static void GenerateMultiplePeople(std::vector<People>& people, int count) {
        std::vector<std::thread> threads;
        int batch_size = count / std::thread::hardware_concurrency();

        // Разделяем задачу по потокам для ускорения генерации
        for (int i = 0; i < std::thread::hardware_concurrency(); ++i) {
            threads.push_back(std::thread([&people, batch_size, i]() {
                for (int j = i * batch_size; j < (i + 1) * batch_size && j < people.size(); ++j) {
                    people[j] = People(); // Генерация нового объекта
                }
            }));
        }

        // Ожидаем завершения всех потоков
        for (auto& t : threads) {
            t.join();
        }
    }
};

#endif
