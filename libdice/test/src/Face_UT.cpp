#include <catch2/catch_all.hpp>

#include <dice/Face.hpp>

namespace Dice {

TEST_CASE("Face::Ctor", "[Face]") {
	SECTION("Default constructor") {
		Face face("");
		CHECK(face() == "");
	}
	SECTION("Heads or Tails") {
		CHECK(Face::HEAD()() == "HEAD");
		CHECK(Face::TAIL()() == "TAIL");
	}
	SECTION("One to Height") {
		CHECK(Face::ONE()() == "ONE");
		CHECK(Face::TWO()() == "TWO");
		CHECK(Face::THREE()() == "THREE");
		CHECK(Face::FOUR()() == "FOUR");
		CHECK(Face::FIVE()() == "FIVE");
		CHECK(Face::SIX()() == "SIX");
		CHECK(Face::SEVEN()() == "SEVEN");
		CHECK(Face::HEIGHT()() == "HEIGHT");
	}
}

TEST_CASE("Face::create", "[Face]") {
	for (std::size_t i = 1; i < 9; ++i) {
		CHECK_NOTHROW(Face::create(i));
		if (i < 8) CHECK(Face::create(i) != Face::create(i + 1));
	}
	CHECK(Face::create(1) == Face::ONE());
	CHECK(Face::create(2) == Face::TWO());
	CHECK(Face::create(8) == Face::HEIGHT());
	CHECK_THROWS_AS(Face::create(0), std::runtime_error);
	CHECK_THROWS_AS(Face::create(9), std::runtime_error);
}

TEST_CASE("Face::operator<<", "[Face]") {
	SECTION("Debug print") {
		INFO("Face: " << Face::HEAD());
		INFO("Face: " << Face::TAIL());
	}
}
}
