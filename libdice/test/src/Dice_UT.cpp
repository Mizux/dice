#include <catch2/catch.hpp>

#include <Dice/Dice.hpp>
#include <chrono>
#include <iostream>
#include <numeric>

namespace Dice {

TEST_CASE("Dice::Ctor", "[Dice]") {
	SECTION("Default constructor") {
		Dice dice;
		CHECK(dice.size() == 0);
	}
	SECTION("Vector<Face>") {
		std::vector<Die> dieVec = {Die::D6(), Die::D6(), Die::D6(), Die::D6()};
		CHECK(dieVec.size() == 4);
		Dice dice(dieVec);
		CHECK(dice.size() == 4);
	}
	SECTION("Initializer_list") {
		Dice dice = {Die::D6(), Die::D6(), Die::D6(), Die::D6()};
		CHECK(dice.size() == 4);
	}
	SECTION("7d6") {
		Dice dice(7, Die::D6());
		CHECK(dice.size() == 7);
	}
}

TEST_CASE("Dice Iterator", "[Dice]") {
	Dice dice(7, Die::D6());
	SECTION("ConstIterator") {
		std::size_t size = 0;
		for (Dice::const_iterator it = dice.begin(); it != dice.end(); ++it) {
			size++;
		}
		CHECK(size == dice.size());
	}
	SECTION("Iterator") {
		std::size_t size = 0;
		for (Dice::iterator it = dice.begin(); it != dice.end(); ++it) {
			size++;
		}
		CHECK(size == dice.size());
	}
}

TEST_CASE("Dice Accessors", "[Dice]") {
	Dice dice = {Die::D6(), Die::D8()};
	SECTION("Operator[] const") {
		const Die& d = dice[1];
		CHECK(d.size() == 8);
	}
	SECTION("Operator[]") {
		Die& d = dice[1];
		CHECK(d.size() == 8);
	}
	SECTION("at const") {
		const Die& d = dice.at(1);
		CHECK(d.size() == 8);
		CHECK_THROWS_AS(dice.at(2), std::out_of_range);
	}
	SECTION("at") {
		Die& d = dice.at(1);
		CHECK(d.size() == 8);
		const Dice& diceCst = dice;
		CHECK_THROWS_AS(diceCst.at(2), std::out_of_range);
	}
}

TEST_CASE("Dice Stat", "[Dice]") {
	SECTION("Empty Dice") {
		Dice dice;
		auto stat = dice.getStat();
		CHECK(stat.size() == 0);
	}
	SECTION("1d6") {
		Dice dice(1, Die::D6());
		auto stat = dice.getStat();
		CHECK(stat.size() == 6);
		CHECK(stat[FaceTuple{Face::ONE()}] == 1 / 6.);
		CHECK(stat[FaceTuple{Face::TWO()}] == 1 / 6.);
		CHECK(stat[FaceTuple{Face::THREE()}] == 1 / 6.);
		CHECK(stat[FaceTuple{Face::FOUR()}] == 1 / 6.);
		CHECK(stat[FaceTuple{Face::FIVE()}] == 1 / 6.);
		CHECK(stat[FaceTuple{Face::SIX()}] == 1 / 6.);
		CHECK(stat[FaceTuple{Face::SEVEN()}] == 0);
	}
	SECTION("Stat 2d{1,1,2}") {
		Dice dice(2, {Face::ONE(), Face::ONE(), Face::TWO()});
		auto stat = dice.getStat();
		REQUIRE(stat.size() == 3);
		std::multiset<Face> one_one = {Face::ONE(), Face::ONE()};
		CHECK(stat[one_one] == 4 / 9.);
		std::multiset<Face> one_two = {Face::ONE(), Face::TWO()};
		CHECK(stat[one_two] == 4 / 9.);
		std::multiset<Face> two_two = {Face::TWO(), Face::TWO()};
		CHECK(stat[two_two] == 1 / 9.);
	}
	SECTION("Stat 2d{1,1,2,3}") {
		Die die({Face::ONE(), Face::ONE(), Face::TWO(), Face::THREE()});
		CHECK(die.size() == 4);
		Dice dice(2, die);
		CHECK(dice.size() == 2);

		auto stat = dice.getStat();
		REQUIRE(stat.size() == 6);
		CHECK(stat.find({Face::ONE(), Face::ONE()}) != stat.end());
		CHECK(stat.find({Face::ONE(), Face::TWO()}) != stat.end());
		CHECK(stat.find({Face::ONE(), Face::THREE()}) != stat.end());
		CHECK(stat.find({Face::TWO(), Face::TWO()}) != stat.end());
		CHECK(stat.find({Face::TWO(), Face::THREE()}) != stat.end());
		CHECK(stat.find({Face::THREE(), Face::THREE()}) != stat.end());
	}
	SECTION("Stat 4d{1,1,2,3}") {
		Die die({Face::ONE(), Face::ONE(), Face::TWO(), Face::THREE()});
		CHECK(die.size() == 4);
		Dice dice(4, die);
		CHECK(dice.size() == 4);

		auto stat           = dice.getStat();
		double sumFreq      = 0.0;
		std::size_t sumRoll = 0;
		for (const auto& it : stat) {
			sumFreq += it.second;
			sumRoll += it.second * dice.rollNumber();
		}
		CHECK(sumFreq == 1.0);
		CHECK(sumRoll == dice.rollNumber());
	}
	SECTION("Dice::Stat::operator<< 2d{1,1,2}") {
		Dice dice(2, {Face::ONE(), Face::ONE(), Face::TWO()});
		INFO("Dic::Stat: " << dice.getStat());
	}
}

TEST_CASE("Dice::rollNumber", "[Dice]") {
	SECTION("6D6") { CHECK(Dice(6, Die::D6()).rollNumber() == std::pow(6, 6)); }
}

TEST_CASE("Dice::operator<<", "[Dice]") {
	SECTION("Debug print") {
		INFO("Dice: " << Dice(3, {Face::ONE(), Face::TWO(), Face::THREE()}));
	}
}

/*
TEST_CASE("Dice::getTupleCount", "[Dice]") {
        SECTION("Heads or Tails") {
                Dice dice(5, {Face::HEADS(), Face::TAILS()});
                TupleCount count = dice.getTupleCount({Face::HEADS(),
Face::HEADS()});
                REQUIRE(count.size() == 3);
                INFO("0: " << count[0] << " 1: " << count[1] << " 2: " <<
count[2]);
                CHECK(count[0] == 6);
                CHECK(count[1] == 20);
                CHECK(count[2] == 6);
                std::size_t sum =
                        std::accumulate(count.begin(),
                                                                                        count.end(),
                                                                                        0,
                                                                                        [](std::size_t lhs, std::pair<int, std::size_t> rhs) {
                                                                                                return lhs + rhs.second;
                                                                                        });
                CHECK(sum == std::pow(dice[0].size(), dice.size()));
        }
        SECTION("5D{H, H, T}, {H, H}") {
                Dice dice(5, {Face::HEADS(), Face::HEADS(), Face::TAILS()});
                TupleCount count = dice.getTupleCount({Face::HEADS(),
Face::HEADS()});
                REQUIRE(count.size() == 3);
                INFO("0: " << count[0] << " 1: " << count[1] << " 2: " <<
count[2]);
                CHECK(count[0] == 11);
                CHECK(count[1] == 120);
                CHECK(count[2] == 112);
                std::size_t sum =
                        std::accumulate(count.begin(),
                                                                                        count.end(),
                                                                                        0,
                                                                                        [](std::size_t lhs, std::pair<int, std::size_t> rhs) {
                                                                                                return lhs + rhs.second;
                                                                                        });
                CHECK(sum == std::pow(dice[0].size(), dice.size()));
        }
        SECTION("6D6, {1,2}") {
                TupleCount count = Dice(6,
Die::D6()).getTupleCount({Face::ONE(), Face::TWO()});
                REQUIRE(count.size() == 4);
                INFO("0: " << count[0] << " 1: " << count[1] << " 2: " <<
count[2] << " 3:"
                                                         << count[3]);
                CHECK(count[0] == 27154);
                CHECK(count[1] == 17532);
                CHECK(count[2] == 1950);
                CHECK(count[3] == 20);
                std::size_t sum =
                        std::accumulate(count.begin(),
                                                                                        count.end(),
                                                                                        0,
                                                                                        [](std::size_t lhs, std::pair<int, std::size_t> rhs) {
                                                                                                return lhs + rhs.second;
                                                                                        });
                CHECK(sum == std::pow(Die::D6().size(), 6));
        }
}

TEST_CASE("Dice::getTupleStat", "[Dice]") {
                SECTION("time for 6D6, {1, 2}") {
                        Dice die(6, Die::D6);
                        auto t1        =
std::chrono::high_resolution_clock::now();
                        TupleStat stat = die.getTupleStat({Face::ONE,
Face::TWO});
                        auto t2        =
std::chrono::high_resolution_clock::now();
                        std::size_t delta =
                                std::chrono::duration_cast<std::chrono::milliseconds>(t2
- t1).count();
                        INFO("time: " << delta << "ms");
                        CHECK(delta < 1000);
                        CHECK(stat.size() == 4);
                }
                SECTION("time for 8D6, {1, 2}") {
                        Dice die(8, Die::D6);
                        auto t1        =
std::chrono::high_resolution_clock::now();
                        TupleStat stat = die.getTupleStat({Face::ONE,
Face::TWO});
                        auto t2        =
std::chrono::high_resolution_clock::now();
                        std::size_t delta =
                                std::chrono::duration_cast<std::chrono::milliseconds>(t2
- t1).count();
                        INFO("time: " << delta << "ms");
                        CHECK(delta < 2000);
                        CHECK(stat.size() == 5);
                }
                SECTION("time for 6D8, {1, 2}") {
                        Dice die(6, Die::D8);
                        auto t1        =
std::chrono::high_resolution_clock::now();
                        TupleStat stat = die.getTupleStat({Face::ONE,
Face::TWO});
                        auto t2        =
std::chrono::high_resolution_clock::now();
                        std::size_t delta =
                                std::chrono::duration_cast<std::chrono::milliseconds>(t2
- t1).count();
                        INFO("time: " << delta << "ms");
                        CHECK(delta < 3000);
                        CHECK(stat.size() == 4);
                }
        SECTION("Heads or Tails") {
                Dice dice(5, {Face::HEADS(), Face::TAILS()});
                TupleStat stat = dice.getTupleStat({Face::HEADS(),
Face::HEADS()});
                REQUIRE(stat.size() == 3);
                INFO("0: " << stat[0] << " 1: " << stat[1] << " 2: " <<
stat[2]);
                CHECK(stat[0] == 0.1875);
                CHECK(stat[1] == 0.625);
                CHECK(stat[2] == 0.1875);
                CHECK(std::accumulate(
                                                stat.begin(), stat.end(), 0.,
[](double lhs, std::pair<int, double> rhs) {
                                                        return lhs + rhs.second;
                                                }) == 1.0);
        }
        SECTION("5D{H, H, T}, {H, H}") {
                Dice die(5, {Face::HEADS(), Face::HEADS(), Face::TAILS()});
                TupleStat stat = die.getTupleStat({Face::HEADS(),
Face::HEADS()});
                REQUIRE(stat.size() == 3);
                INFO("0: " << stat[0] << " 1: " << stat[1] << " 2: " <<
stat[2]);
                CHECK(std::abs(stat[0] - 0.0452675) < 0.00001);
                CHECK(std::abs(stat[1] - 0.493827) < 0.00001);
                CHECK(std::abs(stat[2] - 0.460905) < 0.00001);
                CHECK(std::accumulate(
                                                stat.begin(), stat.end(), 0.,
[](double lhs, std::pair<int, double> rhs) {
                                                        return lhs + rhs.second;
                                                }) == 1.0);
        }
        SECTION("6D6, {1,2}") {
                TupleStat stat = Dice(6, Die::D6()).getTupleStat({Face::ONE(),
Face::TWO()});
                REQUIRE(stat.size() == 4);
                INFO(
                        "0: " << stat[0] << " 1: " << stat[1] << " 2: " <<
stat[2] << " 3: " << stat[3]);
                double sum = std::accumulate(
                        stat.begin(), stat.end(), 0., [](double lhs,
std::pair<int, double> rhs) {
                                return lhs + rhs.second;
                        });
                CHECK(std::abs(sum - 1.0) < 0.00001);
        }
}
*/
}
