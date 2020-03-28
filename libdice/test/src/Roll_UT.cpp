#include <catch2/catch.hpp>

#include <dice/Roll.hpp>
#include <cmath>

namespace Dice {

TEST_CASE("Roll::Ctor", "[Roll]") {
	SECTION("Default constructor") {
		Roll null;
		CHECK(null().empty());
	}
	SECTION("Dice") {
		Dice dice = {5, Die::D8()};
		Roll roll5d8(dice);
		CHECK(roll5d8().size() == 5);
		for (const auto& it : roll5d8()) {
			CHECK(it == Face::ONE());
		}
	}
	SECTION("6d6") {
		Roll roll6d6(6, Die::D6());
		CHECK(roll6d6().size() == 6);
		for (const auto& it : roll6d6()) {
			CHECK(it == Face::ONE());
		}
	}
}

TEST_CASE("Roll::operator++", "[Roll]") {
	SECTION("operator++") {
		Roll roll(6, Die::D6());
		std::size_t count = 0;
		do {
			++count;
			++roll;
		} while (!roll().empty());
		CHECK(count == std::pow(6, 6));
	}
}

TEST_CASE("Roll::findTuple", "[Roll]") {
	SECTION("findTuple") {
		Roll twoDice(2, Die::D6());
		CHECK(twoDice.findTuple({Face::ONE(), Face::ONE(), Face::ONE()}) == 0);

		Roll roll(6, Die::D6()); // roll = {1,1,1,1,1,1}
		INFO("Roll: " << roll);
		CHECK(roll.findTuple({Face::ONE()}) == 6);
		CHECK(roll.findTuple({Face::TWO()}) == 0);
		CHECK(roll.findTuple({Face::ONE(), Face::ONE()}) == 3);
		CHECK(roll.findTuple({Face::ONE(), Face::TWO()}) == 0);
		CHECK(roll.findTuple({Face::ONE(), Face::ONE(), Face::ONE()}) == 2);
	}
}

TEST_CASE("Roll::operator<<", "[Roll]") {
	SECTION("Debug print") { INFO("Roll: " << Roll(2, Die::D6())); }
}
}
