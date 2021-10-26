
add_executable(metacpu_vm main.cpp vm.cpp
                          vm.h instructions.h)
target_include_directories(metacpu_vm PUBLIC ${CMAKE_SOURCE_DIR}/common)