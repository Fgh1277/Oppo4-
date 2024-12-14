// PlantContainer.h
#ifndef PLANT_CONTAINER_H
#define PLANT_CONTAINER_H
#include"C:\Users\Mask\source\repos\LAB1\UnitTest1\pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>


class Plant {
public:
    std::string name;

    Plant(const std::string& name);
    virtual ~Plant();
    virtual std::string getType() const = 0;
    virtual std::string toString() const = 0;
};

class Tree : public Plant {
public:
    int age;

    Tree(const std::string& name, int age);
    std::string getType() const override;
    std::string toString() const override;
};

class Shrub : public Plant {
public:
    std::string flowering_month;

    Shrub(const std::string& name, const std::string& flowering_month);
    std::string getType() const override;
    std::string toString() const override;
};

class Cactus : public Plant {
public:
    double spine_length;

    Cactus(const std::string& name, double spine_length);
    std::string getType() const override;
    std::string toString() const override;
};

class PlantContainer {
private:


public:
    std::vector<Plant*> plants;
    ~PlantContainer();
    void addPlant(Plant* plant);
    bool compare(int value, const std::string& op, int age);
    bool compare(double value, const std::string& op, double length);
    void removePlants(const std::string& condition);
    void printPlants() const;
};

void printHelpFile();
void processCommand(PlantContainer& container, const std::string& command);

#endif // PLANT_CONTAINER_H
