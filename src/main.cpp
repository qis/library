#include <library/random.hpp>
#include <cstdio>

int main() {
  std::puts(library::random().data());
}
