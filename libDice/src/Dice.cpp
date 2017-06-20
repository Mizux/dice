//! @file

#include <Dice/Dice.hpp>

namespace Dice {

Dice::Dice(std::vector<Die> dice)
  : _dice(std::move(dice)) {}

Dice::Dice(std::initializer_list<Die> dice)
  : _dice(dice) {}

Dice::Dice(std::size_t size, const Die& val)
  : _dice(size, val) {}

//! @brief Overload Dice::Stat::operator* to merge a DiceStat with a DieStat.
//! @details This operator is usefull to build DiceStat recurssively by adding one Die
//! at a time.
//! i.e. Stat(3d6) == Stat(1d6) * Stat(1d6) * Stat(1d6).
//! @param[in,out] diceStat The Stat of the Dice pool without taking into account the
//! new Die.
//! @param[in] dieStat The Stat of the new Die to add to the Dice pool.
//! @return The QDebug reference.
Dice::Stat operator*(const Dice::Stat& diceStat, const Die::Stat& dieStat) {
	Dice::Stat result;
	// if Dice Stat Empty simply recopy Die Stat in it.
	if (diceStat.empty()) {
		for (const auto& dieStatIt : dieStat) {
			FaceTuple key = {dieStatIt.first};
			result[key]   = dieStatIt.second;
		}
	} else {
		// otherwise build all possible combinaisons.
		// /!\ several combinaison could lead to the same multiset.
		// e.g. tuple {1, 1, 2} & tuple {2, 1, 1} -> multiset{1, 1, 2}
		for (const auto& diceStatIt : diceStat) {
			for (const auto& dieStatIt : dieStat) {
				std::multiset<Face> key = diceStatIt.first;
				key.insert(dieStatIt.first);
				result[key] += diceStatIt.second * dieStatIt.second;
			}
		}
	}
	return result;
}

Dice::Stat
Dice::getStat() const {
	Dice::Stat result;
	for (const auto& it : _dice) {
		result = result * it.getStat();
	}
	return result;
}
std::size_t
Dice::rollNumber() const {
	std::size_t count = 1;
	for (const auto& it : *this) {
		count *= it.size();
	}
	return count;
}
}
