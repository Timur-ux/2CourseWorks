#include <gtest/gtest.h>
#include <sstream>

#include "LocationRedactor.hpp"
#include "redactorBuilder.hpp"

class RedactorTest : public ::testing::Test {
public:
	std::shared_ptr<LocationRedactor> redactor;
	std::shared_ptr<std::ofstream> outFile;
	std::shared_ptr<ILocation> location;

	std::stringstream outStream;
	std::stringstream inStream;
	void SetUp() override {
		RedactorDirector director;
		Builder builder;

		outFile = std::make_shared<std::ofstream>("test.log");

		redactor = director.createDangeonRedactor(builder, outFile);
		redactor->setOStream(&outStream);
		redactor->setIStream(&inStream);

		location = builder.location;
	}

	void TearDown() override {

	}
};

TEST_F(RedactorTest, testAdd) {
	inStream << "Dragon Figli_Migli 5 15";
	redactor->inputCommand("add");

	auto & mobs = location->getMobsData();

	EXPECT_EQ(mobs.size(), 1);

	auto dragonData = mobs.begin()->second;

	EXPECT_EQ(dragonData.getMobType(), enumMobType::Dragon);
	EXPECT_EQ(dragonData.getPosition(), Position(5, 15));
	EXPECT_EQ(dragonData.getMob()->getName(), "Figli Migli");
}

TEST_F(RedactorTest, testMove) {
	inStream << "Dragon Figli_Migli 5 15" << std::endl;
	redactor->inputCommand("add");

	auto & mobs = location->getMobsData();

	inStream << std::to_string(mobs.begin()->first) + " 25 25" << std::endl;
	redactor->inputCommand("move");

	auto dragonData = mobs.begin()->second;

	EXPECT_EQ(dragonData.getPosition(), Position(25, 25));
}

TEST_F(RedactorTest, testRemove) {
	inStream << "Dragon Figli_Migli 5 15" << std::endl;
	redactor->inputCommand("add");

	auto & mobs = location->getMobsData();

	inStream << std::to_string(mobs.begin()->first) << std::endl;
	redactor->inputCommand("remove");

	EXPECT_EQ(mobs.size(), 0);
}

TEST_F(RedactorTest, testBattle) {
	inStream
		<< "Dragon Figli_Migli 5 15" << std::endl
		<< "Elf Legolas 20 20" << std::endl
		<< "KnightStranger D'Artanian 30 30" << std::endl;
	redactor->inputCommand("add");
	redactor->inputCommand("add");
	redactor->inputCommand("add");

	auto & mobs = location->getMobsData();

	inStream << 30 << std::endl;
	redactor->inputCommand("start battle round");

	EXPECT_EQ(mobs.size(), 0);
}