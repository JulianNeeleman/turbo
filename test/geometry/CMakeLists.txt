project(geometry_test)


file(GLOB geometry_test_SRC "*.cpp")
add_executable(geometry_test ${geometry_test_SRC})

target_link_libraries(
    geometry_test
    ${GTEST_LIBRARY}
    ${GTEST_MAIN_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
)

add_test(geometry_test geometry_test)
