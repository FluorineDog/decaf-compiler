cmake_minimum_required(VERSION 3.8)
project(fuck)
find_package(LLVM REQUIRED CONFIG)
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)

add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
llvm_map_components_to_libnames(llvm_libs support core irreader)

add_executable(sample sample.cpp)
add_executable(imitation imitation.cpp)

# Find the libraries that correspond to the LLVM components
# that we wish to use

# Link against LLVM libraries
target_link_libraries(imitation ${llvm_libs})
target_link_libraries(sample ${llvm_libs})
