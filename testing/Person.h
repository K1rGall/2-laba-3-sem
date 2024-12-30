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
        std::uniform_int_distribution<int> yearDist(1960, 2020);
        std::uniform_int_distribution<int> monthDist(1, 12);
        std::uniform_int_distribution<int> dayDist(1, 28);

        int year = yearDist(gen);
        int month = monthDist(gen);
        int day = dayDist(gen);

        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << day << '.'
            << std::setw(2) << std::setfill('0') << month << '.' << year;
        return oss.str();
    }

    // Генерация случайной зарплаты
    int GenerateRandomSalary() {
        static std::uniform_int_distribution<> salaryDist(0, 1000000); // Диапазон от 0 до 1,000,000
        return salaryDist(gen);
    }

public:
    People() {
        static std::uniform_int_distribution<> firstNameDist(0, countRussianFirstNames - 1);
        static std::uniform_int_distribution<> surnameDist(0, countRussiansurnames - 1);
        static std::uniform_int_distribution<> patronymicDist(0, countRussianPatronymics - 1);

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
        people.resize(count);
        int thread_count = std::thread::hardware_concurrency();
        int batch_size = (count + thread_count - 1) / thread_count;

        std::vector<std::thread> threads;

        for (int i = 0; i < thread_count; ++i) {
            threads.emplace_back([&people, i, batch_size, count]() {
                int start = i * batch_size;
                int end = std::min(start + batch_size, count);
                for (int j = start; j < end; ++j) {
                    people[j] = People(); // Генерация нового объекта
                }
            });
        }

        // Ожидаем завершения всех потоков
        for (auto& t : threads) {
            if (t.joinable()) t.join();
        }
    }
};

#endif
