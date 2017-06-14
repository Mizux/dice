//! @file
#pragma once

#include "Die.hpp"
#include <map>
#include <set>
#include <vector>

namespace Dice {
using FaceTuple = std::multiset<Face>;

//! @brief Store a set of Die. (e.g. manage a pool of Die)
class Dice {
	public:
	//! @brief Type of the elements.
	using value_type = Die;
	//! @brief A random access iterator to @ref value_type.
	//! @note Convertible to const_iterator.
	using iterator = typename std::vector<Die>::iterator;
	//! @brief A random access iterator to const @ref value_type.
	using const_iterator = typename std::vector<Die>::const_iterator;
	//! @brief Get an iterator at the beginning of the vector.
	//! @returns An iterator pointing to the first element in the vector.
	const_iterator begin() const noexcept { return _dice.begin(); }
	//! @brief Get an iterator after the end of the vector.
	//! @returns An iterator pointing after the last element in the vector.
	const_iterator end() const noexcept { return _dice.end(); }
	//! @copydoc begin() const.
	iterator begin() noexcept { return _dice.begin(); }
	//! @copydoc end() const.
	iterator end() noexcept { return _dice.end(); }

	//! @brief Default Ctor.
	Dice() = default;
	//! @brief Default Dtor.
	~Dice() = default;
	//! @brief Default Copy Ctor.
	Dice(const Dice&) = default;
	//! @brief Default Copy Operator.
	//! @return This Dice instance.
	Dice& operator=(const Dice&) = default;
	//! @brief Default Move Ctor.
	Dice(Dice&&) = default;
	//! @brief Default Move Operator.
	//! @return This Dice instance.
	Dice& operator=(Dice&&) = default;

	//! @brief Build a Dice from a list of Die.
	//! @param[in] dice The list of Dice.
	Dice(std::initializer_list<Die> dice);
	//! @brief Build a Dice from a list of @a n Elements.
	//! @details Each element is a copy of val.
	//! @param[in] size Number of element.
	//! @param[in] val Value to fill the container with.
	//! Each of the n elements in the container will be initialized to a copy of
	//! this value.
	Dice(std::size_t size, const Die& val);

	/*! @brief Get access to a single element.
	 * @details For a bound-checked version, look at @ref at(std::size_t) const
	 * method.
	 * @param[in] i Component index requested.
	 * @return The requested element.*/
	inline const Die& operator[](std::size_t i) const noexcept { return _dice[i]; }
	//! @copydoc operator[](std::size_t) const.
	inline Die& operator[](std::size_t i) noexcept { return _dice[i]; }
	/*! @brief Get access to a single element.
	 * @param[in] i Component index requested.
	 * @throw std::out_of_range if component index is not in the vector.
	 * @return The requested element.*/
	inline const Die& at(std::size_t i) const { return _dice.at(i); }
	//! @copydoc at(std::size_t) const.
	inline Die& at(std::size_t i) { return _dice.at(i); }

	//! @brief Get the number of Die.
	//! @returns The number of dice.
	std::size_t size() const noexcept { return _dice.size(); }
	//! @brief Append a new Face to the Die.
	//! @param[in] face The Face to append.
	void push_back(const Face& face);

	//! @brief A map: [Face tuple, frequency].
	using Stat = std::map<FaceTuple, double>;
	//! @brief Compute Face Tuple stats of the Dice.
	//! @details Face are sorted in lexicagraphical order and results merged
	//! (i.e. Die order doesn't matter).
	//! Example: If a Dice has two identical Die whose Face are {1,1,2},
	//! we'll get the map {[{1,1}]=4/9, [{1,2}]=4/9, [{2,2}]=1/9}).
	//! @return For each Face tuple its frequency.
	Stat getStat() const;

	//! @brief Get the number of possible Roll.
	//! @return The number of possible Roll.
	std::size_t rollNumber() const;

	//! @brief Fill an output stream with a Dice.
	//! @param[out] stream Thhe output stream to fill.
	//! @param[in] dice The dice to write down.
	//! @return The output stream.
	friend std::ostream& operator<<(std::ostream& stream, const Dice& dice) {
		stream << "{";
		for (auto it = dice.begin(); it != dice.end();) {
			stream << *it;
			if (++it != dice.end()) stream << ", ";
		}
		stream << "}";
		return stream;
	}

	protected:
	//! @brief Store the list of Die of the Dice pool.
	//! @note A Dice could use several time the same Die or not.
	std::vector<Die> _dice;
};
}
