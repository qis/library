#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#include <library/random.hpp>

TEST_CASE("library::random")
{
  REQUIRE(!library::random().empty());
}

int main(int argc, char* argv[])
{
  doctest::Context context;
  context.applyCommandLine(argc, argv);
  context.setOption("no-version", 1);
  return context.run();
}
