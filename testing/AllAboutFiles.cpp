#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "DynamicArray.h"
#include "Person.h"

void GenerateRandomFile(int count, std::string& fileName)
{
    std::ofstream file(fileName);
    if (!file) {
        std::cerr << "Error opening the file!" << std::endl;
        return;
    }

    for (int i = 0; i < count; ++i) {
        People people = People();

        file << people.GetSurname() << " "
             << people.GetFirstName() << " "
             << people.GetPatronymic() << " "
             << people.GetBirthDate() << " "
             << people.GetSalary() << "\n";
    }

    std::cout << "The data have been successfully written to the file " << fileName << std::endl;

    file.close();
}

Sequence<People>& ReadSequenceFromFile(std::string& fileName, Sequence<People>* sequence)
{
    std::ifstream file(fileName);
    if (!file) {
        std::cout << "Error opening the file!" << std::endl;
        return *sequence;
    }

    int numLines = std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n');
    file.seekg(0, std::ios::beg);

    int i = 0;
    People* array = new People[numLines];
    std::string line;
    int skiped = 0;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string firstName, surname, patronymic, birthDate;
        int accountBalance;

        if (!(iss >> surname >> firstName >> patronymic >> birthDate >> accountBalance)) {
            std::cout << "Error reading line: " << line << std::endl;
            sequence->Append(array, i - skiped);
            delete[] array;
            array = new People[numLines - i - 1];
            i++;
            skiped = i;
            continue;
        }

        People person(firstName, surname, patronymic, birthDate, accountBalance);
        array[i - skiped] = person;
        i++;
    }

    file.close();

    sequence->Append(array, numLines - skiped);
    std::cout << "Count elements " << sequence->GetLength() << std::endl;

    delete[] array;

    return *sequence;
}

void ReadDynamicArrayFromFile(std::string& fileName, DynamicArray<People>* sequence)
{
    sequence = &dynamic_cast<DynamicArray<People>&>(ReadSequenceFromFile(fileName, sequence));
}

void WriteSequenceToFile(std::string& fileName, Sequence<People>* sequence)
{
    std::ofstream file(fileName);
    if (!file) {
        std::cerr << "Error opening the file!" << std::endl;
        return;
    }

    auto begin = sequence->ToBegin();
    auto end = sequence->ToEnd();

    while (*begin != *end)
    {
        file << (**begin).GetSurname() << " "
             << (**begin).GetFirstName() << " "
             << (**begin).GetPatronymic() << " "
             << (**begin).GetBirthDate() << " "
             << (**begin).GetSalary() << "\n";
        ++(*begin);
    }

    std::cout << "The data have been successfully written to the file " << fileName << std::endl;

    file.close();
}
