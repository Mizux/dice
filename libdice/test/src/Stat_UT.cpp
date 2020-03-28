#include <catch2/catch.hpp>

#include <dice/Stat.hpp>
#include <dice/Dice.hpp>
#include <numeric>

namespace Dice {

TEST_CASE("Stat::Factorials", "[Stat]") {
	REQUIRE(factorial(0) == 1.);
	REQUIRE(factorial(1) == 1.);
	REQUIRE(factorial(2) == 2.);
	REQUIRE(factorial(3) == 6.);
	REQUIRE(factorial(10) == 3628800.);
}

TEST_CASE("Stat::Arrangement", "[Stat]") {
	CHECK(arrangement(1, 1) == 1);
	CHECK(arrangement(2, 1) == 2);

	CHECK(arrangement(3, 1) == 3);
	CHECK(arrangement(3, 2) == 6);
	CHECK(arrangement(3, 3) == 6);

	CHECK(arrangement(6, 1) == 6);
	CHECK(arrangement(6, 2) == 30);
	CHECK(arrangement(6, 3) == 120);
	CHECK(arrangement(6, 4) == 360);
	CHECK(arrangement(6, 5) == 720);
	CHECK(arrangement(6, 6) == 720);

	CHECK(arrangement(8, 0) == 1);
	CHECK(arrangement(8, -1) == 0);
	CHECK(arrangement(0, 8) == 0);
	CHECK(arrangement(8, 8) == 40320);
	CHECK(arrangement(8, 7) == 40320);
}

TEST_CASE("Stat::Binomial", "[Stat]") {
	CHECK(binomial(1, 1) == 1);
	CHECK(binomial(2, 1) == 2);

	CHECK(binomial(3, 1) == 3);
	CHECK(binomial(3, 2) == 3);
	CHECK(binomial(3, 3) == 1);

	CHECK(binomial(6, 1) == 6);
	CHECK(binomial(6, 2) == 15);
	CHECK(binomial(6, 3) == 20);
	CHECK(binomial(6, 4) == 15);
	CHECK(binomial(6, 5) == 6);
	CHECK(binomial(6, 6) == 1);

	CHECK(binomial(8, 0) == 1);
	CHECK(binomial(8, -1) == 0);
	CHECK(binomial(0, 8) == 0);
	CHECK(binomial(8, 8) == 1);
	CHECK(binomial(8, 7) == 8);
}
/*
TEST_CASE("Stat::getTupleStat", "[Stat]") {
        SECTION("Heads or Tails") {
                Die die = {Face::HEADS(), Face::TAILS()};

                TupleStat stat = getTupleStat(5, die, {Face::HEADS(),
Face::HEADS()});
                REQUIRE(stat.size() == 3);
                INFO("0: " << stat[0] << " 1: " << stat[1] << " 2: " <<
stat[2]);
                CHECK(std::accumulate(
                        stat.begin(), stat.end(), 0., [](double lhs,
std::pair<int, double> rhs) {
                                return lhs + rhs.second;
                              }) == 1.0);
                CHECK(stat[0] == 0.1875);
                CHECK(stat[1] == 0.625);
                CHECK(stat[2] == 0.1875);
        }
        SECTION("6D6, {1,2}") {
                TupleStat stat = getTupleStat(6, Die::D6(), {Face::ONE(),
Face::TWO()});
                CHECK(stat.size() == 4);
                INFO(
                  "0: " << stat[0] << " 1: " << stat[1] << " 2: " << stat[2] <<
" 3: " << stat[3]);
                double sum = std::accumulate(
                  stat.begin(), stat.end(), 0., [](double lhs, std::pair<int,
double> rhs) {
                          return lhs + rhs.second;
                        });
                CHECK(std::abs(sum - 1.0) < 0.00001);
        }
}
*/
/*
TEST_CASE("Stat::4D6", "[Stat]") {
        Dice fourD6(4, Die::D6());
        TupleCount fourCount = fourD6.getTupleCount({Face::ONE(), Face::TWO()});
        INFO("4D6, 2*{1,2}: " << fourCount[2]);
        INFO("Calculated: " << factorial(4) / (factorial(2) * factorial(2)));

        Dice sixD6(6, Die::D6());
        TupleCount sixCount = sixD6.getTupleCount({Face::ONE(), Face::TWO()});
        INFO("6D6, 1*{1,2}: " << sixCount[1]);
        INFO("6D6, 2*{1,2}: " << sixCount[2]);
        INFO("6D6, 3*{1,2}: " << sixCount[3]);
        INFO("Calculated: " << (factorial(4) /
                                (factorial(2) * factorial(2))) * // permutation
{AABB} = 6
                                   binomial(6, 4) *
                                   std::pow(5, 6 - 4) -
                                 6 * binomial(6, 4) - 6 * binomial(6, 4) * 6 *
2);

        Dice threeD3(3, {Face::ONE(), Face::TWO(), Face::THREE()});
        TupleCount threeCount = threeD3.getTupleCount({Face::ONE(),
Face::TWO()});
        INFO("3D3, 1*{1,2}: " << threeCount[1]);
        INFO("Calculated: " << 2 * binomial(3, 2) * std::pow(6, 1) - 2 *
binomial(3, 2));

        CHECK(false);
}
*/
/*TEST_CASE("Stat::calculateTupleCount", "[Stat]") {
  Die die = Die::D6;
  std::size_t n = 6;
  Tuple t = {Face::ONE, Face::TWO};
  TupleCount calculated = calculateTupleCount(n, die, t);
  TupleCount bruteForce = getTupleCount(n, die, t);
  REQUIRE(calculated.size() == bruteForce.size());
  for (std::size_t idx = 0; idx < calculated.size(); ++idx) {
    INFO("BF[" << idx << "]: " << bruteForce[idx] <<
         " CAL[" << idx << "]: " << calculated[idx]);
    //CHECK(bruteForce[idx] == calculated[idx]);
    CHECK(false);
  }
}*/

/*TEST_CASE("Stat::calculateTupleStat", "[Stat]") {
  Die die = Die::D6;
  std::size_t n = 6;
  Tuple t = {Face::ONE, Face::TWO};
  TupleStat calculated = calculateTupleStat(n, die, t);
  TupleStat bruteForce = getTupleStat(n, die, t);
  REQUIRE(calculated.size() == bruteForce.size());
  for (std::size_t idx = 0; idx < calculated.size(); ++idx) {
    INFO("BF[" << idx << "]: " << bruteForce[idx] <<
         " CAL[" << idx << "]: " << calculated[idx]);
    INFO("div: " << bruteForce[idx] / calculated[idx]);
    CHECK(std::abs(bruteForce[idx] - calculated[idx]) < 0.00001);
  }
}*/

TEST_CASE("Stat::accumulate", "[Stat]") {
	CHECK(accumulate(1, 2) == 3);
	CHECK(accumulate(2, 3) == 5);

	CHECK(accumulate(0, 3) == 6);
	CHECK(accumulate(1, 3) == 6);
}
}
