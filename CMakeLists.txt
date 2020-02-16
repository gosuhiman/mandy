cmake_minimum_required (VERSION 3.14)

project ("mandy")

file(GLOB SRC_DIR CONFIGURE_DEPENDS "src/*.hpp" "src/*.cpp" "src/**/*.hpp" "src/**/*.cpp")

add_executable (mandy ${SRC_DIR})

find_package(SFML COMPONENTS graphics REQUIRED)
if(SFML_FOUND)
    target_link_libraries(mandy sfml-graphics)
endif()

find_library(MPFR_LIBRARY mpfr)
target_link_libraries(mandy ${MPFR_LIBRARY})

find_package(Boost REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

add_compile_definitions(HIGH_PRECISION)
