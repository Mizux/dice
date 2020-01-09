//! @file
#pragma once

#include "Dice.hpp"
#include "Stat.hpp"

namespace Dice {

//! @brief A Roll is a combinaison of Face from a pool of Die.
class Roll {
	public:
	Roll()            = default;
	~Roll()           = default;
	//! @brief Constructs a Roll with the copy of the content of other.
	Roll(const Roll&) = default;
	//! @brief Replaces the contents with a copy of the contents of other.
	//! @return *this.
	Roll& operator=(const Roll&) = default;
	//! @brief Constructs a Roll with the contents of other using move semantics.
	Roll(Roll&&)                 = default;
	//! @brief Replaces the contents with those of other using move semantics.
	//! @return *this.
	Roll& operator=(Roll&&) = default;

	//! @brief Constructs a Roll from a pool of Die (i.e. a Dice).
	//! @param[in] dice The pool of Die.
	explicit Roll(const Dice& dice);
	//! @brief Constructs a Roll from a pool of identical Die.
	//! @param[in] diceNumber The number of Die.
	//! @param[in] die The template Die.
	Roll(std::size_t diceNumber, const Die& die);

	//! @brief Return the current Roll.
	//! @return The list of Face of the current Roll.
	Tuple operator()() const;

	//! @brief Compute next dice Roll (prefix).
	//! @return Next Roll or "empty" Roll if currentRoll was the last one.
	Roll& operator++();

	//! @brief Search a Tuple in a Roll.
	//! @param[in] tuple The Tuple to search.
	//! @return Number of time Tuple is present.
	int findTuple(const Tuple& tuple);

  private:
	//! @brief The pool of Die.
	Dice _dice;
	//! @brief The list of Face currently selectionned (one for each Die).
	std::vector<Die::const_iterator> _currentRoll;
	//! @brief Overloads the insertion operator.
	//! @param[out] stream The ostream object to fill.
	//! @param[in] roll The object to display.
	//! @return The ostream object.
	friend std::ostream& operator<<(std::ostream& stream, const Roll& roll) {
		stream << "{";
		for (auto it = roll._currentRoll.begin(); it != roll._currentRoll.end(); ++it) {
			stream << **it;
			if (it + 1 != roll._currentRoll.end()) stream << ", ";
		}
		stream << "}";
		return stream;
	}
};
}
