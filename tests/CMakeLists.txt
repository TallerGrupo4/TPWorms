if(BUILD_TESTING)
    add_executable(my_tests my_tests.cpp)
    target_link_libraries(my_tests PRIVATE GTest::gtest GTest::gtest_main common_lib)
    include(GoogleTest)
    include_directories("${CMAKE_SOURCE_DIR}/common_src") # Use CMAKE_SOURCE_DIR to specify the path to common_src
    gtest_discover_tests(my_tests)
endif()
