//! @file
#pragma once

#include "Die.hpp"
#include <map>

namespace Dice {

//! @brief Define a Tuple as a vector of Face.
using Tuple = std::vector<Face>;

//! @brief Compute factorial N.
//! @param[in] n The factorial to compute.
//! @return The factorial of N.
double factorial(double n);

//! @brief Compute the k arrangement in N.
//! @details How many distinct ordered k-elements we can have in a set of N
//! elements.
//! @param[in] n The size of the set.
//! @param[in] k The size of the subset.
//! @return The number of possible distinct ordered arrangements.
double arrangement(double n, double k);

//! @brief Compute the k arrangement in N.
//! @details How many distinct unordered k-elements we can have in a set of N
//! elements.
//! @param[in] n The size of the set.
//! @param[in] k The size of the subset.
//! @return The number of possible distinct unordered arrangements.
double binomial(double n, double k);

/*
//! @details Contains the probability to strictly have N time a Tuple.
//! @details key: Number of time the Tuple appears; value: the probability.
//! @invariant The sum must be equal to 1.
using TupleStat = std::map<int, double>;
//! @brief Compute Tuple stats of a pool of Die.
//! @note All dice are identical.
//! @param[in] diceNumber The number of die.
//! @param[in] die The Shape of a Die.
//! @param[in] tuple The Tuple to search.
//! @return A map containing the probability to strictly have N time the Tuple.
TupleStat getTupleStat(std::size_t diceNumber, const Die& die, const Tuple&
tuple);

//! @brief Contains the number of Roll to strictly have N time a Tuple.
//! @details key: Number of time the Tuple appears; value: the number of
possible Roll.
//! @invariant The sum must be equal to the number of possible roll.
using TupleCount = std::map<int, std::size_t>;
//! @brief Compute Tuple counts of a pool of Die.
//! @note All dice are identical.
//! @param[in] diceNumber The number of die.
//! @param[in] die The Shape of a Die.
//! @param[in] tuple The Tuple to search.
//! @return A map containing the number of Roll to strictly have N time the
Tuple.
TupleCount getTupleCount(std::size_t diceNumber, const Die& die, const Tuple&
tuple);
*/

//! @brief Sum of all element in the range [min, max].
//! @param[in] min The first element in the range.
//! @param[in] max The last element in the range.
//! @return The sum of aall elements.
std::size_t accumulate(std::size_t min, std::size_t max);
}
