#include <catch.hpp>
#include <library/random.hpp>

TEST_CASE("library::random") {
  REQUIRE(!library::random().empty());
}
