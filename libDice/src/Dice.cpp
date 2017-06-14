//! @file

#include <Dice/Dice.hpp>

namespace Dice {

Dice::Dice(std::initializer_list<Die> dice)
  : _dice(dice) {}

Dice::Dice(std::size_t size, const Die& val)
  : _dice(size, val) {}

Dice::Stat operator*(Dice::Stat& diceStat, const Die::Stat& dieStat) {
	Dice::Stat result;
	// if Dice Empty simply recopy Die Stat.
	if (diceStat.empty()) {
		for (auto it = dieStat.begin(); it != dieStat.end(); ++it) {
			FaceTuple key = {it->first};
			result[key]   = it->second;
		}
	} else {
		// otherwise build all possible combinaisons.
		// /!\ several combinaison could lead to the same multiset.
		// e.g. tuple {1, 1, 2} & tuple {2, 1, 1} -> multiset{1, 1, 2}
		for (auto itDice = diceStat.begin(); itDice != diceStat.end(); ++itDice) {
			for (auto itDie = dieStat.begin(); itDie != dieStat.end(); ++itDie) {
				std::multiset<Face> key = itDice->first;
				key.insert(itDie->first);
				result[key] += itDice->second * itDie->second;
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
