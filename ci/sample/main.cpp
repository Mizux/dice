#include <cstdlib>
#include <dice/Die.hpp>
#include <dice/Face.hpp>

using namespace Dice;

int main(int /*argc*/, char** /*argv*/) {
  Die die = {Face::HEAD(), Face::TAIL()};

  return EXIT_SUCCESS;
}
