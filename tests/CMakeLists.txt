
set(SOURCES bin_tree_test.cpp)


add_executable(tests ${SOURCES})
target_include_directories(tests PRIVATE
                            ${CMAKE_SOURCE_DIR}/assembler
                            ${CMAKE_SOURCE_DIR}/common)
