#include "doctest.h"
#include "math.hpp"

TEST_CASE("add") {
    CHECK(add(1, 2) == 3);
    CHECK(add(-1, 1) == 0);
}
