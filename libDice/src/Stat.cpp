//! @file

#include <Dice/Dice.hpp>
#include <Dice/Stat.hpp>
#include <cmath>
#include <iostream>

namespace Dice {

double
factorial(double n) {
	return (n > 1.0) ? factorial(n - 1.0) * n : 1.0;
}

double
arrangement(double N, double k) {
	return (k > N || k < 0) ? 0 : factorial(N) / (factorial(N - k));
}

double
binomial(double n, double k) {
	return (k > n || k < 0) ? 0 : factorial(n) / (factorial(n - k) * factorial(k));
}
/*
TupleStat
getTupleStat(std::size_t diceNumber, const Die& die, const Tuple& tuple) {
	return Dice(diceNumber, die).getTupleStat(tuple);
}

TupleCount
getTupleCount(std::size_t diceNumber, const Die& die, const Tuple& tuple) {
	return Dice(diceNumber, die).getTupleCount(tuple);
}
*/
std::size_t
accumulate(std::size_t min, std::size_t max) {
	return (max + min) * (max - min + 1) / 2;
}
}
