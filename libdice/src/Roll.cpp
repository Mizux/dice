//! @file

#include <dice/Roll.hpp>
#include <dice/Stat.hpp>
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

FaceTuple
Roll::operator()() const {
	FaceTuple result;
	for (const auto& it : _currentRoll)
		result.insert(*it);
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
Roll::findTuple(const FaceTuple& tuple) {
	if (tuple.size() > _dice.size()) return 0;

	FaceTuple inputs;
	for (const auto& it : _currentRoll) {
		inputs.insert(*it);
	}
	bool success = true;

	// Find first element equal to v, remove it from inputs.
	auto func = [&success, &inputs](const Face& face) -> void {
		auto it = inputs.find(face);
		if (it != inputs.end()) {
			inputs.erase(it);
		} else {
			success = false;
		}
	};

	int count = 0;
	for (std::size_t i = 0; i < (_dice.size() / tuple.size()); ++i) {
		success = true;
		std::for_each(tuple.begin(), tuple.end(), func);
		if (success)
			count++;
		else
			break;
	}
	return count;
}
}
