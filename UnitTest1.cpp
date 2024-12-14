#include "pch.h"
#include "CppUnitTest.h"
#include "head.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
		
    public:
        TEST_METHOD(TestAddTree)
        {
            PlantContainer container;
            container.addPlant(new Tree("Oak", 15));

            Assert::AreEqual(1, static_cast<int>(container.plants.size()));
            Assert::AreEqual("Tree: Oak, Age: 15", container.plants[0]->toString().c_str());
        }

        TEST_METHOD(TestAddShrub)
        {
            PlantContainer container;
            container.addPlant(new Shrub("Rose", "May"));

            Assert::AreEqual(1, static_cast<int>(container.plants.size()));
            Assert::AreEqual("Shrub: Rose, Flowering Month: May", container.plants[0]->toString().c_str());
        }

        TEST_METHOD(TestAddCactus)
        {
            PlantContainer container;
            container.addPlant(new Cactus("Saguaro", 15.5));

            Assert::AreEqual(1, static_cast<int>(container.plants.size()));
            Assert::AreEqual("Cactus: Saguaro, Spine Length: 15.500000", container.plants[0]->toString().c_str());
        }

        TEST_METHOD(TestRemovePlantsByAge)
        {
            PlantContainer container;
            container.addPlant(new Tree("Oak", 15));
            container.addPlant(new Tree("Pine", 10));

            container.removePlants("age > 12");

            Assert::AreEqual(1, static_cast<int>(container.plants.size()));
            Assert::AreEqual("Tree: Pine, Age: 10", container.plants[0]->toString().c_str());
        }

        TEST_METHOD(TestRemovePlantsByFloweringMonth)
        {
            PlantContainer container;
            container.addPlant(new Shrub("Rose", "May"));
            container.addPlant(new Shrub("Tulip", "April"));

            container.removePlants("month = May");

            Assert::AreEqual(1, static_cast<int>(container.plants.size()));
            Assert::AreEqual("Shrub: Tulip, Flowering Month: April", container.plants[0]->toString().c_str());
        }

        TEST_METHOD(TestRemovePlantsBySpineLength)
        {
            PlantContainer container;
            container.addPlant(new Cactus("Saguaro", 12.5));
            container.addPlant(new Cactus("Barrel", 8.0));

            container.removePlants("spine < 10");

            Assert::AreEqual(1, static_cast<int>(container.plants.size()));
            Assert::AreEqual("Cactus: Saguaro, Spine Length: 12.500000", container.plants[0]->toString().c_str());
        }

        TEST_METHOD(TestPrintPlantsEmpty)
        {
            PlantContainer container;
            std::stringstream buffer;
            std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

            container.printPlants();

            std::cout.rdbuf(old);
            Assert::AreEqual("No plants in the container.\n", buffer.str().c_str());
        }

        TEST_METHOD(TestPrintPlants)
        {
            PlantContainer container;
            container.addPlant(new Tree("Oak", 15));

            std::stringstream buffer;
            std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

            container.printPlants();

            std::cout.rdbuf(old);
            Assert::AreEqual("Plants in the container:\nTree: Oak, Age: 15\n", buffer.str().c_str());
        }
    };
}