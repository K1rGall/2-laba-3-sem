#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "DynamicArray.h"
#include "Person.h"
#include <vector>
#include <string>
#include <queue>
#include <functional>


const std::string TEMP_FILE_PREFIX = "chunk_";

std::vector<People> ReadChunk(std::ifstream &file, int chunkSize) {
    std::vector<People> chunk;
    std::string line;
    while (chunk.size() < chunkSize && std::getline(file, line)) {
        std::istringstream iss(line);
        People person;
        if (iss >> person) {
            chunk.push_back(person);
        }
    }
    return chunk;
}

void WriteChunk(const std::vector<People> &chunk, const std::string &filename) {
    std::ofstream outFile(filename, std::ios::out | std::ios::trunc);
    if (!outFile) {
        std::cerr << "Error: Cannot open file for writing: " << filename << std::endl;
        return;
    }
    for (const auto &person : chunk) {
        outFile << person << "\n";
    }
}

// Внешняя сортировка больших файлов
void ExternalSort(const std::string &inputFile, const std::string &outputFile, int chunkSize) {
    std::ifstream inFile(inputFile);
    if (!inFile) {
        std::cerr << "Error: Cannot open input file: " << inputFile << std::endl;
        return;
    }

    std::vector<std::string> tempFiles;
    int fileCount = 0;

    while (true) {
        std::vector<People> chunk = ReadChunk(inFile, chunkSize);
        if (chunk.empty()) break;

        std::sort(chunk.begin(), chunk.end(), [](const People &a, const People &b) {
            return a.GetBirthDate() < b.GetBirthDate();
        });

        std::string tempFilename = TEMP_FILE_PREFIX + std::to_string(fileCount++) + ".txt";
        WriteChunk(chunk, tempFilename);
        tempFiles.push_back(tempFilename);
    }
    inFile.close();

    auto compare = [](const std::pair<People, int> &a, const std::pair<People, int> &b) {
        return a.first.GetBirthDate() > b.first.GetBirthDate();
    };

    std::priority_queue<std::pair<People, int>, std::vector<std::pair<People, int>>, decltype(compare)> minHeap(compare);

    std::vector<std::ifstream> chunkStreams(tempFiles.size());
    for (int i = 0; i < tempFiles.size(); ++i) {
        chunkStreams[i].open(tempFiles[i]);
        if (!chunkStreams[i]) {
            std::cerr << "Error: Cannot open temporary file: " << tempFiles[i] << std::endl;
            continue;
        }
        std::string line;
        if (std::getline(chunkStreams[i], line)) {
            std::istringstream iss(line);
            People person;
            if (iss >> person) {
                minHeap.push({person, i});
            }
        }
    }

    std::ofstream outFile(outputFile, std::ios::out | std::ios::trunc);
    if (!outFile) {
        std::cerr << "Error: Cannot open output file: " << outputFile << std::endl;
        return;
    }

    while (!minHeap.empty()) {
        auto [person, index] = minHeap.top();
        minHeap.pop();
        outFile << person << "\n";

        std::string line;
        if (std::getline(chunkStreams[index], line)) {
            std::istringstream iss(line);
            People nextPerson;
            if (iss >> nextPerson) {
                minHeap.push({nextPerson, index});
            }
        }
    }

    for (auto &stream : chunkStreams) {
        if (stream.is_open()) {
            stream.close();
        }
    }

    // Удаляем временные файлы
    for (const auto &file : tempFiles) {
        std::remove(file.c_str());
    }
}
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
