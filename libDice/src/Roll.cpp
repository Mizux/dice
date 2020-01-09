//! @file

#include <Dice/Roll.hpp>
#include <Dice/Stat.hpp>
#include <algorithm>

namespace Dice {

Roll::Roll(const Dice& dice)
  : _dice(dice)
  , _currentRoll() {
	for (const auto& it : _dice)
		_currentRoll.push_back(it.begin());
}

Roll::Roll(std::size_t diceNumber, const Die& die)
  : _dice(diceNumber, die)
  , _currentRoll() {
	for (const auto& it : _dice)
		_currentRoll.push_back(it.begin());
}

Tuple
Roll::operator()() const {
	Tuple result;
	for (const auto& it : _currentRoll)
		result.push_back(*it);
	return result;
}

Roll& Roll::operator++() {
	for (std::size_t idx = 0; idx < _dice.size(); ++idx) {
		if (++_currentRoll[idx] != _dice[idx].end()) {
			// increment the Die Face, if valid done...
			break;
		}
		if (idx == _dice.size() - 1) {
			// if we increment the last die to "end()" -> all possibilities.
			_currentRoll = std::vector<Die::const_iterator>();
			break;
		}
		// otherwise reset current Die to first Face, and increment the next one.
		_currentRoll[idx] = _dice[idx].begin();
	}
	return *this;
}

int
Roll::findTuple(const Tuple& tuple) {
	if (tuple.size() > _dice.size()) return 0;

	Tuple inputs;
	for (const auto& it : _currentRoll) {
		inputs.push_back(*it);
	}
	bool sucess = true;

	// Find first element equal to v, remove it from inputs.
	auto func = [&sucess, &inputs](const Face& face) {
		for (auto it = inputs.begin(); it != inputs.end(); ++it) {
			if (*it == face) {
				inputs.erase(it);
				return;
			}
		}
		sucess = false;
	};

	int count = 0;
	for (std::size_t i = 0; i < (_dice.size() / tuple.size()); ++i) {
		sucess = true;
		std::for_each(tuple.begin(), tuple.end(), func);
		if (sucess)
			count++;
		else
			return count;
	}
	return count;
}
}
