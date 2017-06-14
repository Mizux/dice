//! @file
#pragma once

#include "Face.hpp"
#include <map>
#include <vector>

namespace Dice {

//! @brief Store the "shape" of a Die.
class Die {
	public:
	//! @brief Type of the elements.
	using value_type = Face;
	//! @brief A random access iterator to @ref value_type.
	//! @note Convertible to const_iterator.
	using iterator = typename std::vector<Face>::iterator;
	//! @brief A random access iterator to const @ref value_type.
	using const_iterator = typename std::vector<Face>::const_iterator;
	//! @brief Get an iterator at the beginning of the vector.
	//! @returns An iterator pointing to the first element in the vector.
	const_iterator begin() const noexcept { return _faces.begin(); }
	//! @brief Get an iterator after the end of the vector.
	//! @returns An iterator pointing after the last element in the vector.
	const_iterator end() const noexcept { return _faces.end(); }
	//! @copydoc begin() const.
	iterator begin() noexcept { return _faces.begin(); }
	//! @copydoc end() const.
	iterator end() noexcept { return _faces.end(); }

	//! @brief Default Ctor.
	Die() = default;
	//! @brief Default Dtor.
	~Die() = default;
	//! @brief Default Copy Ctor.
	Die(const Die&) = default;
	//! @brief Default Copy Operator.
	//! @return This Die instance.
	Die& operator=(const Die&) = default;
	//! @brief Default Move Ctor.
	Die(Die&&) = default;
	//! @brief Default Move Operator.
	//! @return This Die instance.
	Die& operator=(Die&&) = default;

	//! @brief Build a Die from a list of Face.
	//! @param[in] faces The list of Face.
	Die(std::initializer_list<Face> faces);

	/*! @brief Get access to a single element.
	 * @details For a bound-checked version, look at @ref at(std::size_t) const
	 * method.
	 * @param[in] i Component index requested.
	 * @return The requested element.*/
	inline const Face& operator[](std::size_t i) const noexcept { return _faces[i]; }
	//! @copydoc operator[](std::size_t) const.
	inline Face& operator[](std::size_t i) noexcept { return _faces[i]; }
	/*! @brief Get access to a single element.
	 * @param[in] i Component index requested.
	 * @throw std::out_of_range if component index is not in the vector.
	 * @return The requested element.*/
	inline const Face& at(std::size_t i) const { return _faces.at(i); }
	//! @copydoc at(std::size_t) const.
	inline Face& at(std::size_t i) { return _faces.at(i); }

	//! @brief Get the number of Face.
	//! @returns The number of faces.
	std::size_t size() const noexcept { return _faces.size(); }
	//! @brief Append a new Face to the Die.
	//! @param[in] face The Face to append.
	void push_back(const Face& face);

	//! @brief Get the number of time the Face is present.
	//! @param[in] face Face to count.
	//! @return Number of time Face is present.
	std::size_t countFace(const Face& face) const;

	//! @brief A map, for each Face, how many time it appears.
	using FaceDistribution = std::map<Face, std::size_t>;
	//! @brief Compute Face counts of the Die.
	//! @details If a Die has several time the same Face
	//! (e.g. {1,1,1,2,2,3} we'll get the map {[1]=3, [2]=2, [3]=1}).
	//! @return For each Face its count.
	FaceDistribution getFaceDistribution() const;

	//! @brief A map: [Face, frequency].
	using Stat = std::map<Face, double>;
	//! @brief Compute Face stats of the Die.
	//! @details If a Die has several time the same Face
	//! (e.g. {1,1,1,2,2,3} we'll get the map {[1]=1/2, [2]=1/3, [3]=1/6}).
	//! @return For each Face its frequency.
	Stat getStat() const;

	//! @brief Fill an output stream with a Die.
	//! @param[out] stream The output stream to fill.
	//! @param[in] die The Die to print.
	//! @return The output stream.
	friend std::ostream& operator<<(std::ostream& stream, const Die& die) {
		stream << "{";
		for (auto it = die.begin(); it != die.end();) {
			stream << *it;
			if (++it != die.end()) stream << ", ";
		}
		stream << "}";
		return stream;
	}

	//! @brief Get a Die with the shape {1, 2, 3, 4, 5, 6}.
	//! @return The Die built.
	static Die D6();
	//! @brief Get a Die with the shape {1, 2, 3, 4, 5, 6, 7, 8}.
	//! @return The Die built.
	static Die D8();

	protected:
	//! @brief Store the list of Face of the Die.
	//! @note A Die could have several time the same Face on different Side.
	std::vector<Face> _faces;
};

//! @brief Fill an output stream with a Die::Count.
//! @param[out] stream Thhe output stream to fill.
//! @param[in] count The Die::Count to write down.
//! @return The output stream.
inline std::ostream&
operator<<(std::ostream& stream, const Die::FaceDistribution& count) {
	stream << "{";
	for (auto it = count.begin(); it != count.end();) {
		stream << "[" << it->first << "]: " << it->second;
		if (++it != count.end()) stream << ", ";
	}
	stream << "}";
	return stream;
}

//! @brief Fill an output stream with a Die::Stat.
//! @param[out] stream Thhe output stream to fill.
//! @param[in] stat The Die::Stat to write down.
//! @return The output stream.
inline std::ostream&
operator<<(std::ostream& stream, const Die::Stat& stat) {
	stream << "{";
	for (auto it = stat.begin(); it != stat.end();) {
		stream << "[" << it->first << "]: " << it->second;
		if (++it != stat.end()) stream << ", ";
	}
	stream << "}";
	return stream;
}
}
