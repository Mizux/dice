//! @file
#pragma once

#include <ostream>
#include <vector>
#include <set>

namespace Dice {

//! @brief Stores a Die Glyphe.
//! @note A Die can have several time the same Face.
class Face {
	public:
	//! @brief Constructs a Face.
	//! @param[in] name The glyphe this Face owns.
	explicit Face(std::string name);
	//! @brief Destructs the Face.
	~Face() = default;
	//! @brief Constructs a Face with the copy of the content of other.
	Face(const Face&) = default;
	//! @brief Replaces the contents with a copy of the contents of other.
	//! @return *this.
	Face& operator=(const Face&) = default;
	//! @brief Constructs a Face with the contents of other using move semantics.
	Face(Face&&) = default;
	//! @brief Replaces the contents with those of other using move semantics.
	//! @return *this.
	Face& operator=(Face&&) = default;

	//! @brief Checks if the contents of this instance and rhs are equal.
	//! @param[in] rhs The second instance to compare with.
	//! @return True if equal, false otherwise.
	bool operator==(const Face& rhs) const;
	//! @brief Checks if the contents of this instance and rhs are differents.
	//! @param[in] rhs The second instance to compare with.
	//! @return True if not equal, false otherwise.
	bool operator!=(const Face& rhs) const;
	//! @brief Compares the contents of this instance and rhs lexicographically.
	//! @param[in] rhs The second Face to compare with.
	//! @return True if this instance is lexicographically less than rhs, false
	//! otherwise.
	bool operator<(const Face& rhs) const;

	//! @brief Returns the glyphe of the Face.
	//! @return The glyphe of the Face.
	std::string operator()() const;

	//! @brief Overloads the insertion operator.
	//! @param[out] stream The ostream object to fill.
	//! @param[in] face The object to display.
	//! @return The ostream object.
	friend std::ostream& operator<<(std::ostream& stream, const Face& face) {
		stream << face._value;
		return stream;
	}

	//! @brief Face with "ONE".
	//! @return A Face object.
	static const Face ONE();
	//! @brief Face with "TWO".
	//! @return A Face object.
	static const Face TWO();
	//! @brief Face with "THREE".
	//! @return A Face object.
	static const Face THREE();
	//! @brief Face with "FOUR".
	//! @return A Face object.
	static const Face FOUR();
	//! @brief Face with "FIVE".
	//! @return A Face object.
	static const Face FIVE();
	//! @brief Face with "SIX".
	//! @return A Face object.
	static const Face SIX();
	//! @brief Face with "SEVEN".
	//! @return A Face object.
	static const Face SEVEN();
	//! @brief Face with "HEIGHT".
	//! @return A Face object.
	static const Face HEIGHT();
	//! Constructs a Face with the request value.
	//! @param[in] idx The value of the Face.
	//! @return A Face object.
	static const Face create(int idx);

	//! @brief Face with "HEADS".
	//! @return A Face object.
	static const Face HEAD();
	//! @brief Face with "TAILS".
	//! @return A Face object.
	static const Face TAIL();

	protected:
	//! @brief Stores the value of the face.
	std::string _value;
};

//! @brief Container of a sorted sequence of Face.
using FaceTuple = std::multiset<Face>;

//! @brief Fill an output stream with a FaceTuple.
//! @param[out] stream The output stream to fill.
//! @param[in] tuple The sequence of Face to write down.
//! @return The output stream.
std::ostream& operator<<(std::ostream& stream, const FaceTuple& tuple);


}
