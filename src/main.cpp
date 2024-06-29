#include <library/random.hpp>
#include <fmt/core.h>
#include <cstdio>

int main()
{
  try {
    std::puts(library::random().data());
  }
  catch (const std::exception& e) {
    fmt::print(stderr, "error: {}\n", e.what());
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
