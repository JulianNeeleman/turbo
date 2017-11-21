project(structures_test)


file(GLOB structures_test_SRC "*.cpp")
add_executable(structures_test ${structures_test_SRC})

target_link_libraries(
    structures_test
    ${GTEST_LIBRARY}
    ${GTEST_MAIN_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
)

add_test(structures_test structures_test)
