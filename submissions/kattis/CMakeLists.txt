project(kattis)

file(GLOB submissions_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")
foreach(submission_file ${submissions_SRC})
    string(REPLACE ".cpp" "" problem ${submission_file})
    add_executable(${problem} ${submission_file})
    target_link_libraries(${problem} geometry structures)
endforeach()

