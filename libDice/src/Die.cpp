//! @file

#include <Dice/Die.hpp>

namespace Dice {

Die
Die::D6() {
	return {
	  Face::ONE(), Face::TWO(), Face::THREE(), Face::FOUR(), Face::FIVE(), Face::SIX()};
}

Die
Die::D8() {
	return {Face::ONE(),
	        Face::TWO(),
	        Face::THREE(),
	        Face::FOUR(),
	        Face::FIVE(),
	        Face::SIX(),
	        Face::SEVEN(),
	        Face::HEIGHT()};
}

Die::Die(std::initializer_list<Face> faces)
  : _faces(faces) {}

void
Die::push_back(const Face& face) {
	_faces.push_back(face);
}

std::size_t
Die::countFace(const Face& face) const {
	std::size_t count = 0;
	for (const auto& it : *this) {
		if (face == it) ++count;
	}
	return count;
}

Die::FaceDistribution
Die::getFaceDistribution() const {
	Die::FaceDistribution result;
	for (const auto& it : *this) {
		result[it] = countFace(it);
	}
	return result;
}

Die::Stat
Die::getStat() const {
	Die::Stat result;
	for (const auto& it : *this) {
		result[it] = countFace(it) / double(size());
	}
	return result;
}
}
