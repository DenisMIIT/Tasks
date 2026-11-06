include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)
add_executable(gai_tests VehicleRegistryTests.cpp)
target_link_libraries(gai_tests PRIVATE gai_library GTest::gtest_main)
gtest_discover_tests(gai_tests)
