#!/bin/bash
set -x

# reset coverage
rm -rf coverage coverage.base coverage.run coverage.total
lcov -z -b . -d .

# cmake: get_filename_component(SRC_DIR "../../d/e" ABSOLUTE)
# collect before run
lcov -c -i -b . -d $(realpath ..) --no-external -o coverage.base

#run test
ctest --output-on-failure

# collect coverage
lcov -c -b . -d $(realpath ..) --no-external -o coverage.run

# merge both
lcov -b . -a coverage.base -a coverage.run -o coverage.total
lcov -r coverage.total '*/Catch.hpp' '*moc*' -o coverage.total

genhtml --no-branch-coverage --prefix $(realpath ..) -o coverage coverage.total

# clean up
rm -f coverage.base coverage.run coverage.total
