#include <iostream>
#include <numeric>

#include <dice/Die.hpp>
#include <dice/Face.hpp>

using namespace Dice;

int main(int /*argc*/, char** /*argv*/) {
  Die die = {Face::HEADS(), Face::TAILS()};

	return 0;
}

