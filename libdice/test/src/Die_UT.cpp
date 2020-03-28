#include <catch2/catch.hpp>
#include <sstream>

#include <dice/Die.hpp>

namespace Dice {

TEST_CASE("Die::Ctor", "[Die]") {
	SECTION("Default constructor") {
		Die die;
		CHECK(die.size() == 0);
	}
	SECTION("Initializer list") {
		Die die = {Face::ONE(), Face::TWO(), Face::THREE()};
		CHECK(die.size() == 3);
		die = {
		  Face::ONE(), Face::TWO(), Face::THREE(), Face::FOUR(), Face::FIVE(), Face::SIX()};
		CHECK(die.size() == 6);
	}
	SECTION("d6") {
		Die d6 = Die::D6();
		INFO("d6: " << d6);
		REQUIRE(d6.size() == 6);
		CHECK(d6[0] == Face::ONE());
		CHECK(d6[1] == Face::TWO());
		CHECK(d6[2] == Face::THREE());
		CHECK(d6[3] == Face::FOUR());
		CHECK(d6[4] == Face::FIVE());
		CHECK(d6[5] == Face::SIX());
	}
	SECTION("d8") {
		Die d8 = Die::D8();
		INFO("d8: " << d8);
		REQUIRE(d8.size() == 8);
		CHECK(d8[0] == Face::ONE());
		CHECK(d8[1] == Face::TWO());
		CHECK(d8[2] == Face::THREE());
		CHECK(d8[3] == Face::FOUR());
		CHECK(d8[4] == Face::FIVE());
		CHECK(d8[5] == Face::SIX());
		CHECK(d8[6] == Face::SEVEN());
		CHECK(d8[7] == Face::HEIGHT());
	}
}

TEST_CASE("Die Iterator", "[Die]") {
	Die die = Die::D6();
	SECTION("ConstIterator") {
		std::size_t size = 0;
		for (Die::const_iterator it = die.begin(); it != die.end(); ++it) {
			size++;
		}
		CHECK(size == die.size());
	}
	SECTION("Iterator") {
		std::size_t size = 0;
		for (Die::iterator it = die.begin(); it != die.end(); ++it) {
			size++;
		}
		CHECK(size == die.size());
	}
}

TEST_CASE("Die Accessors", "[Die]") {
	Die die = Die::D6();
	SECTION("Operator[] const") {
		const Face& f = die[1];
		CHECK(f == Face::TWO());
	}
	SECTION("Operator[]") {
		Face& f = die[1];
		CHECK(f == Face::TWO());
	}
	SECTION("at const") {
		const Face& f = die.at(1);
		CHECK(f == Face::TWO());
		CHECK_THROWS_AS(die.at(6), std::out_of_range);
	}
	SECTION("at") {
		Face& f = die.at(1);
		CHECK(f == Face::TWO());
		const Die& dieCst = die;
		CHECK_THROWS_AS(dieCst.at(6), std::out_of_range);
	}
}

TEST_CASE("Die::addFace", "[Die]") {
	Die die;
	CHECK(die.size() == 0);
	die.push_back(Face::ONE());
	CHECK(die.size() == 1);
	CHECK(die.countFace(Face::ONE()) == 1);
}

TEST_CASE("Die::countFace", "[Die]") {
	SECTION("d3") {
		Die d3 = {Face::ONE(), Face::ONE(), Face::THREE()};
		INFO("d3: " << d3);
		CHECK(d3.countFace(Face::ONE()) == 2);
		CHECK(d3.countFace(Face::TWO()) == 0);
		CHECK(d3.countFace(Face::THREE()) == 1);
		CHECK(d3.countFace(Face::SEVEN()) == 0);
	}
	SECTION("d6") {
		Die d6 = Die::D6();
		INFO("Die::D6: " << Die::D6());
		INFO("d6: " << d6);
		CHECK(d6.countFace(Face::ONE()) == 1);
		CHECK(d6.countFace(Face::SEVEN()) == 0);
	}
}

TEST_CASE("Die::getFaceDistribution", "[Die]") {
	SECTION("d3") {
		Die d3 = {Face::ONE(), Face::ONE(), Face::TWO()};
		INFO("d3: " << d3);
		REQUIRE(d3.size() == 3);
		Die::FaceDistribution countD3 = d3.getFaceDistribution();
		INFO("Count d3: " << countD3);
		REQUIRE(countD3.size() == 2);
		CHECK(countD3[Face::ONE()] == 2);
		CHECK(countD3[Face::TWO()] == 1);
		CHECK(countD3.find(Face::THREE()) == countD3.end());
	}
	SECTION("d6") {
		Die d6 = Die::D6();
		INFO("d6: " << d6);
		REQUIRE(d6.size() == 6);
		Die::FaceDistribution countD6 = d6.getFaceDistribution();
		INFO("Count d6: " << countD6);
		CHECK(countD6.size() == 6);
		for (const auto& it : countD6) {
			CHECK(it.second == 1);
		}
	}
}

TEST_CASE("Die::getStat", "[Die]") {
	SECTION("Empty Die") {
		Die die;
		auto stat = die.getStat();
		CHECK(stat.size() == 0);
	}
	SECTION("d3") {
		Die d3 = {Face::ONE(), Face::ONE(), Face::TWO()};
		INFO("d3: " << d3);
		REQUIRE(d3.size() == 3);
		Die::Stat statD3 = d3.getStat();
		INFO("Stat d3: " << statD3)
		REQUIRE(statD3.size() == 2);
		CHECK(statD3[Face::ONE()] == 2. / 3.);
		CHECK(statD3[Face::TWO()] == 1. / 3.);
		CHECK(statD3[Face::THREE()] == 0.);
	}
	SECTION("d6") {
		Die d6 = Die::D6();
		INFO("d6: " << d6);
		REQUIRE(d6.size() == 6);
		Die::Stat statD6 = d6.getStat();
		INFO("Stat d6: " << statD6)
		CHECK(statD6.size() == 6);
		for (const auto& it : statD6) {
			CHECK(it.second == 1.0 / 6.0);
		}
	}
	SECTION("d8") {
		Die d8 = Die::D8();
		INFO("d8: " << d8);
		REQUIRE(d8.size() == 8);
		Die::Stat statD8 = d8.getStat();
		INFO("Stat d8: " << statD8)
		CHECK(statD8.size() == 8);
		for (const auto& it : statD8) {
			CHECK(it.second == 1.0 / 8.0);
		}
	}
	SECTION("Die::Stat::operator<< d3") {
		Die d3 = {Face::ONE(), Face::ONE(), Face::TWO()};
		INFO("Die::Stat: " << d3.getStat());
	}
}

TEST_CASE("Die::operator<<", "[Die]") {
	SECTION("Debug print") {
		INFO("Die: " << Die({Face::ONE(), Face::TWO(), Face::THREE()}));
	}
}
}
