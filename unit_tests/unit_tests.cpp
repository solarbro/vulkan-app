#include <catch2/catch_test_macros.hpp>
#include <vkapp_skeleton.h>

TEST_CASE("Test", "[Test]") {
  const int a = 1;
  const int b = 2;
  const int c = 3;
  REQUIRE(c == a + b);
}
