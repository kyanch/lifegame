#include "universe.h"

#include <gtest/gtest.h>

#include "worlds.h"

TEST(LgStep, Stable) {
  for (const char* stable : world_stable) {
    Universe uni = stable;
    // EXPECT_EQ(std::string(uni), std::string_view(stable));
    uni.next();
    EXPECT_EQ(uni, (Universe)stable);
  }
}