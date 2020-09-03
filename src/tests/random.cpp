#include <gtest/gtest.h>
#include <library/random.hpp>

TEST(library, random)
{
  ASSERT_FALSE(library::random().empty());
}
