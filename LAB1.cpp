﻿#include "C:\Users\Mask\source\repos\LAB1\UnitTest1\pch.h"
#include "head.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>



PlantContainer::~PlantContainer() {
    for (Plant* plant : plants) {
        delete plant; // Освободите память для каждого растения
    }
}
Plant::Plant(const std::string& name) : name(name) {} // Определение конструктора

Plant::~Plant() {}

Tree::Tree(const std::string& name, int age) : Plant(name), age(age) {}

std::string Tree::getType() const { return "Tree"; }
std::string Tree::toString() const {
    return "Tree: " + name + ", Age: " + std::to_string(age);
}


Shrub::Shrub(const std::string& name, const std::string& flowering_month)
    : Plant(name), flowering_month(flowering_month) {}

std::string Shrub::getType() const { return "Shrub"; }
std::string Shrub::toString() const {
    return "Shrub: " + name + ", Flowering Month: " + flowering_month;
}



Cactus::Cactus(const std::string& name, double spine_length)
    : Plant(name), spine_length(spine_length) {}

std::string Cactus::getType() const { return "Cactus"; }
std::string Cactus::toString() const {
    return "Cactus: " + name + ", Spine Length: " + std::to_string(spine_length);
}


void PlantContainer::addPlant(Plant* plant) {
    plants.push_back(plant);
}

bool PlantContainer::compare(int value, const std::string& op, int age) {
    if (op == "=") return value == age;
    if (op == "<") return value < age;
    if (op == ">") return value > age;
    if (op == "<=") return value <= age;
    if (op == ">=") return value >= age;
    return false;
}

bool PlantContainer::compare(double value, const std::string& op, double length) {
    if (op == "=") return value == length;
    if (op == "<") return value < length;
    if (op == ">") return value > length;
    if (op == "<=") return value <= length;
    if (op == ">=") return value >= length;
    return false;
}

void PlantContainer::removePlants(const std::string& condition) {
    std::istringstream iss(condition);
    std::string type;
    iss >> type;

    if (type == "age") {
        std::string op;
        int age;
        iss >> op >> age;
        plants.erase(std::remove_if(plants.begin(), plants.end(),
            [&op, age, this](Plant* plant) {
                Tree* tree = dynamic_cast<Tree*>(plant);
                return tree && this->compare(tree->age, op, age);
            }), plants.end());
    }
    else if (type == "month") {
        std::string op, month;
        iss >> op >> month;
        if (op == "=") {
            plants.erase(std::remove_if(plants.begin(), plants.end(),
                [&month](Plant* plant) {
                    Shrub* shrub = dynamic_cast<Shrub*>(plant);
                    return shrub && shrub->flowering_month == month;
                }), plants.end());
        }
    }
    else if (type == "spine") {
        std::string op;
        double spine_length;
        iss >> op >> spine_length;
        plants.erase(std::remove_if(plants.begin(), plants.end(),
            [&op, spine_length, this](Plant* plant) {
                Cactus* cactus = dynamic_cast<Cactus*>(plant);
                return cactus && this->compare(cactus->spine_length, op, spine_length);
            }), plants.end());
    }
}

void PlantContainer::printPlants() const {
    if (plants.empty()) {
        std::cout << "No plants in the container." << std::endl;
        return;
    }

    std::cout << "Plants in the container:" << std::endl;
    for (const auto& plant : plants) {
        std::cout << plant->toString() << std::endl;
    }
}

void printHelpFile() {
    std::ifstream helpFile("Help.txt");
    if (!helpFile.is_open()) {
        std::cout << "Не удалось открыть файл Help.txt." << std::endl;
        return;
    }
    std::cout << helpFile.rdbuf(); // Выводит содержимое файла в консоль
    helpFile.close();
}

void processCommand(PlantContainer& container, const std::string& command) {
    std::istringstream iss(command);
    std::string cmd;
    iss >> cmd;

    if (cmd == "ADD") {
        std::string type, name;
        std::getline(iss, type, ','); // Чтение до запятой
        std::getline(iss, name, ','); // Чтение имени
        //name.erase(0, name.find_first_not_of(" \n\r\t")); // Удаление пробелов слева
        //name.erase(name.find_last_not_of(" \n\r\t") + 1); // Удаление пробелов справа

        if (type == " tree") {
            int age;
            iss >> age;
            container.addPlant(new Tree(name, age));
        }
        else if (type == " shrub") {
            std::string flowering_month;
            iss >> flowering_month;
            container.addPlant(new Shrub(name, flowering_month));
        }
        else if (type == " cactus") {
            double spine_length;
            iss >> spine_length;
            container.addPlant(new Cactus(name, spine_length));
        }
        else {
            std::cout << "Неизвестный тип растения." << std::endl;
        }
    }
    else if (cmd == "REM") {
        std::string condition;
        std::getline(iss, condition);
        condition.erase(0, condition.find_first_not_of(" \n\r\t")); // Удаление пробелов слева
        container.removePlants(condition);
    }
    else if (cmd == "PRINT") {
        container.printPlants();
    }
    else if (cmd == "HELP") {
        printHelpFile();  // Выводит содержимое файла в консоль
    }
    else if (cmd == "READ") {
        std::string filename;
        iss >> filename;
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "Не удалось открыть файл: " << filename << std::endl;
            return;
        }
        std::string line;
        while (std::getline(file, line)) {
            processCommand(container, line);
        }
        file.close();
    }
    else {
        std::cout << "Неизвестная команда." << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "");
    PlantContainer container;
    std::string command;

    while (true) {
        std::cout << "Введите команду (ADD, REM, PRINT, HELP, READ или EXIT): ";
        std::getline(std::cin, command);

        if (command == "EXIT") {
            break;
        }

        processCommand(container, command);
    }

    return 0;
}