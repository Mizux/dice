//! @file

#include <dice/Face.hpp>
#include <map>

namespace Dice {

const Face
Face::ONE() {
	return Face("ONE");
}

const Face
Face::TWO() {
	return Face("TWO");
}

const Face
Face::THREE() {
	return Face("THREE");
}

const Face
Face::FOUR() {
	return Face("FOUR");
}

const Face
Face::FIVE() {
	return Face("FIVE");
}

const Face
Face::SIX() {
	return Face("SIX");
}

const Face
Face::SEVEN() {
	return Face("SEVEN");
}

const Face
Face::HEIGHT() {
	return Face("HEIGHT");
}

const Face
Face::HEAD() {
	return Face("HEAD");
}

const Face
Face::TAIL() {
	return Face("TAIL");
}

Face::Face(std::string name)
  : _value(std::move(name)) {}

bool
Face::operator==(const Face& rhs) const {
	return _value == rhs._value;
}

bool
Face::operator!=(const Face& rhs) const {
	return !(*this == rhs);
}

bool
Face::operator<(const Face& rhs) const {
	return _value < rhs._value;
}

std::string
Face::operator()() const {
	return _value;
}

const Face
Face::create(int idx) {
	switch (idx) {
		case 1:
			return Face::ONE();
		case 2:
			return Face::TWO();
		case 3:
			return Face::THREE();
		case 4:
			return Face::FOUR();
		case 5:
			return Face::FIVE();
		case 6:
			return Face::SIX();
		case 7:
			return Face::SEVEN();
		case 8:
			return Face::HEIGHT();
		default:
			throw std::runtime_error("not supported");
	}
}

std::ostream&
operator<<(std::ostream& stream, const FaceTuple& tuple) {
	stream << "{";
	for (auto it = tuple.begin(); it != tuple.end();) {
		stream << *it;
		if (++it != tuple.end()) stream << ", ";
	}
	stream << "}";
	return stream;
}
}
